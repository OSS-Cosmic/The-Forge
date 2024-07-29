/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */
#pragma once
#ifndef TF_SIMD_4_32_H
#define TF_SIMD_4_32_H

#include "Forge/Math/Internal/SimdTypes.h"

inline TSimdFloat4 tfSimd4fSplat(float value);
inline TSimdInt4 tfSimd4iSplat(int32_t value);

inline TSimdFloat4 tfSimd4fZero();
inline TSimdInt4 tfSimd4iZero();

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

inline TSimdFloat4 tfSimd4fLoadImmediate(float x, float y, float z, float w);
inline TSimdInt4 tfSimdi32x4Load(int32_t x, int32_t y, int32_t z, int32_t w);

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
#elif defined(TF_FEATURE_CPU_NEON)
    return vbslq_s32(mask, arg1, arg2);
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
#elif defined(TF_FEATURE_CPU_NEON)
    return vbslq_f32(mask, arg1, arg2);
#else
    TSimdInt4 intMask =  tfSimd4fToSimd4i(mask);
    return { (intMask.v[0] == 0) ? arg0.v[0] : arg1.v[0]
            , (intMask.v[1] == 0) ? arg0.v[1] : arg1.v[1]
            , (intMask.v[2] == 0) ? arg0.v[2] : arg1.v[2]
            , (intMask.v[3] == 0) ? arg0.v[3] : arg1.v[3] };
#endif
}

inline TSimdFloat4 tfSimd4fZero() { 
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_setzero_ps();
#elif defined(TF_FEATURE_CPU_NEON)
    return vmovq_n_f32(0.0f);
#else
    return { 0, 0, 0, 0 };
#endif

}
inline TSimdInt4 tfSimd4iZero()
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_setzero_si128();
#elif defined(TF_FEATURE_CPU_NEON)
    return vmovq_n_s32(0);
#else
    return { 0, 0, 0, 0 };
#endif
}

inline TSimdInt4 tfSimd4iNot(TSimdInt4 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_andnot_si128(value, _mm_set1_epi32(TF_SIMDI_MAX));
#elif defined(TF_FEATURE_CPU_NEON)
    return vmvnq_s32(value);
#else
    return { ~value.v[0], ~value.v[1], ~value.v[2], ~value.v[3] };
#endif
}
inline TSimdInt4 tfSimd4iAnd(TSimdInt4 arg1, TSimdInt4 arg2){
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_and_si128(arg1, arg2);
#elif defined(TF_FEATURE_CPU_NEON)
    return vandq_s32(arg1, arg2);
#else
    return { arg1.v[0] & arg2.v[0], arg1.v[1] & arg2.v[1], arg1.v[2] & arg2.v[2], arg1.v[3] & arg2.v[3] };
#endif

}
inline TSimdInt4 tfSimd4iAndNot(TSimdInt4 arg1, TSimdInt4 arg2) { 
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_andnot_si128(arg1, arg2); 
#elif defined(TF_FEATURE_CPU_NEON)
    return vandq_s32(vmvnq_s32(arg1), arg2);
#else
    return { ~arg1.v[0] & arg2.v[0], ~arg1.v[1] & arg2.v[1], ~arg1.v[2] & arg2.v[2], ~arg1.v[3] & arg2.v[3] };
#endif
}
inline TSimdInt4 tfSimd4iOr(TSimdInt4 arg1, TSimdInt4 arg2){
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_or_si128(arg1, arg2); 
#elif defined(TF_FEATURE_CPU_NEON)
    return vorrq_s32(arg1, arg2);
#else
    return { arg1.v[0] | arg2.v[0], arg1.v[1] | arg2.v[1], arg1.v[2] | arg2.v[2], arg1.v[3] | arg2.v[3] };
#endif
}
inline TSimdInt4 tfSimd4iXor(TSimdInt4 arg1, TSimdInt4 arg2){
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_xor_si128(arg1, arg2); 
#elif defined(TF_FEATURE_CPU_NEON)
    return veorq_s32(arg1, arg2);
#else
    return { arg1.v[0] ^ arg2.v[0], arg1.v[1] ^ arg2.v[1], arg1.v[2] ^ arg2.v[2], arg1.v[3] ^ arg2.v[3] };
#endif
}

