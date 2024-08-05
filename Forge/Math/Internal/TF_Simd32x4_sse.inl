#if defined(__CLANGD__)
#define TF_FEATURE_CPU_SSE  
#include "Forge/TF_Config.h"
#include "../TF_Simd32x4.h"
#endif

// Tsimd_f32x4_t
static inline Tsimd_f32x4_t tfSimdLoad_f32x4(float x, float y, float z, float w) { return _mm_set_ps(w, z, y, x); }
static inline Tsimd_f32x4_t tfSimdZero_f32x4() { return _mm_setzero_ps(); }

static inline Tsimd_f32x4_t tfSimdSplat_f32_f32x4(float value) { return _mm_set1_ps(value); }
static inline Tsimd_f32x4_t tfSimdSplat_f32x4_f32x4(Tsimd_f32x4_t value, int index) {
    ASSERT(index < 4);
    switch(index) {
        case 0:return _mm_shuffle_ps(value, value, _MM_SHUFFLE(0, 0, 0, 0));
        case 1:return _mm_shuffle_ps(value, value, _MM_SHUFFLE(1, 1, 1, 1));
        case 2:return _mm_shuffle_ps(value, value, _MM_SHUFFLE(2, 2, 2, 2));
        case 3:
            return _mm_shuffle_ps(value, value, _MM_SHUFFLE(3, 3, 3, 3));
        }
        return {};
}

static inline Tsimd_f32x4_t tfSimdDot_f32x4(Tsimd_f32x4_t a, Tsimd_f32x4_t b) {
    Tsimd_f32x4_t x2 = _mm_mul_ps(a, b);
    Tsimd_f32x4_t tmp = _mm_hadd_ps(x2, x2);
    return _mm_hadd_ps(tmp, tmp);
}
static inline Tsimd_f32x4_t tfSimdLength_f32x4(Tsimd_f32x4_t a) { return tfSimdSqrt_f32x4(tfSimdDot_f32x4(a, a)); }
static inline float tfSimdDot_f32x4_f32(Tsimd_f32x4_t a, Tsimd_f32x4_t b) { return _mm_cvtss_f32(tfSimdDot_f32x4(a, b)); }
static inline float tfSimdLength_f32x4_f32(Tsimd_f32x4_t a) { return _mm_cvtss_f32(tfSimdLength_f32x4(a)); }
static inline float tfSimdLengthSqr_f32x4_f32(Tsimd_f32x4_t a) {return _mm_cvtss_f32(tfSimdDot_f32x4(a, a));}

static inline float tfSimdMaxElem_f32x4_f32(Tsimd_f32x4_t a) { return _mm_cvtss_f32(tfSimdMaxElem_f32x4(a)); }
static inline float tfSimdMinElem_f32x4_f32(Tsimd_f32x4_t a) { return _mm_cvtss_f32(tfSimdMinElem_f32x4(a)); }

static inline Tsimd_f32x4_t tfSimdMaxElem_f32x4(Tsimd_f32x4_t a) {
    return _mm_max_ps(_mm_max_ps(tfSimdSplat_f32x4_f32x4(a, 0), tfSimdSplat_f32x4_f32x4(a, 1)),
                      _mm_max_ps(tfSimdSplat_f32x4_f32x4(a, 2), tfSimdSplat_f32x4_f32x4(a, 3)));
}

static inline Tsimd_f32x4_t tfSimdMinElem_f32x4(Tsimd_f32x4_t a) {
    return _mm_min_ps(_mm_min_ps(tfSimdSplat_f32x4_f32x4(a, 0), tfSimdSplat_f32x4_f32x4(a, 1)),
                      _mm_min_ps(tfSimdSplat_f32x4_f32x4(a, 2), tfSimdSplat_f32x4_f32x4(a, 3)));
}

