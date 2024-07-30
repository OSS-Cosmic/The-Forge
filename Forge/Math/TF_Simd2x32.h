/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#pragma once
#ifndef TF_SIMD_2_32_H
#define TF_SIMD_2_32_H

#include "Forge/Math/Internal/SimdTypes.h"

inline TSimdFloat32x2 tfSimd2fSplat(float value);
inline TSimdInt32x2 tfSimd2iSplat(int32_t value);

inline TSimdFloat32x2 tfSimd2fZero();
inline TSimdInt32x2 tfSimd2iZero();

inline TSimdInt32x2 tfSimd2fToSimd2i(TSimdFloat32x2 value);
inline TSimdFloat32x2 tfSimd2iToSimd2f(TSimdInt32x2 value);

inline TSimdFloat32x2 tfSimd2fSplatIndex0(TSimdFloat32x2 value);
inline TSimdFloat32x2 tfSimd2fSplatIndex1(TSimdFloat32x2 value);

inline TSimdFloat32x2 tfSimd2fSelect(TSimdFloat32x2 arg0, TSimdFloat32x2 arg1, TSimdFloat32x2 mask);
inline TSimdInt32x2 tfSimd2iSelect(TSimdInt32x2 arg0, TSimdInt32x2 arg1, TSimdInt32x2 mask);

inline float tfSimd2fSelectIndex0(TSimdFloat32x2 value);
inline float tfSimd2fSelectIndex1(TSimdFloat32x2 value);

inline TSimdFloat32x2 tfSimdFloat2Load(float x, float y);
inline TSimdInt32x2 tfSimd2iLoadImmediate(int32_t x, int32_t y);

inline TSimdFloat32x2 tfSimd2fAdd(TSimdFloat32x2 arg1, TSimdFloat32x2 arg2);
inline TSimdFloat32x2 tfSimd2fSub(TSimdFloat32x2 arg1, TSimdFloat32x2 arg2);
inline TSimdFloat32x2 tfSimd2fMul(TSimdFloat32x2 arg1, TSimdFloat32x2 arg2);
inline TSimdFloat32x2 tfSimd2fMadd(TSimdFloat32x2 mul1, TSimdFloat32x2 mul2, TSimdFloat32x2 add);
inline TSimdFloat32x2 tfSimd2fDiv(TSimdFloat32x2 arg1, TSimdFloat32x2 arg2);
inline TSimdFloat32x2 tfSimd2fAbs(TSimdFloat32x2 value);

inline TSimdFloat32x2 tfSimd2fNot(TSimdFloat32x2 value);
inline TSimdFloat32x2 tfSimd2fAnd(TSimdFloat32x2 arg1, TSimdFloat32x2 arg2);
inline TSimdFloat32x2 tfSimd2fAndNot(TSimdFloat32x2 arg1, TSimdFloat32x2 arg2);
inline TSimdFloat32x2 tfSimd2fOr(TSimdFloat32x2 arg1, TSimdFloat32x2 arg2);
inline TSimdFloat32x2 tfSimd2fXor(TSimdFloat32x2 arg1, TSimdFloat32x2 arg2);

inline TSimdInt32x2 tfSimd2iNot(TSimdInt32x2 value);
inline TSimdInt32x2 tfSimd2iAnd(TSimdInt32x2 arg1, TSimdInt32x2 arg2);
inline TSimdInt32x2 tfSimd2iAndNot(TSimdInt32x2 arg1, TSimdInt32x2 arg2);
inline TSimdInt32x2 tfSimd2iOr(TSimdInt32x2 arg1, TSimdInt32x2 arg2);
inline TSimdInt32x2 tfSimd2iXor(TSimdInt32x2 arg1, TSimdInt32x2 arg2);

inline TSimdFloat32x2 tfSimd2fFloor(TSimdFloat32x2 value);
inline TSimdFloat32x2 tfSimd2fCeil(TSimdFloat32x2 value);
inline TSimdFloat32x2 tfSimd2fRound(TSimdFloat32x2 value); // Ties to even (banker's rounding)
inline TSimdFloat32x2 tfSimd2fTruncate(TSimdFloat32x2 value);
inline TSimdFloat32x2 tfSimd2fMin(TSimdFloat32x2 arg1, TSimdFloat32x2 arg2);
inline TSimdFloat32x2 tfSimd2fMax(TSimdFloat32x2 arg1, TSimdFloat32x2 arg2);
inline TSimdFloat32x2 tfSimd2fClamp(TSimdFloat32x2 value, TSimdFloat32x2 min, TSimdFloat32x2 max);

