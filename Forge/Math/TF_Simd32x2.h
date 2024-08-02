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

inline Tsimd_f32x2_t tfS32x2FSplat(float value);
inline Tsimd_i32x2_t tfS32x2ISplat(int32_t value);

inline Tsimd_f32x2_t tfS32x2FZero();
inline Tsimd_i32x2_t tfS32x2IZero();

inline Tsimd_i32x2_t tfS32x2FToSimd2i(Tsimd_f32x2_t value);
inline Tsimd_f32x2_t tfS32x2IToSimd2f(Tsimd_i32x2_t value);

inline Tsimd_f32x2_t tfS32x2FSplatIndex0(Tsimd_f32x2_t value);
inline Tsimd_f32x2_t tfS32x2FSplatIndex1(Tsimd_f32x2_t value);

static inline Tsimd_f32x4_t tfSimdFloat2To4Splat0(Tsimd_f32x2_t value); 
static inline Tsimd_f32x4_t tfSimdFloat2To4Splat1(Tsimd_f32x2_t value); 

inline Tsimd_f32x2_t tfS32x2FSelect(Tsimd_f32x2_t arg0, Tsimd_f32x2_t arg1, Tsimd_f32x2_t mask);
inline Tsimd_i32x2_t tfS32x2ISelect(Tsimd_i32x2_t arg0, Tsimd_i32x2_t arg1, Tsimd_i32x2_t mask);

inline float tfS32x2FSelectIndex0(Tsimd_f32x2_t value);
inline float tfS32x2FSelectIndex1(Tsimd_f32x2_t value);

inline Tsimd_f32x2_t tfSimdFloat2x32Load(float x, float y);
inline Tsimd_i32x2_t   tfSimdInt2x32Load(int32_t x, int32_t y);

inline Tsimd_f32x2_t tfS32x2FAdd(Tsimd_f32x2_t arg1, Tsimd_f32x2_t arg2);
inline Tsimd_f32x2_t tfS32x2FSub(Tsimd_f32x2_t arg1, Tsimd_f32x2_t arg2);
inline Tsimd_f32x2_t tfS32x2FMul(Tsimd_f32x2_t arg1, Tsimd_f32x2_t arg2);
inline Tsimd_f32x2_t tfS32x2FMadd(Tsimd_f32x2_t mul1, Tsimd_f32x2_t mul2, Tsimd_f32x2_t add);
inline Tsimd_f32x2_t tfS32x2FDiv(Tsimd_f32x2_t arg1, Tsimd_f32x2_t arg2);
inline Tsimd_f32x2_t tfS32x2FAbs(Tsimd_f32x2_t value);

inline Tsimd_f32x2_t tfS32x2FNot(Tsimd_f32x2_t value);
inline Tsimd_f32x2_t tfS32x2FAnd(Tsimd_f32x2_t arg1, Tsimd_f32x2_t arg2);
inline Tsimd_f32x2_t tfS32x2FAndNot(Tsimd_f32x2_t arg1, Tsimd_f32x2_t arg2);
inline Tsimd_f32x2_t tfS32x2FOr(Tsimd_f32x2_t arg1, Tsimd_f32x2_t arg2);
inline Tsimd_f32x2_t tfS32x2FXor(Tsimd_f32x2_t arg1, Tsimd_f32x2_t arg2);

inline Tsimd_i32x2_t tfS32x2INot(Tsimd_i32x2_t value);
inline Tsimd_i32x2_t tfS32x2IAnd(Tsimd_i32x2_t arg1, Tsimd_i32x2_t arg2);
inline Tsimd_i32x2_t tfS32x2IAndNot(Tsimd_i32x2_t arg1, Tsimd_i32x2_t arg2);
inline Tsimd_i32x2_t tfS32x2IOr(Tsimd_i32x2_t arg1, Tsimd_i32x2_t arg2);
inline Tsimd_i32x2_t tfS32x2IXor(Tsimd_i32x2_t arg1, Tsimd_i32x2_t arg2);

inline Tsimd_f32x2_t tfS32x2FFloor(Tsimd_f32x2_t value);
inline Tsimd_f32x2_t tfS32x2FCeil(Tsimd_f32x2_t value);
inline Tsimd_f32x2_t tfS32x2FRound(Tsimd_f32x2_t value); // Ties to even (banker's rounding)
inline Tsimd_f32x2_t tfS32x2FTruncate(Tsimd_f32x2_t value);
inline Tsimd_f32x2_t tfS32x2FMin(Tsimd_f32x2_t arg1, Tsimd_f32x2_t arg2);
inline Tsimd_f32x2_t tfS32x2FMax(Tsimd_f32x2_t arg1, Tsimd_f32x2_t arg2);
inline Tsimd_f32x2_t tfS32x2FClamp(Tsimd_f32x2_t value, Tsimd_f32x2_t min, Tsimd_f32x2_t max);

inline Tsimd_i32x2_t tfS32x2ICmpEq(Tsimd_i32x2_t arg1, Tsimd_i32x2_t arg2);
inline Tsimd_i32x2_t tfS32x2ICmpNeq(Tsimd_i32x2_t arg1, Tsimd_i32x2_t arg2);
inline Tsimd_i32x2_t tfS32x2ICmpGt(Tsimd_i32x2_t arg1, Tsimd_i32x2_t arg2);
inline Tsimd_i32x2_t tfS32x2ICmpGtEq(Tsimd_i32x2_t arg1, Tsimd_i32x2_t arg2);
inline Tsimd_i32x2_t tfS32x2ICmpLt(Tsimd_i32x2_t arg1, Tsimd_i32x2_t arg2);
inline Tsimd_i32x2_t tfS32x2ICmpLtEq(Tsimd_i32x2_t arg1, Tsimd_i32x2_t arg2);

inline Tsimd_f32x2_t tfS32x2FCmpEq(Tsimd_f32x2_t arg1, Tsimd_f32x2_t arg2);
inline Tsimd_f32x2_t tfS32x2FCmpNeq(Tsimd_f32x2_t arg1, Tsimd_f32x2_t arg2);
inline Tsimd_f32x2_t tfS32x2FCmpGt(Tsimd_f32x2_t arg1, Tsimd_f32x2_t arg2);
inline Tsimd_f32x2_t tfS32x2FCmpGtEq(Tsimd_f32x2_t arg1, Tsimd_f32x2_t arg2);
inline Tsimd_f32x2_t tfS32x2FCmpLt(Tsimd_f32x2_t arg1, Tsimd_f32x2_t arg2);
inline Tsimd_f32x2_t tfS32x2FCmpLtEq(Tsimd_f32x2_t arg1, Tsimd_f32x2_t arg2);

inline bool tfS32x2ICmpAllEq(Tsimd_i32x2_t arg1, Tsimd_i32x2_t arg2);
inline bool tfS32x2FCmpAllEq(Tsimd_f32x2_t arg1, Tsimd_f32x2_t arg2);

static inline bool tfS32x2FCmpAllLt(Tsimd_f32x2_t a, Tsimd_f32x2_t b);

#if defined(TF_FEATURE_CPU_SSE)
#include "Internal/TF_Simd32x2_sse.inl"
#elif defined(TF_FEATURE_CPU_NEON)
#include "Internal/TF_Simd32x2_neon.inl"
#else
#include "Internal/TF_Simd32x2_scalar.inl"
#endif


#endif
