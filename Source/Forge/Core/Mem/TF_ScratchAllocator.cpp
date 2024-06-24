#include "Forge/Core/Mem/TF_ScratchAllocator.h"
#include "Forge/Core/TF_Logging.h"
#include "Forge/Core/TF_Math.h"
#include "Forge/Core/Mem/TF_Memory.h"

void  tfInitScratchAlloc(TFScratchAlloc* scratch, TFScratchAllocDesc* desc) {
  ASSERT(scratch);
  ASSERT(desc);
  memset(scratch, 0, sizeof(TFScratchAlloc));
  scratch->blockSize = desc->blockSize;
  scratch->alignment = max(desc->alignment, sizeof(uint16_t));
}

void* tfScratchAllocMalloc(TFScratchAlloc* alloc, size_t size) {
  const size_t reqSize = round_up_64(size, alloc->alignment);
  if(reqSize > alloc->blockSize) {
    void* result = tf_memalign(alloc->alignment, size);
    arrpush(alloc->allocs, result);
    return result; 
  }
  if(alloc->alloc && (alloc->pos + reqSize) > alloc->blockSize) {
    alloc->alloc = NULL; // we've exausted the block
  }
  if(alloc->alloc == NULL) {
    alloc->alloc = tf_memalign(alloc->alignment, alloc->blockSize);
    alloc->pos = 0;
    arrpush(alloc->allocs, alloc->alloc);
  }
  void* result = ((uint8_t*)alloc->alloc) + alloc->pos;
  alloc->pos += reqSize;
  return result;

}

void tfFreeScratchAlloc(TFScratchAlloc* alloc) {
  for(size_t j = 0; j < arrlen(alloc->allocs); j++) {
    tf_free(alloc->allocs[j]);
  }
  arrfree(alloc->allocs);

}
