
/* ------------------------ gpu.data ------------------------ */
// intel use 3 identifiers 0x163C, 0x8086, 0x8087;

#include "Forge/Core/TF_String.h"
#include "Forge/Core/Mem/TF_ScratchAllocator.h"

#include "Common_3/Graphics/Interfaces/IGraphics.h"

#define MAX_GPU_VENDOR_COUNT                 64
#define MAX_GPU_VENDOR_IDENTIFIER_LENGTH     16
#define MAX_INDENTIFIER_PER_GPU_VENDOR_COUNT 12 

struct GPUVendorDefinition {
    TStrSpan mVendorName = {};
    uint32_t mIdentifierCount = 0;
    uint32_t mIdentifierArray[MAX_INDENTIFIER_PER_GPU_VENDOR_COUNT] = {};
};

struct GPUModelDefinition
{
    uint32_t       mVendorId;
    uint32_t       mDeviceId;
    GPUPresetLevel mPreset;
    TStrSpan mModelName;
};

struct GPUConfiguration {
  TFScratchAlloc mAlloc;

  uint32_t mVendorCount;
  GPUVendorDefinition mVendorDefinitions[MAX_GPU_VENDOR_COUNT]; 
};

void tfInitGPUConfiguration(struct GPUConfiguration* def);
bool tfLoadGPUConfig(struct GPUConfiguration* config, TStrSpan input);
bool tfLoadGPUData(struct GPUConfiguration* config,TStrSpan input);
void tfFreeGPUConfiguration(struct GPUConfiguration* def);
