/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */
#include "Forge/Math/Internal/Types.h"

inline Simd_FloatType2 tfSimd2fSplat(float value);
inline Simd_Int32Type2 tfSimd2iSplat(int32_t value);

inline Simd_FloatType2 tfSimd2fZero();
inline Simd_Int32Type2 tfSimd2iZero();

inline Simd_FloatType  tfSimd2fToSimd1f(Simd_FloatType2 value);
inline Simd_Int32Type2 tfSimd2fToSimd2i(Simd_FloatType2 value);
inline Simd_FloatType2 tfSimd2iToSimd2f(Simd_Int32Type2 value);

inline Simd_FloatType2 tfSimd2fSplatIndex0(Simd_FloatType2 value);
inline Simd_FloatType2 tfSimd2fSplatIndex1(Simd_FloatType2 value);

inline Simd_FloatType2 tfSimd2fSelect(Simd_FloatType2 arg0, Simd_FloatType2 arg1, Simd_FloatType2 mask);
inline Simd_Int32Type2 tfSimd2iSelect(Simd_Int32Type2 arg0, Simd_Int32Type2 arg1, Simd_Int32Type2 mask);

inline float tfSimd2fSelectIndex0(Simd_FloatType2 value);
inline float tfSimd2fSelectIndex1(Simd_FloatType2 value);

inline Simd_FloatType2 tfSimd2fLoadImmediate(float x, float y);
inline Simd_Int32Type2 tfSimd2iLoadImmediate(int32_t x, int32_t y);

inline Simd_FloatType2 tfSimd2fAdd(Simd_FloatType2 arg1, Simd_FloatType2 arg2);
inline Simd_FloatType2 tfSimd2fSub(Simd_FloatType2 arg1, Simd_FloatType2 arg2);
inline Simd_FloatType2 tfSimd2fMul(Simd_FloatType2 arg1, Simd_FloatType2 arg2);
inline Simd_FloatType2 tfSimd2fMadd(Simd_FloatType2 mul1, Simd_FloatType2 mul2, Simd_FloatType2 add);
inline Simd_FloatType2 tfSimd2fDiv(Simd_FloatType2 arg1, Simd_FloatType2 arg2);
inline Simd_FloatType2 tfSimd2fAbs(Simd_FloatType2 value);

inline Simd_FloatType2 tfSimd2fNot(Simd_FloatType2 value);
inline Simd_FloatType2 tfSimd2fAnd(Simd_FloatType2 arg1, Simd_FloatType2 arg2);
inline Simd_FloatType2 tfSimd2fAndNot(Simd_FloatType2 arg1, Simd_FloatType2 arg2);
inline Simd_FloatType2 tfSimd2fOr(Simd_FloatType2 arg1, Simd_FloatType2 arg2);
inline Simd_FloatType2 tfSimd2fXor(Simd_FloatType2 arg1, Simd_FloatType2 arg2);

inline Simd_Int32Type2 tfSimd2iNot(Simd_Int32Type2 value);
inline Simd_Int32Type2 tfSimd2iAnd(Simd_Int32Type2 arg1, Simd_Int32Type2 arg2);
inline Simd_Int32Type2 tfSimd2iAndNot(Simd_Int32Type2 arg1, Simd_Int32Type2 arg2);
inline Simd_Int32Type2 tfSimd2iOr(Simd_Int32Type2 arg1, Simd_Int32Type2 arg2);
inline Simd_Int32Type2 tfSimd2iXor(Simd_Int32Type2 arg1, Simd_Int32Type2 arg2);

inline Simd_FloatType2 tfSimd2fFloor(Simd_FloatType2 value);
inline Simd_FloatType2 tfSimd2fCeil(Simd_FloatType2 value);
inline Simd_FloatType2 tfSimd2fRound(Simd_FloatType2 value); // Ties to even (banker's rounding)
inline Simd_FloatType2 tfSimd2fTruncate(Simd_FloatType2 value);
inline Simd_FloatType2 tfSimd2fMin(Simd_FloatType2 arg1, Simd_FloatType2 arg2);
inline Simd_FloatType2 tfSimd2fMax(Simd_FloatType2 arg1, Simd_FloatType2 arg2);
inline Simd_FloatType2 tfSimd2fClamp(Simd_FloatType2 value, Simd_FloatType2 min, Simd_FloatType2 max);