static inline Tsimd_f32x4_t tfSimdMaxPerElem_f32x4(Tsimd_f32x4_t a, Tsimd_f32x4_t b) { return _mm_max_ps(a, b); }
static inline Tsimd_f32x4_t tfSimdMinPerElem_f32x4(Tsimd_f32x4_t a, Tsimd_f32x4_t b) { return _mm_min_ps(a, b); }

static inline float tfSimdGet_f32x4(Tsimd_f32x4_t value, int index) {
    ASSERT(index < 4);
    return _mm_cvtss_f32(tfSimdSplat_f32x4_f32x4(value, index));
}

static inline Tsimd_f32x4_t tfSimdReplace_f32_f32x4(Tsimd_f32x4_t a,int index, float b) {
    return tfSimdReplace_f32x4_f32x4( a,index, tfSimdSplat_f32_f32x4(b));
}
static inline Tsimd_f32x4_t tfSimdReplace_f32x4_f32x4(Tsimd_f32x4_t a,int index,  Tsimd_f32x4_t b) {
    ASSERT(index < 4);
    switch(index) {
        case 0: return _mm_blend_ps(a, b, 0b0001);
        case 1: return _mm_blend_ps(a, b, 0b0010);
        case 2: return _mm_blend_ps(a, b, 0b0100);
        case 3: return _mm_blend_ps(a, b, 0b1000);
        default:
            break;
    }
    return {};
}

static inline Tsimd_f32x4_t tfSimdSqrt_f32x4(Tsimd_f32x4_t a) { return _mm_sqrt_ps(a); }
static inline Tsimd_f32x4_t tfSimdRcp_f32x4(Tsimd_f32x4_t a) { return _mm_rcp_ps(a); }

static inline Tsimd_f32x4_t tfSimdSub_f32x4(Tsimd_f32x4_t a, Tsimd_f32x4_t b) { return _mm_sub_ps(a, b); }
static inline Tsimd_f32x4_t tfSimdAdd_f32x4(Tsimd_f32x4_t a, Tsimd_f32x4_t b) { return _mm_add_ps(a, b); }
static inline Tsimd_f32x4_t tfSimdMul_f32x4(Tsimd_f32x4_t a, Tsimd_f32x4_t b) { return _mm_mul_ps(a, b); }
static inline Tsimd_f32x4_t tfSimdDiv_f32x4(Tsimd_f32x4_t a, Tsimd_f32x4_t b) { return _mm_div_ps(a, b); }
static inline Tsimd_f32x4_t tfSimdAbs_f32x4(Tsimd_f32x4_t a) { 
    const __m128 signMask = tfSimd_i32x4_To_f32x4(tfSimdSplat_i32_i32x4(0x7FFFFFFF));
    return tfSimdAnd_f32x4(a, signMask);
}
static inline Tsimd_f32x4_t tfSimdMadd_f32x4(Tsimd_f32x4_t a, Tsimd_f32x4_t b, Tsimd_f32x4_t c) {
    return tfSimdAdd_f32x4(tfSimdMul_f32x4(a, b), c);
}

static inline Tsimd_f32x4_t tfSimdNot_f32x4(Tsimd_f32x4_t value) {
    return _mm_andnot_ps(value, tfSimd_i32x4_To_f32x4(tfSimdSplat_i32_i32x4((int32_t)(0xFFFFFFFF))));
}
static inline Tsimd_f32x4_t tfSimdAnd_f32x4(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) { return _mm_and_ps(arg1, arg2); }
static inline Tsimd_f32x4_t tfSimdAndNot_f32x4(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) { return _mm_andnot_ps(arg1, arg2); }
static inline Tsimd_f32x4_t tfSimdOr_f32x4(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) { return _mm_or_ps(arg1, arg2); }
static inline Tsimd_f32x4_t tfSimdXor_f32x4(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) { return _mm_xor_ps(arg1, arg2); }

