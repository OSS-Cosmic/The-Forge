#if defined(__CLANGD__)
#define TF_FEATURE_CPU_SCALAR
#include "Forge/TF_Config.h"
#include "../TF_SimdFloat4x4.h"
#endif

static inline TSimdFloat4x4 tfTransposeSimd4x4F(TSimdFloat4x4 a0) {
    Tsimd_f32x4_t cols0 = { { a0.mCol0.v[0], a0.mCol1.v[0], a0.mCol2.v[0], a0.mCol3.v[0] } };
    Tsimd_f32x4_t cols1 = { { a0.mCol0.v[1], a0.mCol1.v[1], a0.mCol2.v[1], a0.mCol3.v[1] } };
    Tsimd_f32x4_t cols2 = { { a0.mCol0.v[2], a0.mCol1.v[2], a0.mCol2.v[2], a0.mCol3.v[2] } };
    Tsimd_f32x4_t cols3 = { { a0.mCol0.v[3], a0.mCol1.v[3], a0.mCol2.v[3], a0.mCol3.v[3] } };
    TSimdFloat4x4  result;
    result.mCol0 = cols0;
    result.mCol1 = cols1;
    result.mCol2 = cols2;
    result.mCol3 = cols3;
    return result;
}


