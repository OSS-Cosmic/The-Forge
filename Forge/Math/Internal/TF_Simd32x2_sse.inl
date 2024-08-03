#if defined(__CLANGD__)
#define TF_FEATURE_CPU_SSE  
#include "Forge/TF_Config.h"
#include "../TF_Simd32x2.h"
#endif

inline Tsimd_i32x2_t   tfS32x2ISelect(Tsimd_i32x2_t arg0, Tsimd_i32x2_t arg1, Tsimd_i32x2_t mask) { return _mm_blendv_epi8(arg0, arg1, mask); }
inline Tsimd_f32x2_t tfS32x2FSelect(Tsimd_f32x2_t arg0, Tsimd_f32x2_t arg1, Tsimd_f32x2_t mask) {
    return _mm_blendv_ps(arg0, arg1, mask);
}

inline Tsimd_f32x2_t tfS32x2FZero() { return _mm_setzero_ps(); }
inline Tsimd_i32x2_t   tfS32x2IZero() { return _mm_setzero_si128(); }

inline Tsimd_i32x2_t tfS32x2INot(Tsimd_i32x2_t value) {
    const Tsimd_i32x2_t invert = tfS32x2ISplat(TF_SIMDI_MAX);
    return _mm_andnot_si128(value, invert);
}
inline Tsimd_i32x2_t tfS32x2IAnd(Tsimd_i32x2_t arg1, Tsimd_i32x2_t arg2) { return _mm_and_si128(arg1, arg2); }
inline Tsimd_i32x2_t tfS32x2IAndNot(Tsimd_i32x2_t arg1, Tsimd_i32x2_t arg2) { return _mm_andnot_si128(arg1, arg2); }
inline Tsimd_i32x2_t tfS32x2IOr(Tsimd_i32x2_t arg1, Tsimd_i32x2_t arg2) { return _mm_or_si128(arg1, arg2); }
inline Tsimd_i32x2_t tfS32x2IXor(Tsimd_i32x2_t arg1, Tsimd_i32x2_t arg2) { return _mm_xor_si128(arg1, arg2); }

inline Tsimd_f32x2_t tfS32x2FNot(Tsimd_f32x2_t value) {
    const Tsimd_f32x2_t invert = tfS32x2FSplat((float)(0xFFFFFFFF));
    return _mm_andnot_ps(value, invert);
}
inline Tsimd_f32x2_t tfS32x2FAnd(Tsimd_f32x2_t arg1, Tsimd_f32x2_t arg2) { return _mm_and_ps(arg1, arg2); }
inline Tsimd_f32x2_t tfS32x2FAndNot(Tsimd_f32x2_t arg1, Tsimd_f32x2_t arg2) { return _mm_andnot_ps(arg1, arg2); }
inline Tsimd_f32x2_t tfS32x2FOr(Tsimd_f32x2_t arg1, Tsimd_f32x2_t arg2) { return _mm_or_ps(arg1, arg2); }
inline Tsimd_f32x2_t tfS32x2FXor(Tsimd_f32x2_t arg1, Tsimd_f32x2_t arg2) { return _mm_xor_ps(arg1, arg2); }

inline Tsimd_f32x2_t tfS32x2FFloor(Tsimd_f32x2_t value) { return _mm_floor_ps(value); }
inline Tsimd_f32x2_t tfS32x2FCeil(Tsimd_f32x2_t value) { return _mm_ceil_ps(value); }
inline Tsimd_f32x2_t tfS32x2FRound(Tsimd_f32x2_t value) { return _mm_round_ps(value, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC); }
inline Tsimd_f32x2_t tfS32x2FTruncate(Tsimd_f32x2_t value) { return tfS32x2IToSimd2f(tfS32x2FToSimd2i(value)); }
inline Tsimd_f32x2_t tfS32x2FMin(Tsimd_f32x2_t arg1, Tsimd_f32x2_t arg2) { return _mm_min_ps(arg1, arg2); }
inline Tsimd_f32x2_t tfS32x2FMax(Tsimd_f32x2_t arg1, Tsimd_f32x2_t arg2) { return _mm_max_ps(arg1, arg2); }
inline Tsimd_f32x2_t tfS32x2FClamp(Tsimd_f32x2_t value, Tsimd_f32x2_t min, Tsimd_f32x2_t max) {
    return tfS32x2FMax(min, tfS32x2FMin(value, max));
}

inline Tsimd_i32x2_t tfS32x2FToSimd2i(Tsimd_f32x2_t value) { return _mm_castps_si128(value); }

inline Tsimd_f32x2_t tfS32x2IToSimd2f(Tsimd_i32x2_t value) { return _mm_castsi128_ps(value); }

inline float tfS32x2FSelectIndex0(Tsimd_f32x2_t value) { return _mm_cvtss_f32(value); }

inline float tfS32x2FSelectIndex1(Tsimd_f32x2_t value) { return tfS32x2FSelectIndex0(tfS32x2FSplatIndex1(value)); }

