#pragma once

#include "Forge/Core/TF_Core.h"
#include "Forge/Core/TF_Logging.h"

typedef void* (*TFAllocatorMalloc)(void* self, size_t size);

struct TFAllocator {
  void* mSelf;
  TFAllocatorMalloc mMalloc;
};


struct TFScratchAllocator
{
    struct TFAllocScratchBlock* mFreeBlocks;
    struct TFAllocScratchBlock* mCurrent;
    size_t               pos;
    size_t               blockSize;
    size_t               alignment;
};

struct TFScratchAllocDesc
{
    size_t blockSize;
    size_t alignment;
};

struct TFStackAllocatorCheckpoint
{
    struct TFStackAllocBlock* mTop;
    size_t               mPos;
};

struct TFStackAllocator
{
    struct TFStackAllocBlock* mFreeBlocks;
    struct TFStackAllocBlock* mTail;
    struct TFStackAllocBlock* mHead;
    size_t                    mTotalAllocated;
    size_t                    mReserveSize; // we're allocated beyond the reserve then blocks are removed
    size_t                    mPos;
    size_t                    mBlockSize;
    size_t                    mAlignment;
};

struct TFStackAllocDesc
{
    size_t blockSize;
    size_t alignment;
};

// stack allocator
void tfAddStackAllocator(struct TFStackAllocator* alloc, struct TFStackAllocDesc* desc);
void tfAddScratchAllocator(struct TFScratchAllocator* alloc, TFScratchAllocDesc* desc);

void tfFreeScratchAllocator(struct TFScratchAllocator* alloc);
void tfFreeStackAllocator(struct TFStackAllocator* alloc);

// checkpoint allows for the allocation to restore to a checkpoint
struct TFStackAllocatorCheckpoint tfStackAllocGetCheckpoint(struct TFStackAllocator* alloc);
void tfStackAllocRestoreCheckpoint(struct TFStackAllocator* alloc, struct TFStackAllocatorCheckpoint* checkpoint);
void tfStackAllocReset(struct TFStackAllocator* alloc);

void* tfScratchAlloc(struct TFScratchAllocator* alloc, size_t size);
void* tfStackAlloc(struct TFStackAllocator* alloc, size_t size);
