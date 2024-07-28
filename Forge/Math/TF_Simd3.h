/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */
#include "Forge/Math/Internal/Types.h"

inline Simd_FloatType3 tfSimd3fSplat(float value);
inline Simd_Int32Type3 tfSimd3iSplat(int32_t value);

inline Simd_FloatType3 tfSimd3fZero();
inline Simd_Int32Type3 tfSimd3iZero();

inline Simd_FloatType  tfSimd3fToSimd1f(Simd_FloatType3 value);
inline Simd_FloatType2 tfSimd3fToSimd2f(Simd_FloatType3 value);
inline Simd_Int32Type3 tfSimd3fToSimd3i(Simd_FloatType3 value);
inline Simd_FloatType3 tfSimd3iToSimd3f(Simd_Int32Type3 value);

inline Simd_FloatType3 tfSimd3fSplatIndex0(Simd_FloatType3 value);
inline Simd_FloatType3 tfSimd3fSplatIndex1(Simd_FloatType3 value);
inline Simd_FloatType3 tfSimd3fSplatIndex2(Simd_FloatType3 value);

inline Simd_FloatType3 tfSimd3fSelect(Simd_FloatType3 arg0, Simd_FloatType3 arg1, Simd_FloatType3 mask);
inline Simd_Int32Type3 tfSimd3iSelect(Simd_Int32Type3 arg0, Simd_Int32Type3 arg1, Simd_Int32Type3 mask);

inline float tfSimd3fSelectIndex0(Simd_FloatType3 value);
inline float tfSimd3fSelectIndex1(Simd_FloatType3 value);
inline float tfSimd3fSelectIndex2(Simd_FloatType3 value);

inline Simd_FloatType3 tfSimd3fLoadImmediate(float x, float y, float z);
inline Simd_Int32Type3 tfSimd3iLoadImmediate(int32_t x, int32_t y, int32_t z);

inline Simd_FloatType3 tfSimd3fAdd(Simd_FloatType3 arg1, Simd_FloatType3 arg2);
inline Simd_FloatType3 tfSimd3fSub(Simd_FloatType3 arg1, Simd_FloatType3 arg2);
inline Simd_FloatType3 tfSimd3fMul(Simd_FloatType3 arg1, Simd_FloatType3 arg2);
inline Simd_FloatType3 tfSimd3fMadd(Simd_FloatType3 mul1, Simd_FloatType3 mul2, Simd_FloatType3 add);
inline Simd_FloatType3 tfSimd3fDiv(Simd_FloatType3 arg1, Simd_FloatType3 arg2);
inline Simd_FloatType3 tfSimd3fAbs(Simd_FloatType3 value);

inline Simd_FloatType3 tfSimd3fNot(Simd_FloatType3 value);
inline Simd_FloatType3 tfSimd3fAnd(Simd_FloatType3 arg1, Simd_FloatType3 arg2);
inline Simd_FloatType3 tfSimd3fAndNot(Simd_FloatType3 arg1, Simd_FloatType3 arg2);
inline Simd_FloatType3 tfSimd3fOr(Simd_FloatType3 arg1, Simd_FloatType3 arg2);
inline Simd_FloatType3 tfSimd3fXor(Simd_FloatType3 arg1, Simd_FloatType3 arg2);

inline Simd_Int32Type3 tfSimd3iNot(Simd_Int32Type3 value);
inline Simd_Int32Type3 tfSimd3iAnd(Simd_Int32Type3 arg1, Simd_Int32Type3 arg2);
inline Simd_Int32Type3 tfSimd3iAndNot(Simd_Int32Type3 arg1, Simd_Int32Type3 arg2);
inline Simd_Int32Type3 tfSimd3iOr(Simd_Int32Type3 arg1, Simd_Int32Type3 arg2);
inline Simd_Int32Type3 tfSimd3iXor(Simd_Int32Type3 arg1, Simd_Int32Type3 arg2);