inline TSimdInt32x2 tfSimd2iCmpEq(TSimdInt32x2 arg1, TSimdInt32x2 arg2);
inline TSimdInt32x2 tfSimd2iCmpNeq(TSimdInt32x2 arg1, TSimdInt32x2 arg2);
inline TSimdInt32x2 tfSimd2iCmpGt(TSimdInt32x2 arg1, TSimdInt32x2 arg2);
inline TSimdInt32x2 tfSimd2iCmpGtEq(TSimdInt32x2 arg1, TSimdInt32x2 arg2);
inline TSimdInt32x2 tfSimd2iCmpLt(TSimdInt32x2 arg1, TSimdInt32x2 arg2);
inline TSimdInt32x2 tfSimd2iCmpLtEq(TSimdInt32x2 arg1, TSimdInt32x2 arg2);

inline TSimdFloat32x2 tfSimd2fCmpEq(TSimdFloat32x2 arg1, TSimdFloat32x2 arg2);
inline TSimdFloat32x2 tfSimd2fCmpNeq(TSimdFloat32x2 arg1, TSimdFloat32x2 arg2);
inline TSimdFloat32x2 tfSimd2fCmpGt(TSimdFloat32x2 arg1, TSimdFloat32x2 arg2);
inline TSimdFloat32x2 tfSimd2fCmpGtEq(TSimdFloat32x2 arg1, TSimdFloat32x2 arg2);
inline TSimdFloat32x2 tfSimd2fCmpLt(TSimdFloat32x2 arg1, TSimdFloat32x2 arg2);
inline TSimdFloat32x2 tfSimd2fCmpLtEq(TSimdFloat32x2 arg1, TSimdFloat32x2 arg2);

inline bool tfSimd2iCmpAllEq(TSimdInt32x2 arg1, TSimdInt32x2 arg2);
inline bool tfSimd2fCmpAllEq(TSimdFloat32x2 arg1, TSimdFloat32x2 arg2);

// ----------------------------------------------------------------
// --------------------- Implementaion ----------------------------
// ----------------------------------------------------------------

inline TSimdInt32x2 tfSimd2iSelect(TSimdInt32x2 arg0, TSimdInt32x2 arg1, TSimdInt32x2 mask) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_blendv_epi8(arg0, arg1, mask);
#elif defined(TF_FEATURE_CPU_NEON)
    return vbsl_s32(mask, arg1, arg2);
#else
    return {(mask.v[0] == 0) ? arg0.v[0] : arg1.v[0]
            , (mask.v[1] == 0) ? arg0.v[1] : arg1.v[1]};
#endif
}
inline TSimdFloat32x2 tfSimd2fSelect(TSimdFloat32x2 arg0, TSimdFloat32x2 arg1, TSimdFloat32x2 mask)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_blendv_ps(arg0, arg1, mask);
#elif defined(TF_FEATURE_CPU_NEON)
    return vbsl_f32(mask, arg1, arg2);
#else
    TSimdInt32x2 intMask =  tfSimd2fToSimd2i(mask);
    return { (intMask.v[0] == 0) ? arg0.v[0] : arg1.v[0]
            , (intMask.v[1] == 0) ? arg0.v[1] : arg1.v[1]};
#endif
}

inline TSimdFloat32x2 tfSimd2fZero() { 
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_setzero_ps();
#elif defined(TF_FEATURE_CPU_NEON)
    return vmov_n_f32(0);
#else
    return { 0, 0};
#endif
}
inline TSimdInt32x2 tfSimd2iZero()
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_setzero_si128();
#elif defined(TF_FEATURE_CPU_NEON)
    return vmov_n_s32(0);
#else
    return { 0, 0 };
#endif
}