static inline Tsimd_f32x4_t tfSimdCmpEq_f32x4(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) { return _mm_cmpeq_ps(arg1, arg2); }
static inline Tsimd_f32x4_t tfSimdCmpNeq_f32x4(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) { return _mm_cmpneq_ps(arg1, arg2); }
static inline Tsimd_f32x4_t tfSimdCmpGt_f32x4(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) { return _mm_cmpgt_ps(arg1, arg2); }
static inline Tsimd_f32x4_t tfSimdCmpGtEq_f32x4(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) { return _mm_cmpge_ps(arg1, arg2); }
static inline Tsimd_f32x4_t tfSimdCmpLt_f32x4(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) { return _mm_cmplt_ps(arg1, arg2); }
static inline Tsimd_f32x4_t tfSimdCmpLtEq_f32x4(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) { return _mm_cmple_ps(arg1, arg2); }

static inline bool tfSimdCmpAllEq_f32x4(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) {
    return (_mm_movemask_ps(tfSimdCmpEq_f32x4(arg1, arg2)) & 0xf) == 0xf;
}
static inline bool tfSimdCmpAllNeq_f32x4(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) {
    return (_mm_movemask_ps(tfSimdCmpNeq_f32x4(arg1, arg2)) & 0xf) == 0xf;
}
static inline bool tfSimdCmpAllGt_f32x4(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) {
    return (_mm_movemask_ps(tfSimdCmpGt_f32x4(arg1, arg2)) & 0xf) == 0xf;
}
static inline bool tfSimdCmpAllGtEq_f32x4(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) {
    return (_mm_movemask_ps(tfSimdCmpGtEq_f32x4(arg1, arg2)) & 0xf) == 0xf;
}
static inline bool tfSimdCmpAllLt_f32x4(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) {
    return (_mm_movemask_ps(tfSimdCmpLt_f32x4(arg1, arg2)) & 0xf) == 0xf;
}
static inline bool tfSimdCmpAllLtEq_f32x4(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) {
    return (_mm_movemask_ps(tfSimdCmpLtEq_f32x4(arg1, arg2)) & 0xf) == 0xf;
}

// Tsimd_i32x4_t
static inline Tsimd_i32x4_t tfSimdLoad_i32x4(int32_t x, int32_t y, int32_t z, int32_t w) { return _mm_set_epi32(w, z, y, x); }

static inline Tsimd_i32x4_t tfSimdSplat_i32_i32x4(int value) { return _mm_set1_epi32(value); }
static inline Tsimd_i32x4_t tfSimdSplat_i32x4_i32x4(Tsimd_i32x4_t value, int index) {
    ASSERT(index < 4);
    switch(index) {
        case 0:return _mm_shuffle_epi32(value, _MM_SHUFFLE(0, 0, 0, 0));
        case 1:return _mm_shuffle_epi32(value, _MM_SHUFFLE(1, 1, 1, 1));
        case 2:return _mm_shuffle_epi32(value, _MM_SHUFFLE(2, 2, 2, 2));
        case 3:return _mm_shuffle_epi32(value, _MM_SHUFFLE(3, 3, 3, 3));
    }
    return {};
}

static inline int32_t tfSimdGet_i32x4(Tsimd_i32x4_t value, int index) {
    ASSERT(index < 4);
    return _mm_cvtsi128_si32(tfSimdSplat_i32x4_i32x4(value, index));
}

static inline Tsimd_i32x4_t tfSimd_f32x4_To_i32x4(Tsimd_f32x4_t a) { return _mm_castps_si128(a); }
static inline Tsimd_f32x4_t tfSimd_i32x4_To_f32x4(Tsimd_i32x4_t a) { return _mm_castsi128_ps(a); }

