#include "Forge/Graphics/TF_GPUConfig.h"

#define GPUCFG_VERSION_MAJOR           0
#define GPUCFG_VERSION_MINOR           2


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
            const int       leaderOffset = tfStrIndexOfOffset(res, iterable->cursor, tfToRef("#"));
            if (leaderOffset > 0)
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

    return (struct TStrSpan){ 0 };
}

void tfInitGPUConfiguration(struct GPUConfiguration* config) {

    struct TFScratchAllocDesc allocDesc = {
      .blockSize = 8192 
    };
    tfInitScratchAlloc(&config->mAlloc, &allocDesc);
}
void tfFreeGPUConfiguration(struct GPUConfiguration* config) {
  tfFreeScratchAlloc(&config->mAlloc);
  arrfree(config->mGpuModels);
}

static GPUPresetLevel strToPresetLevel(TStrSpan input)
{
    if (tfStrEqual(input, tfToRef("office")))
        return GPU_PRESET_OFFICE;
    if (tfStrIndexOfCaseless(input, tfToRef("verylow")))
        return GPU_PRESET_VERYLOW;
    if (tfStrIndexOfCaseless(input, tfToRef("low")))
        return GPU_PRESET_LOW;
    if (tfStrIndexOfCaseless(input, tfToRef("medium")))
        return GPU_PRESET_MEDIUM;
    if (tfStrIndexOfCaseless(input, tfToRef("high")))
        return GPU_PRESET_HIGH;
    if (tfStrIndexOfCaseless(input, tfToRef("ultra")))
        return GPU_PRESET_ULTRA;
    return GPU_PRESET_NONE;
}

bool tfLoadGPUConfig(struct GPUConfiguration* def, struct GPUConfiguration* config, TStrSpan input)
{
    TFStrGpuConfigIterable iterable = { .buffer = input, .cursor = 0 };
    TStrSpan               line = tfGPUConfigIter(&iterable);

    while (iterable.cursor < iterable.buffer.len)
    {
        line = tfGPUConfigIter(&iterable);
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
                {
                    continue;
                }
                if (tfStrIndexOf(line, tfToRef("END_DEFAULT_CONFIGURATION;")) >= 0)
                {
                    break;
                }
                struct TFStrSplitIterable iterable = { .buffer = line, .delim = tfToRef(";"), .cursor = 0 };
                TStrSpan                  ruleNameSpan = tfStrTrim(tfStrSplitIter(&iterable));
                TStrSpan                  assignmentSpan = tfStrTrim(tfStrSplitIter(&iterable));
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
                {
                    continue;
                }
                if (tfStrIndexOf(line, tfToRef("END_GPU_LIST;")) >= 0)
                {
                    break;
                }
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
                    modelDef.mModelName.buf = (char*)tfScratchAllocMalloc(&config->mAlloc, modelNameSpan.len);
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
                    vendorDef->mVendorName.buf = (char*)tfScratchAllocMalloc(&config->mAlloc, vendorSpan.len);
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
