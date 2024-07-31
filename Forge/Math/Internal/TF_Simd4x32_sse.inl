#if defined(__CLANGD__)
#define TF_FEATURE_CPU_SSE  
#include "Forge/TF_Config.h"
#include "../TF_Simd4x32.h"
#endif

static inline TSimdFloat32x4 tfSimd4fReplaceIndex0ByValue(TSimdFloat32x4 input, float value) {
    return _mm_blend_ps(input, tfSimd4fSplat(value), 0b0001);
}
static inline TSimdFloat32x4 tfSimd4fReplaceIndex1ByValue(TSimdFloat32x4 input, float value) {
    return _mm_blend_ps(input, tfSimd4fSplat(value), 0b0010);
}
static inline TSimdFloat32x4 tfSimd4fReplaceIndex2ByValue(TSimdFloat32x4 input, float value) {
    return _mm_blend_ps(input, tfSimd4fSplat(value), 0b0100);
}
static inline TSimdFloat32x4 tfSimd4fReplaceIndex3ByValue(TSimdFloat32x4 input, float value) {
    return _mm_blend_ps(input, tfSimd4fSplat(value), 0b1000);
}

inline TSimdInt32x4   tfSimd4iSelect(TSimdInt32x4 arg0, TSimdInt32x4 arg1, TSimdInt32x4 mask) { return _mm_blendv_epi8(arg0, arg1, mask); }
inline TSimdFloat32x4 tfSimd4fSelect(TSimdFloat32x4 arg0, TSimdFloat32x4 arg1, TSimdFloat32x4 mask) {
    return _mm_blendv_ps(arg0, arg1, mask);
}

inline TSimdFloat32x4 tfSimd4fZero() { return _mm_setzero_ps(); }
inline TSimdInt32x4   tfSimd4iZero() { return _mm_setzero_si128(); }

inline TSimdInt32x4 tfSimd4iNot(TSimdInt32x4 value) { return _mm_andnot_si128(value, _mm_set1_epi32(TF_SIMDI_MAX)); }
inline TSimdInt32x4 tfSimd4iAnd(TSimdInt32x4 arg1, TSimdInt32x4 arg2) { return _mm_and_si128(arg1, arg2); }
inline TSimdInt32x4 tfSimd4iAndNot(TSimdInt32x4 arg1, TSimdInt32x4 arg2) { return _mm_andnot_si128(arg1, arg2); }
inline TSimdInt32x4 tfSimd4iOr(TSimdInt32x4 arg1, TSimdInt32x4 arg2) { return _mm_or_si128(arg1, arg2); }
inline TSimdInt32x4 tfSimd4iXor(TSimdInt32x4 arg1, TSimdInt32x4 arg2) { return _mm_xor_si128(arg1, arg2); }

inline TSimdFloat32x4 tfSimd4fNot(TSimdFloat32x4 value) { return _mm_andnot_ps(value, _mm_set1_ps((float)(TF_SIMDF_MAX))); }
inline TSimdFloat32x4 tfSimd4fAnd(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2) { return _mm_and_ps(arg1, arg2); }
inline TSimdFloat32x4 tfSimd4fAndNot(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2) { return _mm_andnot_ps(arg1, arg2); }
inline TSimdFloat32x4 tfSimd4fOr(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2) { return _mm_or_ps(arg1, arg2); }
inline TSimdFloat32x4 tfSimd4fXor(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2) { return _mm_xor_ps(arg1, arg2); }

inline TSimdFloat32x4 tfSimd4fFloor(TSimdFloat32x4 value) { return _mm_floor_ps(value); }
inline TSimdFloat32x4 tfSimd4fCeil(TSimdFloat32x4 value) { return _mm_ceil_ps(value); }
inline TSimdFloat32x4 tfSimd4fRound(TSimdFloat32x4 value) { return _mm_round_ps(value, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC); }
inline TSimdFloat32x4 tfSimd4fTruncate(TSimdFloat32x4 value) { return tfSimd4iToSimd4f(tfSimd4fToSimd4i(value)); }
inline TSimdFloat32x4 tfSimd4fMin(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2) { return _mm_min_ps(arg1, arg2); }
inline TSimdFloat32x4 tfSimd4fMax(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2) { return _mm_max_ps(arg1, arg2); }
inline TSimdFloat32x4 tfSimd4fClamp(TSimdFloat32x4 value, TSimdFloat32x4 min, TSimdFloat32x4 max) {
    return tfSimd4fMax(min, tfSimd4fMin(value, max));
}

inline TSimdInt32x4 tfSimd4fToSimd4i(TSimdFloat32x4 value) { return _mm_castps_si128(value); }

inline TSimdFloat32x4 tfSimd4iToSimd4f(TSimdInt32x4 value) { return _mm_castsi128_ps(value); }

inline float tfSimd4fSelectIndex0(TSimdFloat32x4 value) { return _mm_cvtss_f32(value); }
inline float tfSimd4fSelectIndex1(TSimdFloat32x4 value) { return tfSimd4fSelectIndex0(tfSimd4fSplatIndex1(value)); }
inline float tfSimd4fSelectIndex2(TSimdFloat32x4 value) { return tfSimd4fSelectIndex0(tfSimd4fSplatIndex2(value)); }
inline float tfSimd4fSelectIndex3(TSimdFloat32x4 value) { return tfSimd4fSelectIndex0(tfSimd4fSplatIndex3(value)); }

