#if defined(__CLANGD__)
#include "../TF_SimdFloat4.h"
#endif

#include "Forge/Math/TF_Simd32x4.h"

static inline TSimdFloat4 tfLoadSimd4F(float x, float y, float z, float w) {
    TSimdFloat4 res;
    res.mRow = tfSimdFloat4x32Load(x, y, z, w);
    return res;
}

static inline float tfGetElemSimd4F(TSimdFloat4 a, int elem) {
    ASSERT(elem >= 0 && elem < 4);
    switch (elem) {
    case 0:
        return tfSimd4fSelectIndex0(a.mRow);
    case 1:
        return tfSimd4fSelectIndex1(a.mRow);
    case 2:
        return tfSimd4fSelectIndex2(a.mRow);
    case 3:
        return tfSimd4fSelectIndex3(a.mRow);
    }
    return 0;
}
static inline float tfGetXSimd4F(TSimdFloat4 a) { return tfSimd4fSelectIndex0(a.mRow); }
static inline float tfGetYSimd4F(TSimdFloat4 a) { return tfSimd4fSelectIndex1(a.mRow); }
static inline float tfGetZSimd4F(TSimdFloat4 a) { return tfSimd4fSelectIndex2(a.mRow); }
static inline float tfGetWSimd4F(TSimdFloat4 a) { return tfSimd4fSelectIndex3(a.mRow); }
