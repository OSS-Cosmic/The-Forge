/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */
#include "Forge/Math/Internal/Types.h"

inline Simd_FloatType4 tfSimd4fSplat(float value);
inline Simd_Int32Type4 tfSimd4iSplat(int32_t value);

inline Simd_FloatType4 tfSimd4fZero();
inline Simd_Int32Type4 tfSimd4iZero();

inline Simd_FloatType  tfSimd4fToSimd1f(Simd_FloatType4 value);
inline Simd_FloatType2 tfSimd4fToSimd2f(Simd_FloatType4 value);
inline Simd_FloatType3 tfSimd4fToSimd3f(Simd_FloatType4 value);
inline Simd_Int32Type4 tfSimd4fToSimd4i(Simd_FloatType4 value);
inline Simd_FloatType4 tfSimd4iToSimd4f(Simd_Int32Type4 value);

inline Simd_FloatType4 tfSimd4fSplatIndex0(Simd_FloatType4 value);
inline Simd_FloatType4 tfSimd4fSplatIndex1(Simd_FloatType4 value);
inline Simd_FloatType4 tfSimd4fSplatIndex2(Simd_FloatType4 value);
inline Simd_FloatType4 tfSimd4fSplatIndex3(Simd_FloatType4 value);

inline Simd_FloatType4 tfSimd4fSelect(Simd_FloatType4 arg0, Simd_FloatType4 arg1, Simd_FloatType4 mask);
inline Simd_Int32Type4 tfSimd4iSelect(Simd_Int32Type4 arg0, Simd_Int32Type4 arg1, Simd_Int32Type4 mask);

inline float tfSimd4fSelectIndex0(Simd_FloatType4 value);
inline float tfSimd4fSelectIndex1(Simd_FloatType4 value);
inline float tfSimd4fSelectIndex2(Simd_FloatType4 value);
inline float tfSimd4fSelectIndex3(Simd_FloatType4 value);

inline Simd_FloatType4 tfSimd4fLoadImmediate(float x, float y, float z, float w);
inline Simd_Int32Type4 tfSimd4iLoadImmediate(int32_t x, int32_t y, int32_t z, int32_t w);

inline Simd_FloatType4 tfSimd4fAdd(Simd_FloatType4 arg1, Simd_FloatType4 arg2);
inline Simd_FloatType4 tfSimd4fSub(Simd_FloatType4 arg1, Simd_FloatType4 arg2);
inline Simd_FloatType4 tfSimd4fMul(Simd_FloatType4 arg1, Simd_FloatType4 arg2);
inline Simd_FloatType4 tfSimd4fMadd(Simd_FloatType4 mul1, Simd_FloatType4 mul2, Simd_FloatType4 add);
inline Simd_FloatType4 tfSimd4fDiv(Simd_FloatType4 arg1, Simd_FloatType4 arg2);
inline Simd_FloatType4 tfSimd4fAbs(Simd_FloatType4 value);

inline Simd_FloatType4 tfSimd4fNot(Simd_FloatType4 value);
inline Simd_FloatType4 tfSimd4fAnd(Simd_FloatType4 arg1, Simd_FloatType4 arg2);
inline Simd_FloatType4 tfSimd4fAndNot(Simd_FloatType4 arg1, Simd_FloatType4 arg2);
inline Simd_FloatType4 tfSimd4fOr(Simd_FloatType4 arg1, Simd_FloatType4 arg2);
inline Simd_FloatType4 tfSimd4fXor(Simd_FloatType4 arg1, Simd_FloatType4  arg2);

inline Simd_Int32Type4 tfSimd4iNot(Simd_Int32Type4 value);
inline Simd_Int32Type4 tfSimd4iAnd(Simd_Int32Type4 arg1, Simd_Int32Type4 arg2);
inline Simd_Int32Type4 tfSimd4iAndNot(Simd_Int32Type4 arg1, Simd_Int32Type4 arg2);
inline Simd_Int32Type4 tfSimd4iOr(Simd_Int32Type4 arg1, Simd_Int32Type4 arg2);
inline Simd_Int32Type4 tfSimd4iXor(Simd_Int32Type4 arg1, Simd_Int32Type4 arg2);

