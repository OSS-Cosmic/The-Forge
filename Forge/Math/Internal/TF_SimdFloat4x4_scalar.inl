#if defined(__CLANGD__)
#define TF_FEATURE_CPU_SCALAR
#include "Forge/TF_Config.h"
#include "../TF_SimdFloat4x4.h"
#endif

static inline TSimdFloat4x4 tfMatTranpose4x4F(TSimdFloat4x4 a0) {
    TSimdFloat32x4 cols0 = { { a0.mCol0.v[0], a0.mCol1.v[0], a0.mCol2.v[0], a0.mCol3.v[0] } };
    TSimdFloat32x4 cols1 = { { a0.mCol0.v[1], a0.mCol1.v[1], a0.mCol2.v[1], a0.mCol3.v[1] } };
    TSimdFloat32x4 cols2 = { { a0.mCol0.v[2], a0.mCol1.v[2], a0.mCol2.v[2], a0.mCol3.v[2] } };
    TSimdFloat32x4 cols3 = { { a0.mCol0.v[3], a0.mCol1.v[3], a0.mCol2.v[3], a0.mCol3.v[3] } };
    TSimdFloat4x4  result;
    result.mCol0 = cols0;
    result.mCol1 = cols1;
    result.mCol2 = cols2;
    result.mCol3 = cols3;
    return result;
}