inline Simd_FloatType3 tfSimd3fFloor(Simd_FloatType3 value);
inline Simd_FloatType3 tfSimd3fCeil(Simd_FloatType3 value);
inline Simd_FloatType3 tfSimd3fRound(Simd_FloatType3 value); // Ties to even (banker's rounding)
inline Simd_FloatType3 tfSimd3fTruncate(Simd_FloatType3 value);
inline Simd_FloatType3 tfSimd3fMin(Simd_FloatType3 arg1, Simd_FloatType3 arg2);
inline Simd_FloatType3 tfSimd3fMax(Simd_FloatType3 arg1, Simd_FloatType3 arg2);
inline Simd_FloatType3 tfSimd3fClamp(Simd_FloatType3 value, Simd_FloatType3 min, Simd_FloatType3 max);

inline Simd_Int32Type3 tfSimd3iCmpEq(Simd_Int32Type3 arg1, Simd_Int32Type3 arg2);
inline Simd_Int32Type3 tfSimd3iCmpNeq(Simd_Int32Type3 arg1, Simd_Int32Type3 arg2);
inline Simd_Int32Type3 tfSimd3iCmpGt(Simd_Int32Type3 arg1, Simd_Int32Type3 arg2);
inline Simd_Int32Type3 tfSimd3iCmpGtEq(Simd_Int32Type3 arg1, Simd_Int32Type3 arg2);
inline Simd_Int32Type3 tfSimd3iCmpLt(Simd_Int32Type3 arg1, Simd_Int32Type3 arg2);
inline Simd_Int32Type3 tfSimd3iCmpLtEq(Simd_Int32Type3 arg1, Simd_Int32Type3 arg2);

inline Simd_FloatType3 tfSimd3fCmpEq(Simd_FloatType3 arg1, Simd_FloatType3 arg2);
inline Simd_FloatType3 tfSimd3fCmpNeq(Simd_FloatType3 arg1, Simd_FloatType3 arg2);
inline Simd_FloatType3 tfSimd3fCmpGt(Simd_FloatType3 arg1, Simd_FloatType3 arg2);
inline Simd_FloatType3 tfSimd3fCmpGtEq(Simd_FloatType3 arg1, Simd_FloatType3 arg2);
inline Simd_FloatType3 tfSimd3fCmpLt(Simd_FloatType3 arg1, Simd_FloatType3 arg2);
inline Simd_FloatType3 tfSimd3fCmpLtEq(Simd_FloatType3 arg1, Simd_FloatType3 arg2);

inline bool tfSimd3iCmpAllEq(Simd_Int32Type3 arg1, Simd_Int32Type3 arg2);
inline bool tfSimd3fCmpAllEq(Simd_FloatType3 arg1, Simd_FloatType3 arg2);

// ----------------------------------------------------------------
// --------------------- Implementaion ----------------------------
// ----------------------------------------------------------------

inline Simd_Int32Type3 tfSimd3iSelect(Simd_Int32Type3 arg0, Simd_Int32Type3 arg1, Simd_Int32Type3 mask) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_blendv_epi8(arg0, arg1, mask);
#else
    return {(mask.v[0] == 0) ? arg0.v[0] : arg1.v[0]
            , (mask.v[1] == 0) ? arg0.v[1] : arg1.v[1]
            , (mask.v[2] == 0) ? arg0.v[2] : arg1.v[2]};
#endif
}
inline Simd_FloatType3 tfSimd3fSelect(Simd_FloatType3 arg0, Simd_FloatType3 arg1, Simd_FloatType3 mask)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_blendv_ps(arg0, arg1, mask);
#else
    Simd_Int32Type3 intMask =  tfSimd3fToSimd3i(mask);
    return { (intMask.v[0] == 0) ? arg0.v[0] : arg1.v[0]
            , (intMask.v[1] == 0) ? arg0.v[1] : arg1.v[1]
            , (intMask.v[2] == 0) ? arg0.v[2] : arg1.v[2] };