inline Simd_FloatType4 tfSimd4fFloor(Simd_FloatType4 value);
inline Simd_FloatType4 tfSimd4fCeil(Simd_FloatType4 value);
inline Simd_FloatType4 tfSimd4fRound(Simd_FloatType4 value); // Ties to even (banker's rounding)
inline Simd_FloatType4 tfSimd4fTruncate(Simd_FloatType4 value);
inline Simd_FloatType4 tfSimd4fMin(Simd_FloatType4 arg1, Simd_FloatType4 arg2);
inline Simd_FloatType4 tfSimd4fMax(Simd_FloatType4 arg1, Simd_FloatType4 arg2);
inline Simd_FloatType4 tfSimd4fClamp(Simd_FloatType4 value, Simd_FloatType4 min, Simd_FloatType4 max);

inline Simd_Int32Type4 tfSimd4iCmpEq(Simd_Int32Type4 arg1, Simd_Int32Type4 arg2);
inline Simd_Int32Type4 tfSimd4iCmpNeq(Simd_Int32Type4 arg1, Simd_Int32Type4 arg2);
inline Simd_Int32Type4 tfSimd4iCmpGt(Simd_Int32Type4 arg1, Simd_Int32Type4 arg2);
inline Simd_Int32Type4 tfSimd4iCmpGtEq(Simd_Int32Type4 arg1, Simd_Int32Type4 arg2);
inline Simd_Int32Type4 tfSimd4iCmpLt(Simd_Int32Type4 arg1, Simd_Int32Type4 arg2);
inline Simd_Int32Type4 tfSimd4iCmpLtEq(Simd_Int32Type4 arg1, Simd_Int32Type4 arg2);

inline Simd_FloatType4 tfSimd4fCmpEq(Simd_FloatType4 arg1, Simd_FloatType4 arg2);
inline Simd_FloatType4 tfSimd4fCmpNeq(Simd_FloatType4 arg1, Simd_FloatType4 arg2);
inline Simd_FloatType4 tfSimd4fCmpGt(Simd_FloatType4 arg1, Simd_FloatType4 arg2);
inline Simd_FloatType4 tfSimd4fCmpGtEq(Simd_FloatType4 arg1, Simd_FloatType4 arg2);
inline Simd_FloatType4 tfSimd4fCmpLt(Simd_FloatType4 arg1, Simd_FloatType4 arg2);
inline Simd_FloatType4 tfSimd4fCmpLtEq(Simd_FloatType4 arg1, Simd_FloatType4 arg2);

inline bool tfSimd4iCmpAllEq(Simd_Int32Type4 arg1, Simd_Int32Type4 arg2);
inline bool tfSimd4fCmpAllEq(Simd_FloatType4 arg1, Simd_FloatType4 arg2);

// ----------------------------------------------------------------
// --------------------- Implementaion ----------------------------
// ----------------------------------------------------------------
inline Simd_Int32Type4 tfSimd4iSelect(Simd_Int32Type4 arg0, Simd_Int32Type4 arg1, Simd_Int32Type4 mask) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_blendv_epi8(arg0, arg1, mask);
#else
    return {(mask.v[0] == 0) ? arg0.v[0] : arg1.v[0]
            , (mask.v[1] == 0) ? arg0.v[1] : arg1.v[1]
            , (mask.v[2] == 0) ? arg0.v[2] : arg1.v[2]
            , (mask.v[3] == 0) ? arg0.v[3] : arg1.v[3] };
#endif
}
inline Simd_FloatType4 tfSimd4fSelect(Simd_FloatType4 arg0, Simd_FloatType4 arg1, Simd_FloatType4 mask)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_blendv_ps(arg0, arg1, mask);
#else
    Simd_Int32Type4 intMask =  tfSimd4fToSimd4i(mask);
    return { (intMask.v[0] == 0) ? arg0.v[0] : arg1.v[0]
            , (intMask.v[1] == 0) ? arg0.v[1] : arg1.v[1]
            , (intMask.v[2] == 0) ? arg0.v[2] : arg1.v[2]
            , (intMask.v[3] == 0) ? arg0.v[3] : arg1.v[3] };
#endif
}

inline Simd_FloatType4 tfSimd4fZero() { return tfSimd4iToSimd4f(tfSimd4iZero()); }
inline Simd_Int32Type4 tfSimd4iZero()
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_setzero_si128();
#else
    return { 0, 0, 0, 0 };
#endif
}

