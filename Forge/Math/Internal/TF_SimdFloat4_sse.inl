#if defined(__CLANGD__)
#define TF_FEATURE_CPU_SSE
#include "Forge/TF_Config.h"
#include "../TF_SimdFloat4.h"
#endif

static inline float tfVectorDot4F(TSimdFloat4 a0, TSimdFloat4  a1) {
    TSimdFloat32x4 x2 = _mm_mul_ps(a0.mRow, a1.mRow);
    TSimdFloat32x4 tmp = _mm_add_ps(x2, _mm_shuffle_ps(x2, x2, _MM_SHUFFLE(2, 3, 0, 1)));
    return _mm_cvtss_f32(_mm_add_ps(tmp, _mm_shuffle_ps(tmp, tmp, _MM_SHUFFLE(1, 0, 2, 3))));
}

static inline float tfVectorDot3F(TSimdFloat4 a0, TSimdFloat4  a1) {
    TSimdFloat32x4  x2 = _mm_mul_ps(a0.mRow, a1.mRow);
    TSimdFloat32x4  xy = tfSimd4fAdd(tfSimd4fSplatIndex1(x2), x2);
    TSimdFloat32x4   xyz = tfSimd4fAdd(tfSimd4fSplatIndex2(x2), xy);
    return tfSimd4fSelectIndex0(xyz);
}

