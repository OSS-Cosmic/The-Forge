#include "Forge/Graphics/TF_GPUConfig.h"
#include <cstdint>
#include "Forge/Core/TF_String.h"

#define GPUCFG_VERSION_MAJOR           0
#define GPUCFG_VERSION_MINOR           2

static bool testValueUint64(uint64_t a, uint64_t b, GPUConfigExprSymbol op);
static bool testDriveVersion(GPUDriverVersion* v1, GPUDriverVersion* v2, GPUConfigExprSymbol op);

static GPUConfigExprSymbol getOpSymbol(struct TStrSpan input);
static bool parseGPUExpression(struct TFScratchAllocator* alloc,struct GPUConfigExpression* expr, TStrSpan input); 
struct TFStrGpuConfigIterable {
  const struct TStrSpan buffer; // the buffer to iterrate over
  size_t cursor; // the current position in the buffer
};

static struct TStrSpan tfGPUConfigIter(struct TFStrGpuConfigIterable* iterable)
{
    if (iterable->cursor == iterable->buffer.len)
        return (struct TStrSpan){ 0 };

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
    return (struct TStrSpan){ 0 };
}

void tfInitGPUConfiguration(struct GPUConfiguration* config) {
    struct TFScratchAllocDesc allocDesc = {
      .blockSize = 8192 
    };
    tfAddScratchAllocator(&config->mAlloc, &allocDesc);
}

