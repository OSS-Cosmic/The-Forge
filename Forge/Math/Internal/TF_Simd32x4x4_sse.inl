#if defined(__CLANGD__)
#define TF_FEATURE_CPU_SSE
#include "Forge/TF_Config.h"
#include "../TF_Simd32x4x4.h"
#endif


static inline struct Tsimd_f32x4x4_s tfSimdTranspose_f32x4x4(struct Tsimd_f32x4x4_s a0) {
    Tsimd_f32x4_t  tmp0 = _mm_shuffle_ps(a0.mCol0, a0.mCol1, 0x44);
    Tsimd_f32x4_t  tmp2 = _mm_shuffle_ps(a0.mCol0, a0.mCol1, 0xEE);
    Tsimd_f32x4_t  tmp1 = _mm_shuffle_ps(a0.mCol2, a0.mCol3, 0x44);
    Tsimd_f32x4_t  tmp3 = _mm_shuffle_ps(a0.mCol2, a0.mCol3, 0xEE);
    struct Tsimd_f32x4x4_s result;
    result.mCol0 = _mm_shuffle_ps(tmp0, tmp1, 0x88);
    result.mCol1 = _mm_shuffle_ps(tmp0, tmp1, 0xDD);
    result.mCol2 = _mm_shuffle_ps(tmp2, tmp3, 0x88);
    result.mCol3 = _mm_shuffle_ps(tmp2, tmp3, 0xDD);
    return result;
}



static inline struct Tsimd_f32x4x4_s tfSimdLoadOrthographicLH_f32x4x4(float left, float right, float bottom, float top, float zNear, float zFar) {
 
	Tsimd_f32x4_t lbn, rtf;
	Tsimd_f32x4_t diff, sum, inv_diff, neg_inv_diff;
	Tsimd_f32x4_t diagonal, column;
	const Tsimd_f32x4_t l = tfSimdSplat_f32_f32x4(left);
	const Tsimd_f32x4_t f = tfSimdSplat_f32_f32x4(zFar);
	const Tsimd_f32x4_t r = tfSimdSplat_f32_f32x4(right);
	const Tsimd_f32x4_t n = tfSimdSplat_f32_f32x4(zNear);
	const Tsimd_f32x4_t b = tfSimdSplat_f32_f32x4(bottom);
	const Tsimd_f32x4_t t = tfSimdSplat_f32_f32x4(top);
	lbn = _mm_unpacklo_ps(l, n);
	rtf = _mm_unpacklo_ps(r, f);
	lbn = _mm_unpacklo_ps(lbn, b);
	rtf = _mm_unpacklo_ps(rtf, t);
	diff = _mm_sub_ps(rtf, lbn);
	inv_diff = tfSimdRcp_f32x4(diff);
	neg_inv_diff = _mm_sub_ps(_mm_setzero_ps(),inv_diff);
    sum = _mm_add_ps(rtf, tfSimdReplace_f32x4_f32x4(2, lbn, _mm_sub_ps(n, f)));
	diagonal = _mm_add_ps(inv_diff, tfSimdReplace_f32x4_f32x4(2, inv_diff, tfSimdZero_f32x4()));
	column = _mm_mul_ps(sum, neg_inv_diff);
    return {
        tfSimdReplace_f32x4_f32x4(0, tfSimdZero_f32x4(), diagonal),
        tfSimdReplace_f32x4_f32x4(1, tfSimdZero_f32x4(), diagonal),
        tfSimdReplace_f32x4_f32x4(2, tfSimdZero_f32x4(), diagonal),
        tfSimdReplace_f32x4_f32x4(3, column, tfSimdSplat_f32_f32x4(1.0f)),
    };
}