static inline Tsimd_i32x4_t tfSimdAdd_i32x4(Tsimd_i32x4_t a, Tsimd_i32x4_t b) { return _mm_add_epi32(a, b); }
static inline Tsimd_i32x4_t tfSimdMul_i32x4(Tsimd_i32x4_t a, Tsimd_i32x4_t b) { return _mm_mul_epi32(a, b); }
static inline Tsimd_i32x4_t tfSimdAbs_i32x4(Tsimd_i32x4_t a) { return _mm_abs_epi32(a); }
static inline Tsimd_i32x4_t tfSimdMadd_i32x4(Tsimd_i32x4_t a, Tsimd_i32x4_t b, Tsimd_i32x4_t c) {
    return tfSimdAdd_i32x4(tfSimdMul_i32x4(a, b), c);
}
static inline Tsimd_i32x4_t tfSimdNot_i32x4(Tsimd_i32x4_t value) { return _mm_andnot_si128(value, tfSimdSplat_i32_i32x4(0xFFFFFFFF)); }
static inline Tsimd_i32x4_t tfSimdAnd_i32x4(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2) { return _mm_and_si128(arg1, arg2); }
static inline Tsimd_i32x4_t tfSimdAndNot_i32x4(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2) { return _mm_andnot_si128(arg1, arg2); }
static inline Tsimd_i32x4_t tfSimdOr_i32x4(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2) { return _mm_or_si128(arg1, arg2); }
static inline Tsimd_i32x4_t tfSimdXor_i32x4(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2) { return _mm_xor_si128(arg1, arg2); }

static inline Tsimd_i32x4_t tfSimdCmpEq_i32x4(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2) { return _mm_cmpeq_epi32(arg1, arg2); }
static inline Tsimd_i32x4_t tfSimdCmpNeq_i32x4(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2) {
    return tfSimdNot_i32x4(tfSimdCmpEq_i32x4(arg1, arg2));
}
static inline Tsimd_i32x4_t tfSimdCmpGt_i32x4(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2) { return _mm_cmpgt_epi32(arg1, arg2); }

static inline Tsimd_i32x4_t tfSimdCmpGtEq_i32x4(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2) {
    return _mm_or_si128(_mm_cmpgt_epi32(arg1, arg2), _mm_cmpeq_epi32(arg1, arg2));
}
static inline Tsimd_i32x4_t tfSimdCmpLt_i32x4(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2) { return _mm_cmplt_epi32(arg1, arg2); }
static inline Tsimd_i32x4_t tfSimdCmpLtEq_i32x4(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2) { 
    return _mm_or_si128(_mm_cmplt_epi32(arg1, arg2), _mm_cmpeq_epi32(arg1, arg2));
}

static inline bool tfSimdCmpAllEq_i32x4(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2) {
    return (_mm_movemask_epi8(tfSimdCmpEq_i32x4(arg1, arg2)) & 0xFFFF) == 0xFFFF;
}
static inline bool tfSimdCmpAllNeq_i32x4(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2) {
    return (_mm_movemask_epi8(tfSimdCmpNeq_i32x4(arg1, arg2)) & 0xFFFF) == 0xFFFF;
}
static inline bool tfSimdCmpAllGt_i32x4(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2) {
    return (_mm_movemask_epi8(tfSimdCmpGt_i32x4(arg1, arg2))& 0xFFFF) == 0xFFFF;
}
static inline bool tfSimdCmpAllGtEq_i32x4(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2) {
    return (_mm_movemask_epi8(tfSimdCmpGtEq_i32x4(arg1, arg2))& 0xFFFF) == 0xFFFF;
}
static inline bool tfSimdCmpAllLt_i32x4(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2) {
    return (_mm_movemask_epi8(tfSimdCmpLt_i32x4(arg1, arg2)) & 0xFFFF) == 0xFFFF; 
}
static inline bool tfSimdCmpAllLtEq_i32x4(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2) {
    return (_mm_movemask_epi8(tfSimdCmpLtEq_i32x4(arg1, arg2))& 0xFFFF) == 0xFFFF;  
}

