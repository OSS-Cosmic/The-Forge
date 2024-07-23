#include "TF_TestMain.h"
#include "Forge/Core/Mem/TF_Allocators.h"
#include "utest.h"

UTEST(Core, scratchAlloc_1)
{
  struct TFScratchAllocator testAlloc = {0};
  struct TFScratchAllocDesc desc = {0};
  desc.blockSize = 1024;
  desc.alignment = 16;
  tfAddScratchAllocator(&testAlloc, &desc);
  tfScratchAlloc(&testAlloc, 128);
  tfScratchAlloc(&testAlloc, 128);
  tfScratchAlloc(&testAlloc, 128);
  tfScratchAlloc(&testAlloc, 128);
  tfScratchAlloc(&testAlloc, 128);
  tfScratchAlloc(&testAlloc, 128);
  tfScratchAlloc(&testAlloc, 128);
  tfScratchAlloc(&testAlloc, 128);
  tfFreeScratchAllocator(&testAlloc);
}


UTEST(TF, scratchAlloc_2)
{
    struct TFScratchAllocator testAlloc = { 0 };
    struct TFScratchAllocDesc desc = { 0 };
    desc.blockSize = 1024;
    desc.alignment = 16;

    tfAddScratchAllocator(&testAlloc, &desc);
    tfScratchAlloc(&testAlloc, 128);
    tfScratchAlloc(&testAlloc, 128);
    tfScratchAlloc(&testAlloc, 128);
    void* data = tfScratchAlloc(&testAlloc, 2048);
    EXPECT_EQ(((size_t)data) % 16, 0);
    tfFreeScratchAllocator(&testAlloc);
}


#include "Forge/TF_FileSystem.h"
#include "Forge/Core/Mem/TF_Memory.h"
#include "Forge/TF_Log.h"
UTEST_STATE();
TF_UTEST_MAIN("TF_ScratchAllocatorTest")


