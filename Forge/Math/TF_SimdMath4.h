/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */
#include "Forge/Math/Internal/Types.h"

inline TSimdFloat4 tfSimd4fSplat(float value);
inline TSimdInt4 tfSimd4iSplat(int32_t value);

inline TSimdFloat4 tfSimd4fZero();
inline TSimdInt4 tfSimd4iZero();

inline Simd_FloatType  tfSimd4fToSimd1f(TSimdFloat4 value);
inline TSimdFloat2 tfSimd4fToSimd2f(TSimdFloat4 value);
inline TSimdFloat3 tfSimd4fToSimd3f(TSimdFloat4 value);
inline TSimdInt4 tfSimd4fToSimd4i(TSimdFloat4 value);
inline TSimdFloat4 tfSimd4iToSimd4f(TSimdInt4 value);

inline TSimdFloat4 tfSimd4fSplatIndex0(TSimdFloat4 value);
inline TSimdFloat4 tfSimd4fSplatIndex1(TSimdFloat4 value);
inline TSimdFloat4 tfSimd4fSplatIndex2(TSimdFloat4 value);
inline TSimdFloat4 tfSimd4fSplatIndex3(TSimdFloat4 value);

inline TSimdFloat4 tfSimd4fSelect(TSimdFloat4 arg0, TSimdFloat4 arg1, TSimdFloat4 mask);
inline TSimdInt4 tfSimd4iSelect(TSimdInt4 arg0, TSimdInt4 arg1, TSimdInt4 mask);

inline float tfSimd4fSelectIndex0(TSimdFloat4 value);
inline float tfSimd4fSelectIndex1(TSimdFloat4 value);
inline float tfSimd4fSelectIndex2(TSimdFloat4 value);
inline float tfSimd4fSelectIndex3(TSimdFloat4 value);

inline TSimdFloat4 tfSimdFloat4Load(float x, float y, float z, float w);
inline TSimdInt4 tfSimdInt4Load(int32_t x, int32_t y, int32_t z, int32_t w);

inline TSimdFloat4 tfSimd4fAdd(TSimdFloat4 arg1, TSimdFloat4 arg2);
inline TSimdFloat4 tfSimd4fSub(TSimdFloat4 arg1, TSimdFloat4 arg2);
inline TSimdFloat4 tfSimd4fMul(TSimdFloat4 arg1, TSimdFloat4 arg2);
inline TSimdFloat4 tfSimd4fMadd(TSimdFloat4 mul1, TSimdFloat4 mul2, TSimdFloat4 add);
inline TSimdFloat4 tfSimd4fDiv(TSimdFloat4 arg1, TSimdFloat4 arg2);
inline TSimdFloat4 tfSimd4fAbs(TSimdFloat4 value);

inline TSimdFloat4 tfSimd4fNot(TSimdFloat4 value);
inline TSimdFloat4 tfSimd4fAnd(TSimdFloat4 arg1, TSimdFloat4 arg2);
inline TSimdFloat4 tfSimd4fAndNot(TSimdFloat4 arg1, TSimdFloat4 arg2);
inline TSimdFloat4 tfSimd4fOr(TSimdFloat4 arg1, TSimdFloat4 arg2);
inline TSimdFloat4 tfSimd4fXor(TSimdFloat4 arg1, TSimdFloat4  arg2);

inline TSimdInt4 tfSimd4iNot(TSimdInt4 value);
inline TSimdInt4 tfSimd4iAnd(TSimdInt4 arg1, TSimdInt4 arg2);
inline TSimdInt4 tfSimd4iAndNot(TSimdInt4 arg1, TSimdInt4 arg2);
inline TSimdInt4 tfSimd4iOr(TSimdInt4 arg1, TSimdInt4 arg2);
inline TSimdInt4 tfSimd4iXor(TSimdInt4 arg1, TSimdInt4 arg2);

inline TSimdFloat4 tfSimd4fFloor(TSimdFloat4 value);
inline TSimdFloat4 tfSimd4fCeil(TSimdFloat4 value);
inline TSimdFloat4 tfSimd4fRound(TSimdFloat4 value); // Ties to even (banker's rounding)
inline TSimdFloat4 tfSimd4fTruncate(TSimdFloat4 value);
inline TSimdFloat4 tfSimd4fMin(TSimdFloat4 arg1, TSimdFloat4 arg2);
inline TSimdFloat4 tfSimd4fMax(TSimdFloat4 arg1, TSimdFloat4 arg2);
inline TSimdFloat4 tfSimd4fClamp(TSimdFloat4 value, TSimdFloat4 min, TSimdFloat4 max);

