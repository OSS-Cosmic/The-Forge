#include "Forge/Graphics/TF_GPUConfig.h"
#include "Forge/Config.h"

#include <cstdint>

#include "Forge/Core/TF_String.h"

#define GPUCFG_VERSION_MAJOR 0
#define GPUCFG_VERSION_MINOR 2

static bool testValueUint64(uint64_t a, uint64_t b, GPUConfigExprSymbol op);
static bool testDriveVersion(const GPUDriverVersion* v1, const GPUDriverVersion* v2, GPUConfigExprSymbol op);
static bool parseDriverVersionNumber(TStrSpan input, GPUDriverVersion* version);

static GPUConfigExprSymbol getOpSymbol(struct TStrSpan input);
static bool                parseGPUExpression(struct TFScratchAllocator* alloc, struct GPUConfigExpression* expr, TStrSpan input);
struct TFStrGpuConfigIterable
{
    const struct TStrSpan buffer; // the buffer to iterrate over
    size_t                cursor; // the current position in the buffer
};

static struct TStrSpan tfGPUConfigIter(struct TFStrGpuConfigIterable* iterable)
{
    if (iterable->cursor == iterable->buffer.len)
        return { 0 };

    size_t cursor = iterable->cursor;
    for (; cursor < iterable->buffer.len; cursor++)
    {
        if (iterable->buffer.buf[cursor] == '\n' || iterable->buffer.buf[cursor] == '\r')
        {
            struct TStrSpan res = tfSub(iterable->buffer, iterable->cursor, cursor);
            const int       leaderOffset = tfStrIndexOfOffset(res, 0, tfToRef("#"));
            if (leaderOffset >= 0)
            {
                res = tfSub(res, 0, leaderOffset);
            }
            res = tfStrTrim(res);
            while (cursor < iterable->buffer.len)
            {
                if (iterable->buffer.buf[cursor] == '\n' || iterable->buffer.buf[cursor] == '\r')
                {
                    cursor++;
                    continue;
                }
                break;
            }
            iterable->cursor = cursor;
            return res;
        }
    }

    iterable->cursor = cursor;
    return { 0 };
}

void tfInitGPUConfiguration(struct GPUConfiguration* config)
{
    struct TFScratchAllocDesc allocDesc = { 0 };
    allocDesc.blockSize = 8192;
    allocDesc.alignment = 0;
    tfAddScratchAllocator(&config->mAlloc, &allocDesc);
}

void tfFreeGPUConfiguration(struct GPUConfiguration* config)
{
    arrfree(config->mConfigurationUserSettings);
    arrfree(config->mConfigurationSetting);
    arrfree(config->mGPUSelection);
    arrfree(config->mGPURejection);
    arrfree(config->mGpuModels);
    tfFreeScratchAllocator(&config->mAlloc);
}

static GPUPresetLevel strToPresetLevel(TStrSpan input)
{
    if (tfStrCaselessEqual(input, tfToRef("office")))
        return GPU_PRESET_OFFICE;
    if (tfStrCaselessEqual(input, tfToRef("verylow")))
        return GPU_PRESET_VERYLOW;
    if (tfStrCaselessEqual(input, tfToRef("low")))
        return GPU_PRESET_LOW;
    if (tfStrCaselessEqual(input, tfToRef("medium")))
        return GPU_PRESET_MEDIUM;
    if (tfStrCaselessEqual(input, tfToRef("high")))
        return GPU_PRESET_HIGH;
    if (tfStrCaselessEqual(input, tfToRef("ultra")))
        return GPU_PRESET_ULTRA;
    return GPU_PRESET_NONE;
}

static bool isTermToken(const char token) { return isalnum(token) || token == '.'; }

static bool isOpRuleToken(const char token)
{
    switch (token)
    {
    case '<':
    case '>':
    case '=':
    case '!':
        return true;
    default:
        break;
    }
    return false;
}

static GPUConfigExprSymbol getOpSymbol(struct TStrSpan input)
{
    if (tfStrEqual(input, tfToRef(">=")))
        return GPUConfigExprSymbol::GPUSymbolOpGTE;
    if (tfStrEqual(input, tfToRef(">")))
        return GPUConfigExprSymbol::GPUSymbolOpGT;
    if (tfStrEqual(input, tfToRef("<=")))
        return GPUConfigExprSymbol::GPUSymbolOpLTE;
    if (tfStrEqual(input, tfToRef(">")))
        return GPUConfigExprSymbol::GPUSymbolOpGT;
    if (tfStrEqual(input, tfToRef("<")))
        return GPUConfigExprSymbol::GPUSymbolOpLT;
    if (tfStrEqual(input, tfToRef("==")))
        return GPUConfigExprSymbol::GPUSymbolOpEQ;
    if (tfStrEqual(input, tfToRef("!=")))
        return GPUConfigExprSymbol::GPUSymbolOpNE;
    return GPUConfigExprSymbol::GPUSymbolNone;
}