inline TSimdFloat4 tfSimd4fNot(TSimdFloat4 value) { 
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_andnot_ps(value, _mm_set1_ps((float)(TF_SIMDF_MAX)));
#elif defined(TF_FEATURE_CPU_NEON)
    return vreinterpretq_f32_s32(vmvnq_s32(vreinterpretq_s32_f32(value)));
#else
    TSimdInt4 result = { { ~((int32_t)value.v[0]), ~((int32_t)value.v[1]),
                                 ~((int32_t)value.v[2]), ~((int32_t)value.v[3]) } };
    return tfSimd4iToSimd4f(result);
#endif
}
inline TSimdFloat4 tfSimd4fAnd(TSimdFloat4 arg1, TSimdFloat4 arg2) { 
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_and_ps(arg1, arg2);
#elif defined(TF_FEATURE_CPU_NEON)
    return vreinterpretq_f32_s32(vandq_s32(vreinterpretq_s32_f32(arg1), vreinterpretq_s32_f32(arg2)));
#else
    TSimdInt4 result = { ((int32_t)arg1.v[0]) & ((int32_t)arg2.v[0]), ((int32_t)arg1.v[1]) & ((int32_t)arg2.v[1]),
                               ((int32_t)arg1.v[2]) & ((int32_t)arg2.v[2]), ((int32_t)arg1.v[3]) & ((int32_t)arg2.v[3]) };
    return tfSimd4iToSimd4f(result);
#endif
}
inline TSimdFloat4 tfSimd4fAndNot(TSimdFloat4 arg1, TSimdFloat4 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_andnot_ps(arg1, arg2);
#elif defined(TF_FEATURE_CPU_NEON)
    return vreinterpretq_f32_s32(vandq_s32(vmvnq_s32(vreinterpretq_s32_f32(arg1)), vreinterpretq_s32_f32(arg2)));
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
#elif defined(TF_FEATURE_CPU_NEON)
    return vreinterpretq_f32_s32(vorrq_s32(vreinterpretq_s32_f32(arg1), vreinterpretq_s32_f32(arg2)));
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
#elif defined(TF_FEATURE_CPU_NEON)
    return vreinterpretq_f32_s32(veorq_s32(vreinterpretq_s32_f32(arg1), vreinterpretq_s32_f32(arg2)));
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
#elif defined(TF_FEATURE_CPU_NEON)
    return vrndmq_f32(value);
#else
    return { { floorf(value.v[0]), floorf(value.v[1]), floorf(value.v[2]), floorf(value.v[3]) } };
#endif
}
inline TSimdFloat4 tfSimd4fCeil(TSimdFloat4 value) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_ceil_ps(value);
#elif defined(TF_FEATURE_CPU_NEON)
    return vrndpq_f32(value);
#else
    return { { ceilf(value.v[0]), ceilf(value.v[1]), ceilf(value.v[2]), ceilf(value.v[3]) } };
#endif
}
inline TSimdFloat4 tfSimd4fRound(TSimdFloat4 value) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_round_ps(value, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC);
#elif defined(TF_FEATURE_CPU_NEON)
    return vrndnq_f32(value);
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
#elif defined(TF_FEATURE_CPU_NEON)
    return vminq_f32(arg1, arg2);
#else
    return { { fminf(arg1.v[0], arg2.v[0]), fminf(arg1.v[1], arg2.v[1]), fminf(arg1.v[2], arg2.v[2]), fminf(arg1.v[3], arg2.v[3]) } };
#endif
}
inline TSimdFloat4 tfSimd4fMax(TSimdFloat4 arg1, TSimdFloat4 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_max_ps(arg1, arg2);
#elif defined(TF_FEATURE_CPU_NEON)
    return vmaxq_f32(arg1, arg2);
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
#elif defined(TF_FEATURE_CPU_NEON)
    return vreinterpretq_f32_s32(value);
#elif defined(TF_FEATURE_CPU_SCALAR)
    return { (int32_t)value.v[0], (int32_t)value.v[1], (int32_t)value.v[2], (int32_t)value.v[3] };
#endif
}

inline TSimdFloat4 tfSimd4iToSimd4f(TSimdInt4 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_castsi128_ps(value);
#elif defined(TF_FEATURE_CPU_NEON)
    return vreinterpretq_s32_f32(value);
#elif defined(TF_FEATURE_CPU_SCALAR)
    return { (float)value.v[0], (float)value.v[1], (float)value.v[2], (float)value.v[3] };
#endif
}