void tfFreeGPUConfiguration(struct GPUConfiguration* config) {
  tfFreeScratchAllocator(&config->mAlloc);
  arrfree(config->mGpuModels);
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


static bool isTermToken(const char token) {
    return isalnum(token) || token == '.';
}


static bool isOpRuleToken(const char token) {
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

static GPUConfigExprSymbol getOpSymbol(struct TStrSpan input) {
   if(tfStrEqual(input, tfToRef(">=")))
        return GPUConfigExprSymbol::GPUSymbolOpGTE;
   if(tfStrEqual(input, tfToRef(">")))
        return GPUConfigExprSymbol::GPUSymbolOpGT;
   if(tfStrEqual(input, tfToRef("<=")))
        return GPUConfigExprSymbol::GPUSymbolOpLTE;
   if(tfStrEqual(input, tfToRef(">")))
        return GPUConfigExprSymbol::GPUSymbolOpGT;
   if(tfStrEqual(input, tfToRef("<")))
        return GPUConfigExprSymbol::GPUSymbolOpLT;
   if(tfStrEqual(input, tfToRef("==")))
        return GPUConfigExprSymbol::GPUSymbolOpEQ;
   if(tfStrEqual(input, tfToRef("!=")))
        return GPUConfigExprSymbol::GPUSymbolOpNE;
    return GPUConfigExprSymbol::GPUSymbolNone;
}

static bool parseDriverVersionNumber(TStrSpan input, GPUDriverVersion* version)
{
    struct TFStrSplitIterable versionIter = { .buffer = input, .delim = tfToRef("."), .cursor = 0 };
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

static bool parseGPUTerm(struct TFScratchAllocator* alloc, struct GPUConfigTerm* term, TStrSpan input) {
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


static bool parseGPUExpression(struct TFScratchAllocator* alloc,struct GPUConfigExpression* expr, TStrSpan input) {
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
    if(!tfStrEmpty(consume))
        return false;


    if(!tfStrEmpty(leftParam) && !tfStrEmpty(op) && !tfStrEmpty(rightParam)) {
        GPUConfigExprSymbol operatorSym = getOpSymbol(op);
        if (operatorSym == GPUConfigExprSymbol::GPUSymbolNone)
            return false;
        expr->opToken = operatorSym;
        unsigned long long value = 0;
        if(!parseGPUTerm(alloc, &expr->mPrimary, leftParam))
            return false;
        if(!parseGPUTerm(alloc, &expr->mSecondary, leftParam))
            return false;
        return true;
    } else if(!tfStrEmpty(leftParam)) {
        if(!parseGPUTerm(alloc, &expr->mPrimary, leftParam))
            return false;
        return true;
    }
    return false;
}

bool tfLoadGPUConfig(struct GPUConfiguration* config, TStrSpan input)
{
    TFStrGpuConfigIterable iterable = { .buffer = input, .cursor = 0 };
    TStrSpan               line = tfGPUConfigIter(&iterable);
    TStr tempLineMsg = { 0 };

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
                
                if(config->mGpuSelectionCount >= TF_ARRAY_COUNT(config->mGPUSelection)) {
                    tfStrClear(&tempLineMsg);
                    tfstrcatfmt(&tempLineMsg, "Max number of rules exausted '%d'.", TF_ARRAY_COUNT(config->mGPUSelection));
                    break;
                }
                
                struct TFStrSplitIterable tokenIterable = { .buffer = line, .delim = tfToRef(";"), .cursor = 0 };
                TStrSpan                  ruleSpan = tfStrTrim(tfStrSplitIter(&tokenIterable));

                struct TFStrSplitIterable         ruleIterable = { .buffer = ruleSpan, .delim = tfToRef(","), .cursor = 0 };
                bool                              isValid = true;
                
                struct GPUConfigurationSelection* configurationSelection = &config->mGPUSelection[config->mGpuSelectionCount];
                configurationSelection->mComparisonExprCount = 0;

                while (ruleIterable.cursor < ruleIterable.buffer.len)
                {
                    struct TStrSpan exprSpan = tfStrTrim(tfStrSplitIter(&ruleIterable));
                    if(configurationSelection->mComparisonExprCount >= TF_ARRAY_COUNT(configurationSelection->mComparisonExpr)) {
                        isValid = false;
                        tfStrClear(&tempLineMsg);
                        tfstrcatfmt(&tempLineMsg, "Number of expressions is exausted %d.", TF_ARRAY_COUNT(configurationSelection->mComparisonExpr));
                        LOGF(eDEBUG, tempLineMsg.buf);
                        break;
                    }

                    if (!parseGPUExpression(&config->mAlloc, &configurationSelection->mComparisonExpr[configurationSelection->mComparisonExprCount], exprSpan))
                    {
                        isValid = false;
                        tfStrClear(&tempLineMsg);
                        tfstrcatfmt(&tempLineMsg, "Invalid GPU expression '%S'.", exprSpan);
                        LOGF(eDEBUG, tempLineMsg.buf);
                    }
                    else
                    {
                        configurationSelection->mComparisonExprCount++;
                    }
                }

                if (isValid)
                {
                    config->mGpuSelectionCount++;
                }
                else
                {
                    tfStrClear(&tempLineMsg);
                    tfstrcatfmt(&tempLineMsg, "Invalid GPU selection rule '%S'.", line);
                    LOGF(eDEBUG, tempLineMsg.buf);
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

                if(config->mGpuRejectionCount >= TF_ARRAY_COUNT(config->mGPURejection)) {
                    tfStrClear(&tempLineMsg);
                    tfstrcatfmt(&tempLineMsg, "Max number of rules exausted '%d'.", TF_ARRAY_COUNT(config->mGPUSelection));
                    break;
                }

                struct TFStrSplitIterable tokenIterable = { .buffer = line, .delim = tfToRef(";"), .cursor = 0 };
                TStrSpan                  vendorSpan = tfStrTrim(tfStrSplitIter(&tokenIterable));
                TStrSpan                  ruleParametersSpan = tfStrTrim(tfStrSplitIter(&tokenIterable));
                TStrSpan                  reasonSpan = tfStrTrim(tfStrSplitIter(&tokenIterable));
                long long                 vendorId = 0;
                bool                      isValid = true;
                
                struct GPUConfigurationRejection* rejection = &config->mGPURejection[config->mGpuRejectionCount];
                rejection->mComparisonExprCount = 0;

                if (!tfStrReadll(vendorSpan, &vendorId)) {
                    tfStrClear(&tempLineMsg);
                    tfstrcatfmt(&tempLineMsg, "Invalid GPU rejection rule '%S'.", line);
                    LOGF(eDEBUG, tempLineMsg.buf);
                    continue;
                }

                struct TFStrSplitIterable ruleIterable = { .buffer = ruleParametersSpan, .delim = tfToRef(","), .cursor = 0 };
                while (ruleIterable.cursor < ruleIterable.buffer.len)
                {
                    struct TStrSpan exprSpan = tfStrTrim(tfStrSplitIter(&ruleIterable));
                    
                    if(rejection->mComparisonExprCount >= TF_ARRAY_COUNT(rejection->mComparisonExpr)) {
                        isValid = false;
                        tfStrClear(&tempLineMsg);
                        tfstrcatfmt(&tempLineMsg, "Number of expressions is exausted %d.", TF_ARRAY_COUNT(rejection->mComparisonExpr));
                        LOGF(eDEBUG, tempLineMsg.buf);
                        break;
                    }
                    

                    if (!parseGPUExpression(&config->mAlloc, &rejection->mComparisonExpr[rejection->mComparisonExprCount], exprSpan)) {
                        isValid = false;
                        tfStrClear(&tempLineMsg);
                        tfstrcatfmt(&tempLineMsg, "Invalid GPU expression '%S'.", exprSpan);
                        LOGF(eDEBUG, tempLineMsg.buf);
                    }   
                    else
                    {
                        rejection->mComparisonExprCount++;
                    }
                }

                if (!isValid)
                {
                    tfStrClear(&tempLineMsg);
                    tfstrcatfmt(&tempLineMsg, "Invalid GPU rejection rule '%S'.", line);
                    LOGF(eDEBUG, tempLineMsg.buf);
                    continue;
                }
                config->mGpuRejectionCount++;
                rejection->mVendorID = vendorId;
                rejection->mReasonStr.buf = (char*)tfScratchAlloc(&config->mAlloc, reasonSpan.len);
                rejection->mReasonStr.len = reasonSpan.len;
                memcpy(rejection->mReasonStr.buf, reasonSpan.buf, reasonSpan.len);
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

                struct TFStrSplitIterable tokenIterable = { .buffer = line, .delim = tfToRef(";"), .cursor = 0 };
                TStrSpan                  propertySpan = tfStrTrim(tfStrSplitIter(&tokenIterable));
                TStrSpan                  ruleParametersSpan = tfStrTrim(tfStrSplitIter(&tokenIterable));
                TStrSpan                  assignmentSpan = tfStrTrim(tfStrSplitIter(&tokenIterable));
                bool                      isValid = true;
                long long                 assignmentValue = 0;

                if (!tfStrReadll(assignmentSpan, &assignmentValue ))
                {
                    tfStrClear(&tempLineMsg);
                    tfstrcatfmt(&tempLineMsg, "Invalid GPU rejection rule '%S'.", line);
                    LOGF(eDEBUG, tempLineMsg.buf);
                    continue;
                }

                struct GPUConfigurationSetting* setting = &config->mConfigurationSetting[config->mGpuConfigurationSettingCount];

                struct TFStrSplitIterable ruleIterable = { .buffer = ruleParametersSpan, .delim = tfToRef(","), .cursor = 0 };
                while (ruleIterable.cursor < ruleIterable.buffer.len)
                {
                    struct TStrSpan exprSpan = tfStrTrim(tfStrSplitIter(&ruleIterable));
                    
                    if(setting->mComparisonExprCount >= TF_ARRAY_COUNT(setting->mComparisonExpr)) {
                        isValid = false;
                        tfStrClear(&tempLineMsg);
                        tfstrcatfmt(&tempLineMsg, "Number of expressions is exausted %d.", TF_ARRAY_COUNT(setting->mComparisonExpr));
                        LOGF(eDEBUG, tempLineMsg.buf);
                        break;
                    }
                    
                    if (!parseGPUExpression(&config->mAlloc, &setting->mComparisonExpr[setting->mComparisonExprCount], exprSpan)) {
                        isValid = false;
                        tfStrClear(&tempLineMsg);
                        tfstrcatfmt(&tempLineMsg, "Invalid GPU expression '%S'.", exprSpan);
                        LOGF(eDEBUG, tempLineMsg.buf);
                        break;
                    }   
                    setting->mComparisonExprCount++;
                }

                if (!isValid)
                {
                    tfStrClear(&tempLineMsg);
                    tfstrcatfmt(&tempLineMsg, "Invalid GPU setting rule '%S'.", line);
                    LOGF(eDEBUG, tempLineMsg.buf);
                    continue;
                }

                config->mGpuConfigurationSettingCount++;
                setting->mAssignmentValue = assignmentValue;
                setting->mUpdateProperty.buf = (char*)tfScratchAlloc(&config->mAlloc, propertySpan.len);
                setting->mUpdateProperty.len = propertySpan.len;
                memcpy(setting->mUpdateProperty.buf, propertySpan.buf, propertySpan.len);
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

                struct TFStrSplitIterable tokenIterable = { .buffer = line, .delim = tfToRef(";"), .cursor = 0 };
                TStrSpan                  propertySpan = tfStrTrim(tfStrSplitIter(&tokenIterable));
                TStrSpan                  ruleParametersSpan = tfStrTrim(tfStrSplitIter(&tokenIterable));
                TStrSpan                  assignmentSpan = tfStrTrim(tfStrSplitIter(&tokenIterable));
                bool                      isValid = true;
                long long                 assignmentValue = 0;

                if (!tfStrReadll(assignmentSpan, &assignmentValue ) || tfStrEmpty(ruleParametersSpan) || tfStrEmpty(propertySpan))
                {
                    tfStrClear(&tempLineMsg);
                    tfstrcatfmt(&tempLineMsg, "Invalid GPU user setting rule '%S'.", line);
                    LOGF(eDEBUG, tempLineMsg.buf);
                    continue;
                }

                struct GPUConfigurationSetting* setting = &config->mConfigurationUserSettings[config->mGpuUserSettingCount];

                struct TFStrSplitIterable ruleIterable = { .buffer = ruleParametersSpan, .delim = tfToRef(","), .cursor = 0 };
                while (ruleIterable.cursor < ruleIterable.buffer.len)
                {
                    struct TStrSpan exprSpan = tfStrTrim(tfStrSplitIter(&ruleIterable));
                    
                    if(setting->mComparisonExprCount >= TF_ARRAY_COUNT(setting->mComparisonExpr)) {
                        isValid = false;
                        tfStrClear(&tempLineMsg);
                        tfstrcatfmt(&tempLineMsg, "Number of expressions is exausted %d.", TF_ARRAY_COUNT(setting->mComparisonExpr));
                        LOGF(eDEBUG, tempLineMsg.buf);
                        break;
                    }
                    
                    if (!parseGPUExpression(&config->mAlloc, &setting->mComparisonExpr[setting->mComparisonExprCount], exprSpan)) {
                        isValid = false;
                        tfStrClear(&tempLineMsg);
                        tfstrcatfmt(&tempLineMsg, "Invalid GPU expression '%S'.", exprSpan);
                        LOGF(eDEBUG, tempLineMsg.buf);
                        break;
                    }   
                    setting->mComparisonExprCount++;
                }

                if (!isValid)
                {
                    tfStrClear(&tempLineMsg);
                    tfstrcatfmt(&tempLineMsg, "Invalid GPU user setting rule '%S'.", line);
                    LOGF(eDEBUG, tempLineMsg.buf);
                    continue;
                }

                config->mGpuConfigurationSettingCount++;
                setting->mAssignmentValue = assignmentValue;
                setting->mUpdateProperty.buf = (char*)tfScratchAlloc(&config->mAlloc, propertySpan.len);
                setting->mUpdateProperty.len = propertySpan.len;
                memcpy(setting->mUpdateProperty.buf, propertySpan.buf, propertySpan.len);
            }
        }
    }
    return true;
}


bool tfLoadGPUData(struct GPUConfiguration* config,TStrSpan input)
{
    TFStrGpuConfigIterable iterable = { .buffer = input, .cursor = 0 };

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
    TStr tempLineMsg = { 0 };

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
                struct TFStrSplitIterable tokenIterable = { .buffer = line, .delim = tfToRef(";"), .cursor = 0 };
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
                        tfStrClear(&tempLineMsg);
                        tfstrcatfmt(&tempLineMsg, "Error invalid preset level in GPU Default Data Configuration value '%S' in '%S'.",
                                    ruleNameSpan, line);
                        LOGF(eDEBUG, tempLineMsg.buf);
                    }
                }
                else
                {
                        tfStrClear(&tempLineMsg);
                        tfstrcatfmt(&tempLineMsg, "Error could not parse GPU Default Data Configuration rule '%S' in '%S'.",
                                    ruleNameSpan, assignmentSpan);
                        LOGF(eDEBUG, tempLineMsg.buf);
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
                struct TFStrSplitIterable iterable = { .buffer = line, .delim = tfToRef(";"), .cursor = 0 };
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

                struct TFStrSplitIterable iterable = { .buffer = line, .delim = tfToRef(";"), .cursor = 0 };
                TStrSpan                  vendorSpan = tfStrSplitIter(&iterable);
                TStrSpan                  identiferSpan = tfStrSplitIter(&iterable);
                struct TFStrSplitIterable idIterable = { .buffer = identiferSpan, .delim = tfToRef(","), .cursor = 0 };
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
                        tfStrClear(&tempLineMsg);
                        tfstrcatfmt(&tempLineMsg, "Invalid GPU vendor identifier %S from line: '%S'.", vendorSpan, identiferSpan);
                        LOGF(eDEBUG, tempLineMsg.buf);
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
                    tfStrClear(&tempLineMsg);
                    tfstrcatfmt(&tempLineMsg, "Error could not parse GPU vendor in '%S'.", line);
                    LOGF(eDEBUG, tempLineMsg.buf);
                }
            }
        }
    }

    // log default configuration
    LOGF(eINFO, "Default GPU Data:");
    LOGF(eINFO, "    DefaultGPUPresetLevel set to %s", presetLevelToString(config->mDefaultPresetLevel));
    // log gpu vendors
    LOGF(eINFO, "GPU vendors:");
    for(uint32_t vendorIdx = 0; vendorIdx < config->mVendorCount; vendorIdx++) {
        GPUVendorDefinition* vendorDef = &config->mVendorDefinitions[vendorIdx];
        tfStrClear(&tempLineMsg);
        tfstrcatfmt(&tempLineMsg, "%S: ", vendorDef->mVendorName);
        for (uint32_t identIdx = 0; identIdx < vendorDef->mIdentifierCount; identIdx++)
        {
            if (identIdx > 0)
            {
                tfstrcatfmt(&tempLineMsg, ", ");
            }
            tfstrcatprintf(&tempLineMsg, "%#x", vendorDef->mIdentifierArray[identIdx]);
        }
        LOGF(eINFO, tempLineMsg.buf);
    }
    tfStrFree(&tempLineMsg);
    return true;
}