static bool parseDriverVersionNumber(TStrSpan input, GPUDriverVersion* version)
{
    struct TFStrSplitIterable versionIter = { input, tfToRef("."), 0 };
    unsigned long long        value = 0;
    while (versionIter.cursor < versionIter.buffer.len)
    {
        struct TStrSpan verSpan = tfStrSplitIter(&versionIter);
        if (tfStrEmpty(verSpan))
            continue;
        if (!tfStrReadull(verSpan, &value))
            return false;

        version->versionNumbers[version->versionNumbersCount++] = value;
    }
    return true;
}

static bool parseGPUTerm(struct TFScratchAllocator* alloc, struct GPUConfigTerm* term, TStrSpan input)
{
    unsigned long long value = 0;
    memset(term, 0, sizeof(struct GPUConfigTerm));
    if (tfStrIndexOf(input, tfToRef(".")) > 0)
    {
        term->mSymbol = GPUConfigExprSymbol::GPUSymbolDriverVersion;
        return parseDriverVersionNumber(input, &term->mDriverVersion);
    }
    else if (tfStrReadull(input, &value))
    {
        term->mValue = value;
        term->mSymbol = GPUConfigExprSymbol::GPUSymbolDigit;
    }
    term->mSymbol = GPUConfigExprSymbol::GPUSymbolVariable;
    term->mVariable.buf = (char*)tfScratchAlloc(alloc, input.len);
    term->mVariable.len = input.len;
    memcpy(term->mVariable.buf, input.buf, input.len);
    return true;
}

static bool parseGPUExpression(struct TFScratchAllocator* alloc, struct GPUConfigExpression* expr, TStrSpan input)
{
    TStrSpan leftParam = { 0 };
    TStrSpan rightParam = { 0 };
    TStrSpan op = { 0 };

    TStrSpan consume = tfStrLTrim(input);
    size_t   cursor = 0;
    for (cursor = 0; cursor < consume.len; cursor++)
    {
        if (isspace(consume.buf[cursor]) || !isTermToken(consume.buf[cursor]))
            break;
    }
    leftParam = tfSub(consume, 0, cursor);

    consume = tfStrLTrim(tfSub(consume, cursor, consume.len));
    for (cursor = 0; cursor < consume.len; cursor++)
    {
        if (isspace(consume.buf[cursor]) || !isOpRuleToken(consume.buf[cursor]))
            break;
    }
    op = tfSub(consume, 0, cursor);

    consume = tfStrLTrim(tfSub(consume, cursor, consume.len));
    for (cursor = 0; cursor < consume.len; cursor++)
    {
        if (isspace(consume.buf[cursor]) || !isTermToken(consume.buf[cursor]))
            break;
    }
    rightParam = tfSub(consume, 0, cursor);
    consume = tfStrLTrim(tfSub(consume, cursor, consume.len));

    // still have characters left in the expression something is malformed
    if (!tfStrEmpty(consume))
        return false;

    if (!tfStrEmpty(leftParam) && !tfStrEmpty(op) && !tfStrEmpty(rightParam))
    {
        GPUConfigExprSymbol operatorSym = getOpSymbol(op);
        if (operatorSym == GPUConfigExprSymbol::GPUSymbolNone)
            return false;
        expr->opToken = operatorSym;
        unsigned long long value = 0;
        if (!parseGPUTerm(alloc, &expr->mPrimary, leftParam))
            return false;
        if (!parseGPUTerm(alloc, &expr->mSecondary, leftParam))
            return false;
        return true;
    }
    else if (!tfStrEmpty(leftParam))
    {
        if (!parseGPUTerm(alloc, &expr->mPrimary, leftParam))
            return false;
        return true;
    }
    return false;
}