inline float tfSimd4fSelectIndex0(TSimdFloat4 value) { 
#if defined(TF_FEATURE_CPU_SSE)
  return _mm_cvtss_f32(value);
#elif defined(TF_FEATURE_CPU_NEON)
  return vgetq_lane_f32(value, 0);
#elif defined(TF_FEATURE_CPU_SCALAR)
  return value.v[0];
#endif
}
inline float tfSimd4fSelectIndex1(TSimdFloat4 value) { 
#if defined(TF_FEATURE_CPU_SSE)
    return tfSimd4fSelectIndex0(tfSimd4fSplatIndex1(value)); 
#elif defined(TF_FEATURE_CPU_NEON)
    return vgetq_lane_f32(value, 1);
#elif defined(TF_FEATURE_CPU_SCALAR)
  return value.v[1];
#endif
}
inline float tfSimd4fSelectIndex2(TSimdFloat4 value) { 
#if defined(TF_FEATURE_CPU_SSE)
    return tfSimd4fSelectIndex0(tfSimd4fSplatIndex2(value)); 
#elif defined(TF_FEATURE_CPU_NEON)
    return vgetq_lane_f32(value, 2);
#elif defined(TF_FEATURE_CPU_SCALAR)
  return value.v[2];
#endif
}
inline float tfSimd4fSelectIndex3(TSimdFloat4 value) { 
#if defined(TF_FEATURE_CPU_SSE)
    return tfSimd4fSelectIndex0(tfSimd4fSplatIndex3(value)); 
#elif defined(TF_FEATURE_CPU_NEON)
    return vgetq_lane_f32(value, 3);
#elif defined(TF_FEATURE_CPU_SCALAR)
  return value.v[3];
#endif
}

inline TSimdFloat4 tfSimd4fAdd(TSimdFloat4 arg1, TSimdFloat4 arg2)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_add_ps(arg1, arg2);
#elif defined(TF_FEATURE_CPU_NEON)
    return vaddq_f32(arg1, arg2);
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
#elif defined(TF_FEATURE_CPU_NEON)
    return vsubq_f32(arg1, arg2);
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
#elif defined(TF_FEATURE_CPU_NEON)
    return vmulq_f32(arg1, arg2);
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
#if defined(TF_FEATURE_CPU_SSE)
#if 0
    return _mm_fmadd_ps(mul1, mul2, add); // Requires FMA CPUID
#else
    return tfSimd4fAdd(tfSimd4fMul(mul1, mul2), add);
#endif
#elif defined(TF_FEATURE_CPU_NEON)
    return vmlaq_f32(add, mul1, mul2);
#else
    return tfSimd4fAdd(tfSimd4fMul(mul1, mul2), add);
#endif
}

inline TSimdFloat4 tfSimd4fDiv(TSimdFloat4 arg1, TSimdFloat4 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_div_ps(arg1, arg2);
#elif defined(TF_FEATURE_CPU_NEON)
    return vdivq_f32(arg1, arg2);
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
    return _mm_and_ps(value, _mm_set1_ps((float)(0x7FFFFFFF)));
#elif defined(TF_FEATURE_CPU_NEON)
    return vabsq_f32(value);
#else
    return {
        abs(value.v[0]),
        abs(value.v[1]),
        abs(value.v[2]),
        abs(value.v[3]),
    };
#endif
}
inline TSimdFloat4 tfSimd4fLoadImmediate(float x, float y, float z, float w) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_set_ps(w, z, y, x);
#elif defined(TF_FEATURE_CPU_NEON)
    const float values[4] = { x, y, z, w };
    return vld1q_f32(values);
#else
    return { x, y, z, w };
#endif
}


inline TSimdInt4 tfSimdi32x4Load(int32_t x, int32_t y, int32_t z, int32_t w) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_set_epi32(w, z, y, x);
#elif defined(TF_FEATURE_CPU_NEON)
    const int32_t values[4] = { x, y, z, w };
    return vld1q_s32(values);
#else
    return { x, y, z, w };
#endif
}

inline TSimdFloat2 tfSimd4fToSimd2f(TSimdFloat4 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return value;
#elif defined(TF_FEATURE_CPU_NEON)
    return vget_low_f32(value);
#else
    return {value.v[0], value.v[1]};
#endif
}