inline TSimdFloat32x4 tfSimd4fAdd(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2) { return _mm_add_ps(arg1, arg2); }
inline TSimdFloat32x4 tfSimd4fSub(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2) { return _mm_sub_ps(arg1, arg2); }
inline TSimdFloat32x4 tfSimd4fMul(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2) { return _mm_mul_ps(arg1, arg2); }
inline TSimdFloat32x4 tfSimd4fMadd(TSimdFloat32x4 mul1, TSimdFloat32x4 mul2, TSimdFloat32x4 add) {
#if 0
    return _mm_fmadd_ps(mul1, mul2, add); // Requires FMA CPUID
#else
    return tfSimd4fAdd(tfSimd4fMul(mul1, mul2), add);
#endif
}

inline TSimdFloat32x4 tfSimd4fDiv(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2) { return _mm_div_ps(arg1, arg2); }

inline TSimdFloat32x4 tfSimd4fAbs(TSimdFloat32x4 value) {
    const TSimdFloat32x4 signMask = tfSimd4iToSimd4f(tfSimd4iSplat(0x7FFFFFFF));
    return _mm_and_ps(value, signMask);
}
inline TSimdFloat32x4 tfSimdFloat4Load(float x, float y, float z, float w) { return _mm_set_ps(w, z, y, x); }
inline TSimdInt32x4 tfSimdInt4Load(int32_t x, int32_t y, int32_t z, int32_t w) { return _mm_set_epi32(w, z, y, x); }

inline TSimdFloat32x2 tfSimd4fToSimd2f(TSimdFloat32x4 value) { return value; }
inline TSimdFloat32x3 tfSimd4fToSimd3f(TSimdFloat32x4 value) { return value; }

inline TSimdFloat32x4 tfSimd4fSplatIndex0(TSimdFloat32x4 value) { return _mm_shuffle_ps(value, value, _MM_SHUFFLE(0, 0, 0, 0)); }
inline TSimdFloat32x4 tfSimd4fSplatIndex1(TSimdFloat32x4 value) { return _mm_shuffle_ps(value, value, _MM_SHUFFLE(1, 1, 1, 1)); }
inline TSimdFloat32x4 tfSimd4fSplatIndex2(TSimdFloat32x4 value) { return _mm_shuffle_ps(value, value, _MM_SHUFFLE(2, 2, 2, 2)); }
inline TSimdFloat32x4 tfSimd4fSplatIndex3(TSimdFloat32x4 value) { return _mm_shuffle_ps(value, value, _MM_SHUFFLE(3, 3, 3, 3)); }

inline TSimdInt32x4 tfSimd4iSplat(int32_t value) { return _mm_set1_epi32(value); }
inline TSimdFloat32x4 tfSimd4fSplat(float value) { return _mm_set1_ps(value); }

inline TSimdFloat32x4 tfSimd4fCmpEq(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2) { return _mm_cmpeq_ps(arg1, arg2); }
inline TSimdFloat32x4 tfSimd4fCmpNeq(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2) { return _mm_cmpneq_ps(arg1, arg2); }
inline TSimdFloat32x4 tfSimd4fCmpGt(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2) { return _mm_cmpgt_ps(arg1, arg2); }
inline TSimdFloat32x4 tfSimd4fCmpGtEq(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2) { return _mm_cmpge_ps(arg1, arg2); }
inline TSimdFloat32x4 tfSimd4fCmpLt(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2) { return _mm_cmplt_ps(arg1, arg2); }
inline TSimdFloat32x4 tfSimd4fCmpLtEq(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2) { return _mm_cmple_ps(arg1, arg2); }

inline TSimdInt32x4 tfSimd4iCmpEq(TSimdInt32x4 arg1, TSimdInt32x4 arg2) { return _mm_cmpeq_epi32(arg1, arg2); }
inline TSimdInt32x4 tfSimd4iCmpNeq(TSimdInt32x4 arg1, TSimdInt32x4 arg2) {
    return _mm_xor_si128(_mm_cmpeq_epi32(arg1, arg2), _mm_set1_epi32((int32_t)0xFFFFFFFF));
}
inline TSimdInt32x4 tfSimd4iCmpGt(TSimdInt32x4 arg1, TSimdInt32x4 arg2) { return _mm_cmpgt_epi32(arg1, arg2); }
inline TSimdInt32x4 tfSimd4iCmpGtEq(TSimdInt32x4 arg1, TSimdInt32x4 arg2) {
    return _mm_or_si128(_mm_cmpgt_epi32(arg1, arg2), _mm_cmpeq_epi32(arg1, arg2));
}
inline TSimdInt32x4 tfSimd4iCmpLt(TSimdInt32x4 arg1, TSimdInt32x4 arg2) { return _mm_cmplt_epi32(arg1, arg2); }
inline TSimdInt32x4 tfSimd4iCmpLtEq(TSimdInt32x4 arg1, TSimdInt32x4 arg2) {
    return _mm_or_si128(_mm_cmplt_epi32(arg1, arg2), _mm_cmpeq_epi32(arg1, arg2));
}
inline bool tfSimd4fCmpAllLt(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2) {
    TSimdFloat32x4 compare = tfSimd4fCmpLt(arg1, arg2);
    return (_mm_movemask_ps(compare) & 0xf) == 0xf;
}

inline bool tfSimd4fCmpAllGt(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2) {
    TSimdFloat32x4 compare = tfSimd4fCmpGt(arg1, arg2);
    return (_mm_movemask_ps(compare) & 0xf) == 0xf;
}

inline bool tfSimd4fCmpAllEq(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2) {
    TSimdFloat32x4 compare = tfSimd4fCmpEq(arg1, arg2);
    return (_mm_movemask_ps(compare) & 0xf) == 0xf;
}

inline bool tfSimd4iCmpAllEq(TSimdInt32x4 arg1, TSimdInt32x4 arg2) {
    const TSimdInt32x4 compare = tfSimd4iCmpEq(arg1, arg2);
    return (_mm_movemask_epi8(compare) & 0xf) == 0xf;
}
