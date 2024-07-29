/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */
#pragma once
#ifndef TF_SIMD_3_32_H
#define TF_SIMD_3_32_H

#include "Forge/Math/Internal/SimdTypes.h"

inline TSimdf32x3 tfSimd3fSplat(float value);
inline TSimdi32x3 tfSimd3iSplat(int32_t value);

inline TSimdf32x3 tfSimd3fZero();
inline TSimdi32x3 tfSimd3iZero();

inline TSimdf32x2 tfSimd3fToSimd2f(TSimdf32x3 value);
inline TSimdi32x3 tfSimd3fToSimd3i(TSimdf32x3 value);
inline TSimdf32x3 tfSimd3iToSimd3f(TSimdi32x3 value);

inline TSimdf32x3 tfSimd3fSplatIndex0(TSimdf32x3 value);
inline TSimdf32x3 tfSimd3fSplatIndex1(TSimdf32x3 value);
inline TSimdf32x3 tfSimd3fSplatIndex2(TSimdf32x3 value);

inline TSimdf32x3 tfSimd3fSelect(TSimdf32x3 arg0, TSimdf32x3 arg1, TSimdf32x3 mask);
inline TSimdi32x3 tfSimd3iSelect(TSimdi32x3 arg0, TSimdi32x3 arg1, TSimdi32x3 mask);

inline float tfSimd3fSelectIndex0(TSimdf32x3 value);
inline float tfSimd3fSelectIndex1(TSimdf32x3 value);
inline float tfSimd3fSelectIndex2(TSimdf32x3 value);

inline TSimdf32x3 tfSimd3fLoadImmediate(float x, float y, float z);
inline TSimdi32x3 tfSimd3iLoadImmediate(int32_t x, int32_t y, int32_t z);

inline TSimdf32x3 tfSimd3fAdd(TSimdf32x3 arg1, TSimdf32x3 arg2);
inline TSimdf32x3 tfSimd3fSub(TSimdf32x3 arg1, TSimdf32x3 arg2);
inline TSimdf32x3 tfSimd3fMul(TSimdf32x3 arg1, TSimdf32x3 arg2);
inline TSimdf32x3 tfSimd3fMadd(TSimdf32x3 mul1, TSimdf32x3 mul2, TSimdf32x3 add);
inline TSimdf32x3 tfSimd3fDiv(TSimdf32x3 arg1, TSimdf32x3 arg2);
inline TSimdf32x3 tfSimd3fAbs(TSimdf32x3 value);

inline TSimdf32x3 tfSimd3fNot(TSimdf32x3 value);
inline TSimdf32x3 tfSimd3fAnd(TSimdf32x3 arg1, TSimdf32x3 arg2);
inline TSimdf32x3 tfSimd3fAndNot(TSimdf32x3 arg1, TSimdf32x3 arg2);
inline TSimdf32x3 tfSimd3fOr(TSimdf32x3 arg1, TSimdf32x3 arg2);
inline TSimdf32x3 tfSimd3fXor(TSimdf32x3 arg1, TSimdf32x3 arg2);

inline TSimdi32x3 tfSimd3iNot(TSimdi32x3 value);
inline TSimdi32x3 tfSimd3iAnd(TSimdi32x3 arg1, TSimdi32x3 arg2);
inline TSimdi32x3 tfSimd3iAndNot(TSimdi32x3 arg1, TSimdi32x3 arg2);
inline TSimdi32x3 tfSimd3iOr(TSimdi32x3 arg1, TSimdi32x3 arg2);
inline TSimdi32x3 tfSimd3iXor(TSimdi32x3 arg1, TSimdi32x3 arg2);

