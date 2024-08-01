#if defined(__CLANGD__)
#define TF_FEATURE_CPU_SSE  
#include "Forge/TF_Config.h"
#include "../TF_Simd32x2.h"
#endif

inline TSimdInt32x2   tfSimd2iSelect(TSimdInt32x2 arg0, TSimdInt32x2 arg1, TSimdInt32x2 mask) { return _mm_blendv_epi8(arg0, arg1, mask); }
inline TSimdFloat32x2 tfSimd2fSelect(TSimdFloat32x2 arg0, TSimdFloat32x2 arg1, TSimdFloat32x2 mask) {
    return _mm_blendv_ps(arg0, arg1, mask);
}

inline TSimdFloat32x2 tfSimd2fZero() { return _mm_setzero_ps(); }
inline TSimdInt32x2   tfSimd2iZero() { return _mm_setzero_si128(); }

inline TSimdInt32x2 tfSimd2iNot(TSimdInt32x2 value) {
    const TSimdInt32x2 invert = tfSimd2iSplat(TF_SIMDI_MAX);
    return _mm_andnot_si128(value, invert);
}
inline TSimdInt32x2 tfSimd2iAnd(TSimdInt32x2 arg1, TSimdInt32x2 arg2) { return _mm_and_si128(arg1, arg2); }
inline TSimdInt32x2 tfSimd2iAndNot(TSimdInt32x2 arg1, TSimdInt32x2 arg2) { return _mm_andnot_si128(arg1, arg2); }
inline TSimdInt32x2 tfSimd2iOr(TSimdInt32x2 arg1, TSimdInt32x2 arg2) { return _mm_or_si128(arg1, arg2); }
inline TSimdInt32x2 tfSimd2iXor(TSimdInt32x2 arg1, TSimdInt32x2 arg2) { return _mm_xor_si128(arg1, arg2); }

inline TSimdFloat32x2 tfSimd2fNot(TSimdFloat32x2 value) {
    const TSimdFloat32x2 invert = tfSimd2fSplat((float)(0xFFFFFFFF));
    return _mm_andnot_ps(value, invert);
}
inline TSimdFloat32x2 tfSimd2fAnd(TSimdFloat32x2 arg1, TSimdFloat32x2 arg2) { return _mm_and_ps(arg1, arg2); }
inline TSimdFloat32x2 tfSimd2fAndNot(TSimdFloat32x2 arg1, TSimdFloat32x2 arg2) { return _mm_andnot_ps(arg1, arg2); }
inline TSimdFloat32x2 tfSimd2fOr(TSimdFloat32x2 arg1, TSimdFloat32x2 arg2) { return _mm_or_ps(arg1, arg2); }
inline TSimdFloat32x2 tfSimd2fXor(TSimdFloat32x2 arg1, TSimdFloat32x2 arg2) { return _mm_xor_ps(arg1, arg2); }

inline TSimdFloat32x2 tfSimd2fFloor(TSimdFloat32x2 value) { return _mm_floor_ps(value); }
inline TSimdFloat32x2 tfSimd2fCeil(TSimdFloat32x2 value) { return _mm_ceil_ps(value); }
inline TSimdFloat32x2 tfSimd2fRound(TSimdFloat32x2 value) { return _mm_round_ps(value, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC); }
inline TSimdFloat32x2 tfSimd2fTruncate(TSimdFloat32x2 value) { return tfSimd2iToSimd2f(tfSimd2fToSimd2i(value)); }
inline TSimdFloat32x2 tfSimd2fMin(TSimdFloat32x2 arg1, TSimdFloat32x2 arg2) { return _mm_min_ps(arg1, arg2); }
inline TSimdFloat32x2 tfSimd2fMax(TSimdFloat32x2 arg1, TSimdFloat32x2 arg2) { return _mm_max_ps(arg1, arg2); }
inline TSimdFloat32x2 tfSimd2fClamp(TSimdFloat32x2 value, TSimdFloat32x2 min, TSimdFloat32x2 max) {
    return tfSimd2fMax(min, tfSimd2fMin(value, max));
}

inline TSimdInt32x2 tfSimd2fToSimd2i(TSimdFloat32x2 value) { return _mm_castps_si128(value); }

inline TSimdFloat32x2 tfSimd2iToSimd2f(TSimdInt32x2 value) { return _mm_castsi128_ps(value); }

inline float tfSimd2fSelectIndex0(TSimdFloat32x2 value) { return _mm_cvtss_f32(value); }

inline float tfSimd2fSelectIndex1(TSimdFloat32x2 value) { return tfSimd2fSelectIndex0(tfSimd2fSplatIndex1(value)); }

