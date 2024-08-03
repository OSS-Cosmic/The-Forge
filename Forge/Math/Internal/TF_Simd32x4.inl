#if defined(__CLANGD__)
#define TF_FEATURE_CPU_SSE
#include "Forge/TF_Config.h"
#include "../TF_Simd32x4.h"
#endif

static inline bool tfSimdIsClose_f32x4(Tsimd_f32x4_t ar0,Tsimd_f32x4_t ar1, float epsilon) {
  return tfSimdCmpAllLt_f32x4(tfSimdAbs_f32x4(tfSimdSub_f32x4(ar0, ar1)), tfSimdSplat_f32_f32x4(epsilon));
}

static Tsimd_f32x4_t tfNormWithLength_f32x4(Tsimd_f32x4_t input, float* outLength) {
#if TF_FEATURE_CPU_SCALAR
    float len = tfSimdLength_f32x4_f32(input);
    if (outLength)
        (*outLength) = len;
    return {
        input.v[0] / len,
        input.v[1] / len,
        input.v[2] / len,
        input.v[3] / len,
    };
#else
  Tsimd_f32x4_t len = tfSimdLength_f32x4(input);
  if(outLength) 
    (*outLength) = tfSimdGet_f32x4(len, 0);
  return tfSimdDiv_f32x4(input, len);
#endif
}