inline Simd_Int32Type4 tfSimd4iNot(Simd_Int32Type4 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    const Simd_Int32Type4 invert = tfSimd4iSplat(TF_SIMDI_MAX);
    return _mm_andnot_si128(value, invert);
#else
    return { ~value.v[0], ~value.v[1], ~value.v[2], ~value.v[3] };
#endif
}
inline Simd_Int32Type4 tfSimd4iAnd(Simd_Int32Type4 arg1, Simd_Int32Type4 arg2){
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_and_si128(arg1, arg2);
#else
    return { arg1.v[0] & arg2.v[0], arg1.v[1] & arg2.v[1], arg1.v[2] & arg2.v[2], arg1.v[3] & arg2.v[3] };
#endif

}
inline Simd_Int32Type4 tfSimd4iAndNot(Simd_Int32Type4 arg1, Simd_Int32Type4 arg2) { 
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_andnot_si128(arg1, arg2); 
#else
    return { ~arg1.v[0] & arg2.v[0], ~arg1.v[1] & arg2.v[1], ~arg1.v[2] & arg2.v[2], ~arg1.v[3] & arg2.v[3] };
#endif
}
inline Simd_Int32Type4 tfSimd4iOr(Simd_Int32Type4 arg1, Simd_Int32Type4 arg2){
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_or_si128(arg1, arg2); 
#else
    return { arg1.v[0] | arg2.v[0], arg1.v[1] | arg2.v[1], arg1.v[2] | arg2.v[2], arg1.v[3] | arg2.v[3] };
#endif
}
inline Simd_Int32Type4 tfSimd4iXor(Simd_Int32Type4 arg1, Simd_Int32Type4 arg2){
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_xor_si128(arg1, arg2); 
#else
    return { arg1.v[0] ^ arg2.v[0], arg1.v[1] ^ arg2.v[1], arg1.v[2] ^ arg2.v[2], arg1.v[3] ^ arg2.v[3] };
#endif
}

inline Simd_FloatType4 tfSimd4fNot(Simd_FloatType4 value) { 
#if defined(TF_FEATURE_CPU_SSE)
    const Simd_FloatType4 invert = tfSimd4fSplat((float)(0xFFFFFFFF));
    return _mm_andnot_ps(value, invert);
#else
    Simd_Int32Type4 result = { { ~((int32_t)value.v[0]), ~((int32_t)value.v[1]),
                                 ~((int32_t)value.v[2]), ~((int32_t)value.v[3]) } };
    return tfSimd4iToSimd4f(result);
#endif
}
inline Simd_FloatType4 tfSimd4fAnd(Simd_FloatType4 arg1, Simd_FloatType4 arg2) { 
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_and_ps(arg1, arg2);
#else
    Simd_Int32Type4 result = { ((int32_t)arg1.v[0]) & ((int32_t)arg2.v[0]), ((int32_t)arg1.v[1]) & ((int32_t)arg2.v[1]),
                               ((int32_t)arg1.v[2]) & ((int32_t)arg2.v[2]), ((int32_t)arg1.v[3]) & ((int32_t)arg2.v[3]) };
    return tfSimd4iToSimd4f(result);
#endif
}
inline Simd_FloatType4 tfSimd4fAndNot(Simd_FloatType4 arg1, Simd_FloatType4 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_andnot_ps(arg1, arg2);
#else
    Simd_Int32Type4 result = { { ~((int32_t)arg1.v[0]) & ((int32_t)arg2.v[0]),
                                 ~((int32_t)arg1.v[1]) & ((int32_t)arg2.v[1]),
                                 ~((int32_t)arg1.v[2]) & ((int32_t)arg2.v[2]),
                                 ~((int32_t)arg1.v[3]) & ((int32_t)arg2.v[3]) } };
    return tfSimd4iToSimd4f(result);
#endif
}
inline Simd_FloatType4 tfSimd4fOr(Simd_FloatType4 arg1, Simd_FloatType4 arg2) { 
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_or_ps(arg1, arg2);
#else
    Simd_Int32Type4 result = { { ((int32_t)arg1.v[0]) | ((int32_t)arg2.v[0]),
                                 ((int32_t)arg1.v[1]) | ((int32_t)arg2.v[1]),
                                 ((int32_t)arg1.v[2]) | ((int32_t)arg2.v[2]),
                                 ((int32_t)arg1.v[3]) | ((int32_t)arg2.v[3]) } };
    return tfSimd4iToSimd4f(result);
#endif
}
inline Simd_FloatType4 tfSimd4fXor(Simd_FloatType4 arg1, Simd_FloatType4 arg2) { 
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_xor_ps(arg1, arg2);
#else
    Simd_Int32Type4 result = { { ((int32_t)arg1.v[0]) ^ ((int32_t)arg2.v[0]),
                                 ((int32_t)arg1.v[1]) ^ ((int32_t)arg2.v[1]),
                                 ((int32_t)arg1.v[2]) ^ ((int32_t)arg2.v[2]),
                                 ((int32_t)arg1.v[3]) ^ ((int32_t)arg2.v[3]) } };
    return tfSimd4iToSimd4f(result);
#endif
}