#endif
}

inline Simd_FloatType3 tfSimd3fZero() { return tfSimd3iToSimd3f(tfSimd3iZero()); }
inline Simd_Int32Type3 tfSimd3iZero()
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_setzero_si128();
#else
    return { 0, 0, 0 };
#endif
}

inline Simd_Int32Type3 tfSimd3iNot(Simd_Int32Type3 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    const Simd_Int32Type3 invert = tfSimd3iSplat(TF_SIMDI_MAX);
    return _mm_andnot_si128(value, invert);
#else
    return { ~value.v[0], ~value.v[1], ~value.v[2] };
#endif
}
inline Simd_Int32Type3 tfSimd3iAnd(Simd_Int32Type3 arg1, Simd_Int32Type3 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_and_si128(arg1, arg2);
#else
    return { arg1.v[0] & arg2.v[0], arg1.v[1] & arg2.v[1], arg1.v[2] & arg2.v[2]};
#endif

}
inline Simd_Int32Type3 tfSimd3iAndNot(Simd_Int32Type3 arg1, Simd_Int32Type3 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_andnot_si128(arg1, arg2); 
#else
    return { ~arg1.v[0] & arg2.v[0], ~arg1.v[1] & arg2.v[1], ~arg1.v[2] & arg2.v[2]};
#endif
}
inline Simd_Int32Type3 tfSimd3iOr(Simd_Int32Type3 arg1, Simd_Int32Type3 arg2)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_or_si128(arg1, arg2);
#else
    return { arg1.v[0] | arg2.v[0], arg1.v[1] | arg2.v[1], arg1.v[2] | arg2.v[2]};
#endif
}
inline Simd_Int32Type3 tfSimd3iXor(Simd_Int32Type3 arg1, Simd_Int32Type3 arg2){
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_xor_si128(arg1, arg2); 
#else
    return { arg1.v[0] ^ arg2.v[0], arg1.v[1] ^ arg2.v[1], arg1.v[2] ^ arg2.v[2] };
#endif
}

inline Simd_FloatType3 tfSimd3fNot(Simd_FloatType3 value) {
#if defined(TF_FEATURE_CPU_SSE)
    const Simd_FloatType3 invert = tfSimd3fSplat((float)(0xFFFFFFFF));
    return _mm_andnot_ps(value, invert);
#else
    Simd_Int32Type3 result = {{ ~((int32_t)value.v[0]), ~((int32_t)value.v[1]),
                                 ~((int32_t)value.v[2])} } ;
    return tfSimd3iToSimd3f(result);
#endif
}
inline Simd_FloatType3 tfSimd3fAnd(Simd_FloatType3 arg1, Simd_FloatType3 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_and_ps(arg1, arg2);
#else
    Simd_Int32Type3 result = { ((int32_t)arg1.v[0]) & ((int32_t)arg2.v[0]), ((int32_t)arg1.v[1]) & ((int32_t)arg2.v[1]),
                               ((int32_t)arg1.v[2]) & ((int32_t)arg2.v[2]) };
    return tfSimd3iToSimd3f(result);
#endif
}
inline Simd_FloatType3 tfSimd3fAndNot(Simd_FloatType3 arg1, Simd_FloatType3 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_andnot_ps(arg1, arg2);
#else
    Simd_Int32Type3 result = { { ~((int32_t)arg1.v[0]) & ((int32_t)arg2.v[0]),
                                 ~((int32_t)arg1.v[1]) & ((int32_t)arg2.v[1]),
                                 ~((int32_t)arg1.v[2]) & ((int32_t)arg2.v[2]) } };
    return tfSimd3iToSimd3f(result);
#endif
}
inline Simd_FloatType3 tfSimd3fOr(Simd_FloatType3 arg1, Simd_FloatType3 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_or_ps(arg1, arg2);
#else
    Simd_Int32Type3 result = { { ((int32_t)arg1.v[0]) | ((int32_t)arg2.v[0]),
                                 ((int32_t)arg1.v[1]) | ((int32_t)arg2.v[1]),
                                 ((int32_t)arg1.v[2]) | ((int32_t)arg2.v[2]) } };
    return tfSimd3iToSimd3f(result);
#endif
}
inline Simd_FloatType3 tfSimd3fXor(Simd_FloatType3 arg1, Simd_FloatType3 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_xor_ps(arg1, arg2);
#else
    Simd_Int32Type3 result = { { ((int32_t)arg1.v[0]) ^ ((int32_t)arg2.v[0]),
                                 ((int32_t)arg1.v[1]) ^ ((int32_t)arg2.v[1]),
                                 ((int32_t)arg1.v[2]) ^ ((int32_t)arg2.v[2]) } };
    return tfSimd3iToSimd3f(result);
#endif
}