inline TSimdInt32x2 tfSimd2iNot(TSimdInt32x2 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    const TSimdInt32x2 invert = tfSimd2iSplat(TF_SIMDI_MAX);
    return _mm_andnot_si128(value, invert);
#elif defined(TF_FEATURE_CPU_NEON)
    return vmvn_s32(value);
#else
    return { ~value.v[0], ~value.v[1] };
#endif
}
inline TSimdInt32x2 tfSimd2iAnd(TSimdInt32x2 arg1, TSimdInt32x2 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_and_si128(arg1, arg2);
#elif defined(TF_FEATURE_CPU_NEON)
    return vand_s32(arg1, arg2);
#else
    return { arg1.v[0] & arg2.v[0], arg1.v[1] & arg2.v[1]};
#endif
}
inline TSimdInt32x2 tfSimd2iAndNot(TSimdInt32x2 arg1, TSimdInt32x2 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_andnot_si128(arg1, arg2); 
#elif defined(TF_FEATURE_CPU_NEON)
    return vand_s32(vmvn_s32(arg1), arg2);
#else
    return { ~arg1.v[0] & arg2.v[0], ~arg1.v[1] & arg2.v[1]};
#endif
}
inline TSimdInt32x2 tfSimd2iOr(TSimdInt32x2 arg1, TSimdInt32x2 arg2)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_or_si128(arg1, arg2);
#elif defined(TF_FEATURE_CPU_NEON)
    return vorr_s32(arg1, arg2);
#else
    return { arg1.v[0] | arg2.v[0], arg1.v[1] | arg2.v[1]};
#endif
}
inline TSimdInt32x2 tfSimd2iXor(TSimdInt32x2 arg1, TSimdInt32x2 arg2){
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_xor_si128(arg1, arg2); 
#elif defined(TF_FEATURE_CPU_NEON)
    return veor_s32(arg1, arg2);
#else
    return { arg1.v[0] ^ arg2.v[0], arg1.v[1] ^ arg2.v[1]};
#endif
}

inline TSimdFloat32x2 tfSimd2fNot(TSimdFloat32x2 value) {
#if defined(TF_FEATURE_CPU_SSE)
    const TSimdFloat32x2 invert = tfSimd2fSplat((float)(0xFFFFFFFF));
    return _mm_andnot_ps(value, invert);
#elif defined(TF_FEATURE_CPU_NEON)
    return vreinterpret_f32_s32(vmvn_s32(vreinterpret_s32_f32(value)));
#else
    TSimdInt32x2 result = {{ ~((int32_t)value.v[0]), ~((int32_t)value.v[1])} } ;
    return tfSimd2iToSimd2f(result);
#endif
}
inline TSimdFloat32x2 tfSimd2fAnd(TSimdFloat32x2 arg1, TSimdFloat32x2 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_and_ps(arg1, arg2);
#elif defined(TF_FEATURE_CPU_NEON)
    return vreinterpret_f32_s32(vand_s32(vreinterpret_s32_f32(arg1), vreinterpret_s32_f32(arg2)));
#else
    TSimdInt32x2 result = { ((int32_t)arg1.v[0]) & ((int32_t)arg2.v[0]), ((int32_t)arg1.v[1]) & ((int32_t)arg2.v[1]) };
    return tfSimd2iToSimd2f(result);
#endif
}
inline TSimdFloat32x2 tfSimd2fAndNot(TSimdFloat32x2 arg1, TSimdFloat32x2 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_andnot_ps(arg1, arg2);
#elif defined(TF_FEATURE_CPU_NEON)
    return vreinterpret_f32_s32(vand_s32(vmvn_s32(vreinterpret_s32_f32(arg1)), vreinterpret_s32_f32(arg2)));
#else
    TSimdInt32x2 result = { { ~((int32_t)arg1.v[0]) & ((int32_t)arg2.v[0]),
                                 ~((int32_t)arg1.v[1]) & ((int32_t)arg2.v[1])} };
    return tfSimd2iToSimd2f(result);
#endif
}
inline TSimdFloat32x2 tfSimd2fOr(TSimdFloat32x2 arg1, TSimdFloat32x2 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_or_ps(arg1, arg2);
#elif defined(TF_FEATURE_CPU_NEON)
    return vreinterpret_f32_s32(vorr_s32(vreinterpret_s32_f32(arg1), vreinterpret_s32_f32(arg2)));
#else
    TSimdInt32x2 result = { { ((int32_t)arg1.v[0]) | ((int32_t)arg2.v[0]),
                                 ((int32_t)arg1.v[1]) | ((int32_t)arg2.v[1])} };
    return tfSimd2iToSimd2f(result);
#endif
}
inline TSimdFloat32x2 tfSimd2fXor(TSimdFloat32x2 arg1, TSimdFloat32x2 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_xor_ps(arg1, arg2);
#elif defined(TF_FEATURE_CPU_NEON)
    return vreinterpret_f32_s32(veor_s32(vreinterpret_s32_f32(arg1), vreinterpret_s32_f32(arg2)));
#else
    TSimdInt32x2 result = { { ((int32_t)arg1.v[0]) ^ ((int32_t)arg2.v[0]),
                                 ((int32_t)arg1.v[1]) ^ ((int32_t)arg2.v[1]) } };
    return tfSimd2iToSimd2f(result);
#endif
}