bool tfLoadGPUConfig(struct GPUConfiguration* config, TStrSpan input)
{
    TFStrGpuConfigIterable iterable = { input, 0 };
    TStrSpan               line = tfGPUConfigIter(&iterable);

    while (iterable.cursor < iterable.buffer.len)
    {
        line = tfGPUConfigIter(&iterable);

        if (tfStrIndexOf(line, tfToRef("BEGIN_GPU_SELECTION;")) >= 0)
        {
            while (iterable.cursor < iterable.buffer.len)
            {
                line = tfGPUConfigIter(&iterable);
                if (tfStrEmpty(line))
                    continue;
                if (tfStrIndexOf(line, tfToRef("END_GPU_SELECTION;")) >= 0)
                    break;


                struct TFStrSplitIterable tokenIterable = { line, tfToRef(";"), 0 };
                TStrSpan                  ruleSpan = tfStrTrim(tfStrSplitIter(&tokenIterable));

                struct TFStrSplitIterable ruleIterable = { ruleSpan, tfToRef(","), 0 };
                bool                      isValid = true;

                struct GPUConfigurationSelection configurationSelection = { 0 };
                    //= &config->mGPUSelection[config->mGpuSelectionCount];
                configurationSelection.mComparisonExprCount = 0;

                while (ruleIterable.cursor < ruleIterable.buffer.len)
                {
                    struct TStrSpan exprSpan = tfStrTrim(tfStrSplitIter(&ruleIterable));
                    if (configurationSelection.mComparisonExprCount >= TF_ARRAY_COUNT(configurationSelection.mComparisonExpr))
                    {
                        isValid = false;
                        LOGF(eDEBUG, "Number of expressions is exausted %d.", TF_ARRAY_COUNT(configurationSelection.mComparisonExpr));
                        break;
                    }

                    if (!parseGPUExpression(&config->mAlloc,
                                           &configurationSelection.mComparisonExpr[configurationSelection.mComparisonExprCount], exprSpan))
                    {
                        isValid = false;
                        LOGF(eDEBUG, "Invalid GPU expression '%.*s'.", (int)exprSpan.len, exprSpan.buf); 
                        break;
                    }
                    configurationSelection.mComparisonExprCount++;
                }

                if (isValid)
                {
                    arrpush(config->mGPUSelection, configurationSelection);
                }
                else
                {
                    LOGF(eDEBUG, "Invalid GPU selection rule '%.*s'.", line.len, line.buf);
                }
            }
        }
        else if (tfStrIndexOf(line, tfToRef("BEGIN_DRIVER_REJECTION;")) >= 0)
        {
            while (iterable.cursor < iterable.buffer.len)
            {
                line = tfGPUConfigIter(&iterable);
                if (tfStrEmpty(line))
                    continue;
                if (tfStrIndexOf(line, tfToRef("END_DRIVER_REJECTION;")) >= 0)
                    break;


                struct TFStrSplitIterable tokenIterable = { line, tfToRef(";"), 0 };
                TStrSpan                  vendorSpan = tfStrTrim(tfStrSplitIter(&tokenIterable));
                TStrSpan                  ruleParametersSpan = tfStrTrim(tfStrSplitIter(&tokenIterable));
                TStrSpan                  reasonSpan = tfStrTrim(tfStrSplitIter(&tokenIterable));
                long long                 vendorId = 0;
                bool                      isValid = true;

                struct GPUConfigurationRejection rejection = { 0 };

                // &config->mGPURejection[config->mGpuRejectionCount];
                rejection.mComparisonExprCount = 0;

                if (!tfStrReadll(vendorSpan, &vendorId))
                {
                    LOGF(eDEBUG, "Invalid GPU rejection rule '%.*s'.", line.len, line.buf);
                    continue;
                }

                struct TFStrSplitIterable ruleIterable = { ruleParametersSpan, tfToRef(","), 0 };
                while (ruleIterable.cursor < ruleIterable.buffer.len)
                {
                    struct TStrSpan exprSpan = tfStrTrim(tfStrSplitIter(&ruleIterable));

                    if (rejection.mComparisonExprCount >= TF_ARRAY_COUNT(rejection.mComparisonExpr))
                    {
                        isValid = false;
                        LOGF(eDEBUG, "Number of expressions is exausted %d.", TF_ARRAY_COUNT(rejection.mComparisonExpr));
                        break;
                    }

                    if (!parseGPUExpression(&config->mAlloc, &rejection.mComparisonExpr[rejection.mComparisonExprCount], exprSpan))
                    {
                        isValid = false;
                        LOGF(eDEBUG, "Invalid GPU expression '%.*s'.", exprSpan.len, exprSpan.buf);
                        break;
                    }
                    rejection.mComparisonExprCount++;

                }

                if (!isValid)
                {
                    LOGF(eDEBUG, "Invalid GPU rejection rule '%.*s'.", line.len, line.buf);
                    continue;
                }
                //config->mGpuRejectionCount++;
                rejection.mVendorID = vendorId;
                rejection.mReasonStr.buf = (char*)tfScratchAlloc(&config->mAlloc, reasonSpan.len);
                rejection.mReasonStr.len = reasonSpan.len;
                memcpy(rejection.mReasonStr.buf, reasonSpan.buf, reasonSpan.len);
                arrpush(config->mGPURejection, rejection);
            }
        }
        else if (tfStrIndexOf(line, tfToRef("BEGIN_GPU_SETTINGS;")) >= 0)
        {
            while (iterable.cursor < iterable.buffer.len)
            {
                line = tfGPUConfigIter(&iterable);
                if (tfStrEmpty(line))
                    continue;
                if (tfStrIndexOf(line, tfToRef("END_GPU_SETTINGS;")) >= 0)
                    break;

                struct TFStrSplitIterable tokenIterable = { line, tfToRef(";"), 0 };
                TStrSpan                  propertySpan = tfStrTrim(tfStrSplitIter(&tokenIterable));
                TStrSpan                  ruleParametersSpan = tfStrTrim(tfStrSplitIter(&tokenIterable));
                TStrSpan                  assignmentSpan = tfStrTrim(tfStrSplitIter(&tokenIterable));
                bool                      isValid = true;
                long long                 assignmentValue = 0;

                if (!tfStrReadll(assignmentSpan, &assignmentValue))
                {
                    LOGF(eDEBUG, "Invalid GPU rejection rule '%.*s'.", (int)line.len, line.buf);
                    continue;
                }

                struct GPUConfigurationSetting setting = { 0 }; //&config->mConfigurationSetting[config->mGpuConfigurationSettingCount];

                struct TFStrSplitIterable ruleIterable = { ruleParametersSpan, tfToRef(","), 0 };
                while (ruleIterable.cursor < ruleIterable.buffer.len)
                {
                    struct TStrSpan exprSpan = tfStrTrim(tfStrSplitIter(&ruleIterable));

                    if (setting.mComparisonExprCount >= TF_ARRAY_COUNT(setting.mComparisonExpr))
                    {
                        isValid = false;
                        LOGF(eDEBUG, "Number of expressions is exausted %d.", TF_ARRAY_COUNT(setting.mComparisonExpr));
                        break;
                    }

                    if (!parseGPUExpression(&config->mAlloc, &setting.mComparisonExpr[setting.mComparisonExprCount], exprSpan))
                    {
                        isValid = false;
                        LOGF(eDEBUG, "Invalid GPU expression '%.*s'.", exprSpan.len, exprSpan.buf);
                        break;
                    }
                    setting.mComparisonExprCount++;
                }

                if (!isValid)
                {
                    LOGF(eDEBUG, "Invalid GPU setting rule '%.*s'.", (int)line.len, line.buf);
                    continue;
                }

                //config->mGpuConfigurationSettingCount++;
                setting.mAssignmentValue = assignmentValue;
                setting.mUpdateProperty.buf = (char*)tfScratchAlloc(&config->mAlloc, propertySpan.len);
                setting.mUpdateProperty.len = propertySpan.len;
                memcpy(setting.mUpdateProperty.buf, propertySpan.buf, propertySpan.len);
                arrpush(config->mConfigurationSetting, setting);
            }
        }
        else if (tfStrIndexOf(line, tfToRef("BEGIN_USER_SETTINGS;")) >= 0)
        {
            while (iterable.cursor < iterable.buffer.len)
            {
                line = tfGPUConfigIter(&iterable);
                if (tfStrEmpty(line))
                    continue;
                if (tfStrIndexOf(line, tfToRef("END_USER_SETTINGS;")) >= 0)
                    break;

                struct TFStrSplitIterable tokenIterable = { line, tfToRef(";"), 0 };
                TStrSpan                  propertySpan = tfStrTrim(tfStrSplitIter(&tokenIterable));
                TStrSpan                  ruleParametersSpan = tfStrTrim(tfStrSplitIter(&tokenIterable));
                TStrSpan                  assignmentSpan = tfStrTrim(tfStrSplitIter(&tokenIterable));
                bool                      isValid = true;
                long long                 assignmentValue = 0;

                if (!tfStrReadll(assignmentSpan, &assignmentValue) || tfStrEmpty(ruleParametersSpan) || tfStrEmpty(propertySpan))
                {
                    LOGF(eDEBUG, "Invalid GPU user setting rule '%.*s'.", (int)line.len, line.buf);
                    continue;
                }

                struct GPUConfigurationSetting setting = { 0 };

                struct TFStrSplitIterable ruleIterable = { ruleParametersSpan, tfToRef(","), 0 };
                while (ruleIterable.cursor < ruleIterable.buffer.len)
                {
                    struct TStrSpan exprSpan = tfStrTrim(tfStrSplitIter(&ruleIterable));

                    if (setting.mComparisonExprCount >= TF_ARRAY_COUNT(setting.mComparisonExpr))
                    {
                        isValid = false;
                        LOGF(eDEBUG, "Number of expressions is exausted %d.", TF_ARRAY_COUNT(setting.mComparisonExpr));
                        break;
                    }

                    if (!parseGPUExpression(&config->mAlloc, &setting.mComparisonExpr[setting.mComparisonExprCount], exprSpan))
                    {
                        isValid = false;
                        LOGF(eDEBUG, "Invalid GPU expression '%.*s'.", exprSpan.len, exprSpan.buf);
                        break;
                    }
                    setting.mComparisonExprCount++;
                }

                if (!isValid)
                {
                    LOGF(eDEBUG, "Invalid GPU user setting rule '%.*s'.", (int)line.len, line.buf);
                    continue;
                }

                //config.mGpuConfigurationSettingCount++;
                setting.mAssignmentValue = assignmentValue;
                setting.mUpdateProperty.buf = (char*)tfScratchAlloc(&config->mAlloc, propertySpan.len);
                setting.mUpdateProperty.len = propertySpan.len;
                memcpy(setting.mUpdateProperty.buf, propertySpan.buf, propertySpan.len);
                arrpush(config->mConfigurationUserSettings, setting);
            }
        }
    }
    return true;
}

