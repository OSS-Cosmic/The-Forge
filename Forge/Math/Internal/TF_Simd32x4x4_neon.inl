#if defined(__CLANGD__)
#define TF_FEATURE_CPU_NEON
#include "Forge/TF_Config.h"
#include "../TF_Simd32x4x4.h"
#endif

//static inline TSimdFloat4x4 tfTransposeSimd4x4F(TSimdFloat4x4 a0) {
//    // abcd    aecg    aeim
//    // efgh -> bfdh -> bfjn
//    // ijkl    imko    cgko
//    // mnop    jnlp    dhlp
//    const TSimd32Fx4  tmp0 = vtrn1q_f32(a0.mCol0, a0.mCol1);
//    const TSimd32Fx4  tmp1 = vtrn2q_f32(a0.mCol0, a0.mCol1);
//    const TSimd32Fx4  tmp2 = vtrn1q_f32(a0.mCol2, a0.mCol3);
//    const TSimd32Fx4  tmp3 = vtrn2q_f32(a0.mCol2, a0.mCol3);
//    TSimdFloat4x4  result;
//    result.mCol0 = vtrn1q_f64(tmp0, tmp2);
//    result.mCol1 = vtrn1q_f64(tmp1, tmp3);
//    result.mCol2 = vtrn2q_f64(tmp0, tmp2);
//    result.mCol3 = vtrn2q_f64(tmp1, tmp3);
//    return result;
//}
//
//