inline Simd_FloatType4 tfSimd4fFloor(Simd_FloatType4 value) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_floor_ps(value);
#else
    return { { floorf(value.v[0]), floorf(value.v[1]), floorf(value.v[2]), floorf(value.v[3]) } };
#endif
}
inline Simd_FloatType4 tfSimd4fCeil(Simd_FloatType4 value) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_ceil_ps(value);
#else
    return { { ceilf(value.v[0]), ceilf(value.v[1]), ceilf(value.v[2]), ceilf(value.v[3]) } };
#endif
}
inline Simd_FloatType4 tfSimd4fRound(Simd_FloatType4 value) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_round_ps(value, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC);
#else
    // While 'roundf' may seem the obvious choice here, it rounds halfway cases
    // away from zero regardless of the current rounding mode, but 'rintf' uses
    // the current rounding mode which is consistent with other implementations.
    return { { rintf(value.v[0]), rintf(value.v[1]), rintf(value.v[2]), rintf(value.v[3]) } };
#endif
}
inline Simd_FloatType4 tfSimd4fTruncate(Simd_FloatType4 value) { return tfSimd4iToSimd4f(tfSimd4fToSimd4i(value)); }
inline Simd_FloatType4 tfSimd4fMin(Simd_FloatType4 arg1, Simd_FloatType4 arg2)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_min_ps(arg1, arg2);
#else
    return { { fminf(arg1.v[0], arg2.v[0]), fminf(arg1.v[1], arg2.v[1]), fminf(arg1.v[2], arg2.v[2]), fminf(arg1.v[3], arg2.v[3]) } };
#endif
}
inline Simd_FloatType4 tfSimd4fMax(Simd_FloatType4 arg1, Simd_FloatType4 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_max_ps(arg1, arg2);
#else
    return { { fmaxf(arg1.v[0], arg2.v[0]), fmaxf(arg1.v[1], arg2.v[1]), fmaxf(arg1.v[2], arg2.v[2]), fmaxf(arg1.v[3], arg2.v[3]) } };
#endif
}
inline Simd_FloatType4 tfSimd4fClamp(Simd_FloatType4 value, Simd_FloatType4 min, Simd_FloatType4 max)
{
    return tfSimd4fMax(min, tfSimd4fMin(value, max));
}

inline Simd_Int32Type4 tfSimd4fToSimd4i(Simd_FloatType4 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_castps_si128(value);
#elif defined(TF_FEATURE_CPU_SCALAR)
    return { (int32_t)value.v[0], (int32_t)value.v[1], (int32_t)value.v[2], (int32_t)value.v[3] };
#endif
}

inline Simd_FloatType4 tfSimd4iToSimd4f(Simd_Int32Type4 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_castsi128_ps(value);
#elif defined(TF_FEATURE_CPU_SCALAR)
    return { (float)value.v[0], (float)value.v[1], (float)value.v[2], (float)value.v[3] };
#endif
}

inline float tfSimd4fSelectIndex0(Simd_FloatType4 value) { 
#if defined(TF_FEATURE_CPU_SSE)
  return _mm_cvtss_f32(value);
#elif defined(TF_FEATURE_CPU_SCALAR)
  return value.v[0];
#endif
}
inline float tfSimd4fSelectIndex1(Simd_FloatType4 value) { return tfSimd4fSelectIndex0(tfSimd4fSplatIndex1(value)); }
inline float tfSimd4fSelectIndex2(Simd_FloatType4 value) { return tfSimd4fSelectIndex0(tfSimd4fSplatIndex2(value)); }
inline float tfSimd4fSelectIndex3(Simd_FloatType4 value) { return tfSimd4fSelectIndex0(tfSimd4fSplatIndex3(value)); }

inline Simd_FloatType4 tfSimd4fAdd(Simd_FloatType4 arg1, Simd_FloatType4 arg2)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_add_ps(arg1, arg2);
#else
    return {
        arg1.v[0] + arg2.v[0],
        arg1.v[1] + arg2.v[1],
        arg1.v[2] + arg2.v[2],
        arg1.v[3] + arg2.v[3],
    };