bool tfLoadGPUData(struct GPUConfiguration* config, TStrSpan input)
{
    TFStrGpuConfigIterable iterable = { input, 0 };

    TStrSpan line = tfGPUConfigIter(&iterable);
    {
        uint32_t versionMajor = 0;
        uint32_t versionMinor = 0;
        int      read = tfstrsscanf(line, "version:%u.%u", &versionMajor, &versionMinor);
        if (read != 2)
        {
            LOGF(eINFO, "Ill-formatted gpu.data file. Missing version at beginning of file");
            return false;
        }
        else if (versionMajor != GPUCFG_VERSION_MAJOR || versionMinor != GPUCFG_VERSION_MINOR)
        {
            LOGF(eINFO, "gpu.data version mismatch. Expected version %u.%u but got %u.%u", GPUCFG_VERSION_MAJOR, GPUCFG_VERSION_MINOR,
                 versionMajor, versionMinor);
            return false;
        }
    }

    while (iterable.cursor < iterable.buffer.len)
    {
        line = tfGPUConfigIter(&iterable);

        if (tfStrIndexOf(line, tfToRef("BEGIN_DEFAULT_CONFIGURATION;")) >= 0)
        {
            while (iterable.cursor < iterable.buffer.len)
            {
                line = tfGPUConfigIter(&iterable);
                if (tfStrEmpty(line))
                    continue;
                if (tfStrIndexOf(line, tfToRef("END_DEFAULT_CONFIGURATION;")) >= 0)
                    break;
                struct TFStrSplitIterable tokenIterable = { line, tfToRef(";"), 0 };
                TStrSpan                  ruleNameSpan = tfStrTrim(tfStrSplitIter(&tokenIterable));
                TStrSpan                  assignmentSpan = tfStrTrim(tfStrSplitIter(&tokenIterable));
                if (tfStrIndexOf(ruleNameSpan, tfToRef("DefaultPresetLevel")) >= 0)
                {
                    GPUPresetLevel defaultLevel = strToPresetLevel(assignmentSpan);
                    if (defaultLevel != GPUPresetLevel::GPU_PRESET_NONE)
                    {
                        config->mDefaultPresetLevel = defaultLevel;
                    }
                    else
                    {
                        LOGF(eDEBUG, "Error invalid preset level in GPU Default Data Configuration value '%.*s' in '%.*s'.", (int)ruleNameSpan.len, ruleNameSpan.buf, line.len, line.buf);
                    }
                }
                else
                {
                    LOGF(eDEBUG, "Error could not parse GPU Default Data Configuration rule '%.*s' in '%.*s'.", (int)ruleNameSpan.len, ruleNameSpan.buf, (int)assignmentSpan.len, assignmentSpan.buf);
                }
            }
        }
        else if (tfStrIndexOf(line, tfToRef("BEGIN_GPU_LIST;")) >= 0)
        {
            while (iterable.cursor < iterable.buffer.len)
            {
                line = tfGPUConfigIter(&iterable);
                if (tfStrEmpty(line))
                    continue;
                if (tfStrIndexOf(line, tfToRef("END_GPU_LIST;")) >= 0)
                    break;
                struct GPUModelDefinition modelDef = { 0 };
                struct TFStrSplitIterable iterable = { line, tfToRef(";"), 0 };
                TStrSpan                  vendorIdSpan = tfStrTrim(tfStrSplitIter(&iterable));
                TStrSpan                  modelIdSpan = tfStrTrim(tfStrSplitIter(&iterable));
                TStrSpan                  presetSpan = tfStrTrim(tfStrSplitIter(&iterable));
                TStrSpan                  vendorNameSpan = tfStrTrim(tfStrSplitIter(&iterable));
                TStrSpan                  modelNameSpan = tfStrTrim(tfStrSplitIter(&iterable));

                unsigned long long vendorId = 0;
                unsigned long long modelId = 0;
                if (tfStrReadull(vendorIdSpan, &vendorId))
                {
                    modelDef.mVendorId = vendorId;
                }
                if (tfStrReadull(modelIdSpan, &modelId))
                {
                    modelDef.mDeviceId = modelId;
                }
                modelDef.mPreset = strToPresetLevel(presetSpan);
                if (!tfStrEmpty(modelNameSpan))
                {
                    modelDef.mModelName.buf = (char*)tfScratchAlloc(&config->mAlloc, modelNameSpan.len);
                    modelDef.mModelName.len = modelNameSpan.len;
                    memcpy(modelDef.mModelName.buf, modelNameSpan.buf, modelNameSpan.len);
                }

                if (modelDef.mVendorId && modelDef.mDeviceId)
                {
                    arrpush(config->mGpuModels, modelDef);
                }
            }
        }
        else if (tfStrIndexOf(line, tfToRef("BEGIN_VENDOR_LIST;")) >= 0)
        {
            while (iterable.cursor < iterable.buffer.len)
            {
                line = tfGPUConfigIter(&iterable);
                if (tfStrEmpty(line))
                {
                    continue;
                }
                if (tfStrIndexOf(line, tfToRef("END_VENDOR_LIST;")) >= 0)
                {
                    break;
                }
                GPUVendorDefinition* vendorDef = &config->mVendorDefinitions[config->mVendorCount];
                memset(vendorDef, 0, sizeof(GPUVendorDefinition));

                struct TFStrSplitIterable iterable = {line, tfToRef(";"), 0 };
                TStrSpan                  vendorSpan = tfStrSplitIter(&iterable);
                TStrSpan                  identiferSpan = tfStrSplitIter(&iterable);
                struct TFStrSplitIterable idIterable = { identiferSpan, tfToRef(","),  0 };
                while (idIterable.cursor < idIterable.buffer.len)
                {
                    TStrSpan           idSpan = tfStrTrim(tfStrSplitIter(&idIterable));
                    unsigned long long vendorID = 0;
                    if (vendorDef->mIdentifierCount >= MAX_INDENTIFIER_PER_GPU_VENDOR_COUNT)
                    {
                        // we've ran out of vendor identifiers
                        vendorDef->mIdentifierCount = 0;
                        break;
                    }

                    if (tfStrReadull(idSpan, &vendorID))
                    {
                        vendorDef->mIdentifierArray[vendorDef->mIdentifierCount++] = vendorID;
                    }
                    else
                    {
                        LOGF(eDEBUG, "Invalid GPU vendor identifier %.*s from line: '%.*s'.", vendorSpan.len, vendorSpan.buf, identiferSpan.len, identiferSpan.buf);
                        break;
                    }
                }

                if (vendorDef->mIdentifierCount > 0 && !tfStrEmpty(tfStrTrim(vendorSpan)))
                {
                    vendorDef->mVendorName.buf = (char*)tfScratchAlloc(&config->mAlloc, vendorSpan.len);
                    vendorDef->mVendorName.len = vendorSpan.len;
                    memcpy(vendorDef->mVendorName.buf, vendorSpan.buf, vendorSpan.len);
                    config->mVendorCount++;
                }
                else
                {
                    LOGF(eDEBUG, "Error could not parse GPU vendor in '%.*s'.", line.len, line.buf);
                }
            }
        }
    }

    // log default configuration
    LOGF(eINFO, "Default GPU Data:");
    LOGF(eINFO, "    DefaultGPUPresetLevel set to %s", presetLevelToString(config->mDefaultPresetLevel));
    // log gpu vendors
    LOGF(eINFO, "GPU vendors:");
    TStr vendorBufStr = {0};
    for (uint32_t vendorIdx = 0; vendorIdx < config->mVendorCount; vendorIdx++)
    {
        GPUVendorDefinition* vendorDef = &config->mVendorDefinitions[vendorIdx];
        tfStrClear(&vendorBufStr);
        tfstrcatfmt(&vendorBufStr, "%S: ", vendorDef->mVendorName);
        for (uint32_t identIdx = 0; identIdx < vendorDef->mIdentifierCount; identIdx++)
        {
            if (identIdx > 0)
            {
                tfstrcatfmt(&vendorBufStr, ", ");
            }
            tfstrcatprintf(&vendorBufStr, "%#x", vendorDef->mIdentifierArray[identIdx]);
        }
        LOGF(eINFO, vendorBufStr.buf);
    }
    tfStrFree(&vendorBufStr);
    return true;
}