inline TSimdFloat32x2 tfSimd2fFloor(TSimdFloat32x2 value) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_floor_ps(value);
#elif defined(TF_FEATURE_CPU_NEON)
    return vrndm_f32(value);
#else
    return { { floorf(value.v[0]), floorf(value.v[1]) } };
#endif
}
inline TSimdFloat32x2 tfSimd2fCeil(TSimdFloat32x2 value) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_ceil_ps(value);
#elif defined(TF_FEATURE_CPU_NEON)
    return vrndp_f32(value);
#else
    return { { ceilf(value.v[0]), ceilf(value.v[1]) } };
#endif
}
inline TSimdFloat32x2 tfSimd2fRound(TSimdFloat32x2 value) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_round_ps(value, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC);
#elif defined(TF_FEATURE_CPU_NEON)
    return vrndn_f32(value);
#else
    // While 'roundf' may seem the obvious choice here, it rounds halfway cases
    // away from zero regardless of the current rounding mode, but 'rintf' uses
    // the current rounding mode which is consistent with other implementations.
    return { { rintf(value.v[0]), rintf(value.v[1]) } };
#endif
}
inline TSimdFloat32x2 tfSimd2fTruncate(TSimdFloat32x2 value) { return tfSimd2iToSimd2f(tfSimd2fToSimd2i(value)); }
inline TSimdFloat32x2 tfSimd2fMin(TSimdFloat32x2 arg1, TSimdFloat32x2 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_min_ps(arg1, arg2);
#elif defined(TF_FEATURE_CPU_NEON)
    return vmin_f32(arg1, arg2);
#else
    return { { fminf(arg1.v[0], arg2.v[0]), fminf(arg1.v[1], arg2.v[1]) } };
#endif
}
inline TSimdFloat32x2 tfSimd2fMax(TSimdFloat32x2 arg1, TSimdFloat32x2 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_max_ps(arg1, arg2);
#elif defined(TF_FEATURE_CPU_NEON)
    return vmax_f32(arg1, arg2);
#else
    return { { fmaxf(arg1.v[0], arg2.v[0]), fmaxf(arg1.v[1], arg2.v[1]) } };
#endif
}
inline TSimdFloat32x2 tfSimd2fClamp(TSimdFloat32x2 value, TSimdFloat32x2 min, TSimdFloat32x2 max) {
    return tfSimd2fMax(min, tfSimd2fMin(value, max));
}

inline TSimdInt32x2 tfSimd2fToSimd2i(TSimdFloat32x2 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_castps_si128(value);
#elif defined(TF_FEATURE_CPU_NEON)
    return vreinterpret_s32_f32(value);
#elif defined(TF_FEATURE_CPU_SCALAR)
    return { (int32_t)value.v[0], (int32_t)value.v[1]};
#endif
}

inline TSimdFloat32x2 tfSimd2iToSimd2f(TSimdInt32x2 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_castsi128_ps(value);
#elif defined(TF_FEATURE_CPU_NEON)
    return vreinterpret_f32_s32(value);
#elif defined(TF_FEATURE_CPU_SCALAR)
    return { (float)value.v[0], (float)value.v[1] };
#endif
}

inline float tfSimd2fSelectIndex0(TSimdFloat32x2 value) { 
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_cvtss_f32(value);
#elif defined(TF_FEATURE_CPU_NEON)
    return vget_lane_f32(value, 0);
#elif defined(TF_FEATURE_CPU_SCALAR)
    return value.v[0];
#endif
}