inline TSimdf32x3 tfSimd3fFloor(TSimdf32x3 value);
inline TSimdf32x3 tfSimd3fCeil(TSimdf32x3 value);
inline TSimdf32x3 tfSimd3fRound(TSimdf32x3 value); // Ties to even (banker's rounding)
inline TSimdf32x3 tfSimd3fTruncate(TSimdf32x3 value);
inline TSimdf32x3 tfSimd3fMin(TSimdf32x3 arg1, TSimdf32x3 arg2);
inline TSimdf32x3 tfSimd3fMax(TSimdf32x3 arg1, TSimdf32x3 arg2);
inline TSimdf32x3 tfSimd3fClamp(TSimdf32x3 value, TSimdf32x3 min, TSimdf32x3 max);

inline TSimdi32x3 tfSimd3iCmpEq(TSimdi32x3 arg1, TSimdi32x3 arg2);
inline TSimdi32x3 tfSimd3iCmpNeq(TSimdi32x3 arg1, TSimdi32x3 arg2);
inline TSimdi32x3 tfSimd3iCmpGt(TSimdi32x3 arg1, TSimdi32x3 arg2);
inline TSimdi32x3 tfSimd3iCmpGtEq(TSimdi32x3 arg1, TSimdi32x3 arg2);
inline TSimdi32x3 tfSimd3iCmpLt(TSimdi32x3 arg1, TSimdi32x3 arg2);
inline TSimdi32x3 tfSimd3iCmpLtEq(TSimdi32x3 arg1, TSimdi32x3 arg2);

inline TSimdf32x3 tfSimd3fCmpEq(TSimdf32x3 arg1, TSimdf32x3 arg2);
inline TSimdf32x3 tfSimd3fCmpNeq(TSimdf32x3 arg1, TSimdf32x3 arg2);
inline TSimdf32x3 tfSimd3fCmpGt(TSimdf32x3 arg1, TSimdf32x3 arg2);
inline TSimdf32x3 tfSimd3fCmpGtEq(TSimdf32x3 arg1, TSimdf32x3 arg2);
inline TSimdf32x3 tfSimd3fCmpLt(TSimdf32x3 arg1, TSimdf32x3 arg2);
inline TSimdf32x3 tfSimd3fCmpLtEq(TSimdf32x3 arg1, TSimdf32x3 arg2);

inline bool tfSimd3iCmpAllEq(TSimdi32x3 arg1, TSimdi32x3 arg2);
inline bool tfSimd3fCmpAllEq(TSimdf32x3 arg1, TSimdf32x3 arg2);

// ----------------------------------------------------------------
// --------------------- Implementaion ----------------------------
// ----------------------------------------------------------------

inline TSimdi32x3 tfSimd3iSelect(TSimdi32x3 arg0, TSimdi32x3 arg1, TSimdi32x3 mask) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_blendv_epi8(arg0, arg1, mask);
#elif defined(TF_FEATURE_CPU_NEON)
    return vbslq_s32(mask, arg1, arg2);
#else
    return {(mask.v[0] == 0) ? arg0.v[0] : arg1.v[0]
            , (mask.v[1] == 0) ? arg0.v[1] : arg1.v[1]
            , (mask.v[2] == 0) ? arg0.v[2] : arg1.v[2]};
#endif
}
inline TSimdf32x3 tfSimd3fSelect(TSimdf32x3 arg0, TSimdf32x3 arg1, TSimdf32x3 mask)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_blendv_ps(arg0, arg1, mask);
#elif defined(TF_FEATURE_CPU_NEON)
    return vbslq_f32(mask, arg1, arg2);
#else
    TSimdi32x3 intMask =  tfSimd3fToSimd3i(mask);
    return { (intMask.v[0] == 0) ? arg0.v[0] : arg1.v[0]
            , (intMask.v[1] == 0) ? arg0.v[1] : arg1.v[1]
            , (intMask.v[2] == 0) ? arg0.v[2] : arg1.v[2] };
#endif
}

inline TSimdf32x3 tfSimd3fZero() { 
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_setzero_ps();
#elif defined(TF_FEATURE_CPU_NEON)
    return vmovq_n_f32(0.0f);
#else
    return { 0, 0, 0 };
#endif
}
inline TSimdi32x3 tfSimd3iZero()
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_setzero_si128();
#elif defined(TF_FEATURE_CPU_NEON)
    return vmovq_n_s32(0);