static bool writeVariableToProperty(GPUConfigSelection* pSelection, TStrSpan variable, GPUConfigTerm* value)
{
    if (value->mSymbol == GPUConfigExprSymbol::GPUSymbolDigit)
    {
#define GPU_CONFIG_PROPERTY(VAR, PROPERTY)                                       \
    if (tfStrCaselessEqual(tfToRef(VAR), variable))                              \
    {                                                                            \
        COMPILE_ASSERT(sizeof(decltype(pSelection->PROPERTY)) <= sizeof(value)); \
        pSelection->PROPERTY = (decltype(pSelection->PROPERTY))value->mValue;    \
        return true;                                                             \
    }
#define GPU_CONFIG_PROPERTY_READ_ONLY(VAR, PROPERTY)
#include "./GPUPropTable.inl"
#undef GPU_CONFIG_PROPERTY_READ_ONLY
#undef GPU_CONFIG_PROPERTY
    }

    return false;
}

static bool readVariableFromProperty(GPUConfigSelection* pSelection, TStrSpan variable, GPUConfigTerm* value)
{
    if (tfStrCaselessEqual(variable, tfToRef("driverversion")))
    {
        if (parseDriverVersionNumber(
                TStrSpan{ pSelection->mDeviceAdapter->mGpuDriverVersion, strlen(pSelection->mDeviceAdapter->mGpuDriverVersion) },
                &value->mDriverVersion))
        {
            value->mSymbol = GPUConfigExprSymbol::GPUSymbolDriverVersion;
            return true;
        }
        return false;
    }

#define GPU_CONFIG_PROPERTY(VAR, PROPERTY)                      \
    if (tfStrCaselessEqual(tfToRef(VAR), variable))             \
    {                                                           \
        (*value).mSymbol = GPUConfigExprSymbol::GPUSymbolDigit; \
        (*value).mValue = (uint64_t)(pSelection->PROPERTY);     \
        return true;                                            \
    }
#define GPU_CONFIG_PROPERTY_READ_ONLY(VAR, PROPERTY) GPU_CONFIG_PROPERTY(VAR, PROPERTY)
#include "./GPUPropTable.inl"
#undef GPU_CONFIG_PROPERTY_READ_ONLY
#undef GPU_CONFIG_PROPERTY
    return false;
}