inline float tfSimd2fSelectIndex1(TSimdFloat32x2 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return tfSimd2fSelectIndex0(tfSimd2fSplatIndex1(value));
#elif defined(TF_FEATURE_CPU_NEON)
    return vget_lane_f32(value, 1);
#elif defined(TF_FEATURE_CPU_SCALAR)
    return value.v[1];
#endif
}

inline TSimdFloat32x2 tfSimd2fAdd(TSimdFloat32x2 arg1, TSimdFloat32x2 arg2)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_add_ps(arg1, arg2);
#elif defined(TF_FEATURE_CPU_NEON)
    return vadd_f32(arg1, arg2);
#else
    return {
        arg1.v[0] + arg2.v[0],
        arg1.v[1] + arg2.v[1],
    };
#endif
}
inline TSimdFloat32x2 tfSimd2fSub(TSimdFloat32x2 arg1, TSimdFloat32x2 arg2)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_sub_ps(arg1, arg2);
#elif defined(TF_FEATURE_CPU_NEON)
    return vsub_f32(arg1, arg2);
#else
    return {
        arg1.v[0] - arg2.v[0],
        arg1.v[1] - arg2.v[1],
    };
#endif
}
inline TSimdFloat32x2 tfSimd2fMul(TSimdFloat32x2 arg1, TSimdFloat32x2 arg2)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_mul_ps(arg1, arg2);
#elif defined(TF_FEATURE_CPU_NEON)
    return vmul_f32(arg1, arg2);
#else
    return {
        arg1.v[0] * arg2.v[0],
        arg1.v[1] * arg2.v[1],
    };
#endif
}
inline TSimdFloat32x2 tfSimd2fMadd(TSimdFloat32x2 mul1, TSimdFloat32x2 mul2, TSimdFloat32x2 add) 
{
#if defined(TF_FEATURE_CPU_SSE)
#if 0
    return _mm_fmadd_ps(mul1, mul2, add); // Requires FMA CPUID
#else
    return tfSimd2fAdd(tfSimd2fMul(mul1, mul2), add);
#endif
#elif defined(TF_FEATURE_CPU_NEON)
    return vmla_f32(add, mul1, mul2);
#else
    return tfSimd2fAdd(tfSimd2fMul(mul1, mul2), add);
#endif

}
inline TSimdFloat32x2 tfSimd2fDiv(TSimdFloat32x2 arg1, TSimdFloat32x2 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_div_ps(arg1, arg2);
#elif defined(TF_FEATURE_CPU_NEON)
    return vdiv_f32(arg1, arg2);
#else
    return {
        arg1.v[0] / arg2.v[0],
        arg1.v[1] / arg2.v[1],
    };
#endif
}

inline TSimdFloat32x2 tfSimd2fAbs(TSimdFloat32x2 value) {
#if defined(TF_FEATURE_CPU_SSE)
    const TSimdFloat32x4 signMask = tfSimd2iToSimd2f(tfSimd2iSplat(0x7FFFFFFF));
    return _mm_and_ps(value, signMask );
#elif defined(TF_FEATURE_CPU_NEON)
    return vabs_f32(value);
#else
    return {
        abs(value.v[0]),
        abs(value.v[1]),
    };
#endif
}

inline TSimdFloat32x2 tfSimdFloat2Load(float x, float y) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_set_ps(0.0f, 0.0f, y, x);
#elif defined(TF_FEATURE_CPU_NEON)
    const float values[2] = { x, y };
    return vld1_f32(values);
#else
    return { x, y};
#endif
}


inline TSimdInt32x2 tfSimd2iLoadImmediate(int32_t x, int32_t y) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_set_epi32(0.0f, 0.0f, x, y);
#elif defined(TF_FEATURE_CPU_NEON)
    const int32_t values[2] = { x, y };
    return vld1_s32(values);
#else
    return { x, y};
#endif
}


inline TSimdFloat32x2 tfSimd2fSplatIndex0(TSimdFloat32x2 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_shuffle_ps(value, value, _MM_SHUFFLE(0, 0, 0, 0));
#elif defined(TF_FEATURE_CPU_NEON)
    return vdup_lane_f32(value, 0);
#else
  return {value.v[0],value.v[0]};
#endif
}