typedef uint64_t (*PropertyGetter)(const GpuProperties* pSetting);
typedef void (*PropertySetter)(GpuProperties* pSetting, uint64_t value);

#define GPU_CONFIG_PROPERTY(name, prop)                                             \
    {                                                                               \
        name, [](const GpuProperties* pSetting) { return (uint64_t)pSetting->prop; }, \
            [](GpuProperties* pSetting, uint64_t value)                               \
        {                                                                           \
            COMPILE_ASSERT(sizeof(decltype(pSetting->prop)) <= sizeof(value));      \
            pSetting->prop = (decltype(pSetting->prop))value;                       \
        }                                                                           \
    }

#define GPU_CONFIG_PROPERTY_READ_ONLY(name, prop)                                   \
    {                                                                               \
        name, [](const GpuProperties* pSetting) { return (uint64_t)pSetting->prop; }, \
            [](GpuProperties* pSetting, uint64_t value)                               \
        {                                                                           \
            UNREF_PARAM(value);                                                     \
            UNREF_PARAM(pSetting);                                                  \
            LOGF(eDEBUG, "GPUConfig: Unsupported setting %s from gpu.cfg", name);   \
            ASSERT(false);                                                          \
        }                                                                           \
    }

struct GPUProperty
{
    TStrSpan  name;
    PropertyGetter getter;
    PropertySetter setter;
};