static bool testDriveVersion(const GPUDriverVersion* v1, const GPUDriverVersion* v2, GPUConfigExprSymbol op)
{
    uint32_t tokenLength = TF_MAX(v1->versionNumbersCount, v2->versionNumbersCount);
    if (op == GPUConfigExprSymbol::GPUSymbolOpGTE || op == GPUConfigExprSymbol::GPUSymbolOpLTE || op == GPUConfigExprSymbol::GPUSymbolOpEQ)
    {
        bool isEqual = true;
        for (uint32_t i = 0; i < tokenLength; i++)
            isEqual = (v1->versionNumbers[i] == v2->versionNumbers[i]) && isEqual;
        if (isEqual)
            return true;
    }

    for (uint32_t i = 0; i < tokenLength; i++)
    {
        if (v1->versionNumbers[i] != v2->versionNumbers[i])
        {
            if (testValueUint64(v1->versionNumbers[i], v2->versionNumbers[i], op))
                return true;
            break;
        }
    }
    return false;
}

static bool testValueUint64(uint64_t a, uint64_t b, GPUConfigExprSymbol op)
{
    switch (op)
    {
    case GPUConfigExprSymbol::GPUSymbolOpEQ:
        return a == b;
    case GPUConfigExprSymbol::GPUSymbolOpNE:
        return a != b;
    case GPUConfigExprSymbol::GPUSymbolOpLT:
        return a < b;
    case GPUConfigExprSymbol::GPUSymbolOpGT:
        return a > b;
    case GPUConfigExprSymbol::GPUSymbolOpLTE:
        return a <= b;
    case GPUConfigExprSymbol::GPUSymbolOpGTE:
        return a >= b;
    default:
        break;
    }
    ASSERT(false);
    return false;
}