#endif
}
inline Simd_FloatType4 tfSimd4fSub(Simd_FloatType4 arg1, Simd_FloatType4 arg2)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_sub_ps(arg1, arg2);
#else
    return {
        arg1.v[0] - arg2.v[0],
        arg1.v[1] - arg2.v[1],
        arg1.v[2] - arg2.v[2],
        arg1.v[3] - arg2.v[3],
    };
#endif
}
inline Simd_FloatType4 tfSimd4fMul(Simd_FloatType4 arg1, Simd_FloatType4 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_mul_ps(arg1, arg2); 
#else
    return {
        arg1.v[0] * arg2.v[0],
        arg1.v[1] * arg2.v[1],
        arg1.v[2] * arg2.v[2],
        arg1.v[3] * arg2.v[3],
    };
#endif

}
inline Simd_FloatType4 tfSimd4fMadd(Simd_FloatType4 mul1, Simd_FloatType4 mul2, Simd_FloatType4 add)
{
#if 0
    return _mm_fmadd_ps(mul1, mul2, add); // Requires FMA CPUID
#else
    return tfSimd4fAdd(tfSimd4fMul(mul1, mul2), add);
#endif
}
inline Simd_FloatType4 tfSimd4fDiv(Simd_FloatType4 arg1, Simd_FloatType4 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_div_ps(arg1, arg2);
#else
    return {
        arg1.v[0] / arg2.v[0],
        arg1.v[1] / arg2.v[1],
        arg1.v[2] / arg2.v[2],
        arg1.v[3] / arg2.v[3],
    };
#endif
}

inline Simd_FloatType4 tfSimd4fAbs(Simd_FloatType4 value) { 
#if defined(TF_FEATURE_CPU_SSE)
    return value;
    //return _mm_abs_epi32(value); 
#else
    return {
        abs(value.v[0]),
        abs(value.v[1]),
        abs(value.v[2]),
        abs(value.v[3]),
    };
#endif
}
inline Simd_FloatType4 tfSimd4fLoadImmediate(float x, float y, float z, float w) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_set_ps(w, z, y, x);
#else
    return { x, y, z, w };
#endif
}


inline Simd_Int32Type4 tfSimd4iLoadImmediate(int32_t x, int32_t y, int32_t z, int32_t w) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_set_epi32(w, z, y, x);
#else
    return { x, y, z, w };
#endif
}

inline Simd_FloatType tfSimd4fToSimd1f(Simd_FloatType4 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return value;
#else
    return value.v[0];
#endif
}

inline Simd_FloatType2 tfSimd4fToSimd2f(Simd_FloatType4 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return value;
#else
    return {value.v[0], value.v[1]};
#endif
}

inline Simd_FloatType3 tfSimd4fToSimd3f(Simd_FloatType4 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return value;
#else
    return {value.v[0], value.v[1], value.v[2]};
#endif
}

inline Simd_FloatType4 tfSimd4fSplatIndex0(Simd_FloatType4 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_shuffle_ps(value, value, _MM_SHUFFLE(0, 0, 0, 0));
#else
  return {value.v[0],value.v[0],value.v[0],value.v[0]};
#endif
}

inline Simd_FloatType4 tfSimd4fSplatIndex1(Simd_FloatType4 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_shuffle_ps(value, value, _MM_SHUFFLE(1, 1, 1, 1));
#else
  return {value.v[1],value.v[1],value.v[1],value.v[1]};
#endif
}

inline Simd_FloatType4 tfSimd4fSplatIndex2(Simd_FloatType4 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_shuffle_ps(value, value, _MM_SHUFFLE(2, 2, 2, 2));
#else
  return {value.v[2],value.v[2],value.v[2],value.v[2]};
#endif
}

inline Simd_FloatType4 tfSimd4fSplatIndex3(Simd_FloatType4 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_shuffle_ps(value, value, _MM_SHUFFLE(3, 3, 3, 3));
#else
  return {value.v[3],value.v[3],value.v[3],value.v[3]};
#endif
}

inline Simd_Int32Type4 tfSimd4iSplat(int32_t value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_set1_epi32(value);
#else
    return { value, value, value, value };
#endif
}

inline Simd_FloatType4 tfSimd4fSplat(float value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_set1_ps(value);
#else
    return { value, value, value, value };
#endif
}

inline Simd_Int32Type4 tfSimdSplat4i(int32_t value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_set1_epi32(value);
#else
    return { value, value, value, value };
#endif
}


