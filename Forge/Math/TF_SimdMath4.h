/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */
#include "Forge/Math/Internal/Types.h"

inline TSimd32fx4 tfSimd4fSplat(float value);
inline TSimdi32x4 tfSimd4iSplat(int32_t value);

inline TSimd32fx4 tfSimd4fZero();
inline TSimdi32x4 tfSimd4iZero();

inline Simd_FloatType  tfSimd4fToSimd1f(TSimd32fx4 value);
inline TSimdf32x2 tfSimd4fToSimd2f(TSimd32fx4 value);
inline TSimdf32x3 tfSimd4fToSimd3f(TSimd32fx4 value);
inline TSimdi32x4 tfSimd4fToSimd4i(TSimd32fx4 value);
inline TSimd32fx4 tfSimd4iToSimd4f(TSimdi32x4 value);

inline TSimd32fx4 tfSimd4fSplatIndex0(TSimd32fx4 value);
inline TSimd32fx4 tfSimd4fSplatIndex1(TSimd32fx4 value);
inline TSimd32fx4 tfSimd4fSplatIndex2(TSimd32fx4 value);
inline TSimd32fx4 tfSimd4fSplatIndex3(TSimd32fx4 value);

inline TSimd32fx4 tfSimd4fSelect(TSimd32fx4 arg0, TSimd32fx4 arg1, TSimd32fx4 mask);
inline TSimdi32x4 tfSimd4iSelect(TSimdi32x4 arg0, TSimdi32x4 arg1, TSimdi32x4 mask);

inline float tfS32x4FSelectIndex0(TSimd32fx4 value);
inline float tfS32x4FSelectIndex1(TSimd32fx4 value);
inline float tfS32x4FSelectIndex2(TSimd32fx4 value);
inline float tfS32x4FSelectIndex3(TSimd32fx4 value);

inline TSimd32fx4 tfSimdFloat4Load(float x, float y, float z, float w);
inline TSimdi32x4 tfSimdInt4Load(int32_t x, int32_t y, int32_t z, int32_t w);

inline TSimd32fx4 tfSimd4fAdd(TSimd32fx4 arg1, TSimd32fx4 arg2);
inline TSimd32fx4 tfSimd4fSub(TSimd32fx4 arg1, TSimd32fx4 arg2);
inline TSimd32fx4 tfSimd4fMul(TSimd32fx4 arg1, TSimd32fx4 arg2);
inline TSimd32fx4 tfSimd4fMadd(TSimd32fx4 mul1, TSimd32fx4 mul2, TSimd32fx4 add);
inline TSimd32fx4 tfSimd4fDiv(TSimd32fx4 arg1, TSimd32fx4 arg2);
inline TSimd32fx4 tfSimd4fAbs(TSimd32fx4 value);

inline TSimd32fx4 tfSimd4fNot(TSimd32fx4 value);
inline TSimd32fx4 tfSimd4fAnd(TSimd32fx4 arg1, TSimd32fx4 arg2);
inline TSimd32fx4 tfSimd4fAndNot(TSimd32fx4 arg1, TSimd32fx4 arg2);
inline TSimd32fx4 tfSimd4fOr(TSimd32fx4 arg1, TSimd32fx4 arg2);
inline TSimd32fx4 tfSimd4fXor(TSimd32fx4 arg1, TSimd32fx4  arg2);

inline TSimdi32x4 tfSimd4iNot(TSimdi32x4 value);
inline TSimdi32x4 tfSimd4iAnd(TSimdi32x4 arg1, TSimdi32x4 arg2);
inline TSimdi32x4 tfSimd4iAndNot(TSimdi32x4 arg1, TSimdi32x4 arg2);
inline TSimdi32x4 tfSimd4iOr(TSimdi32x4 arg1, TSimdi32x4 arg2);
inline TSimdi32x4 tfSimd4iXor(TSimdi32x4 arg1, TSimdi32x4 arg2);

inline TSimd32fx4 tfSimd4fFloor(TSimd32fx4 value);
inline TSimd32fx4 tfSimd4fCeil(TSimd32fx4 value);
inline TSimd32fx4 tfSimd4fRound(TSimd32fx4 value); // Ties to even (banker's rounding)
inline TSimd32fx4 tfSimd4fTruncate(TSimd32fx4 value);
inline TSimd32fx4 tfSimd4fMin(TSimd32fx4 arg1, TSimd32fx4 arg2);
inline TSimd32fx4 tfSimd4fMax(TSimd32fx4 arg1, TSimd32fx4 arg2);
inline TSimd32fx4 tfSimd4fClamp(TSimd32fx4 value, TSimd32fx4 min, TSimd32fx4 max);

