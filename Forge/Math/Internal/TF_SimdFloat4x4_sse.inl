#if defined(__CLANGD__)
#define TF_FEATURE_CPU_SSE
#include "Forge/TF_Config.h"
#include "../TF_SimdFloat4x4.h"
#endif

static inline TSimdFloat4x4 tfMatTranpose4x4F(TSimdFloat4x4 a0) {
    TSimdFloat32x4 tmp0 = _mm_shuffle_ps(a0.mCol0, a0.mCol1, 0x44);
    TSimdFloat32x4 tmp2 = _mm_shuffle_ps(a0.mCol0, a0.mCol1, 0xEE);
    TSimdFloat32x4 tmp1 = _mm_shuffle_ps(a0.mCol2, a0.mCol3, 0x44);
    TSimdFloat32x4 tmp3 = _mm_shuffle_ps(a0.mCol2, a0.mCol3, 0xEE);
    TSimdFloat4x4  result;
    result.mCol0 = _mm_shuffle_ps(tmp0, tmp1, 0x88);
    result.mCol1 = _mm_shuffle_ps(tmp0, tmp1, 0xDD);
    result.mCol2 = _mm_shuffle_ps(tmp2, tmp3, 0x88);
    result.mCol3 = _mm_shuffle_ps(tmp2, tmp3, 0xDD);
    return result;
}