inline TSimdInt4 tfSimd4iCmpEq(TSimdInt4 arg1, TSimdInt4 arg2);
inline TSimdInt4 tfSimd4iCmpNeq(TSimdInt4 arg1, TSimdInt4 arg2);
inline TSimdInt4 tfSimd4iCmpGt(TSimdInt4 arg1, TSimdInt4 arg2);
inline TSimdInt4 tfSimd4iCmpGtEq(TSimdInt4 arg1, TSimdInt4 arg2);
inline TSimdInt4 tfSimd4iCmpLt(TSimdInt4 arg1, TSimdInt4 arg2);
inline TSimdInt4 tfSimd4iCmpLtEq(TSimdInt4 arg1, TSimdInt4 arg2);

inline TSimdFloat4 tfSimd4fCmpEq(TSimdFloat4 arg1, TSimdFloat4 arg2);
inline TSimdFloat4 tfSimd4fCmpNeq(TSimdFloat4 arg1, TSimdFloat4 arg2);
inline TSimdFloat4 tfSimd4fCmpGt(TSimdFloat4 arg1, TSimdFloat4 arg2);
inline TSimdFloat4 tfSimd4fCmpGtEq(TSimdFloat4 arg1, TSimdFloat4 arg2);
inline TSimdFloat4 tfSimd4fCmpLt(TSimdFloat4 arg1, TSimdFloat4 arg2);
inline TSimdFloat4 tfSimd4fCmpLtEq(TSimdFloat4 arg1, TSimdFloat4 arg2);

inline bool tfSimd4iCmpAllEq(TSimdInt4 arg1, TSimdInt4 arg2);
inline bool tfSimd4fCmpAllEq(TSimdFloat4 arg1, TSimdFloat4 arg2);

// ----------------------------------------------------------------
// --------------------- Implementaion ----------------------------
// ----------------------------------------------------------------
inline TSimdInt4 tfSimd4iSelect(TSimdInt4 arg0, TSimdInt4 arg1, TSimdInt4 mask) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_blendv_epi8(arg0, arg1, mask);
#else
    return {(mask.v[0] == 0) ? arg0.v[0] : arg1.v[0]
            , (mask.v[1] == 0) ? arg0.v[1] : arg1.v[1]
            , (mask.v[2] == 0) ? arg0.v[2] : arg1.v[2]
            , (mask.v[3] == 0) ? arg0.v[3] : arg1.v[3] };
#endif
}
inline TSimdFloat4 tfSimd4fSelect(TSimdFloat4 arg0, TSimdFloat4 arg1, TSimdFloat4 mask)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_blendv_ps(arg0, arg1, mask);
#else
    TSimdInt4 intMask =  tfSimd4fToSimd4i(mask);
    return { (intMask.v[0] == 0) ? arg0.v[0] : arg1.v[0]
            , (intMask.v[1] == 0) ? arg0.v[1] : arg1.v[1]
            , (intMask.v[2] == 0) ? arg0.v[2] : arg1.v[2]
            , (intMask.v[3] == 0) ? arg0.v[3] : arg1.v[3] };
#endif
}

inline TSimdFloat4 tfSimd4fZero() { return tfSimd4iToSimd4f(tfSimd4iZero()); }
inline TSimdInt4 tfSimd4iZero()
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_setzero_si128();
#else
    return { 0, 0, 0, 0 };
#endif
}

inline TSimdInt4 tfSimd4iNot(TSimdInt4 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    const TSimdInt4 invert = tfSimd4iSplat(TF_SIMDI_MAX);
    return _mm_andnot_si128(value, invert);
#else
    return { ~value.v[0], ~value.v[1], ~value.v[2], ~value.v[3] };
#endif
}
inline TSimdInt4 tfSimd4iAnd(TSimdInt4 arg1, TSimdInt4 arg2){
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_and_si128(arg1, arg2);
#else
    return { arg1.v[0] & arg2.v[0], arg1.v[1] & arg2.v[1], arg1.v[2] & arg2.v[2], arg1.v[3] & arg2.v[3] };
#endif

}
inline TSimdInt4 tfSimd4iAndNot(TSimdInt4 arg1, TSimdInt4 arg2) { 
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_andnot_si128(arg1, arg2); 
#else
    return { ~arg1.v[0] & arg2.v[0], ~arg1.v[1] & arg2.v[1], ~arg1.v[2] & arg2.v[2], ~arg1.v[3] & arg2.v[3] };
#endif
}
inline TSimdInt4 tfSimd4iOr(TSimdInt4 arg1, TSimdInt4 arg2){
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_or_si128(arg1, arg2); 
#else
    return { arg1.v[0] | arg2.v[0], arg1.v[1] | arg2.v[1], arg1.v[2] | arg2.v[2], arg1.v[3] | arg2.v[3] };
#endif
}
inline TSimdInt4 tfSimd4iXor(TSimdInt4 arg1, TSimdInt4 arg2){
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_xor_si128(arg1, arg2); 
#else
    return { arg1.v[0] ^ arg2.v[0], arg1.v[1] ^ arg2.v[1], arg1.v[2] ^ arg2.v[2], arg1.v[3] ^ arg2.v[3] };
#endif
}

