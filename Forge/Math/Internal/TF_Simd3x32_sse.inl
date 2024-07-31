#if defined(__CLANGD__)
#define TF_FEATURE_CPU_SSE  
#include "Forge/TF_Config.h"
#include "../TF_Simd3x32.h"
#endif

inline TSimdInt32x3   tfSimd3iSelect(TSimdInt32x3 arg0, TSimdInt32x3 arg1, TSimdInt32x3 mask) { return _mm_blendv_epi8(arg0, arg1, mask); }
inline TSimdFloat32x3 tfSimd3fSelect(TSimdFloat32x3 arg0, TSimdFloat32x3 arg1, TSimdFloat32x3 mask) {
    return _mm_blendv_ps(arg0, arg1, mask);
}

inline TSimdFloat32x3 tfSimd3fZero() { return _mm_setzero_ps(); }
inline TSimdInt32x3   tfSimd3iZero() { return _mm_setzero_si128(); }

inline TSimdInt32x3 tfSimd3iNot(TSimdInt32x3 value) { return _mm_andnot_si128(value, _mm_set1_epi32(TF_SIMDI_MAX)); }
inline TSimdInt32x3 tfSimd3iAnd(TSimdInt32x3 arg1, TSimdInt32x3 arg2) { return _mm_and_si128(arg1, arg2); }
inline TSimdInt32x3 tfSimd3iAndNot(TSimdInt32x3 arg1, TSimdInt32x3 arg2) { return _mm_andnot_si128(arg1, arg2); }
inline TSimdInt32x3 tfSimd3iOr(TSimdInt32x3 arg1, TSimdInt32x3 arg2) { return _mm_or_si128(arg1, arg2); }
inline TSimdInt32x3 tfSimd3iXor(TSimdInt32x3 arg1, TSimdInt32x3 arg2) { return _mm_xor_si128(arg1, arg2); }

inline TSimdFloat32x3 tfSimd3fNot(TSimdFloat32x3 value) {
    const TSimdFloat32x3 invert = tfSimd3fSplat((float)(0xFFFFFFFF));
    return _mm_andnot_ps(value, invert);
}
inline TSimdFloat32x3 tfSimd3fAnd(TSimdFloat32x3 arg1, TSimdFloat32x3 arg2) { return _mm_and_ps(arg1, arg2); }
inline TSimdFloat32x3 tfSimd3fAndNot(TSimdFloat32x3 arg1, TSimdFloat32x3 arg2) { return _mm_andnot_ps(arg1, arg2); }
inline TSimdFloat32x3 tfSimd3fOr(TSimdFloat32x3 arg1, TSimdFloat32x3 arg2) { return _mm_or_ps(arg1, arg2); }
inline TSimdFloat32x3 tfSimd3fXor(TSimdFloat32x3 arg1, TSimdFloat32x3 arg2) { return _mm_xor_ps(arg1, arg2); }

inline TSimdFloat32x3 tfSimd3fFloor(TSimdFloat32x3 value) { return _mm_floor_ps(value); }
inline TSimdFloat32x3 tfSimd3fCeil(TSimdFloat32x3 value) { return _mm_ceil_ps(value); }
inline TSimdFloat32x3 tfSimd3fRound(TSimdFloat32x3 value) { return _mm_round_ps(value, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC); }
inline TSimdFloat32x3 tfSimd3fTruncate(TSimdFloat32x3 value) { return tfSimd3iToSimd3f(tfSimd3fToSimd3i(value)); }
inline TSimdFloat32x3 tfSimd3fMin(TSimdFloat32x3 arg1, TSimdFloat32x3 arg2) { return _mm_min_ps(arg1, arg2); }
inline TSimdFloat32x3 tfSimd3fMax(TSimdFloat32x3 arg1, TSimdFloat32x3 arg2) { return _mm_max_ps(arg1, arg2); }
inline TSimdFloat32x3 tfSimd3fClamp(TSimdFloat32x3 value, TSimdFloat32x3 min, TSimdFloat32x3 max) {
    return tfSimd3fMax(min, tfSimd3fMin(value, max));
}

inline TSimdInt32x3 tfSimd3fToSimd3i(TSimdFloat32x3 value) { return _mm_castps_si128(value); }

inline TSimdFloat32x3 tfSimd3iToSimd3f(TSimdInt32x3 value) { return _mm_castsi128_ps(value); }

inline float tfSimd3fSelectIndex0(TSimdFloat32x3 value) { return _mm_cvtss_f32(value); }

inline float tfSimd3fSelectIndex1(TSimdFloat32x3 value) { return tfSimd3fSelectIndex0(tfSimd3fSplatIndex1(value)); }

inline float tfSimd3fSelectIndex2(TSimdFloat32x3 value) { return tfSimd3fSelectIndex0(tfSimd3fSplatIndex2(value)); }