#else
    return { 0, 0, 0 };
#endif
}

inline TSimdi32x3 tfSimd3iNot(TSimdi32x3 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_andnot_si128(value, _mm_set1_epi32(TF_SIMDI_MAX));
#elif defined(TF_FEATURE_CPU_NEON)
    return vmvnq_s32(value);
#else
    return { ~value.v[0], ~value.v[1], ~value.v[2] };
#endif
}
inline TSimdi32x3 tfSimd3iAnd(TSimdi32x3 arg1, TSimdi32x3 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_and_si128(arg1, arg2);
#elif defined(TF_FEATURE_CPU_NEON)
    return vandq_s32(arg1, arg2);
#else
    return { arg1.v[0] & arg2.v[0], arg1.v[1] & arg2.v[1], arg1.v[2] & arg2.v[2]};
#endif

}
inline TSimdi32x3 tfSimd3iAndNot(TSimdi32x3 arg1, TSimdi32x3 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_andnot_si128(arg1, arg2); 
#elif defined(TF_FEATURE_CPU_NEON)
    return vandq_s32(vmvnq_s32(arg1), arg2);
#else
    return { ~arg1.v[0] & arg2.v[0], ~arg1.v[1] & arg2.v[1], ~arg1.v[2] & arg2.v[2]};
#endif
}
inline TSimdi32x3 tfSimd3iOr(TSimdi32x3 arg1, TSimdi32x3 arg2)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_or_si128(arg1, arg2);
#elif defined(TF_FEATURE_CPU_NEON)
    return vorrq_s32(arg1, arg2);
#else
    return { arg1.v[0] | arg2.v[0], arg1.v[1] | arg2.v[1], arg1.v[2] | arg2.v[2]};
#endif
}
inline TSimdi32x3 tfSimd3iXor(TSimdi32x3 arg1, TSimdi32x3 arg2){
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_xor_si128(arg1, arg2); 
#elif defined(TF_FEATURE_CPU_NEON)
    return veorq_s32(arg1, arg2);
#else
    return { arg1.v[0] ^ arg2.v[0], arg1.v[1] ^ arg2.v[1], arg1.v[2] ^ arg2.v[2] };
#endif
}

