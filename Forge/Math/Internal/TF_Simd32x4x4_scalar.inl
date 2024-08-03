#if defined(__CLANGD__)
#define TF_FEATURE_CPU_SCALAR
#include "Forge/TF_Config.h"
#include "../TF_Simd32x4x4.h"
#endif

static inline struct Tsimd_f32x4x4_s tfSimdTranspose_f32x4x4(struct Tsimd_f32x4x4_s a0) {
    Tsimd_f32x4_t          cols0 = { { a0.mCol0.v[0], a0.mCol1.v[0], a0.mCol2.v[0], a0.mCol3.v[0] } };
    Tsimd_f32x4_t          cols1 = { { a0.mCol0.v[1], a0.mCol1.v[1], a0.mCol2.v[1], a0.mCol3.v[1] } };
    Tsimd_f32x4_t          cols2 = { { a0.mCol0.v[2], a0.mCol1.v[2], a0.mCol2.v[2], a0.mCol3.v[2] } };
    Tsimd_f32x4_t          cols3 = { { a0.mCol0.v[3], a0.mCol1.v[3], a0.mCol2.v[3], a0.mCol3.v[3] } };
    struct Tsimd_f32x4x4_s result;
    result.mCol0 = cols0;
    result.mCol1 = cols1;
    result.mCol2 = cols2;
    result.mCol3 = cols3;
    return result;
}


static inline struct Tsimd_f32x4x4_s tfSimdLoadOrthographicLH_f32x4x4(float left, float right, float bottom, float top, float zNear, float zFar) {
    struct Tsimd_f32x4x4_s res;
    res.mCol0 = tfSimdLoad_f32x4(2.0 / (right - left), 0,0,0);
    res.mCol1 = tfSimdLoad_f32x4(0, 2.0 / (top - bottom),0,0);
    res.mCol2 = tfSimdLoad_f32x4(0, 0,1.0 / (zFar - zNear),0);
    res.mCol3 = tfSimdLoad_f32x4(-(right + left) / (right - left), -(top + bottom) / (top - bottom),-zNear / (zFar - zNear), 1.0f );
    return res;
}


//static inline struct Tsimd_f32x4x4_s tfSimdSetTranslation_f32x4x4(struct Tsimd_f32x4x4_s input, Tsimd_f32x3_t translation) {
//    input.mCol3.v[0] = translation.v[0];
//    input.mCol3.v[1] = translation.v[1];
//    input.mCol3.v[2] = translation.v[2];
//    return input;
//}