inline Simd_Int32Type2 tfSimd2iCmpEq(Simd_Int32Type2 arg1, Simd_Int32Type2 arg2);
inline Simd_Int32Type2 tfSimd2iCmpNeq(Simd_Int32Type2 arg1, Simd_Int32Type2 arg2);
inline Simd_Int32Type2 tfSimd2iCmpGt(Simd_Int32Type2 arg1, Simd_Int32Type2 arg2);
inline Simd_Int32Type2 tfSimd2iCmpGtEq(Simd_Int32Type2 arg1, Simd_Int32Type2 arg2);
inline Simd_Int32Type2 tfSimd2iCmpLt(Simd_Int32Type2 arg1, Simd_Int32Type2 arg2);
inline Simd_Int32Type2 tfSimd2iCmpLtEq(Simd_Int32Type2 arg1, Simd_Int32Type2 arg2);

inline Simd_FloatType2 tfSimd2fCmpEq(Simd_FloatType2 arg1, Simd_FloatType2 arg2);
inline Simd_FloatType2 tfSimd2fCmpNeq(Simd_FloatType2 arg1, Simd_FloatType2 arg2);
inline Simd_FloatType2 tfSimd2fCmpGt(Simd_FloatType2 arg1, Simd_FloatType2 arg2);
inline Simd_FloatType2 tfSimd2fCmpGtEq(Simd_FloatType2 arg1, Simd_FloatType2 arg2);
inline Simd_FloatType2 tfSimd2fCmpLt(Simd_FloatType2 arg1, Simd_FloatType2 arg2);
inline Simd_FloatType2 tfSimd2fCmpLtEq(Simd_FloatType2 arg1, Simd_FloatType2 arg2);

inline bool tfSimd2iCmpAllEq(Simd_Int32Type2 arg1, Simd_Int32Type2 arg2);
inline bool tfSimd2fCmpAllEq(Simd_FloatType2 arg1, Simd_FloatType2 arg2);

// ----------------------------------------------------------------
// --------------------- Implementaion ----------------------------
// ----------------------------------------------------------------

inline Simd_Int32Type2 tfSimd2iSelect(Simd_Int32Type2 arg0, Simd_Int32Type2 arg1, Simd_Int32Type2 mask) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_blendv_epi8(arg0, arg1, mask);
#else
    return {(mask.v[0] == 0) ? arg0.v[0] : arg1.v[0]
            , (mask.v[1] == 0) ? arg0.v[1] : arg1.v[1]};
#endif
}
inline Simd_FloatType2 tfSimd2fSelect(Simd_FloatType2 arg0, Simd_FloatType2 arg1, Simd_FloatType2 mask)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_blendv_ps(arg0, arg1, mask);
#else
    Simd_Int32Type2 intMask =  tfSimd2fToSimd2i(mask);
    return { (intMask.v[0] == 0) ? arg0.v[0] : arg1.v[0]
            , (intMask.v[1] == 0) ? arg0.v[1] : arg1.v[1]};
#endif
}

inline Simd_FloatType2 tfSimd2fZero() { return tfSimd2iToSimd2f(tfSimd2iZero()); }
inline Simd_Int32Type2 tfSimd2iZero()
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_setzero_si128();
#else
    return { 0, 0 };
#endif
}

inline Simd_Int32Type2 tfSimd2iNot(Simd_Int32Type2 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    const Simd_Int32Type2 invert = tfSimd2iSplat(TF_SIMDI_MAX);
    return _mm_andnot_si128(value, invert);
#else
    return { ~value.v[0], ~value.v[1] };
#endif
}
inline Simd_Int32Type2 tfSimd2iAnd(Simd_Int32Type2 arg1, Simd_Int32Type2 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_and_si128(arg1, arg2);
#else
    return { arg1.v[0] & arg2.v[0], arg1.v[1] & arg2.v[1]};
#endif
}
inline Simd_Int32Type2 tfSimd2iAndNot(Simd_Int32Type2 arg1, Simd_Int32Type2 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_andnot_si128(arg1, arg2); 
#else
    return { ~arg1.v[0] & arg2.v[0], ~arg1.v[1] & arg2.v[1]};
#endif
}
inline Simd_Int32Type2 tfSimd2iOr(Simd_Int32Type2 arg1, Simd_Int32Type2 arg2)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_or_si128(arg1, arg2);
#else
    return { arg1.v[0] | arg2.v[0], arg1.v[1] | arg2.v[1]};