inline TSimdf32x3 tfSimd3fNot(TSimdf32x3 value) {
#if defined(TF_FEATURE_CPU_SSE)
    const TSimdf32x3 invert = tfSimd3fSplat((float)(0xFFFFFFFF));
    return _mm_andnot_ps(value, invert);
#elif defined(TF_FEATURE_CPU_NEON)
    return vreinterpretq_f32_s32(vmvnq_s32(vreinterpretq_s32_f32(value)));
#else
    TSimdi32x3 result = {{ ~((int32_t)value.v[0]), ~((int32_t)value.v[1]),
                                 ~((int32_t)value.v[2])} } ;
    return tfSimd3iToSimd3f(result);
#endif
}
inline TSimdf32x3 tfSimd3fAnd(TSimdf32x3 arg1, TSimdf32x3 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_and_ps(arg1, arg2);
#elif defined(TF_FEATURE_CPU_NEON)
    return vreinterpretq_f32_s32(vandq_s32(vreinterpretq_s32_f32(arg1), vreinterpretq_s32_f32(arg2)));
#else
    TSimdi32x3 result = { ((int32_t)arg1.v[0]) & ((int32_t)arg2.v[0]), ((int32_t)arg1.v[1]) & ((int32_t)arg2.v[1]),
                               ((int32_t)arg1.v[2]) & ((int32_t)arg2.v[2]) };
    return tfSimd3iToSimd3f(result);
#endif
}
inline TSimdf32x3 tfSimd3fAndNot(TSimdf32x3 arg1, TSimdf32x3 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_andnot_ps(arg1, arg2);
#elif defined(TF_FEATURE_CPU_NEON)
    return vreinterpretq_f32_s32(vandq_s32(vmvnq_s32(vreinterpretq_s32_f32(arg1)), vreinterpretq_s32_f32(arg2)));
#else
    TSimdi32x3 result = { { ~((int32_t)arg1.v[0]) & ((int32_t)arg2.v[0]),
                                 ~((int32_t)arg1.v[1]) & ((int32_t)arg2.v[1]),
                                 ~((int32_t)arg1.v[2]) & ((int32_t)arg2.v[2]) } };
    return tfSimd3iToSimd3f(result);
#endif
}
inline TSimdf32x3 tfSimd3fOr(TSimdf32x3 arg1, TSimdf32x3 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_or_ps(arg1, arg2);
#elif defined(TF_FEATURE_CPU_NEON)
    return vreinterpretq_f32_s32(vorrq_s32(vreinterpretq_s32_f32(arg1), vreinterpretq_s32_f32(arg2)));
#else
    TSimdi32x3 result = { { ((int32_t)arg1.v[0]) | ((int32_t)arg2.v[0]),
                                 ((int32_t)arg1.v[1]) | ((int32_t)arg2.v[1]),
                                 ((int32_t)arg1.v[2]) | ((int32_t)arg2.v[2]) } };
    return tfSimd3iToSimd3f(result);
#endif
}
inline TSimdf32x3 tfSimd3fXor(TSimdf32x3 arg1, TSimdf32x3 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_xor_ps(arg1, arg2);
#elif defined(TF_FEATURE_CPU_NEON)
    return vreinterpretq_f32_s32(veorq_s32(vreinterpretq_s32_f32(arg1), vreinterpretq_s32_f32(arg2)));
#else
    TSimdi32x3 result = { { ((int32_t)arg1.v[0]) ^ ((int32_t)arg2.v[0]),
                                 ((int32_t)arg1.v[1]) ^ ((int32_t)arg2.v[1]),
                                 ((int32_t)arg1.v[2]) ^ ((int32_t)arg2.v[2]) } };
    return tfSimd3iToSimd3f(result);
#endif
}

inline TSimdf32x3 tfSimd3fFloor(TSimdf32x3 value) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_floor_ps(value);
#elif defined(TF_FEATURE_CPU_NEON)
    return vrndmq_f32(value);
#else
    return { { floorf(value.v[0]), floorf(value.v[1]), floorf(value.v[2]) } };
#endif
}
inline TSimdf32x3 tfSimd3fCeil(TSimdf32x3 value) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_ceil_ps(value);
#elif defined(TF_FEATURE_CPU_NEON)
    return vrndpq_f32(value);
#else
    return { { ceilf(value.v[0]), ceilf(value.v[1]), ceilf(value.v[2]) } };
#endif
}
inline TSimdf32x3 tfSimd3fRound(TSimdf32x3 value) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_round_ps(value, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC);
#elif defined(TF_FEATURE_CPU_NEON)
    return vrndnq_f32(value);
#else
    // While 'roundf' may seem the obvious choice here, it rounds halfway cases
    // away from zero regardless of the current rounding mode, but 'rintf' uses
    // the current rounding mode which is consistent with other implementations.
    return { { rintf(value.v[0]), rintf(value.v[1]), rintf(value.v[2]) } };
