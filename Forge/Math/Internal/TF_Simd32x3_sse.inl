#if defined(__CLANGD__)
#define TF_FEATURE_CPU_SSE  
#include "Forge/TF_Config.h"
#include "../TF_Simd32x3.h"
#endif

static inline Tsimd_f32x3_t tfSimdLoad_f32x3(float x, float y, float z) { return _mm_set_ps(0.0f, z, y, x); }
static inline Tsimd_f32x3_t tfSimdZero_f32x4() { return _mm_setzero_ps(); }



//inline Tsimd_i32x3_t   tfS32x3iSelect(Tsimd_i32x3_t arg0, Tsimd_i32x3_t arg1, Tsimd_i32x3_t mask) { return _mm_blendv_epi8(arg0, arg1, mask); }
//inline Tsimd_f32x3_t tfS32x3FSelect(Tsimd_f32x3_t arg0, Tsimd_f32x3_t arg1, Tsimd_f32x3_t mask) {
//    return _mm_blendv_ps(arg0, arg1, mask);
//}
//
//inline Tsimd_f32x3_t tfS32x3FZero() { return _mm_setzero_ps(); }
//inline Tsimd_i32x3_t   tfS32x3iZero() { return _mm_setzero_si128(); }
//
//inline Tsimd_i32x3_t tfS32x3iNot(Tsimd_i32x3_t value) { return _mm_andnot_si128(value, _mm_set1_epi32(TF_SIMDI_MAX)); }
//inline Tsimd_i32x3_t tfS32x3iAnd(Tsimd_i32x3_t arg1, Tsimd_i32x3_t arg2) { return _mm_and_si128(arg1, arg2); }
//inline Tsimd_i32x3_t tfS32x3iAndNot(Tsimd_i32x3_t arg1, Tsimd_i32x3_t arg2) { return _mm_andnot_si128(arg1, arg2); }
//inline Tsimd_i32x3_t tfS32x3iOr(Tsimd_i32x3_t arg1, Tsimd_i32x3_t arg2) { return _mm_or_si128(arg1, arg2); }
//inline Tsimd_i32x3_t tfS32x3iXor(Tsimd_i32x3_t arg1, Tsimd_i32x3_t arg2) { return _mm_xor_si128(arg1, arg2); }
//
//inline Tsimd_f32x3_t tfS32x3FNot(Tsimd_f32x3_t value) {
//    const Tsimd_f32x3_t invert = tfS32x3FSplat((float)(0xFFFFFFFF));
//    return _mm_andnot_ps(value, invert);
//}
//inline Tsimd_f32x3_t tfS32x3FAnd(Tsimd_f32x3_t arg1, Tsimd_f32x3_t arg2) { return _mm_and_ps(arg1, arg2); }
//inline Tsimd_f32x3_t tfS32x3FAndNot(Tsimd_f32x3_t arg1, Tsimd_f32x3_t arg2) { return _mm_andnot_ps(arg1, arg2); }
//inline Tsimd_f32x3_t tfS32x3FOr(Tsimd_f32x3_t arg1, Tsimd_f32x3_t arg2) { return _mm_or_ps(arg1, arg2); }
//inline Tsimd_f32x3_t tfS32x3FXor(Tsimd_f32x3_t arg1, Tsimd_f32x3_t arg2) { return _mm_xor_ps(arg1, arg2); }
//
//inline Tsimd_f32x3_t tfS32x3FFloor(Tsimd_f32x3_t value) { return _mm_floor_ps(value); }
//inline Tsimd_f32x3_t tfS32x3FCeil(Tsimd_f32x3_t value) { return _mm_ceil_ps(value); }
//inline Tsimd_f32x3_t tfS32x3FRound(Tsimd_f32x3_t value) { return _mm_round_ps(value, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC); }
//inline Tsimd_f32x3_t tfS32x3FTruncate(Tsimd_f32x3_t value) { return tfS32x3iToSimd3f(tfS32x3FToSimd3i(value)); }
//inline Tsimd_f32x3_t tfS32x3FMin(Tsimd_f32x3_t arg1, Tsimd_f32x3_t arg2) { return _mm_min_ps(arg1, arg2); }
//inline Tsimd_f32x3_t tfS32x3FMax(Tsimd_f32x3_t arg1, Tsimd_f32x3_t arg2) { return _mm_max_ps(arg1, arg2); }
//inline Tsimd_f32x3_t tfS32x3FClamp(Tsimd_f32x3_t value, Tsimd_f32x3_t min, Tsimd_f32x3_t max) {
//    return tfS32x3FMax(min, tfS32x3FMin(value, max));
//}
//
//inline Tsimd_i32x3_t tfS32x3FToSimd3i(Tsimd_f32x3_t value) { return _mm_castps_si128(value); }
//inline Tsimd_f32x3_t tfS32x3iToSimd3f(Tsimd_i32x3_t value) { return _mm_castsi128_ps(value); }
//
//inline float tfS32x3FSelectIndex0(Tsimd_f32x3_t value) { return _mm_cvtss_f32(value); }
//inline float tfS32x3FSelectIndex1(Tsimd_f32x3_t value) { return tfS32x3FSelectIndex0(tfS32x3FSplatIndex1(value)); }
//inline float tfS32x3FSelectIndex2(Tsimd_f32x3_t value) { return tfS32x3FSelectIndex0(tfS32x3FSplatIndex2(value)); }
//
//static inline Tsimd_f32x3_t tfSimd3x32FReplaceIndex0ByValue(Tsimd_f32x3_t input, float value) {
//    return _mm_blend_ps(input, tfS32x3FSplat(value), 0b0001);
//}
//static inline Tsimd_f32x3_t tfSimd3x32FReplaceIndex1ByValue(Tsimd_f32x3_t input, float value) {
//    return _mm_blend_ps(input, tfS32x3FSplat(value), 0b0010);
//}
//static inline Tsimd_f32x3_t tfSimd3x32FReplaceIndex2ByValue(Tsimd_f32x3_t input, float value) {
//    return _mm_blend_ps(input, tfS32x3FSplat(value), 0b0100);
//}
//
//inline Tsimd_f32x3_t tfS32x3FAdd(Tsimd_f32x3_t arg1, Tsimd_f32x3_t arg2) { return _mm_add_ps(arg1, arg2); }
//inline Tsimd_f32x3_t tfS32x3FSub(Tsimd_f32x3_t arg1, Tsimd_f32x3_t arg2) { return _mm_sub_ps(arg1, arg2); }
//inline Tsimd_f32x3_t tfS32x3FMul(Tsimd_f32x3_t arg1, Tsimd_f32x3_t arg2) { return _mm_mul_ps(arg1, arg2); }
//inline Tsimd_f32x3_t tfS32x3FMadd(Tsimd_f32x3_t mul1, Tsimd_f32x3_t mul2, Tsimd_f32x3_t add) {
//#if 0
//    return _mm_fmadd_ps(mul1, mul2, add); // Requires FMA CPUID
//#else
//    return tfS32x3FAdd(tfS32x3FMul(mul1, mul2), add);
//#endif
//}
//inline Tsimd_f32x3_t tfS32x3FDiv(Tsimd_f32x3_t arg1, Tsimd_f32x3_t arg2) { return _mm_div_ps(arg1, arg2); }
//
//inline Tsimd_f32x3_t tfS32x3FAbs(Tsimd_f32x3_t value) {
//    const Tsimd_f32x4_t signMask = tfS32x3iToSimd3f(tfS32x3iSplat(0x7FFFFFFF));
//    return _mm_and_ps(value, signMask);
//}
//
//inline Tsimd_f32x3_t tfSimd3x32FLoad(float x, float y, float z) { return _mm_set_ps(0.0f, z, y, x); }
//inline Tsimd_i32x3_t tfSimd3x32ILoad(int32_t x, int32_t y, int32_t z) { return _mm_set_epi32(0.0f, x, y, z); }
//
//inline Tsimd_f32x2_t tfS32x3FToSimd2f(Tsimd_f32x3_t value) { return value; }
//
//static inline Tsimd_f32x4_t tfS32x3FTo32x4FSplat0(Tsimd_f32x3_t value) { return _mm_shuffle_ps(value, value, _MM_SHUFFLE(0, 0, 0, 0)); }
//static inline Tsimd_f32x4_t tfS32x3FTo32x4FSplat1(Tsimd_f32x3_t value) { return _mm_shuffle_ps(value, value, _MM_SHUFFLE(1, 1, 1, 1)); }
//static inline Tsimd_f32x4_t tfS32x3FTo32x4FSplat2(Tsimd_f32x3_t value) { return _mm_shuffle_ps(value, value, _MM_SHUFFLE(2, 2, 2, 2)); }
//
//inline Tsimd_f32x3_t tfS32x3FSplatIndex0(Tsimd_f32x3_t value) { return _mm_shuffle_ps(value, value, _MM_SHUFFLE(0, 0, 0, 0)); }
//inline Tsimd_f32x3_t tfS32x3FSplatIndex1(Tsimd_f32x3_t value) { return _mm_shuffle_ps(value, value, _MM_SHUFFLE(1, 1, 1, 1)); }
//inline Tsimd_f32x3_t tfS32x3FSplatIndex2(Tsimd_f32x3_t value) { return _mm_shuffle_ps(value, value, _MM_SHUFFLE(2, 2, 2, 2)); }
//
//inline Tsimd_i32x3_t   tfS32x3iSplat(int32_t value) { return _mm_set1_epi32(value); }
//inline Tsimd_f32x3_t tfS32x3FSplat(float value) { return _mm_set1_ps(value); }
//
//inline Tsimd_i32x3_t tfS32x3iCmpEq(Tsimd_i32x3_t arg1, Tsimd_i32x3_t arg2) { return _mm_cmpeq_epi32(arg1, arg2); }
//inline Tsimd_i32x3_t tfS32x3iCmpNeq(Tsimd_i32x3_t arg1, Tsimd_i32x3_t arg2) {
//    return _mm_xor_si128(_mm_cmpeq_epi32(arg1, arg2), _mm_set1_epi32((int32_t)0xFFFFFFFF));
//}
//inline Tsimd_i32x3_t tfS32x3iCmpGt(Tsimd_i32x3_t arg1, Tsimd_i32x3_t arg2) { return _mm_cmpgt_epi32(arg1, arg2); }
//inline Tsimd_i32x3_t tfS32x3iCmpGtEq(Tsimd_i32x3_t arg1, Tsimd_i32x3_t arg2) {
//    return _mm_or_si128(_mm_cmpgt_epi32(arg1, arg2), _mm_cmpeq_epi32(arg1, arg2));
//}
//inline Tsimd_i32x3_t tfS32x3iCmpLt(Tsimd_i32x3_t arg1, Tsimd_i32x3_t arg2) { return _mm_cmplt_epi32(arg1, arg2); }
//inline Tsimd_i32x3_t tfS32x3iCmpLtEq(Tsimd_i32x3_t arg1, Tsimd_i32x3_t arg2) {
//    return _mm_or_si128(_mm_cmplt_epi32(arg1, arg2), _mm_cmpeq_epi32(arg1, arg2));
//}
//inline bool tfS32x3FCmpAllEq(Tsimd_f32x3_t arg1, Tsimd_f32x3_t arg2) {
//    Tsimd_f32x3_t compare = tfS32x3FCmpEq(arg1, arg2);
//    return (_mm_movemask_ps(compare) & 0b0111) == 0b0111;
//}
//inline bool tfS32x3iCmpAllEq(Tsimd_i32x3_t arg1, Tsimd_i32x3_t arg2) {
//    const Tsimd_i32x3_t compare = tfS32x3iCmpEq(arg1, arg2);
//    return (_mm_movemask_epi8(compare) & 0b0111) == 0b0111;
//}
//static inline bool tfSimdFloat32x3CmpAllLt(Tsimd_f32x3_t a, Tsimd_f32x3_t b) {
//    Tsimd_f32x3_t compare = tfS32x3FCmpLt(a, b);
//    return (_mm_movemask_ps(compare) & 0b0111) == 0b0111;
//}
//
