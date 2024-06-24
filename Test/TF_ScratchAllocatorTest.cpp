#include "Forge/Core/Mem/TF_ScratchAllocator.h"
#include "utest.h"

UTEST(Core, scratchAlloc_1)
{
  struct TFScratchAlloc testAlloc = {0};
  struct TFScratchAllocDesc desc = {
    .blockSize = 1024,
    .alignment = 16
  };
  tfInitScratchAlloc(&testAlloc, &desc);
  tfScratchAllocMalloc(&testAlloc, 128);
  tfScratchAllocMalloc(&testAlloc, 128);
  tfScratchAllocMalloc(&testAlloc, 128);
  tfScratchAllocMalloc(&testAlloc, 128);
  tfScratchAllocMalloc(&testAlloc, 128);
  tfScratchAllocMalloc(&testAlloc, 128);
  tfScratchAllocMalloc(&testAlloc, 128);
  tfScratchAllocMalloc(&testAlloc, 128);
  EXPECT_EQ(arrlen(testAlloc.allocs), 1);
  tfFreeScratchAlloc(&testAlloc);
}


UTEST(TF, scratchAlloc_2)
{
  struct TFScratchAlloc testAlloc = {0};
  struct TFScratchAllocDesc desc = {
    .blockSize = 1024,
    .alignment = 16
  };
  tfInitScratchAlloc(&testAlloc, &desc);
  tfScratchAllocMalloc(&testAlloc, 128);
  tfScratchAllocMalloc(&testAlloc, 128);
  tfScratchAllocMalloc(&testAlloc, 128);
  void* data = tfScratchAllocMalloc(&testAlloc, 2048);
  EXPECT_EQ(((size_t)data) % 16, 0);
  EXPECT_EQ(arrlen(testAlloc.allocs), 2);
  tfFreeScratchAlloc(&testAlloc);
}


UTEST_STATE();
#include "Common_3/Utilities/Interfaces/IFileSystem.h"
#include "Common_3/Utilities/Interfaces/IMemory.h"

int main(int argc, const char* const argv[])
{
    if (!initMemAlloc("TF_StringTest"))
        return EXIT_FAILURE;

    FileSystemInitDesc fsDesc = {};
    fsDesc.pAppName = "TF_StringTest";

    if (!initFileSystem(&fsDesc))
        return EXIT_FAILURE;

    fsSetPathForResourceDir(pSystemFileIO, RM_DEBUG, RD_LOG, "");

    int res = utest_main(argc, argv);
    exitMemAlloc();
    return res;
}