inline TSimdi32x4 tfSimd4iCmpEq(TSimdi32x4 arg1, TSimdi32x4 arg2);
inline TSimdi32x4 tfSimd4iCmpNeq(TSimdi32x4 arg1, TSimdi32x4 arg2);
inline TSimdi32x4 tfSimd4iCmpGt(TSimdi32x4 arg1, TSimdi32x4 arg2);
inline TSimdi32x4 tfSimd4iCmpGtEq(TSimdi32x4 arg1, TSimdi32x4 arg2);
inline TSimdi32x4 tfSimd4iCmpLt(TSimdi32x4 arg1, TSimdi32x4 arg2);
inline TSimdi32x4 tfSimd4iCmpLtEq(TSimdi32x4 arg1, TSimdi32x4 arg2);

inline TSimd32fx4 tfSimd4fCmpEq(TSimd32fx4 arg1, TSimd32fx4 arg2);
inline TSimd32fx4 tfSimd4fCmpNeq(TSimd32fx4 arg1, TSimd32fx4 arg2);
inline TSimd32fx4 tfSimd4fCmpGt(TSimd32fx4 arg1, TSimd32fx4 arg2);
inline TSimd32fx4 tfSimd4fCmpGtEq(TSimd32fx4 arg1, TSimd32fx4 arg2);
inline TSimd32fx4 tfSimd4fCmpLt(TSimd32fx4 arg1, TSimd32fx4 arg2);
inline TSimd32fx4 tfSimd4fCmpLtEq(TSimd32fx4 arg1, TSimd32fx4 arg2);

inline bool tfSimd4iCmpAllEq(TSimdi32x4 arg1, TSimdi32x4 arg2);
inline bool tfSimd4fCmpAllEq(TSimd32fx4 arg1, TSimd32fx4 arg2);

// ----------------------------------------------------------------
// --------------------- Implementaion ----------------------------
// ----------------------------------------------------------------
inline TSimdi32x4 tfSimd4iSelect(TSimdi32x4 arg0, TSimdi32x4 arg1, TSimdi32x4 mask) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_blendv_epi8(arg0, arg1, mask);
#else
    return {(mask.v[0] == 0) ? arg0.v[0] : arg1.v[0]
            , (mask.v[1] == 0) ? arg0.v[1] : arg1.v[1]
            , (mask.v[2] == 0) ? arg0.v[2] : arg1.v[2]
            , (mask.v[3] == 0) ? arg0.v[3] : arg1.v[3] };
#endif
}
inline TSimd32fx4 tfSimd4fSelect(TSimd32fx4 arg0, TSimd32fx4 arg1, TSimd32fx4 mask)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_blendv_ps(arg0, arg1, mask);
#else
    TSimdi32x4 intMask =  tfSimd4fToSimd4i(mask);
    return { (intMask.v[0] == 0) ? arg0.v[0] : arg1.v[0]
            , (intMask.v[1] == 0) ? arg0.v[1] : arg1.v[1]
            , (intMask.v[2] == 0) ? arg0.v[2] : arg1.v[2]
            , (intMask.v[3] == 0) ? arg0.v[3] : arg1.v[3] };
#endif
}

inline TSimd32fx4 tfSimd4fZero() { return tfSimd4iToSimd4f(tfSimd4iZero()); }
inline TSimdi32x4 tfSimd4iZero()
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_setzero_si128();
#else
    return { 0, 0, 0, 0 };
#endif
}

inline TSimdi32x4 tfSimd4iNot(TSimdi32x4 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    const TSimdi32x4 invert = tfSimd4iSplat(TF_SIMDI_MAX);
    return _mm_andnot_si128(value, invert);
#else
    return { ~value.v[0], ~value.v[1], ~value.v[2], ~value.v[3] };
#endif
}
inline TSimdi32x4 tfSimd4iAnd(TSimdi32x4 arg1, TSimdi32x4 arg2){
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_and_si128(arg1, arg2);
#else
    return { arg1.v[0] & arg2.v[0], arg1.v[1] & arg2.v[1], arg1.v[2] & arg2.v[2], arg1.v[3] & arg2.v[3] };
#endif

}
inline TSimdi32x4 tfSimd4iAndNot(TSimdi32x4 arg1, TSimdi32x4 arg2) { 
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_andnot_si128(arg1, arg2); 
#else
    return { ~arg1.v[0] & arg2.v[0], ~arg1.v[1] & arg2.v[1], ~arg1.v[2] & arg2.v[2], ~arg1.v[3] & arg2.v[3] };
#endif
}
inline TSimdi32x4 tfSimd4iOr(TSimdi32x4 arg1, TSimdi32x4 arg2){
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_or_si128(arg1, arg2); 
#else
    return { arg1.v[0] | arg2.v[0], arg1.v[1] | arg2.v[1], arg1.v[2] | arg2.v[2], arg1.v[3] | arg2.v[3] };
#endif
}
inline TSimdi32x4 tfSimd4iXor(TSimdi32x4 arg1, TSimdi32x4 arg2){
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_xor_si128(arg1, arg2); 
#else
    return { arg1.v[0] ^ arg2.v[0], arg1.v[1] ^ arg2.v[1], arg1.v[2] ^ arg2.v[2], arg1.v[3] ^ arg2.v[3] };
#endif
}