#endif
}
inline TSimdf32x3 tfSimd3fTruncate(TSimdf32x3 value) { return tfSimd3iToSimd3f(tfSimd3fToSimd3i(value)); }
inline TSimdf32x3 tfSimd3fMin(TSimdf32x3 arg1, TSimdf32x3 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_min_ps(arg1, arg2);
#elif defined(TF_FEATURE_CPU_NEON)
    return vminq_f32(arg1, arg2);
#else
    return { { fminf(arg1.v[0], arg2.v[0]), fminf(arg1.v[1], arg2.v[1]), fminf(arg1.v[2], arg2.v[2]) } };
#endif
}
inline TSimdf32x3 tfSimd3fMax(TSimdf32x3 arg1, TSimdf32x3 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_max_ps(arg1, arg2);
#elif defined(TF_FEATURE_CPU_NEON)
    return vmaxq_f32(arg1, arg2);
#else
    return { { fmaxf(arg1.v[0], arg2.v[0]), fmaxf(arg1.v[1], arg2.v[1]), fmaxf(arg1.v[2], arg2.v[2]) } };
#endif
}
inline TSimdf32x3 tfSimd3fClamp(TSimdf32x3 value, TSimdf32x3 min, TSimdf32x3 max) {
    return tfSimd3fMax(min, tfSimd3fMin(value, max));
}

inline TSimdi32x3 tfSimd3fToSimd3i(TSimdf32x3 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_castps_si128(value);
#elif defined(TF_FEATURE_CPU_NEON)
    return vreinterpretq_f32_s32(value);
#elif defined(TF_FEATURE_CPU_SCALAR)
    return { (int32_t)value.v[0], (int32_t)value.v[1], (int32_t)value.v[2]};
#endif
}

inline TSimdf32x3 tfSimd3iToSimd3f(TSimdi32x3 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_castsi128_ps(value);
#elif defined(TF_FEATURE_CPU_NEON)
    return vreinterpretq_s32_f32(value);
#elif defined(TF_FEATURE_CPU_SCALAR)
    return { (float)value.v[0], (float)value.v[1], (float)value.v[2]};
#endif
}

inline float tfSimd3fSelectIndex0(TSimdf32x3 value) { 
#if defined(TF_FEATURE_CPU_SSE)
  return _mm_cvtss_f32(value);
#elif defined(TF_FEATURE_CPU_NEON)
  return vgetq_lane_f32(value, 0);
#elif defined(TF_FEATURE_CPU_SCALAR)
  return value.v[0];
#endif
}

inline float tfSimd3fSelectIndex1(TSimdf32x3 value) {
#if defined(TF_FEATURE_CPU_SSE)
    return tfSimd3fSelectIndex0(tfSimd3fSplatIndex1(value)); 
#elif defined(TF_FEATURE_CPU_NEON)
    return vgetq_lane_f32(value, 1);
#elif defined(TF_FEATURE_CPU_SCALAR)
  return value.v[1];
#endif
}

inline float tfSimd3fSelectIndex2(TSimdf32x3 value) { 
#if defined(TF_FEATURE_CPU_SSE)
    return tfSimd3fSelectIndex0(tfSimd3fSplatIndex2(value)); 
#elif defined(TF_FEATURE_CPU_NEON)
    return vgetq_lane_f32(value, 2);
#elif defined(TF_FEATURE_CPU_SCALAR)
  return value.v[2];
#endif
}

inline TSimdf32x3 tfSimd3fAdd(TSimdf32x3 arg1, TSimdf32x3 arg2)
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
    };
#endif
}
inline TSimdf32x3 tfSimd3fSub(TSimdf32x3 arg1, TSimdf32x3 arg2)
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
    };
#endif
}
inline TSimdf32x3 tfSimd3fMul(TSimdf32x3 arg1, TSimdf32x3 arg2)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_mul_ps(arg1, arg2);
#elif defined(TF_FEATURE_CPU_NEON)
    return vmulq_f32(arg1, arg2);
#else
    return {
        arg1.v[0] * arg2.v[0],
        arg1.v[1] * arg2.v[1],
        arg1.v[2] * arg2.v[2],
    };