#endif
}
inline Simd_Int32Type2 tfSimd2iXor(Simd_Int32Type2 arg1, Simd_Int32Type2 arg2){
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_xor_si128(arg1, arg2); 
#else
    return { arg1.v[0] ^ arg2.v[0], arg1.v[1] ^ arg2.v[1]};
#endif
}

inline Simd_FloatType2 tfSimd2fNot(Simd_FloatType2 value) {
#if defined(TF_FEATURE_CPU_SSE)
    const Simd_FloatType2 invert = tfSimd2fSplat((float)(0xFFFFFFFF));
    return _mm_andnot_ps(value, invert);
#else
    Simd_Int32Type2 result = {{ ~((int32_t)value.v[0]), ~((int32_t)value.v[1])} } ;
    return tfSimd2iToSimd2f(result);
#endif
}
inline Simd_FloatType2 tfSimd2fAnd(Simd_FloatType2 arg1, Simd_FloatType2 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_and_ps(arg1, arg2);
#else
    Simd_Int32Type2 result = { ((int32_t)arg1.v[0]) & ((int32_t)arg2.v[0]), ((int32_t)arg1.v[1]) & ((int32_t)arg2.v[1]) };
    return tfSimd2iToSimd2f(result);
#endif
}
inline Simd_FloatType2 tfSimd2fAndNot(Simd_FloatType2 arg1, Simd_FloatType2 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_andnot_ps(arg1, arg2);
#else
    Simd_Int32Type2 result = { { ~((int32_t)arg1.v[0]) & ((int32_t)arg2.v[0]),
                                 ~((int32_t)arg1.v[1]) & ((int32_t)arg2.v[1])} };
    return tfSimd2iToSimd2f(result);
#endif
}
inline Simd_FloatType2 tfSimd2fOr(Simd_FloatType2 arg1, Simd_FloatType2 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_or_ps(arg1, arg2);
#else
    Simd_Int32Type2 result = { { ((int32_t)arg1.v[0]) | ((int32_t)arg2.v[0]),
                                 ((int32_t)arg1.v[1]) | ((int32_t)arg2.v[1])} };
    return tfSimd2iToSimd2f(result);
#endif
}
inline Simd_FloatType2 tfSimd2fXor(Simd_FloatType2 arg1, Simd_FloatType2 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_xor_ps(arg1, arg2);
#else
    Simd_Int32Type2 result = { { ((int32_t)arg1.v[0]) ^ ((int32_t)arg2.v[0]),
                                 ((int32_t)arg1.v[1]) ^ ((int32_t)arg2.v[1]) } };
    return tfSimd2iToSimd2f(result);
#endif
}

inline Simd_FloatType2 tfSimd2fFloor(Simd_FloatType2 value) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_floor_ps(value);
#else
    return { { floorf(value.v[0]), floorf(value.v[1]) } };
#endif
}
inline Simd_FloatType2 tfSimd2fCeil(Simd_FloatType2 value) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_ceil_ps(value);
#else
    return { { ceilf(value.v[0]), ceilf(value.v[1]) } };
#endif
}
inline Simd_FloatType2 tfSimd2fRound(Simd_FloatType2 value) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_round_ps(value, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC);
#else
    // While 'roundf' may seem the obvious choice here, it rounds halfway cases
    // away from zero regardless of the current rounding mode, but 'rintf' uses
    // the current rounding mode which is consistent with other implementations.
    return { { rintf(value.v[0]), rintf(value.v[1]) } };
