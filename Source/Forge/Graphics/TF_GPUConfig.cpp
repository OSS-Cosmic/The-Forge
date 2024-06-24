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
      .blockSize = 4096 
    };
    tfInitScratchAlloc(&config->mAlloc, &allocDesc);
}
void tfFreeGPUConfiguration(struct GPUConfiguration* config) {
  tfFreeScratchAlloc(&config->mAlloc);
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
    TStr errorMsg = { 0 };

    while (iterable.cursor < iterable.buffer.len)
    {
        line = tfGPUConfigIter(&iterable);
        if (tfStrIndexOf(line, tfToRef("BEGIN_VENDOR_LIST;")) >= 0)
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

                bool                      validVendor = 0;
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
                        tfStrClear(&errorMsg);
                        tfstrcatfmt(&errorMsg, "Invalid GPU vendor identifier %S from line: '%S'.", vendorSpan, identiferSpan);
                        LOGF(eDEBUG, errorMsg.buf);
                        tfStrFree(&errorMsg);
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
                    tfStrClear(&errorMsg);
                    tfstrcatfmt(&errorMsg, "Error could not parse GPU vendor in '%S'.", line);
                    LOGF(eDEBUG, errorMsg.buf);
                    tfStrFree(&errorMsg);
                }
            }
        }
    }
    return true;
}