inline TSimdFloat4 tfSimd4fNot(TSimdFloat4 value) { 
#if defined(TF_FEATURE_CPU_SSE)
    const TSimdFloat4 invert = tfSimd4fSplat((float)(0xFFFFFFFF));
    return _mm_andnot_ps(value, invert);
#else
    TSimdInt4 result = { { ~((int32_t)value.v[0]), ~((int32_t)value.v[1]),
                                 ~((int32_t)value.v[2]), ~((int32_t)value.v[3]) } };
    return tfSimd4iToSimd4f(result);
#endif
}
inline TSimdFloat4 tfSimd4fAnd(TSimdFloat4 arg1, TSimdFloat4 arg2) { 
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_and_ps(arg1, arg2);
#else
    TSimdInt4 result = { ((int32_t)arg1.v[0]) & ((int32_t)arg2.v[0]), ((int32_t)arg1.v[1]) & ((int32_t)arg2.v[1]),
                               ((int32_t)arg1.v[2]) & ((int32_t)arg2.v[2]), ((int32_t)arg1.v[3]) & ((int32_t)arg2.v[3]) };
    return tfSimd4iToSimd4f(result);
#endif
}
inline TSimdFloat4 tfSimd4fAndNot(TSimdFloat4 arg1, TSimdFloat4 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_andnot_ps(arg1, arg2);
#else
    TSimdInt4 result = { { ~((int32_t)arg1.v[0]) & ((int32_t)arg2.v[0]),
                                 ~((int32_t)arg1.v[1]) & ((int32_t)arg2.v[1]),
                                 ~((int32_t)arg1.v[2]) & ((int32_t)arg2.v[2]),
                                 ~((int32_t)arg1.v[3]) & ((int32_t)arg2.v[3]) } };
    return tfSimd4iToSimd4f(result);
#endif
}
inline TSimdFloat4 tfSimd4fOr(TSimdFloat4 arg1, TSimdFloat4 arg2) { 
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_or_ps(arg1, arg2);
#else
    TSimdInt4 result = { { ((int32_t)arg1.v[0]) | ((int32_t)arg2.v[0]),
                                 ((int32_t)arg1.v[1]) | ((int32_t)arg2.v[1]),
                                 ((int32_t)arg1.v[2]) | ((int32_t)arg2.v[2]),
                                 ((int32_t)arg1.v[3]) | ((int32_t)arg2.v[3]) } };
    return tfSimd4iToSimd4f(result);
#endif
}
inline TSimdFloat4 tfSimd4fXor(TSimdFloat4 arg1, TSimdFloat4 arg2) { 
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_xor_ps(arg1, arg2);
#else
    TSimdInt4 result = { { ((int32_t)arg1.v[0]) ^ ((int32_t)arg2.v[0]),
                                 ((int32_t)arg1.v[1]) ^ ((int32_t)arg2.v[1]),
                                 ((int32_t)arg1.v[2]) ^ ((int32_t)arg2.v[2]),
                                 ((int32_t)arg1.v[3]) ^ ((int32_t)arg2.v[3]) } };
    return tfSimd4iToSimd4f(result);
#endif
}

inline TSimdFloat4 tfSimd4fFloor(TSimdFloat4 value) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_floor_ps(value);
#else
    return { { floorf(value.v[0]), floorf(value.v[1]), floorf(value.v[2]), floorf(value.v[3]) } };
#endif
}
inline TSimdFloat4 tfSimd4fCeil(TSimdFloat4 value) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_ceil_ps(value);
#else
    return { { ceilf(value.v[0]), ceilf(value.v[1]), ceilf(value.v[2]), ceilf(value.v[3]) } };