static int compareTerms(const GPUConfigTerm* t1, const GPUConfigTerm* t2, GPUConfigExprSymbol op)
{
    if (t1->mSymbol == GPUConfigExprSymbol::GPUSymbolDigit && t2->mSymbol == GPUConfigExprSymbol::GPUSymbolDigit)
    {
        return testValueUint64(t1->mValue, t2->mValue, op) ? 1 : -1;
    }
    if (t1->mSymbol == GPUConfigExprSymbol::GPUSymbolDriverVersion && t2->mSymbol == GPUConfigExprSymbol::GPUSymbolDriverVersion)
    {
        return testDriveVersion(&t1->mDriverVersion, &t2->mDriverVersion, op) ? 1 : -1;
    }
    return 0;
}

GPUPresetLevel tfQueryPresetLevel(const struct GPUConfiguration* config, uint32_t vendorId, uint32_t modelId)
{
    for (uint32_t modelIndex = 0; modelIndex < arrlen(config->mGpuModels); modelIndex++)
    {
        struct GPUModelDefinition* model = &config->mGpuModels[modelIndex];
        if (model->mVendorId == vendorId && model->mDeviceId == modelId && model->mDeviceId)
        {
            return model->mPreset;
        }
    }
    return GPU_PRESET_NONE;
}

struct GPUConfigSelection tfApplyGPUConfig(const struct GPUConfiguration* def, const struct RendererContext* context)
{
    GPUConfigSelection* selections = NULL;
    {
        const size_t numberOfDevices = arrlen(context->pAdapters);
        arrsetlen(selections, numberOfDevices);
        for (size_t i = 0; i < numberOfDevices; i++)
        {
            memcpy(&selections[i].mGpuProperty, &context->pAdapters[i].mDefaultProps, sizeof(GpuProperties));
            selections[i].mDeviceAdapter = &context->pAdapters[i];
            selections[i].mPresetLevel = tfQueryPresetLevel(def, selections[i].mGpuProperty.mGpuVendorPreset.mVendorId,
                                                            selections[i].mGpuProperty.mGpuVendorPreset.mModelId);
        }
    }