inline Simd_FloatType3 tfSimd3fFloor(Simd_FloatType3 value) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_floor_ps(value);
#else
    return { { floorf(value.v[0]), floorf(value.v[1]), floorf(value.v[2]) } };
#endif
}
inline Simd_FloatType3 tfSimd3fCeil(Simd_FloatType3 value) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_ceil_ps(value);
#else
    return { { ceilf(value.v[0]), ceilf(value.v[1]), ceilf(value.v[2]) } };
#endif
}
inline Simd_FloatType3 tfSimd3fRound(Simd_FloatType3 value) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_round_ps(value, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC);
#else
    // While 'roundf' may seem the obvious choice here, it rounds halfway cases
    // away from zero regardless of the current rounding mode, but 'rintf' uses
    // the current rounding mode which is consistent with other implementations.
    return { { rintf(value.v[0]), rintf(value.v[1]), rintf(value.v[2]) } };
#endif
}
inline Simd_FloatType3 tfSimd3fTruncate(Simd_FloatType3 value) { return tfSimd3iToSimd3f(tfSimd3fToSimd3i(value)); }
inline Simd_FloatType3 tfSimd3fMin(Simd_FloatType3 arg1, Simd_FloatType3 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_min_ps(arg1, arg2);
#else
    return { { fminf(arg1.v[0], arg2.v[0]), fminf(arg1.v[1], arg2.v[1]), fminf(arg1.v[2], arg2.v[2]) } };
#endif
}
inline Simd_FloatType3 tfSimd3fMax(Simd_FloatType3 arg1, Simd_FloatType3 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_max_ps(arg1, arg2);
#else
    return { { fmaxf(arg1.v[0], arg2.v[0]), fmaxf(arg1.v[1], arg2.v[1]), fmaxf(arg1.v[2], arg2.v[2]) } };
#endif
}
inline Simd_FloatType3 tfSimd3fClamp(Simd_FloatType3 value, Simd_FloatType3 min, Simd_FloatType3 max) {
    return tfSimd3fMax(min, tfSimd3fMin(value, max));
}

inline Simd_Int32Type3 tfSimd3fToSimd3i(Simd_FloatType3 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_castps_si128(value);
#elif defined(TF_FEATURE_CPU_SCALAR)
    return { (int32_t)value.v[0], (int32_t)value.v[1], (int32_t)value.v[2]};
#endif
}

inline Simd_FloatType3 tfSimd3iToSimd3f(Simd_Int32Type3 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_castsi128_ps(value);
#elif defined(TF_FEATURE_CPU_SCALAR)
    return { (float)value.v[0], (float)value.v[1], (float)value.v[2]};
#endif
}

inline float tfSimd3fSelectIndex0(Simd_FloatType3 value) { 
#if defined(TF_FEATURE_CPU_SSE)
  return _mm_cvtss_f32(value);
#elif defined(TF_FEATURE_CPU_SCALAR)
  return value.v[0];
#endif
}
inline float tfSimd3fSelectIndex1(Simd_FloatType3 value) { return tfSimd3fSelectIndex0(tfSimd3fSplatIndex1(value)); }
inline float tfSimd3fSelectIndex2(Simd_FloatType3 value) { return tfSimd3fSelectIndex0(tfSimd3fSplatIndex2(value)); }