inline TSimd32fx4 tfSimd4fNot(TSimd32fx4 value) { 
#if defined(TF_FEATURE_CPU_SSE)
    const TSimd32fx4 invert = tfSimd4fSplat((float)(0xFFFFFFFF));
    return _mm_andnot_ps(value, invert);
#else
    TSimdi32x4 result = { { ~((int32_t)value.v[0]), ~((int32_t)value.v[1]),
                                 ~((int32_t)value.v[2]), ~((int32_t)value.v[3]) } };
    return tfSimd4iToSimd4f(result);
#endif
}
inline TSimd32fx4 tfSimd4fAnd(TSimd32fx4 arg1, TSimd32fx4 arg2) { 
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_and_ps(arg1, arg2);
#else
    TSimdi32x4 result = { ((int32_t)arg1.v[0]) & ((int32_t)arg2.v[0]), ((int32_t)arg1.v[1]) & ((int32_t)arg2.v[1]),
                               ((int32_t)arg1.v[2]) & ((int32_t)arg2.v[2]), ((int32_t)arg1.v[3]) & ((int32_t)arg2.v[3]) };
    return tfSimd4iToSimd4f(result);
#endif
}
inline TSimd32fx4 tfSimd4fAndNot(TSimd32fx4 arg1, TSimd32fx4 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_andnot_ps(arg1, arg2);
#else
    TSimdi32x4 result = { { ~((int32_t)arg1.v[0]) & ((int32_t)arg2.v[0]),
                                 ~((int32_t)arg1.v[1]) & ((int32_t)arg2.v[1]),
                                 ~((int32_t)arg1.v[2]) & ((int32_t)arg2.v[2]),
                                 ~((int32_t)arg1.v[3]) & ((int32_t)arg2.v[3]) } };
    return tfSimd4iToSimd4f(result);
#endif
}
inline TSimd32fx4 tfSimd4fOr(TSimd32fx4 arg1, TSimd32fx4 arg2) { 
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_or_ps(arg1, arg2);
#else
    TSimdi32x4 result = { { ((int32_t)arg1.v[0]) | ((int32_t)arg2.v[0]),
                                 ((int32_t)arg1.v[1]) | ((int32_t)arg2.v[1]),
                                 ((int32_t)arg1.v[2]) | ((int32_t)arg2.v[2]),
                                 ((int32_t)arg1.v[3]) | ((int32_t)arg2.v[3]) } };
    return tfSimd4iToSimd4f(result);
#endif
}
inline TSimd32fx4 tfSimd4fXor(TSimd32fx4 arg1, TSimd32fx4 arg2) { 
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_xor_ps(arg1, arg2);
#else
    TSimdi32x4 result = { { ((int32_t)arg1.v[0]) ^ ((int32_t)arg2.v[0]),
                                 ((int32_t)arg1.v[1]) ^ ((int32_t)arg2.v[1]),
                                 ((int32_t)arg1.v[2]) ^ ((int32_t)arg2.v[2]),
                                 ((int32_t)arg1.v[3]) ^ ((int32_t)arg2.v[3]) } };
    return tfSimd4iToSimd4f(result);
#endif
}

inline TSimd32fx4 tfSimd4fFloor(TSimd32fx4 value) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_floor_ps(value);
#else
    return { { floorf(value.v[0]), floorf(value.v[1]), floorf(value.v[2]), floorf(value.v[3]) } };
#endif
}
inline TSimd32fx4 tfSimd4fCeil(TSimd32fx4 value) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_ceil_ps(value);
#else
    return { { ceilf(value.v[0]), ceilf(value.v[1]), ceilf(value.v[2]), ceilf(value.v[3]) } };