    for (size_t selectionIdx = 0; selectionIdx < arrlen(selections); selectionIdx++)
    {
        for (size_t i = 0; i < arrlen(def->mConfigurationSetting); i++)
        {
            const struct GPUConfigurationSetting* setting = &def->mConfigurationSetting[i];
            GPUConfigTerm                         assignmentTerm;
            if (readVariableFromProperty(&selections[selectionIdx], setting->mUpdateProperty, &assignmentTerm) &&
                assignmentTerm.mSymbol == GPUConfigExprSymbol::GPUSymbolDigit)
            {
                bool isValid = true;
                for (size_t ruleIdx = 0; ruleIdx < setting->mComparisonExprCount; ruleIdx++)
                {
                    const GPUConfigExpression* rule = &setting->mComparisonExpr[ruleIdx];

                    GPUConfigTerm primaryTerm = rule->mPrimary;
                    GPUConfigTerm secondTerm = rule->mSecondary;
                    if (rule->mPrimary.mSymbol == GPUConfigExprSymbol::GPUSymbolVariable)
                        readVariableFromProperty(&selections[selectionIdx], rule->mPrimary.mVariable, &primaryTerm);
                    if (rule->mSecondary.mSymbol == GPUConfigExprSymbol::GPUSymbolVariable)
                        readVariableFromProperty(&selections[selectionIdx], rule->mSecondary.mVariable, &secondTerm);

                    const int termRes = compareTerms(&primaryTerm, &secondTerm, rule->opToken);
                    if (termRes != 0)
                        isValid = isValid && (termRes > 0);

                    if (rule->mPrimary.mSymbol == GPUConfigExprSymbol::GPUSymbolVariable &&
                        rule->opToken == GPUConfigExprSymbol::GPUSymbolNone)
                    {
                        isValid = isValid && (assignmentTerm.mValue > 0);
                        if (!isValid)
                            break;
                    }
                }

                if (isValid)
                {
                    GPUConfigTerm writeTerm;
                    writeTerm.mSymbol = GPUConfigExprSymbol::GPUSymbolDigit;
                    writeTerm.mValue = setting->mAssignmentValue;

                    if (writeVariableToProperty(&selections[selectionIdx], setting->mUpdateProperty, &writeTerm))
                    {
                        LOGF(eDEBUG, "GPU: %s, setting %.*s to %llu", selections[selectionIdx].mDeviceAdapter->mGpuName,
                             setting->mUpdateProperty.len, setting->mUpdateProperty.buf, setting->mAssignmentValue);
                    }
                }
            }
        }
    }

    uint32_t selectionIndex = 0;
    for (size_t testIndex = 0; testIndex < arrlen(selections); testIndex++)
    {
        GPUConfigSelection* testSelection = &selections[testIndex];
        GPUConfigSelection* refSelection = &selections[selectionIndex];
        for (size_t ruleIndex = 0; ruleIndex < arrlen(def->mGPUSelection); ruleIndex++)
        {
            bool                                    refPass = true;
            bool                                    testPass = true;
            const struct GPUConfigurationSelection* selectionRule = &def->mGPUSelection[ruleIndex];
            for (size_t ruleIdx = 0; ruleIdx < selectionRule->mComparisonExprCount; ruleIdx++)
            {
                const GPUConfigExpression* rule = &selectionRule->mComparisonExpr[ruleIdx];

                GPUConfigTerm testPrimaryTerm = rule->mPrimary;
                GPUConfigTerm testSecondaryTerm = rule->mSecondary;
                if (rule->mPrimary.mSymbol == GPUConfigExprSymbol::GPUSymbolVariable)
                    readVariableFromProperty(testSelection, rule->mPrimary.mVariable, &testPrimaryTerm);
                if (rule->mSecondary.mSymbol == GPUConfigExprSymbol::GPUSymbolVariable)
                    readVariableFromProperty(testSelection, rule->mSecondary.mVariable, &testSecondaryTerm);

                const int testRes = compareTerms(&testPrimaryTerm, &testSecondaryTerm, rule->opToken);
                if (testRes != 0)
                    testPass = testPass && (testRes > 0);

                GPUConfigTerm refPrimaryTerm = rule->mPrimary;
                GPUConfigTerm refSecondaryTerm = rule->mSecondary;
                if (rule->mPrimary.mSymbol == GPUConfigExprSymbol::GPUSymbolVariable)
                    readVariableFromProperty(refSelection, rule->mPrimary.mVariable, &refPrimaryTerm);
                if (rule->mSecondary.mSymbol == GPUConfigExprSymbol::GPUSymbolVariable)
                    readVariableFromProperty(refSelection, rule->mSecondary.mVariable, &refSecondaryTerm);

                const int refRes = compareTerms(&testPrimaryTerm, &testSecondaryTerm, rule->opToken);
                if (refRes != 0)
                    refPass = refPass && (refRes > 0);

                if (rule->mPrimary.mSymbol == GPUConfigExprSymbol::GPUSymbolVariable && rule->opToken == GPUConfigExprSymbol::GPUSymbolNone)
                {
                    if (testPrimaryTerm.mSymbol == GPUConfigExprSymbol::GPUSymbolDigit &&
                        refPrimaryTerm.mSymbol == GPUConfigExprSymbol::GPUSymbolDigit)
                    {
                        testPass = testPass && (testPrimaryTerm.mValue >= refPrimaryTerm.mValue);
                        refPass = refPass && (refPrimaryTerm.mValue >= testPrimaryTerm.mValue);
                    }
                }
            }
            if (testPass != refPass)
            {
                // log rule selection
                // uint32_t chosenIndex = testPass ? testIndex : selectionIndex;
                // uint32_t nonChosenIndex = testPass ? selectionIndex : testIndex;
                if (testPass && !refPass)
                {
                    selectionIndex = testIndex;
                }
                break;
            }
        }
    }

    LOGF(eINFO, "Choosing GPU: %s", selections[selectionIndex].mGpuProperty.mGpuVendorPreset.mGpuName);
    GPUConfigSelection result = selections[selectionIndex];
    arrfree(selections);
    return result;
}