#endif
}
inline Simd_FloatType2 tfSimd2fTruncate(Simd_FloatType2 value) { return tfSimd2iToSimd2f(tfSimd2fToSimd2i(value)); }
inline Simd_FloatType2 tfSimd2fMin(Simd_FloatType2 arg1, Simd_FloatType2 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_min_ps(arg1, arg2);
#else
    return { { fminf(arg1.v[0], arg2.v[0]), fminf(arg1.v[1], arg2.v[1]) } };
#endif
}
inline Simd_FloatType2 tfSimd2fMax(Simd_FloatType2 arg1, Simd_FloatType2 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_max_ps(arg1, arg2);
#else
    return { { fmaxf(arg1.v[0], arg2.v[0]), fmaxf(arg1.v[1], arg2.v[1]) } };
#endif
}
inline Simd_FloatType2 tfSimd2fClamp(Simd_FloatType2 value, Simd_FloatType2 min, Simd_FloatType2 max) {
    return tfSimd2fMax(min, tfSimd2fMin(value, max));
}

inline Simd_Int32Type2 tfSimd2fToSimd2i(Simd_FloatType2 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_castps_si128(value);
#elif defined(TF_FEATURE_CPU_SCALAR)
    return { (int32_t)value.v[0], (int32_t)value.v[1]};
#endif
}

inline Simd_FloatType2 tfSimd2iToSimd2f(Simd_Int32Type2 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_castsi128_ps(value);
#elif defined(TF_FEATURE_CPU_SCALAR)
    return { (float)value.v[0], (float)value.v[1] };
#endif
}

inline float tfSimd2fSelectIndex0(Simd_FloatType2 value) { 
#if defined(TF_FEATURE_CPU_SSE)
  return _mm_cvtss_f32(value);
#elif defined(TF_FEATURE_CPU_SCALAR)
  return value.v[0];
#endif
}
inline float tfSimd2fSelectIndex1(Simd_FloatType2 value) { return tfSimd2fSelectIndex0(tfSimd2fSplatIndex1(value)); }

inline Simd_FloatType2 tfSimd2fAdd(Simd_FloatType2 arg1, Simd_FloatType2 arg2)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_add_ps(arg1, arg2);
#else
    return {
        arg1.v[0] + arg2.v[0],
        arg1.v[1] + arg2.v[1],
    };
#endif
}
inline Simd_FloatType2 tfSimd2fSub(Simd_FloatType2 arg1, Simd_FloatType2 arg2)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_sub_ps(arg1, arg2);
#else
    return {
        arg1.v[0] - arg2.v[0],
        arg1.v[1] - arg2.v[1],
    };
#endif
}
inline Simd_FloatType2 tfSimd2fMul(Simd_FloatType2 arg1, Simd_FloatType2 arg2)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_mul_ps(arg1, arg2);
#else
    return {
        arg1.v[0] * arg2.v[0],
        arg1.v[1] * arg2.v[1],
    };
#endif
}
inline Simd_FloatType2 tfSimd2fMadd(Simd_FloatType2 mul1, Simd_FloatType2 mul2, Simd_FloatType2 add) 
{
#if 0
    return _mm_fmadd_ps(mul1, mul2, add); // Requires FMA CPUID
#else
    return tfSimd2fAdd(tfSimd2fMul(mul1, mul2), add);
#endif
}
inline Simd_FloatType2 tfSimd2fDiv(Simd_FloatType2 arg1, Simd_FloatType2 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_div_ps(arg1, arg2);
#else
    return {
        arg1.v[0] / arg2.v[0],
        arg1.v[1] / arg2.v[1],
    };
#endif
}

inline Simd_FloatType2 tfSimd2fAbs(Simd_FloatType2 value) {
#if defined(TF_FEATURE_CPU_SSE)
    return value;
    //return _mm_abs_epi32(value); 
#else
    return {
        abs(value.v[0]),
        abs(value.v[1]),
    };
#endif
}

inline Simd_FloatType2 tfSimd2fLoadImmediate(float x, float y) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_set_ps(0.0f, 0.0f, y, x);
#else
    return { x, y};
#endif
}


inline Simd_Int32Type2 tfSimd2iLoadImmediate(int32_t x, int32_t y) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_set_epi32(0.0f, 0.0f, x, y);
#else
    return { x, y};
#endif
}

inline Simd_FloatType  tfSimd2fToSimd1f(Simd_FloatType2 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return value;
#else
    return value.v[0];
#endif
}

inline Simd_FloatType2 tfSimd2fToSimd2f(Simd_FloatType2 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return value;
#else
    return {value.v[0], value.v[1]};
#endif
}