inline TSimdFloat3 tfSimd4fToSimd3f(TSimdFloat4 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return value;
#elif defined(TF_FEATURE_CPU_NEON)
    return value;
#else
    return {value.v[0], value.v[1], value.v[2]};
#endif
}

inline TSimdFloat4 tfSimd4fSplatIndex0(TSimdFloat4 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_shuffle_ps(value, value, _MM_SHUFFLE(0, 0, 0, 0));
#elif defined(TF_FEATURE_CPU_NEON)
    return vdupq_laneq_f32(value, 0);
#else
  return {value.v[0],value.v[0],value.v[0],value.v[0]};
#endif
}

inline TSimdFloat4 tfSimd4fSplatIndex1(TSimdFloat4 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_shuffle_ps(value, value, _MM_SHUFFLE(1, 1, 1, 1));
#elif defined(TF_FEATURE_CPU_NEON)
    return vdupq_laneq_f32(value, 1);
#else
  return {value.v[1],value.v[1],value.v[1],value.v[1]};
#endif
}

inline TSimdFloat4 tfSimd4fSplatIndex2(TSimdFloat4 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_shuffle_ps(value, value, _MM_SHUFFLE(2, 2, 2, 2));
#elif defined(TF_FEATURE_CPU_NEON)
    return vdupq_laneq_f32(value, 2);
#else
  return {value.v[2],value.v[2],value.v[2],value.v[2]};
#endif
}

inline TSimdFloat4 tfSimd4fSplatIndex3(TSimdFloat4 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_shuffle_ps(value, value, _MM_SHUFFLE(3, 3, 3, 3));
#elif defined(TF_FEATURE_CPU_NEON)
    return vdupq_laneq_f32(value, 3);
#else
  return {value.v[3],value.v[3],value.v[3],value.v[3]};
#endif
}

inline TSimdInt4 tfSimd4iSplat(int32_t value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_set1_epi32(value);
#elif defined(TF_FEATURE_CPU_NEON)
    return vdupq_n_s32(value);
#else
    return { value, value, value, value };
#endif
}

inline TSimdFloat4 tfSimd4fSplat(float value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_set1_ps(value);
#elif defined(TF_FEATURE_CPU_NEON)
    return vdupq_n_f32(value);
#else
    return { value, value, value, value };
#endif
}