inline TSimdFloat32x3 tfSimd3fAdd(TSimdFloat32x3 arg1, TSimdFloat32x3 arg2) { return _mm_add_ps(arg1, arg2); }
inline TSimdFloat32x3 tfSimd3fSub(TSimdFloat32x3 arg1, TSimdFloat32x3 arg2) { return _mm_sub_ps(arg1, arg2); }
inline TSimdFloat32x3 tfSimd3fMul(TSimdFloat32x3 arg1, TSimdFloat32x3 arg2) { return _mm_mul_ps(arg1, arg2); }
inline TSimdFloat32x3 tfSimd3fMadd(TSimdFloat32x3 mul1, TSimdFloat32x3 mul2, TSimdFloat32x3 add) {
#if 0
    return _mm_fmadd_ps(mul1, mul2, add); // Requires FMA CPUID
#else
    return tfSimd3fAdd(tfSimd3fMul(mul1, mul2), add);
#endif
}
inline TSimdFloat32x3 tfSimd3fDiv(TSimdFloat32x3 arg1, TSimdFloat32x3 arg2) { return _mm_div_ps(arg1, arg2); }

inline TSimdFloat32x3 tfSimd3fAbs(TSimdFloat32x3 value) {
    const TSimdFloat32x4 signMask = tfSimd3iToSimd3f(tfSimd3iSplat(0x7FFFFFFF));
    return _mm_and_ps(value, signMask);
}

inline TSimdFloat32x3 tfSimdFloat3Load(float x, float y, float z) { return _mm_set_ps(0.0f, z, y, x); }

inline TSimdInt32x3 tfSimdInt3Load(int32_t x, int32_t y, int32_t z) { return _mm_set_epi32(0.0f, x, y, z); }

inline TSimdFloat32x2 tfSimd3fToSimd2f(TSimdFloat32x3 value) { return value; }

static inline TSimdFloat32x4 tfSimdFloat3To4Splat0(TSimdFloat32x3 value) { return _mm_shuffle_ps(value, value, _MM_SHUFFLE(0, 0, 0, 0)); }
static inline TSimdFloat32x4 tfSimdFloat3To4Splat1(TSimdFloat32x3 value) { return _mm_shuffle_ps(value, value, _MM_SHUFFLE(1, 1, 1, 1)); }
static inline TSimdFloat32x4 tfSimdFloat3To4Splat2(TSimdFloat32x3 value) { return _mm_shuffle_ps(value, value, _MM_SHUFFLE(2, 2, 2, 2)); }

inline TSimdFloat32x3 tfSimd3fSplatIndex0(TSimdFloat32x3 value) { return _mm_shuffle_ps(value, value, _MM_SHUFFLE(0, 0, 0, 0)); }
inline TSimdFloat32x3 tfSimd3fSplatIndex1(TSimdFloat32x3 value) { return _mm_shuffle_ps(value, value, _MM_SHUFFLE(1, 1, 1, 1)); }
inline TSimdFloat32x3 tfSimd3fSplatIndex2(TSimdFloat32x3 value) { return _mm_shuffle_ps(value, value, _MM_SHUFFLE(2, 2, 2, 2)); }

inline TSimdInt32x3 tfSimd3iSplat(int32_t value) { return _mm_set1_epi32(value); }
inline TSimdFloat32x3 tfSimd3fSplat(float value) { return _mm_set1_ps(value); }

inline TSimdInt32x3 tfSimd3iCmpEq(TSimdInt32x3 arg1, TSimdInt32x3 arg2) { return _mm_cmpeq_epi32(arg1, arg2); }
inline TSimdInt32x3 tfSimd3iCmpNeq(TSimdInt32x3 arg1, TSimdInt32x3 arg2) {
    return _mm_xor_si128(_mm_cmpeq_epi32(arg1, arg2), _mm_set1_epi32((int32_t)0xFFFFFFFF));
}
inline TSimdInt32x3 tfSimd3iCmpGt(TSimdInt32x3 arg1, TSimdInt32x3 arg2) { return _mm_cmpgt_epi32(arg1, arg2); }
inline TSimdInt32x3 tfSimd3iCmpGtEq(TSimdInt32x3 arg1, TSimdInt32x3 arg2) {
    return _mm_or_si128(_mm_cmpgt_epi32(arg1, arg2), _mm_cmpeq_epi32(arg1, arg2));
}
inline TSimdInt32x3 tfSimd3iCmpLt(TSimdInt32x3 arg1, TSimdInt32x3 arg2) { return _mm_cmplt_epi32(arg1, arg2); }
inline TSimdInt32x3 tfSimd3iCmpLtEq(TSimdInt32x3 arg1, TSimdInt32x3 arg2) {
    return _mm_or_si128(_mm_cmplt_epi32(arg1, arg2), _mm_cmpeq_epi32(arg1, arg2));
}
inline bool tfSimd3fCmpAllEq(TSimdFloat32x3 arg1, TSimdFloat32x3 arg2) {
    TSimdFloat32x3 compare = tfSimd3fCmpEq(arg1, arg2);
    return (_mm_movemask_ps(compare) & 0b0111) == 0b0111;
}

inline bool tfSimd3iCmpAllEq(TSimdInt32x3 arg1, TSimdInt32x3 arg2) {
    const TSimdInt32x3 compare = tfSimd3iCmpEq(arg1, arg2);
    return (_mm_movemask_epi8(compare) & 0b0111) == 0b0111;
}