#endif
}
inline TSimdFloat4 tfSimd4fRound(TSimdFloat4 value) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_round_ps(value, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC);
#else
    // While 'roundf' may seem the obvious choice here, it rounds halfway cases
    // away from zero regardless of the current rounding mode, but 'rintf' uses
    // the current rounding mode which is consistent with other implementations.
    return { { rintf(value.v[0]), rintf(value.v[1]), rintf(value.v[2]), rintf(value.v[3]) } };
#endif
}
inline TSimdFloat4 tfSimd4fTruncate(TSimdFloat4 value) { return tfSimd4iToSimd4f(tfSimd4fToSimd4i(value)); }
inline TSimdFloat4 tfSimd4fMin(TSimdFloat4 arg1, TSimdFloat4 arg2)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_min_ps(arg1, arg2);
#else
    return { { fminf(arg1.v[0], arg2.v[0]), fminf(arg1.v[1], arg2.v[1]), fminf(arg1.v[2], arg2.v[2]), fminf(arg1.v[3], arg2.v[3]) } };
#endif
}
inline TSimdFloat4 tfSimd4fMax(TSimdFloat4 arg1, TSimdFloat4 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_max_ps(arg1, arg2);
#else
    return { { fmaxf(arg1.v[0], arg2.v[0]), fmaxf(arg1.v[1], arg2.v[1]), fmaxf(arg1.v[2], arg2.v[2]), fmaxf(arg1.v[3], arg2.v[3]) } };
#endif
}
inline TSimdFloat4 tfSimd4fClamp(TSimdFloat4 value, TSimdFloat4 min, TSimdFloat4 max)
{
    return tfSimd4fMax(min, tfSimd4fMin(value, max));
}

inline TSimdInt4 tfSimd4fToSimd4i(TSimdFloat4 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_castps_si128(value);
#elif defined(TF_FEATURE_CPU_SCALAR)
    return { (int32_t)value.v[0], (int32_t)value.v[1], (int32_t)value.v[2], (int32_t)value.v[3] };
#endif
}

inline TSimdFloat4 tfSimd4iToSimd4f(TSimdInt4 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_castsi128_ps(value);
#elif defined(TF_FEATURE_CPU_SCALAR)
    return { (float)value.v[0], (float)value.v[1], (float)value.v[2], (float)value.v[3] };
#endif
}

inline float tfSimd4fSelectIndex0(TSimdFloat4 value) { 
#if defined(TF_FEATURE_CPU_SSE)
  return _mm_cvtss_f32(value);
#elif defined(TF_FEATURE_CPU_SCALAR)
  return value.v[0];
#endif
}
inline float tfSimd4fSelectIndex1(TSimdFloat4 value) { return tfSimd4fSelectIndex0(tfSimd4fSplatIndex1(value)); }
inline float tfSimd4fSelectIndex2(TSimdFloat4 value) { return tfSimd4fSelectIndex0(tfSimd4fSplatIndex2(value)); }
inline float tfSimd4fSelectIndex3(TSimdFloat4 value) { return tfSimd4fSelectIndex0(tfSimd4fSplatIndex3(value)); }