inline Simd_FloatType3 tfSimd3fAdd(Simd_FloatType3 arg1, Simd_FloatType3 arg2)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_add_ps(arg1, arg2);
#else
    return {
        arg1.v[0] + arg2.v[0],
        arg1.v[1] + arg2.v[1],
        arg1.v[2] + arg2.v[2],
    };
#endif
}
inline Simd_FloatType3 tfSimd3fSub(Simd_FloatType3 arg1, Simd_FloatType3 arg2)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_sub_ps(arg1, arg2);
#else
    return {
        arg1.v[0] - arg2.v[0],
        arg1.v[1] - arg2.v[1],
        arg1.v[2] - arg2.v[2],
    };
#endif
}
inline Simd_FloatType3 tfSimd3fMul(Simd_FloatType3 arg1, Simd_FloatType3 arg2)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_mul_ps(arg1, arg2);
#else
    return {
        arg1.v[0] * arg2.v[0],
        arg1.v[1] * arg2.v[1],
        arg1.v[2] * arg2.v[2],
    };
#endif
}
inline Simd_FloatType3 tfSimd3fMadd(Simd_FloatType3 mul1, Simd_FloatType3 mul2, Simd_FloatType3 add) 
{
#if 0
    return _mm_fmadd_ps(mul1, mul2, add); // Requires FMA CPUID
#else
    return tfSimd3fAdd(tfSimd3fMul(mul1, mul2), add);
#endif
}
inline Simd_FloatType3 tfSimd3fDiv(Simd_FloatType3 arg1, Simd_FloatType3 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_div_ps(arg1, arg2);
#else
    return {
        arg1.v[0] / arg2.v[0],
        arg1.v[1] / arg2.v[1],
        arg1.v[2] / arg2.v[2]
    };
#endif
}

inline Simd_FloatType3 tfSimd3fAbs(Simd_FloatType3 value) {
#if defined(TF_FEATURE_CPU_SSE)
    return value;
    //return _mm_abs_epi32(value); 
#else
    return {
        abs(value.v[0]),
        abs(value.v[1]),
        abs(value.v[2]),
    };
#endif
}

inline Simd_FloatType3 tfSimd3fLoadImmediate(float x, float y, float z) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_set_ps(0.0f, z, y, x);
#else
    return { x, y, z};
#endif
}


inline Simd_Int32Type3 tfSimd3iLoadImmediate(int32_t x, int32_t y, int32_t z) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_set_epi32(0.0f, x, y, z);
#else
    return { x, y, z};
#endif
}

inline Simd_FloatType  tfSimd3fToSimd1f(Simd_FloatType3 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return value;
#else
    return value.v[0];
#endif
}

inline Simd_FloatType2 tfSimd3fToSimd2f(Simd_FloatType3 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return value;
#else
    return {value.v[0], value.v[1]};
#endif
}

inline Simd_FloatType3 tfSimd3fSplatIndex0(Simd_FloatType3 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_shuffle_ps(value, value, _MM_SHUFFLE(0, 0, 0, 0));
#else
  return {value.v[0],value.v[0],value.v[0]};
#endif
}

inline Simd_FloatType3 tfSimd3fSplatIndex1(Simd_FloatType3 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_shuffle_ps(value, value, _MM_SHUFFLE(1, 1, 1, 1));
#else
  return {value.v[1],value.v[1],value.v[1]};
#endif
}

inline Simd_FloatType3 tfSimd3fSplatIndex2(Simd_FloatType3 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_shuffle_ps(value, value, _MM_SHUFFLE(2, 2, 2, 2));
#else
  return {value.v[2],value.v[2],value.v[2]};
#endif
}

inline Simd_Int32Type3 tfSimd3iSplat(int32_t value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_set1_epi32(value);
#else
    return { value, value, value };
#endif
}