#endif
}
inline TSimdf32x3 tfSimd3fMadd(TSimdf32x3 mul1, TSimdf32x3 mul2, TSimdf32x3 add) 
{
#if defined(TF_FEATURE_CPU_SSE)
#if 0
    return _mm_fmadd_ps(mul1, mul2, add); // Requires FMA CPUID
#else
    return tfSimd3fAdd(tfSimd3fMul(mul1, mul2), add);
#endif
#elif defined(TF_FEATURE_CPU_NEON)
    return vmlaq_f32(add, mul1, mul2);
#else
    return tfSimd3fAdd(tfSimd3fMul(mul1, mul2), add);
#endif

}
inline TSimdf32x3 tfSimd3fDiv(TSimdf32x3 arg1, TSimdf32x3 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_div_ps(arg1, arg2);
#elif defined(TF_FEATURE_CPU_NEON)
    return vdivq_f32(arg1, arg2);
#else
    return {
        arg1.v[0] / arg2.v[0],
        arg1.v[1] / arg2.v[1],
        arg1.v[2] / arg2.v[2]
    };
#endif
}

inline TSimdf32x3 tfSimd3fAbs(TSimdf32x3 value) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_and_ps(value, _mm_set1_ps((float)(0x7FFFFFFF)));
#elif defined(TF_FEATURE_CPU_NEON)
    return vabsq_f32(value);
#else
    return {
        abs(value.v[0]),
        abs(value.v[1]),
        abs(value.v[2]),
    };
#endif
}

inline TSimdf32x3 tfSimd3fLoadImmediate(float x, float y, float z) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_set_ps(0.0f, z, y, x);
#elif defined(TF_FEATURE_CPU_NEON)
    const float values[4] = { x, y, z, 0.0f };
    return vld1q_f32(values);
#else
    return { x, y, z};
#endif
}


inline TSimdi32x3 tfSimd3iLoadImmediate(int32_t x, int32_t y, int32_t z) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_set_epi32(0.0f, x, y, z);
#elif defined(TF_FEATURE_CPU_NEON)
    const int32_t values[4] = { x, y, z, 0 };
    return vld1q_s32(values);
#else
    return { x, y, z};
#endif
}

inline TSimdf32x2 tfSimd3fToSimd2f(TSimdf32x3 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return value;
#elif defined(TF_FEATURE_CPU_NEON)
    return vget_low_f32(value);
#else
    return {value.v[0], value.v[1]};
#endif
}

inline TSimdf32x3 tfSimd3fSplatIndex0(TSimdf32x3 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_shuffle_ps(value, value, _MM_SHUFFLE(0, 0, 0, 0));
#elif defined(TF_FEATURE_CPU_NEON)
    return vdupq_laneq_f32(value, 0);
#else
  return {value.v[0],value.v[0],value.v[0]};
#endif
}

inline TSimdf32x3 tfSimd3fSplatIndex1(TSimdf32x3 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_shuffle_ps(value, value, _MM_SHUFFLE(1, 1, 1, 1));
#elif defined(TF_FEATURE_CPU_NEON)
    return vdupq_laneq_f32(value, 1);
#else
  return {value.v[1],value.v[1],value.v[1]};
#endif
}

inline TSimdf32x3 tfSimd3fSplatIndex2(TSimdf32x3 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_shuffle_ps(value, value, _MM_SHUFFLE(2, 2, 2, 2));
#elif defined(TF_FEATURE_CPU_NEON)
    return vdupq_laneq_f32(value, 2);
#else
  return {value.v[2],value.v[2],value.v[2]};
#endif
}

inline TSimdi32x3 tfSimd3iSplat(int32_t value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_set1_epi32(value);
#elif defined(TF_FEATURE_CPU_NEON)
    return vdupq_n_s32(value);
#else
    return { value, value, value };
#endif
}

inline TSimdf32x3 tfSimd3fSplat(float value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_set1_ps(value);
#elif defined(TF_FEATURE_CPU_NEON)
    return vdupq_n_f32(value);
#else
    return { value, value, value };
#endif
}

