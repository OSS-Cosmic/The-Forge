#pragma once

#include "Forge/Core/TF_Core.h"

struct TFScratchAlloc {
  void** allocs;
  void* alloc;
  size_t pos;
  size_t blockSize;
  size_t alignment;
};

struct TFScratchAllocDesc {
  size_t blockSize;
  size_t alignment;
};

void  tfInitScratchAlloc(struct TFScratchAlloc* alloc, TFScratchAllocDesc* desc);
void* tfScratchAllocMalloc(struct TFScratchAlloc* alloc, size_t size);
void  tfFreeScratchAlloc(struct TFScratchAlloc* alloc);