inline TSimdFloat32x2 tfSimd2fSplatIndex1(TSimdFloat32x2 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_shuffle_ps(value, value, _MM_SHUFFLE(1, 1, 1, 1));
#elif defined(TF_FEATURE_CPU_NEON)
    return vdup_lane_f32(value, 1);
#else
  return {value.v[1],value.v[1]};
#endif
}


inline TSimdInt32x2 tfSimd2iSplat(int32_t value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_set1_epi32(value);
#elif defined(TF_FEATURE_CPU_NEON)
    return vdup_n_s32(value);
#else
    return { value, value };
#endif
}

inline TSimdFloat32x2 tfSimd2fSplat(float value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_set1_ps(value);
#elif defined(TF_FEATURE_CPU_NEON)
    return vdup_n_f32(value);
#else
    return { value, value };
#endif
}

inline TSimdInt32x2 tfSimd2iCmpEq(TSimdInt32x2 arg1, TSimdInt32x2 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_cmpeq_epi32(arg1, arg2);
#elif defined(TF_FEATURE_CPU_NEON)
    return vceq_s32(arg1, arg2);
#else
    return { { (arg1.v[0] == arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, 
               (arg1.v[1] == arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000} };
#endif
}
inline TSimdInt32x2 tfSimd2iCmpNeq(TSimdInt32x2 arg1, TSimdInt32x2 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_xor_si128(
        _mm_cmpeq_epi32(arg1, arg2), 
        _mm_set1_epi32((int32_t)0xFFFFFFFF));
#elif defined(TF_FEATURE_CPU_NEON)
    return vmvn_s32(vceq_s32(arg1, arg2));
#else
    return { { (arg1.v[0] != arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, 
               (arg1.v[1] != arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000} };
#endif
}
inline TSimdInt32x2 tfSimd2iCmpGt(TSimdInt32x2 arg1, TSimdInt32x2 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_cmpgt_epi32(arg1, arg2);
#elif defined(TF_FEATURE_CPU_NEON)
    return vcgt_s32(arg1, arg2);
#else
    return { { (arg1.v[0] > arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, 
               (arg1.v[1] > arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000} };
#endif
}
inline TSimdInt32x2 tfSimd2iCmpGtEq(TSimdInt32x2 arg1, TSimdInt32x2 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_or_si128(
        _mm_cmpgt_epi32(arg1, arg2), 
        _mm_cmpeq_epi32(arg1, arg2));
#elif defined(TF_FEATURE_CPU_NEON)
    return vcgt_s32(arg1, arg2);
#else
    return { { (arg1.v[0] >= arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, 
               (arg1.v[1] >= arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000} };
#endif
}
inline TSimdInt32x2 tfSimd2iCmpLt(TSimdInt32x2 arg1, TSimdInt32x2 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_cmplt_epi32(arg1, arg2);
#elif defined(TF_FEATURE_CPU_NEON)
    return vclt_s32(arg1, arg2);
#else
    return { { (arg1.v[0] < arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, 
               (arg1.v[1] < arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000} };
#endif
}
inline TSimdInt32x2 tfSimd2iCmpLtEq(TSimdInt32x2 arg1, TSimdInt32x2 arg2) {

#if defined(TF_FEATURE_CPU_SSE)
    return _mm_or_si128(
        _mm_cmplt_epi32(arg1, arg2), 
        _mm_cmpeq_epi32(arg1, arg2));
#elif defined(TF_FEATURE_CPU_NEON)
    return vcle_s32(arg1, arg2);
#else
    return { { (arg1.v[0] < arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, 
               (arg1.v[1] < arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000} };
#endif

}

inline bool tfSimd2fCmpAllEq(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    TSimdFloat32x4  compare = tfSimd2fCmpEq(arg1, arg2);
    return (_mm_movemask_ps(compare) & 0b0011) == 0b0011;
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

inline bool tfSimd2iCmpAllEq(TSimdInt32x2 arg1, TSimdInt32x2 arg2)
{
#if defined(TF_FEATURE_CPU_SSE)
    const TSimdInt32x2 compare = tfSimd2iCmpEq(arg1, arg2);
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

#endif