inline Tsimd_f32x2_t tfS32x2FAdd(Tsimd_f32x2_t arg1, Tsimd_f32x2_t arg2) { return _mm_add_ps(arg1, arg2); }
inline Tsimd_f32x2_t tfS32x2FSub(Tsimd_f32x2_t arg1, Tsimd_f32x2_t arg2) { return _mm_sub_ps(arg1, arg2); }
inline Tsimd_f32x2_t tfS32x2FMul(Tsimd_f32x2_t arg1, Tsimd_f32x2_t arg2) { return _mm_mul_ps(arg1, arg2); }
inline Tsimd_f32x2_t tfS32x2FMadd(Tsimd_f32x2_t mul1, Tsimd_f32x2_t mul2, Tsimd_f32x2_t add) {
#if 0
    return _mm_fmadd_ps(mul1, mul2, add); // Requires FMA CPUID
#else
    return tfS32x2FAdd(tfS32x2FMul(mul1, mul2), add);
#endif
}
inline Tsimd_f32x2_t tfS32x2FDiv(Tsimd_f32x2_t arg1, Tsimd_f32x2_t arg2) { return _mm_div_ps(arg1, arg2); }

inline Tsimd_f32x2_t tfS32x2FAbs(Tsimd_f32x2_t value) {
    const Tsimd_f32x4_t signMask = tfS32x2IToSimd2f(tfS32x2ISplat(0x7FFFFFFF));
    return _mm_and_ps(value, signMask);
}

inline Tsimd_f32x2_t tfSimdFloat2Load(float x, float y) { return _mm_set_ps(0.0f, 0.0f, y, x); }

inline Tsimd_i32x2_t tfS32x2ILoadImmediate(int32_t x, int32_t y) { return _mm_set_epi32(0.0f, 0.0f, x, y); }

inline Tsimd_f32x2_t tfS32x2FSplatIndex0(Tsimd_f32x2_t value) { return _mm_shuffle_ps(value, value, _MM_SHUFFLE(0, 0, 0, 0)); }
inline Tsimd_f32x2_t tfS32x2FSplatIndex1(Tsimd_f32x2_t value) { return _mm_shuffle_ps(value, value, _MM_SHUFFLE(1, 1, 1, 1)); }

static inline Tsimd_f32x4_t tfSimdFloat2To4Splat0(Tsimd_f32x2_t value) { return _mm_shuffle_ps(value, value, _MM_SHUFFLE(0, 0, 0, 0)); }
static inline Tsimd_f32x4_t tfSimdFloat2To4Splat1(Tsimd_f32x2_t value) { return _mm_shuffle_ps(value, value, _MM_SHUFFLE(1, 1, 1, 1)); }

inline Tsimd_i32x2_t tfS32x2ISplat(int32_t value) { return _mm_set1_epi32(value); }
inline Tsimd_f32x2_t tfS32x2FSplat(float value) { return _mm_set1_ps(value); }

inline Tsimd_i32x2_t tfS32x2ICmpEq(Tsimd_i32x2_t arg1, Tsimd_i32x2_t arg2) { return _mm_cmpeq_epi32(arg1, arg2); }
inline Tsimd_i32x2_t tfS32x2ICmpNeq(Tsimd_i32x2_t arg1, Tsimd_i32x2_t arg2) {
    return _mm_xor_si128(_mm_cmpeq_epi32(arg1, arg2), _mm_set1_epi32((int32_t)0xFFFFFFFF));
}
inline Tsimd_i32x2_t tfS32x2ICmpGt(Tsimd_i32x2_t arg1, Tsimd_i32x2_t arg2) { return _mm_cmpgt_epi32(arg1, arg2); }
inline Tsimd_i32x2_t tfS32x2ICmpGtEq(Tsimd_i32x2_t arg1, Tsimd_i32x2_t arg2) {
    return _mm_or_si128(_mm_cmpgt_epi32(arg1, arg2), _mm_cmpeq_epi32(arg1, arg2));
}
inline Tsimd_i32x2_t tfS32x2ICmpLt(Tsimd_i32x2_t arg1, Tsimd_i32x2_t arg2) { return _mm_cmplt_epi32(arg1, arg2); }
inline Tsimd_i32x2_t tfS32x2ICmpLtEq(Tsimd_i32x2_t arg1, Tsimd_i32x2_t arg2) {
    return _mm_or_si128(_mm_cmplt_epi32(arg1, arg2), _mm_cmpeq_epi32(arg1, arg2));
}

inline bool tfS32x2FCmpAllEq(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) {
    Tsimd_f32x4_t compare = tfS32x2FCmpEq(arg1, arg2);
    return (_mm_movemask_ps(compare) & 0b0011) == 0b0011;
}

inline bool tfS32x2ICmpAllEq(Tsimd_i32x2_t arg1, Tsimd_i32x2_t arg2) {
    const Tsimd_i32x2_t compare = tfS32x2ICmpEq(arg1, arg2);
    return (_mm_movemask_epi8(compare) & 0b0011) == 0b0011;
}

static inline bool tfS32x2FCmpAllLt(Tsimd_f32x2_t a, Tsimd_f32x2_t b) {
    Tsimd_f32x3_t compare = tfS32x2FCmpLt(a, b);
    return (_mm_movemask_ps(compare) & 0b0011) == 0b0011;
}