#endif
}
inline TSimd32fx4 tfSimd4fRound(TSimd32fx4 value) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_round_ps(value, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC);
#else
    // While 'roundf' may seem the obvious choice here, it rounds halfway cases
    // away from zero regardless of the current rounding mode, but 'rintf' uses
    // the current rounding mode which is consistent with other implementations.
    return { { rintf(value.v[0]), rintf(value.v[1]), rintf(value.v[2]), rintf(value.v[3]) } };
#endif
}
inline TSimd32fx4 tfSimd4fTruncate(TSimd32fx4 value) { return tfSimd4iToSimd4f(tfSimd4fToSimd4i(value)); }
inline TSimd32fx4 tfSimd4fMin(TSimd32fx4 arg1, TSimd32fx4 arg2)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_min_ps(arg1, arg2);
#else
    return { { fminf(arg1.v[0], arg2.v[0]), fminf(arg1.v[1], arg2.v[1]), fminf(arg1.v[2], arg2.v[2]), fminf(arg1.v[3], arg2.v[3]) } };
#endif
}
inline TSimd32fx4 tfSimd4fMax(TSimd32fx4 arg1, TSimd32fx4 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_max_ps(arg1, arg2);
#else
    return { { fmaxf(arg1.v[0], arg2.v[0]), fmaxf(arg1.v[1], arg2.v[1]), fmaxf(arg1.v[2], arg2.v[2]), fmaxf(arg1.v[3], arg2.v[3]) } };
#endif
}
inline TSimd32fx4 tfSimd4fClamp(TSimd32fx4 value, TSimd32fx4 min, TSimd32fx4 max)
{
    return tfSimd4fMax(min, tfSimd4fMin(value, max));
}

inline TSimdi32x4 tfSimd4fToSimd4i(TSimd32fx4 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_castps_si128(value);
#elif defined(TF_FEATURE_CPU_SCALAR)
    return { (int32_t)value.v[0], (int32_t)value.v[1], (int32_t)value.v[2], (int32_t)value.v[3] };
#endif
}

inline TSimd32fx4 tfSimd4iToSimd4f(TSimdi32x4 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_castsi128_ps(value);
#elif defined(TF_FEATURE_CPU_SCALAR)
    return { (float)value.v[0], (float)value.v[1], (float)value.v[2], (float)value.v[3] };
#endif
}

inline float tfS32x4FSelectIndex0(TSimd32fx4 value) { 
#if defined(TF_FEATURE_CPU_SSE)
  return _mm_cvtss_f32(value);
#elif defined(TF_FEATURE_CPU_SCALAR)
  return value.v[0];
#endif
}
inline float tfS32x4FSelectIndex1(TSimd32fx4 value) { return tfS32x4FSelectIndex0(tfSimd4fSplatIndex1(value)); }
inline float tfS32x4FSelectIndex2(TSimd32fx4 value) { return tfS32x4FSelectIndex0(tfSimd4fSplatIndex2(value)); }
inline float tfS32x4FSelectIndex3(TSimd32fx4 value) { return tfS32x4FSelectIndex0(tfSimd4fSplatIndex3(value)); }