inline Simd_Int32Type4 tfSimd4iCmpEq(Simd_Int32Type4 arg1, Simd_Int32Type4 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_cmpeq_epi32(arg1, arg2);
#else
    return { { (arg1.v[0] == arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, 
               (arg1.v[1] == arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000,
               (arg1.v[2] == arg2.v[2]) ? (int32_t)0xFFFFFFFF : 0x00000000, 
               (arg1.v[3] == arg2.v[3]) ? (int32_t)0xFFFFFFFF : 0x00000000 } };
#endif
}
inline Simd_Int32Type4 tfSimd4iCmpNeq(Simd_Int32Type4 arg1, Simd_Int32Type4 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_xor_si128(
        _mm_cmpeq_epi32(arg1, arg2), 
        _mm_set1_epi32((int32_t)0xFFFFFFFF));
#else
    return { { (arg1.v[0] != arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, 
               (arg1.v[1] != arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000,
               (arg1.v[2] != arg2.v[2]) ? (int32_t)0xFFFFFFFF : 0x00000000, 
               (arg1.v[3] != arg2.v[3]) ? (int32_t)0xFFFFFFFF : 0x00000000 } };
#endif
}
inline Simd_Int32Type4 tfSimd4iCmpGt(Simd_Int32Type4 arg1, Simd_Int32Type4 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_cmpgt_epi32(arg1, arg2);
#else
    return { { (arg1.v[0] > arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, 
               (arg1.v[1] > arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000,
               (arg1.v[2] > arg2.v[2]) ? (int32_t)0xFFFFFFFF : 0x00000000, 
               (arg1.v[3] > arg2.v[3]) ? (int32_t)0xFFFFFFFF : 0x00000000 } };
#endif
}
inline Simd_Int32Type4 tfSimd4iCmpGtEq(Simd_Int32Type4 arg1, Simd_Int32Type4 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_or_si128(
        _mm_cmpgt_epi32(arg1, arg2), 
        _mm_cmpeq_epi32(arg1, arg2));
#else
    return { { (arg1.v[0] >= arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, 
               (arg1.v[1] >= arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000,
               (arg1.v[2] >= arg2.v[2]) ? (int32_t)0xFFFFFFFF : 0x00000000, 
               (arg1.v[3] >= arg2.v[3]) ? (int32_t)0xFFFFFFFF : 0x00000000 } };
#endif
}
inline Simd_Int32Type4 tfSimd4iCmpLt(Simd_Int32Type4 arg1, Simd_Int32Type4 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_cmplt_epi32(arg1, arg2);
#else
    return { { (arg1.v[0] < arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, 
               (arg1.v[1] < arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000,
               (arg1.v[2] < arg2.v[2]) ? (int32_t)0xFFFFFFFF : 0x00000000, 
               (arg1.v[3] < arg2.v[3]) ? (int32_t)0xFFFFFFFF : 0x00000000 } };
#endif
}
inline Simd_Int32Type4 tfSimd4iCmpLtEq(Simd_Int32Type4 arg1, Simd_Int32Type4 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_or_si128(
        _mm_cmplt_epi32(arg1, arg2), 
        _mm_cmpeq_epi32(arg1, arg2));
#else
    return { { (arg1.v[0] < arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, 
               (arg1.v[1] < arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000,
               (arg1.v[2] < arg2.v[2]) ? (int32_t)0xFFFFFFFF : 0x00000000, 
               (arg1.v[3] < arg2.v[3]) ? (int32_t)0xFFFFFFFF : 0x00000000 } };
#endif

}




//inline bool tfSimd4fCmpAllEq(Simd_FloatType4 arg1, Simd_FloatType4 arg2) {
//#if defined(TF_FEATURE_CPU_SSE)
//    const Simd_FloatType4 compare = tfSimd4fCmpAllEq(arg1, arg2);
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

inline bool tfSimd4iCmpAllEq(Simd_Int32Type4 arg1, Simd_Int32Type4 arg2)
{
#if defined(TF_FEATURE_CPU_SSE)
    const Simd_Int32Type4 compare = tfSimd4iCmpEq(arg1, arg2);
    return (_mm_movemask_epi8(compare) & 0xf) == 0xf;
#else
    for(int i = 0; i < 4; i++) {
        if (arg1.v[i] != arg2.v[i])
        {
            return false;
        }
    }
    return true;
#endif
}