// should we enable all setter? modifying the model or vendor id for example...
const GPUProperty availableGpuProperties[] = {
    GPU_CONFIG_PROPERTY(tfToRef("allowbuffertextureinsameheap"), mAllowBufferTextureInSameHeap),
    GPU_CONFIG_PROPERTY(tfToRef("amdasicfamily"), mAmdAsicFamily),
    GPU_CONFIG_PROPERTY(tfToRef("builtindrawid"), mBuiltinDrawID),
#if defined(METAL)
    GPU_CONFIG_PROPERTY(tfToRef("cubemaptexturearraysupported"), mCubeMapTextureArraySupported),
    GPU_CONFIG_PROPERTY(tfToRef("tessellationindirectdrawsupported"), mTessellationIndirectDrawSupported),
#if !defined(TARGET_IOS)
    GPU_CONFIG_PROPERTY(tfToRef("isheadless"), mIsHeadLess),
#endif
#endif
    GPU_CONFIG_PROPERTY_READ_ONLY(tfToRef("deviceid"), mGpuVendorPreset.mModelId),
#if defined(DIRECT3D11) || defined(DIRECT3D12)
    GPU_CONFIG_PROPERTY(tfToRef("directxfeaturelevel"), mFeatureLevel),
    GPU_CONFIG_PROPERTY(tfToRef("suppressinvalidsubresourcestateafterexit"), mSuppressInvalidSubresourceStateAfterExit),
#endif
    GPU_CONFIG_PROPERTY(tfToRef("geometryshadersupported"), mGeometryShaderSupported),
    GPU_CONFIG_PROPERTY(tfToRef("gpupresetlevel"), mGpuVendorPreset.mPresetLevel),
    GPU_CONFIG_PROPERTY(tfToRef("graphicqueuesupported"), mGraphicsQueueSupported),
    GPU_CONFIG_PROPERTY(tfToRef("hdrsupported"), mHDRSupported),
#if defined(VULKAN)
    GPU_CONFIG_PROPERTY(tfToRef("dynamicrenderingenabled"), mDynamicRenderingSupported),
    GPU_CONFIG_PROPERTY(tfToRef("xclipsetransferqueueworkaroundenabled"), mXclipseTransferQueueWorkaround),
#endif
    GPU_CONFIG_PROPERTY(tfToRef("indirectcommandbuffer"), mIndirectCommandBuffer),
    GPU_CONFIG_PROPERTY(tfToRef("indirectrootconstant"), mIndirectRootConstant),
    GPU_CONFIG_PROPERTY(tfToRef("maxboundtextures"), mMaxBoundTextures),
#if defined(DIRECT3D12)
    GPU_CONFIG_PROPERTY(tfToRef("maxrootsignaturedwords", mMaxRootSignatureDWORDS),
#endif
    GPU_CONFIG_PROPERTY(tfToRef("maxvertexinputbindings"), mMaxVertexInputBindings),
    GPU_CONFIG_PROPERTY(tfToRef("multidrawindirect"), mMultiDrawIndirect),
    GPU_CONFIG_PROPERTY(tfToRef("occlusionqueries"), mOcclusionQueries),
    GPU_CONFIG_PROPERTY(tfToRef("pipelinestatsqueries"), mPipelineStatsQueries),
    GPU_CONFIG_PROPERTY(tfToRef("primitiveidsupported"), mPrimitiveIdSupported),
    GPU_CONFIG_PROPERTY(tfToRef("rasterorderviewsupport"), mROVsSupported),
    GPU_CONFIG_PROPERTY(tfToRef("raytracingsupported"), mRaytracingSupported),
    GPU_CONFIG_PROPERTY(tfToRef("rayquerysupported"), mRayQuerySupported),
    GPU_CONFIG_PROPERTY(tfToRef("raypipelinesupported"), mRayPipelineSupported),
    GPU_CONFIG_PROPERTY(tfToRef("softwarevrssupported"), mSoftwareVRSSupported),
    GPU_CONFIG_PROPERTY(tfToRef("tessellationsupported"), mTessellationSupported),
    GPU_CONFIG_PROPERTY(tfToRef("timestampqueries"), mTimestampQueries),
    GPU_CONFIG_PROPERTY(tfToRef("uniformbufferalignment"), mUniformBufferAlignment),
    GPU_CONFIG_PROPERTY(tfToRef("uploadbuffertexturealignment"), mUploadBufferTextureAlignment),
    GPU_CONFIG_PROPERTY(tfToRef("uploadbuffertexturerowalignment"), mUploadBufferTextureRowAlignment),
    GPU_CONFIG_PROPERTY_READ_ONLY(tfToRef("vendorid"), mGpuVendorPreset.mVendorId),
    GPU_CONFIG_PROPERTY(tfToRef("vram"), mVRAM),
    GPU_CONFIG_PROPERTY(tfToRef("wavelanecount"), mWaveLaneCount),
    GPU_CONFIG_PROPERTY(tfToRef("waveopssupport"), mWaveOpsSupportFlags),
};


static const GPUProperty* findGPUProperty(TStrSpan test)
{
    for (size_t i = 0; i < TF_ARRAY_COUNT(availableGpuProperties); i++)
    {
        if (tfStrCaselessEqual(availableGpuProperties[i].name, test))
        {
            return &availableGpuProperties[i];
        }
    }
    return NULL;
}

static bool testDriveVersion(GPUDriverVersion* v1, GPUDriverVersion* v2, GPUConfigExprSymbol op)
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

static bool testValueUint64(uint64_t a, uint64_t b, GPUConfigExprSymbol op) {
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

static inline bool tryUnpackUintDriverTerm(GpuProperties* gpuProp, const GPUConfigTerm* t1, GPUDriverVersion* value)
{
    if (t1->mSymbol == GPUConfigExprSymbol::GPUSymbolVariable && tfStrCaselessEqual(t1->mVariable, tfToRef("driverversion")))
    {
        if (parseDriverVersionNumber(
                TStrSpan{ gpuProp->mGpuVendorPreset.mGpuDriverVersion, strlen(gpuProp->mGpuVendorPreset.mGpuDriverVersion) }, value))
        {
            return true;
        }
    } 
    if (t1->mSymbol == GPUConfigExprSymbol::GPUSymbolDriverVersion)
    {
        (*value) = t1->mDriverVersion;
        return true;
    }

    return false;
}

static inline bool tryUnpackUint64Term(GpuProperties* gpuProp, const GPUConfigTerm* t1, uint64_t* value) {
    if (t1->mSymbol == GPUConfigExprSymbol::GPUSymbolVariable)
    {
        const GPUProperty* p1 = findGPUProperty(t1->mVariable);
        (*value) = p1->getter(gpuProp);
        return true;
    }
    
    if (t1->mSymbol == GPUConfigExprSymbol::GPUSymbolDigit)
    {
        (*value) = t1->mValue;
        return true;
    }
    return false;
}

struct GpuSelection tfApplyGPUConfig(const struct GPUConfiguration* def, const struct RendererContext* context)
{
    GpuSelection* selections = NULL;
    {
        const size_t numberOfDevices = arrlen(context->pAdapters);
        arrsetlen(selections, numberOfDevices);
        for (size_t i = 0; i < numberOfDevices; i++)
        {
            memcpy(&selections[i].properties, &context->pAdapters[i].mDefaultProps, sizeof(GpuProperties));
            selections[i].device = &context->pAdapters[i];
        }
    }

    TStr tempLineMsg = { 0 };
    for (size_t j = 0; j < arrlen(selections); j++)
    {
        for (size_t i = 0; i < def->mGpuConfigurationSettingCount; i++)
        {
            const struct GPUConfigurationSetting* setting = &def->mConfigurationSetting[i];
            const GPUProperty*                    assignmentProp = findGPUProperty(setting->mUpdateProperty);
            if (assignmentProp)
            {
                bool isValid = true;
                for (size_t ruleIdx = 0; ruleIdx < setting->mComparisonExprCount; ruleIdx++)
                {
                    const GPUConfigExpression* rule =  &setting->mComparisonExpr[ruleIdx];
                    {
                        GPUDriverVersion v1 = { 0 };
                        GPUDriverVersion v2 = { 0 };
                        if (tryUnpackUintDriverTerm(&selections[j].properties, &rule->mPrimary, &v1) &&
                            tryUnpackUintDriverTerm(&selections[j].properties, &rule->mSecondary, &v2))
                            isValid = isValid && testDriveVersion(&v1, &v2, rule->opToken);
                        if (!isValid)
                            break;
                    }
                    {
                        uint64_t v1 = 0;
                        uint64_t v2 = 0;
                        if (tryUnpackUint64Term(&selections[j].properties, &rule->mPrimary, &v1) &&
                            tryUnpackUint64Term(&selections[j].properties, &rule->mSecondary, &v2))
                            isValid = isValid && testValueUint64(v1, v2, rule->opToken);
                        if (!isValid)
                            break;
                    }
                    if (rule->mPrimary.mSymbol == GPUConfigExprSymbol::GPUSymbolVariable)
                    {
                        const GPUProperty* p1 = findGPUProperty(rule->mPrimary.mVariable);
                        isValid = isValid && (p1->getter(&selections[j].properties) > 0);
                        if (!isValid)
                            break;
                    }
                }

                if (isValid)
                {
                    assignmentProp->setter(&selections[j].properties, setting->mAssignmentValue);
                    tfStrClear(&tempLineMsg);
                    tfstrcatfmt(&tempLineMsg, "GPU: %s, setting %S to %llu", selections[j].properties.mGpuVendorPreset.mGpuName,
                                setting->mUpdateProperty, setting->mAssignmentValue);
                    LOGF(eDEBUG, tempLineMsg.buf);
                }
            }
            else
            {
                tfStrClear(&tempLineMsg);
                tfstrcatfmt(&tempLineMsg, "Unhandled property '%S'.", setting->mUpdateProperty);
                LOGF(eDEBUG, tempLineMsg.buf);
            }
        }
    }

    uint32_t selectionIndex = 0;
    for (size_t testIndex = 0; testIndex < arrlen(selections); testIndex++)
    {
        GpuSelection* testSelection = &selections[testIndex];
        GpuSelection* refSelection = &selections[selectionIndex];
        bool          refPass = true;
        bool          testPass = true;

        for (size_t ruleIndex = 0; ruleIndex < def->mGpuSelectionCount; ruleIndex++)
        {
            const struct GPUConfigurationSelection* selectionRule = &def->mGPUSelection[ruleIndex];
            for (size_t ruleIdx = 0; ruleIdx < selectionRule->mComparisonExprCount; ruleIdx++)
            {
                const GPUConfigExpression* rule = &selectionRule->mComparisonExpr[ruleIdx];
                {
                    GPUDriverVersion v1 = { 0 };
                    GPUDriverVersion v2 = { 0 };
                    if (tryUnpackUintDriverTerm(&testSelection->properties, &rule->mPrimary, &v1) &&
                        tryUnpackUintDriverTerm(&testSelection->properties, &rule->mSecondary, &v2))
                        testPass = testPass && testDriveVersion(&v1, &v2, rule->opToken);
                }
                {
                    uint64_t v1 = 0;
                    uint64_t v2 = 0;
                    if (tryUnpackUint64Term(&testSelection->properties, &rule->mPrimary, &v1) &&
                        tryUnpackUint64Term(&testSelection->properties, &rule->mSecondary, &v2))
                        testPass = testPass && testValueUint64(v1, v2, rule->opToken);
                }
                {
                    GPUDriverVersion v1 = { 0 };
                    GPUDriverVersion v2 = { 0 };
                    if (tryUnpackUintDriverTerm(&refSelection->properties, &rule->mPrimary, &v1) &&
                        tryUnpackUintDriverTerm(&refSelection->properties, &rule->mSecondary, &v2))
                        refPass = refPass && testDriveVersion(&v1, &v2, rule->opToken);
                }
                {
                    uint64_t v1 = 0;
                    uint64_t v2 = 0;
                    if (tryUnpackUint64Term(&refSelection->properties, &rule->mPrimary, &v1) &&
                        tryUnpackUint64Term(&refSelection->properties, &rule->mSecondary, &v2))
                        refPass = refPass && testValueUint64(v1, v2, rule->opToken);
                }
                if (rule->mPrimary.mSymbol == GPUConfigExprSymbol::GPUSymbolVariable)
                {
                    uint64_t refValue = 0;
                    uint64_t testValue = 0;
                    if (tryUnpackUint64Term(&refSelection->properties, &rule->mPrimary, &refValue) &&
                        tryUnpackUint64Term(&testSelection->properties, &rule->mSecondary, &testValue)) {
                        testPass &= testValue >= refValue;
                        refPass &= refValue >= testValue;
                    }
                }
            }
        }
        if(testPass != refPass) {
            // log rule selection
            uint32_t chosenIndex = testPass ? testIndex : selectionIndex;
            uint32_t nonChosenIndex = testPass ? selectionIndex : testIndex;
            LOGF(eINFO, "Choosing GPU: %s", selections[chosenIndex].properties.mGpuVendorPreset.mGpuName);
            if(testPass && !refPass) {
                selectionIndex = testIndex;
            }
        }
    }

    tfStrFree(&tempLineMsg);
    arrfree(selections);
    return selections[selectionIndex];
}