inline TSimdFloat4 tfSimd4fCmpEq(TSimdFloat4 arg1, TSimdFloat4 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_cmpeq_ps(arg1, arg2);
#elif defined(TF_FEATURE_CPU_NEON)
    return vreinterpretq_f32_s32(vceqq_f32(arg1, arg2));
#else
    return { { (arg1.v[0] == arg2.v[0]) ? (float)0xFFFFFFFF : 0x00000000, 
               (arg1.v[1] == arg2.v[1]) ? (float)0xFFFFFFFF : 0x00000000,
               (arg1.v[2] == arg2.v[2]) ? (float)0xFFFFFFFF : 0x00000000, 
               (arg1.v[3] == arg2.v[3]) ? (float)0xFFFFFFFF : 0x00000000 } };
#endif
}
inline TSimdFloat4 tfSimd4fCmpNeq(TSimdFloat4 arg1, TSimdFloat4 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_cmpneq_ps(arg1, arg2);
#elif defined(TF_FEATURE_CPU_NEON)
    return vreinterpretq_f32_s32(vmvnq_s32(vceqq_f32(arg1, arg2)));
#else
    return { { (arg1.v[0] != arg2.v[0]) ? (float)0xFFFFFFFF : 0x00000000, 
               (arg1.v[1] != arg2.v[1]) ? (float)0xFFFFFFFF : 0x00000000,
               (arg1.v[2] != arg2.v[2]) ? (float)0xFFFFFFFF : 0x00000000, 
               (arg1.v[3] != arg2.v[3]) ? (float)0xFFFFFFFF : 0x00000000 } };
#endif
}
inline TSimdFloat4 tfSimd4fCmpGt(TSimdFloat4 arg1, TSimdFloat4 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_cmpgt_ps(arg1, arg2);
#elif defined(TF_FEATURE_CPU_NEON)
    return vreinterpretq_f32_s32(vcgtq_f32(arg1, arg2));
#else
    return { { (arg1.v[0] > arg2.v[0]) ? (float)0xFFFFFFFF : 0x00000000, 
               (arg1.v[1] > arg2.v[1]) ? (float)0xFFFFFFFF : 0x00000000,
               (arg1.v[2] > arg2.v[2]) ? (float)0xFFFFFFFF : 0x00000000, 
               (arg1.v[3] > arg2.v[3]) ? (float)0xFFFFFFFF : 0x00000000 } };
#endif
}
inline TSimdFloat4 tfSimd4fCmpGtEq(TSimdFloat4 arg1, TSimdFloat4 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_cmpge_ps(arg1, arg2);
#elif defined(TF_FEATURE_CPU_NEON)
    return vreinterpretq_f32_s32(vcgeq_f32(arg1, arg2));
#else
    return { { (arg1.v[0] >= arg2.v[0]) ? (float)0xFFFFFFFF : 0x00000000, 
               (arg1.v[1] >= arg2.v[1]) ? (float)0xFFFFFFFF : 0x00000000,
               (arg1.v[2] >= arg2.v[2]) ? (float)0xFFFFFFFF : 0x00000000, 
               (arg1.v[3] >= arg2.v[3]) ? (float)0xFFFFFFFF : 0x00000000 } };
#endif
}
inline TSimdFloat4 tfSimd4fCmpLt(TSimdFloat4 arg1, TSimdFloat4 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_cmplt_ps(arg1, arg2);
#elif defined(TF_FEATURE_CPU_NEON)
    return vreinterpretq_f32_s32(vcltq_f32(arg1, arg2));
#else
    return { { (arg1.v[0] < arg2.v[0]) ? (float)0xFFFFFFFF : 0x00000000, 
               (arg1.v[1] < arg2.v[1]) ? (float)0xFFFFFFFF : 0x00000000,
               (arg1.v[2] < arg2.v[2]) ? (float)0xFFFFFFFF : 0x00000000, 
               (arg1.v[3] < arg2.v[3]) ? (float)0xFFFFFFFF : 0x00000000 } };
#endif

}
inline TSimdFloat4 tfSimd4fCmpLtEq(TSimdFloat4 arg1, TSimdFloat4 arg2) {

#if defined(TF_FEATURE_CPU_SSE)
    return _mm_cmple_ps(arg1, arg2);
#elif defined(TF_FEATURE_CPU_NEON)
    return vreinterpretq_f32_s32(vcleq_f32(arg1, arg2));
#else
    return { { (arg1.v[0] <= arg2.v[0]) ? (float)0xFFFFFFFF : 0x00000000, 
               (arg1.v[1] <= arg2.v[1]) ? (float)0xFFFFFFFF : 0x00000000,
               (arg1.v[2] <= arg2.v[2]) ? (float)0xFFFFFFFF : 0x00000000, 
               (arg1.v[3] <= arg2.v[3]) ? (float)0xFFFFFFFF : 0x00000000 } };
#endif

}


inline TSimdInt4 tfSimd4iCmpEq(TSimdInt4 arg1, TSimdInt4 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_cmpeq_epi32(arg1, arg2);
#elif defined(TF_FEATURE_CPU_NEON)
    return vceqq_s32(arg1, arg2);
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
#elif defined(TF_FEATURE_CPU_NEON)
    return vmvnq_s32(vceqq_s32(arg1, arg2));
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
#elif defined(TF_FEATURE_CPU_NEON)
    return vcgtq_s32(arg1, arg2);
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
#elif defined(TF_FEATURE_CPU_NEON)
    return vcgeq_s32(arg1, arg2);
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
#elif defined(TF_FEATURE_CPU_NEON)
    return vcltq_s32(arg1, arg2);
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
#elif defined(TF_FEATURE_CPU_NEON)
    return vcleq_s32(arg1, arg2);
#else
    return { { (arg1.v[0] < arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, 
               (arg1.v[1] < arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000,
               (arg1.v[2] < arg2.v[2]) ? (int32_t)0xFFFFFFFF : 0x00000000, 
               (arg1.v[3] < arg2.v[3]) ? (int32_t)0xFFFFFFFF : 0x00000000 } };
#endif

}

inline bool tfSimd4fCmpAllEq(TSimdFloat4 arg1, TSimdFloat4 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    TSimdFloat4  compare = tfSimd4fCmpEq(arg1, arg2);
    return (_mm_movemask_ps(compare) & 0xf) == 0xf;
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

#endif