inline TSimd32fx4 tfSimd4fAdd(TSimd32fx4 arg1, TSimd32fx4 arg2)
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
inline TSimd32fx4 tfSimd4fSub(TSimd32fx4 arg1, TSimd32fx4 arg2)
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
inline TSimd32fx4 tfSimd4fMul(TSimd32fx4 arg1, TSimd32fx4 arg2) {
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
inline TSimd32fx4 tfSimd4fMadd(TSimd32fx4 mul1, TSimd32fx4 mul2, TSimd32fx4 add)
{
#if 0
    return _mm_fmadd_ps(mul1, mul2, add); // Requires FMA CPUID
#else
    return tfSimd4fAdd(tfSimd4fMul(mul1, mul2), add);
#endif
}
inline TSimd32fx4 tfSimd4fDiv(TSimd32fx4 arg1, TSimd32fx4 arg2) {
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

inline TSimd32fx4 tfSimd4fAbs(TSimd32fx4 value) { 
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
inline TSimd32fx4 tfSimdFloat4Load(float x, float y, float z, float w) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_set_ps(w, z, y, x);
#else
    return { x, y, z, w };
#endif
}


inline TSimdi32x4 tfSimdInt4Load(int32_t x, int32_t y, int32_t z, int32_t w) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_set_epi32(w, z, y, x);
#else
    return { x, y, z, w };
#endif
}

inline Simd_FloatType tfSimd4fToSimd1f(TSimd32fx4 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return value;
#else
    return value.v[0];
#endif
}

inline TSimdf32x2 tfSimd4fToSimd2f(TSimd32fx4 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return value;
#else
    return {value.v[0], value.v[1]};
#endif
}

inline TSimdf32x3 tfSimd4fToSimd3f(TSimd32fx4 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return value;
#else
    return {value.v[0], value.v[1], value.v[2]};
#endif
}

inline TSimd32fx4 tfSimd4fSplatIndex0(TSimd32fx4 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_shuffle_ps(value, value, _MM_SHUFFLE(0, 0, 0, 0));
#else
  return {value.v[0],value.v[0],value.v[0],value.v[0]};
#endif
}

inline TSimd32fx4 tfSimd4fSplatIndex1(TSimd32fx4 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_shuffle_ps(value, value, _MM_SHUFFLE(1, 1, 1, 1));
#else
  return {value.v[1],value.v[1],value.v[1],value.v[1]};
#endif
}

inline TSimd32fx4 tfSimd4fSplatIndex2(TSimd32fx4 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_shuffle_ps(value, value, _MM_SHUFFLE(2, 2, 2, 2));
#else
  return {value.v[2],value.v[2],value.v[2],value.v[2]};
#endif
}

inline TSimd32fx4 tfSimd4fSplatIndex3(TSimd32fx4 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_shuffle_ps(value, value, _MM_SHUFFLE(3, 3, 3, 3));
#else
  return {value.v[3],value.v[3],value.v[3],value.v[3]};
#endif
}

inline TSimdi32x4 tfSimd4iSplat(int32_t value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_set1_epi32(value);
#else
    return { value, value, value, value };
#endif
}

inline TSimd32fx4 tfSimd4fSplat(float value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_set1_ps(value);
#else
    return { value, value, value, value };
#endif
}

inline TSimdi32x4 tfSimdSplat4i(int32_t value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_set1_epi32(value);
#else
    return { value, value, value, value };
#endif
}


inline TSimdi32x4 tfSimd4iCmpEq(TSimdi32x4 arg1, TSimdi32x4 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_cmpeq_epi32(arg1, arg2);
#else
    return { { (arg1.v[0] == arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, 
               (arg1.v[1] == arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000,
               (arg1.v[2] == arg2.v[2]) ? (int32_t)0xFFFFFFFF : 0x00000000, 
               (arg1.v[3] == arg2.v[3]) ? (int32_t)0xFFFFFFFF : 0x00000000 } };
#endif
}
inline TSimdi32x4 tfSimd4iCmpNeq(TSimdi32x4 arg1, TSimdi32x4 arg2) {
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
inline TSimdi32x4 tfSimd4iCmpGt(TSimdi32x4 arg1, TSimdi32x4 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_cmpgt_epi32(arg1, arg2);
#else
    return { { (arg1.v[0] > arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, 
               (arg1.v[1] > arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000,
               (arg1.v[2] > arg2.v[2]) ? (int32_t)0xFFFFFFFF : 0x00000000, 
               (arg1.v[3] > arg2.v[3]) ? (int32_t)0xFFFFFFFF : 0x00000000 } };
#endif
}
inline TSimdi32x4 tfSimd4iCmpGtEq(TSimdi32x4 arg1, TSimdi32x4 arg2) {
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
inline TSimdi32x4 tfSimd4iCmpLt(TSimdi32x4 arg1, TSimdi32x4 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_cmplt_epi32(arg1, arg2);
#else
    return { { (arg1.v[0] < arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, 
               (arg1.v[1] < arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000,
               (arg1.v[2] < arg2.v[2]) ? (int32_t)0xFFFFFFFF : 0x00000000, 
               (arg1.v[3] < arg2.v[3]) ? (int32_t)0xFFFFFFFF : 0x00000000 } };
#endif
}
inline TSimdi32x4 tfSimd4iCmpLtEq(TSimdi32x4 arg1, TSimdi32x4 arg2) {
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




//inline bool tfSimd4fCmpAllEq(TSimd32fx4 arg1, TSimd32fx4 arg2) {
//#if defined(TF_FEATURE_CPU_SSE)
//    const TSimd32fx4 compare = tfSimd4fCmpAllEq(arg1, arg2);
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

inline bool tfSimd4iCmpAllEq(TSimdi32x4 arg1, TSimdi32x4 arg2)
{
#if defined(TF_FEATURE_CPU_SSE)
    const TSimdi32x4 compare = tfSimd4iCmpEq(arg1, arg2);
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