// DELETE everything below
//static inline Tsimd_f32x4_t tfS32x4FReplaceIndex0(Tsimd_f32x4_t input, Tsimd_f32x4_t value) {
//    return _mm_blend_ps(input, value, 0b0001);
//}
//static inline Tsimd_f32x4_t tfS32x4FReplaceIndex1(Tsimd_f32x4_t input, Tsimd_f32x4_t value){
//    return _mm_blend_ps(input, value, 0b0010);
//}
//static inline Tsimd_f32x4_t tfS32x4FReplaceIndex2(Tsimd_f32x4_t input, Tsimd_f32x4_t value){
//    return _mm_blend_ps(input, value, 0b0100);
//}
//static inline Tsimd_f32x4_t tfS32x4FReplaceIndex3(Tsimd_f32x4_t input, Tsimd_f32x4_t value){
//    return _mm_blend_ps(input, value, 0b1000);
//}
//
//
//static inline Tsimd_f32x4_t tfS32x4FReplaceIndex0ByValue(Tsimd_f32x4_t input, float value) {
//    return _mm_blend_ps(input, tfS32x4FSplat(value), 0b0001);
//}
//static inline Tsimd_f32x4_t tfSimdFloat4ReplaceIndex1ByValue(Tsimd_f32x4_t input, float value) {
//    return _mm_blend_ps(input, tfS32x4FSplat(value), 0b0010);
//}
//static inline Tsimd_f32x4_t tfSimd4fReplaceIndex2ByValue(Tsimd_f32x4_t input, float value) {
//    return _mm_blend_ps(input, tfS32x4FSplat(value), 0b0100);
//}
//static inline Tsimd_f32x4_t tfSimd4fReplaceIndex3ByValue(Tsimd_f32x4_t input, float value) {
//    return _mm_blend_ps(input, tfS32x4FSplat(value), 0b1000);
//}
//
//inline Tsimd_i32x4_t   tfSimd4iSelect(Tsimd_i32x4_t arg0, Tsimd_i32x4_t arg1, Tsimd_i32x4_t mask) { return _mm_blendv_epi8(arg0, arg1, mask); }
//inline Tsimd_f32x4_t tfSimd4fSelect(Tsimd_f32x4_t arg0, Tsimd_f32x4_t arg1, Tsimd_f32x4_t mask) {
//    return _mm_blendv_ps(arg0, arg1, mask);
//}
//
//inline Tsimd_f32x4_t tfSimd4fZero() { return _mm_setzero_ps(); }
//inline Tsimd_i32x4_t   tfSimd4iZero() { return _mm_setzero_si128(); }
//
//inline Tsimd_i32x4_t tfSimd4iNot(Tsimd_i32x4_t value) { return _mm_andnot_si128(value, _mm_set1_epi32(TF_SIMDI_MAX)); }
//inline Tsimd_i32x4_t tfSimd4iAnd(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2) { return _mm_and_si128(arg1, arg2); }
//inline Tsimd_i32x4_t tfSimd4iAndNot(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2) { return _mm_andnot_si128(arg1, arg2); }
//inline Tsimd_i32x4_t tfSimd4iOr(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2) { return _mm_or_si128(arg1, arg2); }
//inline Tsimd_i32x4_t tfSimd4iXor(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2) { return _mm_xor_si128(arg1, arg2); }
//
//inline Tsimd_f32x4_t tfSimd4fNot(Tsimd_f32x4_t value) { return _mm_andnot_ps(value, _mm_set1_ps((float)(TF_SIMDF_MAX))); }
//inline Tsimd_f32x4_t tfSimd4fAnd(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) { return _mm_and_ps(arg1, arg2); }
//inline Tsimd_f32x4_t tfSimd4fAndNot(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) { return _mm_andnot_ps(arg1, arg2); }
//inline Tsimd_f32x4_t tfSimd4fOr(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) { return _mm_or_ps(arg1, arg2); }
//inline Tsimd_f32x4_t tfSimd4fXor(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) { return _mm_xor_ps(arg1, arg2); }
//
//inline Tsimd_f32x4_t tfSimd4fFloor(Tsimd_f32x4_t value) { return _mm_floor_ps(value); }
//inline Tsimd_f32x4_t tfSimd4fCeil(Tsimd_f32x4_t value) { return _mm_ceil_ps(value); }
//inline Tsimd_f32x4_t tfSimd4fRound(Tsimd_f32x4_t value) { return _mm_round_ps(value, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC); }
//inline Tsimd_f32x4_t tfSimd4fTruncate(Tsimd_f32x4_t value) { return tfSimd4iToSimd4f(tfSimd4fToSimd4i(value)); }
//inline Tsimd_f32x4_t tfSimd4fMin(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) { return _mm_min_ps(arg1, arg2); }
//inline Tsimd_f32x4_t tfSimd4fMax(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) { return _mm_max_ps(arg1, arg2); }
//inline Tsimd_f32x4_t tfSimd4fClamp(Tsimd_f32x4_t value, Tsimd_f32x4_t min, Tsimd_f32x4_t max) {
//    return tfSimd4fMax(min, tfSimd4fMin(value, max));
//}
//
//inline Tsimd_i32x4_t tfSimd4fToSimd4i(Tsimd_f32x4_t value) { return _mm_castps_si128(value); }
//inline Tsimd_f32x4_t tfSimd4iToSimd4f(Tsimd_i32x4_t value) { return _mm_castsi128_ps(value); }
//
//inline float tfSimd4fSelectIndex0(Tsimd_f32x4_t value) { return _mm_cvtss_f32(value); }
//inline float tfSimd4fSelectIndex1(Tsimd_f32x4_t value) { return tfSimd4fSelectIndex0(tfSimd4fSplatIndex1(value)); }
//inline float tfSimd4fSelectIndex2(Tsimd_f32x4_t value) { return tfSimd4fSelectIndex0(tfSimd4fSplatIndex2(value)); }
//inline float tfSimd4fSelectIndex3(Tsimd_f32x4_t value) { return tfSimd4fSelectIndex0(tfSimd4fSplatIndex3(value)); }
//
//inline Tsimd_f32x4_t tfSimd4fAdd(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) { return _mm_add_ps(arg1, arg2); }
//inline Tsimd_f32x4_t tfSimd4fSub(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) { return _mm_sub_ps(arg1, arg2); }
//inline Tsimd_f32x4_t tfSimd4fMul(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) { return _mm_mul_ps(arg1, arg2); }
//inline Tsimd_f32x4_t tfSimd4fMadd(Tsimd_f32x4_t mul1, Tsimd_f32x4_t mul2, Tsimd_f32x4_t add) {
//#if 0
//    return _mm_fmadd_ps(mul1, mul2, add); // Requires FMA CPUID
//#else
//    return tfSimd4fAdd(tfSimd4fMul(mul1, mul2), add);
//#endif
//}
//
//inline Tsimd_f32x4_t tfSimdFloat4x32Div(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) { return _mm_div_ps(arg1, arg2); }
//
//inline Tsimd_f32x4_t tfSimd4fAbs(Tsimd_f32x4_t value) {
//    const Tsimd_f32x4_t signMask = tfSimd4iToSimd4f(tfSimd4iSplat(0x7FFFFFFF));
//    return _mm_and_ps(value, signMask);
//}
//inline Tsimd_f32x4_t tfSimdFloat4x32Load(float x, float y, float z, float w) { return _mm_set_ps(w, z, y, x); }
//inline Tsimd_i32x4_t tfSimdInt4x32Load(int32_t x, int32_t y, int32_t z, int32_t w) { return _mm_set_epi32(w, z, y, x); }
//
//inline Tsimd_f32x2_t tfSimd4fToSimd2f(Tsimd_f32x4_t value) { return value; }
//inline Tsimd_f32x3_t tfSimd4fToSimd3f(Tsimd_f32x4_t value) { return value; }
//
//inline Tsimd_f32x4_t tfSimd4fSplatIndex0(Tsimd_f32x4_t value) { return _mm_shuffle_ps(value, value, _MM_SHUFFLE(0, 0, 0, 0)); }
//inline Tsimd_f32x4_t tfSimd4fSplatIndex1(Tsimd_f32x4_t value) { return _mm_shuffle_ps(value, value, _MM_SHUFFLE(1, 1, 1, 1)); }
//inline Tsimd_f32x4_t tfSimd4fSplatIndex2(Tsimd_f32x4_t value) { return _mm_shuffle_ps(value, value, _MM_SHUFFLE(2, 2, 2, 2)); }
//inline Tsimd_f32x4_t tfSimd4fSplatIndex3(Tsimd_f32x4_t value) { return _mm_shuffle_ps(value, value, _MM_SHUFFLE(3, 3, 3, 3)); }
//
//inline Tsimd_i32x4_t tfSimd4iSplat(int32_t value) { return _mm_set1_epi32(value); }
//inline Tsimd_f32x4_t tfSimd4fSplat(float value) { return _mm_set1_ps(value); }
//
//inline Tsimd_f32x4_t tfSimd4fCmpEq(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) { return _mm_cmpeq_ps(arg1, arg2); }
//inline Tsimd_f32x4_t tfSimd4fCmpNeq(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) { return _mm_cmpneq_ps(arg1, arg2); }
//inline Tsimd_f32x4_t tfSimd4fCmpGt(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) { return _mm_cmpgt_ps(arg1, arg2); }
//inline Tsimd_f32x4_t tfSimd4fCmpGtEq(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) { return _mm_cmpge_ps(arg1, arg2); }
//inline Tsimd_f32x4_t tfSimd4fCmpLt(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) { return _mm_cmplt_ps(arg1, arg2); }
//inline Tsimd_f32x4_t tfSimd4fCmpLtEq(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) { return _mm_cmple_ps(arg1, arg2); }
//
//inline Tsimd_i32x4_t tfSimd4iCmpEq(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2) { return _mm_cmpeq_epi32(arg1, arg2); }
//inline Tsimd_i32x4_t tfSimd4iCmpNeq(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2) {
//    return _mm_xor_si128(_mm_cmpeq_epi32(arg1, arg2), _mm_set1_epi32((int32_t)0xFFFFFFFF));
//}
//inline Tsimd_i32x4_t tfSimd4iCmpGt(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2) { return _mm_cmpgt_epi32(arg1, arg2); }
//inline Tsimd_i32x4_t tfSimd4iCmpGtEq(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2) {
//    return _mm_or_si128(_mm_cmpgt_epi32(arg1, arg2), _mm_cmpeq_epi32(arg1, arg2));
//}
//inline Tsimd_i32x4_t tfSimd4iCmpLt(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2) { return _mm_cmplt_epi32(arg1, arg2); }
//inline Tsimd_i32x4_t tfSimd4iCmpLtEq(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2) {
//    return _mm_or_si128(_mm_cmplt_epi32(arg1, arg2), _mm_cmpeq_epi32(arg1, arg2));
//}
//inline bool tfSimd4fCmpAllLt(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) {
//    Tsimd_f32x4_t compare = tfSimd4fCmpLt(arg1, arg2);
//    return (_mm_movemask_ps(compare) & 0xf) == 0xf;
//}
//
//inline bool tfSimd4fCmpAllGt(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) {
//    Tsimd_f32x4_t compare = tfSimd4fCmpGt(arg1, arg2);
//    return (_mm_movemask_ps(compare) & 0xf) == 0xf;
//}
//
//inline bool tfSimd4fCmpAllEq(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) {
//    Tsimd_f32x4_t compare = tfSimd4fCmpEq(arg1, arg2);
//    return (_mm_movemask_ps(compare) & 0xf) == 0xf;
//}
//
//inline bool tfSimd4iCmpAllEq(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2) {
//    const Tsimd_i32x4_t compare = tfSimd4iCmpEq(arg1, arg2);
//    return (_mm_movemask_epi8(compare) & 0xf) == 0xf;
//}
