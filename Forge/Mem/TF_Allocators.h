#pragma once

#include "Forge/TF_Log.h"

typedef void* (*TFAllocatorMalloc)(void* self, size_t size);
typedef void* (*TFAllocatorFree)(void* self, void* ptr);

struct TFAllocator {
  void* mSelf;
  TFAllocatorMalloc mMalloc;
  TFAllocatorFree mFree;
};

struct TFFixedBufferAllocDesc
{
    void* mBuffer;
    size_t mSize;
    size_t mAlignment;
};

struct TFFixedBufferAllocator
{
    void*  mData;
    size_t mSize;
    size_t mPos;
    size_t mAlignment;
};

struct TFScratchAllocDesc
{
    size_t blockSize;
    size_t alignment;
};

struct TFScratchAllocator
{
    struct TFAllocScratchBlock* mFreeBlocks;
    struct TFAllocScratchBlock* mCurrent;
    size_t                      pos;
    size_t                      blockSize;
    size_t                      alignment;
};

struct TFStackAllocatorCheckpoint
{
    struct TFStackAllocBlock* mTop;
    size_t                    mPos;
};

struct TFStackAllocDesc
{
    size_t mBlockSize;
    size_t mAlignment;
};


#ifdef __cplusplus
extern "C" {
#endif

// stack allocator
void tfAddFixedAllocator(struct TFFixedBufferAllocator* alloc, struct TFFixedBufferAllocDesc* desc);
void tfAddScratchAllocator(struct TFScratchAllocator* alloc, struct TFScratchAllocDesc* desc);

void tfFreeScratchAllocator(struct TFScratchAllocator* alloc);
void tfFreeStackAllocator(struct TFStackAllocator* alloc);

void* tfScratchAlloc(struct TFScratchAllocator* alloc, size_t size);
void* tfFixedBufferAlloc(struct TFFixedBufferAllocator* alloc, size_t size);

#ifdef __cplusplus
}
#endif