inline TSimdFloat4 tfSimd4fAdd(TSimdFloat4 arg1, TSimdFloat4 arg2)
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
inline TSimdFloat4 tfSimd4fSub(TSimdFloat4 arg1, TSimdFloat4 arg2)
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
inline TSimdFloat4 tfSimd4fMul(TSimdFloat4 arg1, TSimdFloat4 arg2) {
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
inline TSimdFloat4 tfSimd4fMadd(TSimdFloat4 mul1, TSimdFloat4 mul2, TSimdFloat4 add)
{
#if 0
    return _mm_fmadd_ps(mul1, mul2, add); // Requires FMA CPUID
#else
    return tfSimd4fAdd(tfSimd4fMul(mul1, mul2), add);
#endif
}
inline TSimdFloat4 tfSimd4fDiv(TSimdFloat4 arg1, TSimdFloat4 arg2) {
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

inline TSimdFloat4 tfSimd4fAbs(TSimdFloat4 value) { 
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
inline TSimdFloat4 tfSimdFloat4Load(float x, float y, float z, float w) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_set_ps(w, z, y, x);
#else
    return { x, y, z, w };
#endif
}


inline TSimdInt4 tfSimdInt4Load(int32_t x, int32_t y, int32_t z, int32_t w) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_set_epi32(w, z, y, x);
#else
    return { x, y, z, w };
#endif
}

inline Simd_FloatType tfSimd4fToSimd1f(TSimdFloat4 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return value;
#else
    return value.v[0];
#endif
}

inline TSimdFloat2 tfSimd4fToSimd2f(TSimdFloat4 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return value;
#else
    return {value.v[0], value.v[1]};
#endif
}

inline TSimdFloat3 tfSimd4fToSimd3f(TSimdFloat4 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return value;
#else
    return {value.v[0], value.v[1], value.v[2]};
#endif
}

inline TSimdFloat4 tfSimd4fSplatIndex0(TSimdFloat4 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_shuffle_ps(value, value, _MM_SHUFFLE(0, 0, 0, 0));
#else
  return {value.v[0],value.v[0],value.v[0],value.v[0]};
#endif
}

inline TSimdFloat4 tfSimd4fSplatIndex1(TSimdFloat4 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_shuffle_ps(value, value, _MM_SHUFFLE(1, 1, 1, 1));
#else
  return {value.v[1],value.v[1],value.v[1],value.v[1]};
#endif
}

inline TSimdFloat4 tfSimd4fSplatIndex2(TSimdFloat4 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_shuffle_ps(value, value, _MM_SHUFFLE(2, 2, 2, 2));
#else
  return {value.v[2],value.v[2],value.v[2],value.v[2]};
#endif
}

inline TSimdFloat4 tfSimd4fSplatIndex3(TSimdFloat4 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_shuffle_ps(value, value, _MM_SHUFFLE(3, 3, 3, 3));
#else
  return {value.v[3],value.v[3],value.v[3],value.v[3]};
#endif
}

inline TSimdInt4 tfSimd4iSplat(int32_t value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_set1_epi32(value);
#else
    return { value, value, value, value };
#endif
}

inline TSimdFloat4 tfSimd4fSplat(float value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_set1_ps(value);
#else
    return { value, value, value, value };
#endif
}

inline TSimdInt4 tfSimdSplat4i(int32_t value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_set1_epi32(value);
#else
    return { value, value, value, value };
#endif
}


inline TSimdInt4 tfSimd4iCmpEq(TSimdInt4 arg1, TSimdInt4 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_cmpeq_epi32(arg1, arg2);
#else
    return { { (arg1.v[0] == arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, 
               (arg1.v[1] == arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000,
               (arg1.v[2] == arg2.v[2]) ? (int32_t)0xFFFFFFFF : 0x00000000, 
               (arg1.v[3] == arg2.v[3]) ? (int32_t)0xFFFFFFFF : 0x00000000 } };
#endif
}
inline TSimdInt4 tfSimd4iCmpNeq(TSimdInt4 arg1, TSimdInt4 arg2) {
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
inline TSimdInt4 tfSimd4iCmpGt(TSimdInt4 arg1, TSimdInt4 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_cmpgt_epi32(arg1, arg2);
#else
    return { { (arg1.v[0] > arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, 
               (arg1.v[1] > arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000,
               (arg1.v[2] > arg2.v[2]) ? (int32_t)0xFFFFFFFF : 0x00000000, 
               (arg1.v[3] > arg2.v[3]) ? (int32_t)0xFFFFFFFF : 0x00000000 } };
#endif
}
inline TSimdInt4 tfSimd4iCmpGtEq(TSimdInt4 arg1, TSimdInt4 arg2) {
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
inline TSimdInt4 tfSimd4iCmpLt(TSimdInt4 arg1, TSimdInt4 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_cmplt_epi32(arg1, arg2);
#else
    return { { (arg1.v[0] < arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, 
               (arg1.v[1] < arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000,
               (arg1.v[2] < arg2.v[2]) ? (int32_t)0xFFFFFFFF : 0x00000000, 
               (arg1.v[3] < arg2.v[3]) ? (int32_t)0xFFFFFFFF : 0x00000000 } };
#endif
}
inline TSimdInt4 tfSimd4iCmpLtEq(TSimdInt4 arg1, TSimdInt4 arg2) {
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




//inline bool tfSimd4fCmpAllEq(TSimdFloat4 arg1, TSimdFloat4 arg2) {
//#if defined(TF_FEATURE_CPU_SSE)
//    const TSimdFloat4 compare = tfSimd4fCmpAllEq(arg1, arg2);
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

inline bool tfSimd4iCmpAllEq(TSimdInt4 arg1, TSimdInt4 arg2)
{
#if defined(TF_FEATURE_CPU_SSE)
    const TSimdInt4 compare = tfSimd4iCmpEq(arg1, arg2);
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