inline TSimdFloat32x2 tfSimd2fAdd(TSimdFloat32x2 arg1, TSimdFloat32x2 arg2) { return _mm_add_ps(arg1, arg2); }
inline TSimdFloat32x2 tfSimd2fSub(TSimdFloat32x2 arg1, TSimdFloat32x2 arg2) { return _mm_sub_ps(arg1, arg2); }
inline TSimdFloat32x2 tfSimd2fMul(TSimdFloat32x2 arg1, TSimdFloat32x2 arg2) { return _mm_mul_ps(arg1, arg2); }
inline TSimdFloat32x2 tfSimd2fMadd(TSimdFloat32x2 mul1, TSimdFloat32x2 mul2, TSimdFloat32x2 add) {
#if 0
    return _mm_fmadd_ps(mul1, mul2, add); // Requires FMA CPUID
#else
    return tfSimd2fAdd(tfSimd2fMul(mul1, mul2), add);
#endif
}
inline TSimdFloat32x2 tfSimd2fDiv(TSimdFloat32x2 arg1, TSimdFloat32x2 arg2) { return _mm_div_ps(arg1, arg2); }

inline TSimdFloat32x2 tfSimd2fAbs(TSimdFloat32x2 value) {
    const TSimdFloat32x4 signMask = tfSimd2iToSimd2f(tfSimd2iSplat(0x7FFFFFFF));
    return _mm_and_ps(value, signMask);
}

inline TSimdFloat32x2 tfSimdFloat2Load(float x, float y) { return _mm_set_ps(0.0f, 0.0f, y, x); }

inline TSimdInt32x2 tfSimd2iLoadImmediate(int32_t x, int32_t y) { return _mm_set_epi32(0.0f, 0.0f, x, y); }

inline TSimdFloat32x2 tfSimd2fSplatIndex0(TSimdFloat32x2 value) { return _mm_shuffle_ps(value, value, _MM_SHUFFLE(0, 0, 0, 0)); }
inline TSimdFloat32x2 tfSimd2fSplatIndex1(TSimdFloat32x2 value) { return _mm_shuffle_ps(value, value, _MM_SHUFFLE(1, 1, 1, 1)); }

static inline TSimdFloat32x4 tfSimdFloat2To4Splat0(TSimdFloat32x2 value) { return _mm_shuffle_ps(value, value, _MM_SHUFFLE(0, 0, 0, 0)); }
static inline TSimdFloat32x4 tfSimdFloat2To4Splat1(TSimdFloat32x2 value) { return _mm_shuffle_ps(value, value, _MM_SHUFFLE(1, 1, 1, 1)); }

inline TSimdInt32x2 tfSimd2iSplat(int32_t value) { return _mm_set1_epi32(value); }
inline TSimdFloat32x2 tfSimd2fSplat(float value) { return _mm_set1_ps(value); }

inline TSimdInt32x2 tfSimd2iCmpEq(TSimdInt32x2 arg1, TSimdInt32x2 arg2) { return _mm_cmpeq_epi32(arg1, arg2); }
inline TSimdInt32x2 tfSimd2iCmpNeq(TSimdInt32x2 arg1, TSimdInt32x2 arg2) {
    return _mm_xor_si128(_mm_cmpeq_epi32(arg1, arg2), _mm_set1_epi32((int32_t)0xFFFFFFFF));
}
inline TSimdInt32x2 tfSimd2iCmpGt(TSimdInt32x2 arg1, TSimdInt32x2 arg2) { return _mm_cmpgt_epi32(arg1, arg2); }
inline TSimdInt32x2 tfSimd2iCmpGtEq(TSimdInt32x2 arg1, TSimdInt32x2 arg2) {
    return _mm_or_si128(_mm_cmpgt_epi32(arg1, arg2), _mm_cmpeq_epi32(arg1, arg2));
}
inline TSimdInt32x2 tfSimd2iCmpLt(TSimdInt32x2 arg1, TSimdInt32x2 arg2) { return _mm_cmplt_epi32(arg1, arg2); }
inline TSimdInt32x2 tfSimd2iCmpLtEq(TSimdInt32x2 arg1, TSimdInt32x2 arg2) {
    return _mm_or_si128(_mm_cmplt_epi32(arg1, arg2), _mm_cmpeq_epi32(arg1, arg2));
}

inline bool tfSimd2fCmpAllEq(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2) {
    TSimdFloat32x4 compare = tfSimd2fCmpEq(arg1, arg2);
    return (_mm_movemask_ps(compare) & 0b0011) == 0b0011;
}

inline bool tfSimd2iCmpAllEq(TSimdInt32x2 arg1, TSimdInt32x2 arg2) {
    const TSimdInt32x2 compare = tfSimd2iCmpEq(arg1, arg2);
    return (_mm_movemask_epi8(compare) & 0b0011) == 0b0011;
}

static inline bool tfSimdFloat32x2CmpAllLt(TSimdFloat32x2 a, TSimdFloat32x2 b) {
    TSimdFloat32x3 compare = tfSimd2fCmpLt(a, b);
    return (_mm_movemask_ps(compare) & 0b0011) == 0b0011;
}

