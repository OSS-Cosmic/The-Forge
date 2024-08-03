#if defined(__CLANGD__)
#define TF_FEATURE_CPU_SSE
#include "Forge/TF_Config.h"
#include "../TF_SimdFloat4.h"
#endif


static inline Tsimd_f32x4_t ___Simd4x324Dot4(TSimdFloat4 a0, TSimdFloat4 a1) {
    Tsimd_f32x4_t x2 = _mm_mul_ps(a0.mRow, a1.mRow);
    Tsimd_f32x4_t tmp = _mm_add_ps(x2, _mm_shuffle_ps(x2, x2, _MM_SHUFFLE(2, 3, 0, 1)));
    return _mm_add_ps(tmp, _mm_shuffle_ps(tmp, tmp, _MM_SHUFFLE(1, 0, 2, 3)));
}

static inline float tfVectorDot4F(TSimdFloat4 a0, TSimdFloat4 a1) {
    return _mm_cvtss_f32(___Simd4x324Dot4(a0, a1));
}

static inline float tfVectorLengthSq4F(TSimdFloat4 a0, TSimdFloat4  a1) {
    return _mm_cvtss_f32(___Simd4x324Dot4(a0, a1));

}
static inline float tfVectorLength4F(TSimdFloat4 a0, TSimdFloat4  a1) {
    return _mm_cvtss_f32(_mm_sqrt_ps(___Simd4x324Dot4(a0, a1)));
}