inline Simd_FloatType3 tfSimd3fSplat(float value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_set1_ps(value);
#else
    return { value, value, value };
#endif
}

inline Simd_Int32Type3 tfSimd3iCmpEq(Simd_Int32Type3 arg1, Simd_Int32Type3 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_cmpeq_epi32(arg1, arg2);
#else
    return { { (arg1.v[0] == arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, 
               (arg1.v[1] == arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000,
               (arg1.v[2] == arg2.v[2]) ? (int32_t)0xFFFFFFFF : 0x00000000} };
#endif
}
inline Simd_Int32Type3 tfSimd3iCmpNeq(Simd_Int32Type3 arg1, Simd_Int32Type3 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_xor_si128(
        _mm_cmpeq_epi32(arg1, arg2), 
        _mm_set1_epi32((int32_t)0xFFFFFFFF));
#else
    return { { (arg1.v[0] != arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, 
               (arg1.v[1] != arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000,
               (arg1.v[2] != arg2.v[2]) ? (int32_t)0xFFFFFFFF : 0x00000000} };
#endif
}
inline Simd_Int32Type3 tfSimd3iCmpGt(Simd_Int32Type3 arg1, Simd_Int32Type3 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_cmpgt_epi32(arg1, arg2);
#else
    return { { (arg1.v[0] > arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, 
               (arg1.v[1] > arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000,
               (arg1.v[2] > arg2.v[2]) ? (int32_t)0xFFFFFFFF : 0x00000000} };
#endif
}
inline Simd_Int32Type3 tfSimd3iCmpGtEq(Simd_Int32Type3 arg1, Simd_Int32Type3 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_or_si128(
        _mm_cmpgt_epi32(arg1, arg2), 
        _mm_cmpeq_epi32(arg1, arg2));
#else
    return { { (arg1.v[0] >= arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, 
               (arg1.v[1] >= arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000,
               (arg1.v[2] >= arg2.v[2]) ? (int32_t)0xFFFFFFFF : 0x00000000} };
#endif
}
inline Simd_Int32Type3 tfSimd3iCmpLt(Simd_Int32Type3 arg1, Simd_Int32Type3 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_cmplt_epi32(arg1, arg2);
#else
    return { { (arg1.v[0] < arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, 
               (arg1.v[1] < arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000,
               (arg1.v[2] < arg2.v[2]) ? (int32_t)0xFFFFFFFF : 0x00000000 } };
#endif
}
inline Simd_Int32Type3 tfSimd3iCmpLtEq(Simd_Int32Type3 arg1, Simd_Int32Type3 arg2) {

#if defined(TF_FEATURE_CPU_SSE)
    return _mm_or_si128(
        _mm_cmplt_epi32(arg1, arg2), 
        _mm_cmpeq_epi32(arg1, arg2));
#else
    return { { (arg1.v[0] < arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, 
               (arg1.v[1] < arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000,
               (arg1.v[2] < arg2.v[2]) ? (int32_t)0xFFFFFFFF : 0x00000000} };
#endif

}

//inline bool tfSimd4fCmpAllEq(Simd_FloatType4 arg1, Simd_FloatType4 arg2) {
//#if defined(TF_FEATURE_CPU_SSE)
//    const Simd_FloatType4 compare = tfSimd3fCmpAllEq(arg1, arg2);
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

inline bool tfSimd3iCmpAllEq(Simd_Int32Type3 arg1, Simd_Int32Type3 arg2)
{
#if defined(TF_FEATURE_CPU_SSE)
    const Simd_Int32Type3 compare = tfSimd3iCmpEq(arg1, arg2);
    return (_mm_movemask_epi8(compare) & 0b0111) == 0b0111;
#else
    for(int i = 0; i < 3; i++) {
        if (arg1.v[i] != arg2.v[i])
        {
            return false;
        }
    }
    return true;
#endif
}