inline Simd_FloatType2 tfSimd2fSplatIndex0(Simd_FloatType2 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_shuffle_ps(value, value, _MM_SHUFFLE(0, 0, 0, 0));
#else
  return {value.v[0],value.v[0]};
#endif
}

inline Simd_FloatType2 tfSimd2fSplatIndex1(Simd_FloatType2 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_shuffle_ps(value, value, _MM_SHUFFLE(1, 1, 1, 1));
#else
  return {value.v[1],value.v[1]};
#endif
}

inline Simd_FloatType2 tfSimd2fSplatIndex2(Simd_FloatType2 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_shuffle_ps(value, value, _MM_SHUFFLE(2, 2, 2, 2));
#else
  return {value.v[2],value.v[2]};
#endif
}

inline Simd_Int32Type2 tfSimd2iSplat(int32_t value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_set1_epi32(value);
#else
    return { value, value };
#endif
}

inline Simd_FloatType2 tfSimd2fSplat(float value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_set1_ps(value);
#else
    return { value, value };
#endif
}

inline Simd_Int32Type2 tfSimd2iCmpEq(Simd_Int32Type2 arg1, Simd_Int32Type2 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_cmpeq_epi32(arg1, arg2);
#else
    return { { (arg1.v[0] == arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, 
               (arg1.v[1] == arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000} };
#endif
}
inline Simd_Int32Type2 tfSimd2iCmpNeq(Simd_Int32Type2 arg1, Simd_Int32Type2 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_xor_si128(
        _mm_cmpeq_epi32(arg1, arg2), 
        _mm_set1_epi32((int32_t)0xFFFFFFFF));
#else
    return { { (arg1.v[0] != arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, 
               (arg1.v[1] != arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000} };
#endif
}
inline Simd_Int32Type2 tfSimd2iCmpGt(Simd_Int32Type2 arg1, Simd_Int32Type2 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_cmpgt_epi32(arg1, arg2);
#else
    return { { (arg1.v[0] > arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, 
               (arg1.v[1] > arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000} };
#endif
}
inline Simd_Int32Type2 tfSimd2iCmpGtEq(Simd_Int32Type2 arg1, Simd_Int32Type2 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_or_si128(
        _mm_cmpgt_epi32(arg1, arg2), 
        _mm_cmpeq_epi32(arg1, arg2));
#else
    return { { (arg1.v[0] >= arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, 
               (arg1.v[1] >= arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000} };
#endif
}
inline Simd_Int32Type2 tfSimd2iCmpLt(Simd_Int32Type2 arg1, Simd_Int32Type2 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_cmplt_epi32(arg1, arg2);
#else
    return { { (arg1.v[0] < arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, 
               (arg1.v[1] < arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000} };
#endif
}
inline Simd_Int32Type2 tfSimd2iCmpLtEq(Simd_Int32Type2 arg1, Simd_Int32Type2 arg2) {

#if defined(TF_FEATURE_CPU_SSE)
    return _mm_or_si128(
        _mm_cmplt_epi32(arg1, arg2), 
        _mm_cmpeq_epi32(arg1, arg2));
#else
    return { { (arg1.v[0] < arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, 
               (arg1.v[1] < arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000} };
#endif

}

//inline bool tfSimd4fCmpAllEq(Simd_FloatType4 arg1, Simd_FloatType4 arg2) {
//#if defined(TF_FEATURE_CPU_SSE)
//    const Simd_FloatType4 compare = tfSimd2fCmpAllEq(arg1, arg2);
//    return (_mm_movemask_epi8(compare) & 0xf) == 0xf;
//#else
//    for(int i = 0; i < 4; i++) {
//        if (arg1.v[i] != arg2.v[i])
//        {
//            return false;
//        }
//    }
//    return true;
//#endif
//
//}

inline bool tfSimd2iCmpAllEq(Simd_Int32Type2 arg1, Simd_Int32Type2 arg2)
{
#if defined(TF_FEATURE_CPU_SSE)
    const Simd_Int32Type2 compare = tfSimd2iCmpEq(arg1, arg2);
    return (_mm_movemask_epi8(compare) & 0b0011) == 0b0011;
#else
    for(int i = 0; i < 2; i++) {
        if (arg1.v[i] != arg2.v[i])
        {
            return false;
        }
    }
    return true;
#endif
}