inline TSimdi32x3 tfSimd3iCmpEq(TSimdi32x3 arg1, TSimdi32x3 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_cmpeq_epi32(arg1, arg2);
#elif defined(TF_FEATURE_CPU_NEON)
    return vceqq_s32(arg1, arg2);
#else
    return { { (arg1.v[0] == arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, 
               (arg1.v[1] == arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000,
               (arg1.v[2] == arg2.v[2]) ? (int32_t)0xFFFFFFFF : 0x00000000} };
#endif
}
inline TSimdi32x3 tfSimd3iCmpNeq(TSimdi32x3 arg1, TSimdi32x3 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_xor_si128(
        _mm_cmpeq_epi32(arg1, arg2), 
        _mm_set1_epi32((int32_t)0xFFFFFFFF));
#elif defined(TF_FEATURE_CPU_NEON)
    return vmvnq_s32(vceqq_s32(arg1, arg2));
#else
    return { { (arg1.v[0] != arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, 
               (arg1.v[1] != arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000,
               (arg1.v[2] != arg2.v[2]) ? (int32_t)0xFFFFFFFF : 0x00000000} };
#endif
}
inline TSimdi32x3 tfSimd3iCmpGt(TSimdi32x3 arg1, TSimdi32x3 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_cmpgt_epi32(arg1, arg2);
#elif defined(TF_FEATURE_CPU_NEON)
    return vcgtq_s32(arg1, arg2);
#else
    return { { (arg1.v[0] > arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, 
               (arg1.v[1] > arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000,
               (arg1.v[2] > arg2.v[2]) ? (int32_t)0xFFFFFFFF : 0x00000000} };
#endif
}
inline TSimdi32x3 tfSimd3iCmpGtEq(TSimdi32x3 arg1, TSimdi32x3 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_or_si128(
        _mm_cmpgt_epi32(arg1, arg2), 
        _mm_cmpeq_epi32(arg1, arg2));
#elif defined(TF_FEATURE_CPU_NEON)
    return vcgeq_s32(arg1, arg2);
#else
    return { { (arg1.v[0] >= arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, 
               (arg1.v[1] >= arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000,
               (arg1.v[2] >= arg2.v[2]) ? (int32_t)0xFFFFFFFF : 0x00000000} };
#endif
}
inline TSimdi32x3 tfSimd3iCmpLt(TSimdi32x3 arg1, TSimdi32x3 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_cmplt_epi32(arg1, arg2);
#elif defined(TF_FEATURE_CPU_NEON)
    return vcltq_s32(arg1, arg2);
#else
    return { { (arg1.v[0] < arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, 
               (arg1.v[1] < arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000,
               (arg1.v[2] < arg2.v[2]) ? (int32_t)0xFFFFFFFF : 0x00000000 } };
#endif
}
inline TSimdi32x3 tfSimd3iCmpLtEq(TSimdi32x3 arg1, TSimdi32x3 arg2) {

#if defined(TF_FEATURE_CPU_SSE)
    return _mm_or_si128(
        _mm_cmplt_epi32(arg1, arg2), 
        _mm_cmpeq_epi32(arg1, arg2));
#elif defined(TF_FEATURE_CPU_NEON)
    return vcleq_s32(arg1, arg2);
#else
    return { { (arg1.v[0] < arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, 
               (arg1.v[1] < arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000,
               (arg1.v[2] < arg2.v[2]) ? (int32_t)0xFFFFFFFF : 0x00000000} };
#endif

}
inline bool tfSimd3fCmpAllEq(TSimdf32x4 arg1, TSimdf32x4 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    TSimdf32x4  compare = tfSimd3fCmpEq(arg1, arg2);
    return (_mm_movemask_ps(compare) & 0b0111) == 0b0111;
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

inline bool tfSimd3iCmpAllEq(TSimdi32x3 arg1, TSimdi32x3 arg2)
{
#if defined(TF_FEATURE_CPU_SSE)
    const TSimdi32x3 compare = tfSimd3iCmpEq(arg1, arg2);
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

#endif
