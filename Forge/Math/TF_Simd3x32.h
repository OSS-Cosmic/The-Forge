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

inline TSimdFloat32x3 tfSimd3fSplat(float value);
inline TSimdInt32x3 tfSimd3iSplat(int32_t value);

inline TSimdFloat32x3 tfSimd3fZero();
inline TSimdInt32x3 tfSimd3iZero();

inline TSimdFloat32x2 tfSimd3fToSimd2f(TSimdFloat32x3 value);
inline TSimdInt32x3 tfSimd3fToSimd3i(TSimdFloat32x3 value);
inline TSimdFloat32x3 tfSimd3iToSimd3f(TSimdInt32x3 value);

inline TSimdFloat32x3 tfSimd3fSplatIndex0(TSimdFloat32x3 value);
inline TSimdFloat32x3 tfSimd3fSplatIndex1(TSimdFloat32x3 value);
inline TSimdFloat32x3 tfSimd3fSplatIndex2(TSimdFloat32x3 value);

static inline TSimdFloat32x4 tfSimdFloat3To4Splat0(TSimdFloat32x3 value);
static inline TSimdFloat32x4 tfSimdFloat3To4Splat1(TSimdFloat32x3 value);
static inline TSimdFloat32x4 tfSimdFloat3To4Splat2(TSimdFloat32x3 value);

inline TSimdFloat32x3 tfSimd3fSelect(TSimdFloat32x3 arg0, TSimdFloat32x3 arg1, TSimdFloat32x3 mask);
inline TSimdInt32x3 tfSimd3iSelect(TSimdInt32x3 arg0, TSimdInt32x3 arg1, TSimdInt32x3 mask);

inline float tfSimd3fSelectIndex0(TSimdFloat32x3 value);
inline float tfSimd3fSelectIndex1(TSimdFloat32x3 value);
inline float tfSimd3fSelectIndex2(TSimdFloat32x3 value);

inline TSimdFloat32x3 tfSimdFloat3Load(float x, float y, float z);
inline TSimdInt32x3 tfSimdInt3Load(int32_t x, int32_t y, int32_t z);

inline TSimdFloat32x3 tfSimd3fAdd(TSimdFloat32x3 arg1, TSimdFloat32x3 arg2);
inline TSimdFloat32x3 tfSimd3fSub(TSimdFloat32x3 arg1, TSimdFloat32x3 arg2);
inline TSimdFloat32x3 tfSimd3fMul(TSimdFloat32x3 arg1, TSimdFloat32x3 arg2);
inline TSimdFloat32x3 tfSimd3fMadd(TSimdFloat32x3 mul1, TSimdFloat32x3 mul2, TSimdFloat32x3 add);
inline TSimdFloat32x3 tfSimd3fDiv(TSimdFloat32x3 arg1, TSimdFloat32x3 arg2);
inline TSimdFloat32x3 tfSimd3fAbs(TSimdFloat32x3 value);

inline TSimdFloat32x3 tfSimd3fNot(TSimdFloat32x3 value);
inline TSimdFloat32x3 tfSimd3fAnd(TSimdFloat32x3 arg1, TSimdFloat32x3 arg2);
inline TSimdFloat32x3 tfSimd3fAndNot(TSimdFloat32x3 arg1, TSimdFloat32x3 arg2);
inline TSimdFloat32x3 tfSimd3fOr(TSimdFloat32x3 arg1, TSimdFloat32x3 arg2);
inline TSimdFloat32x3 tfSimd3fXor(TSimdFloat32x3 arg1, TSimdFloat32x3 arg2);

inline TSimdInt32x3 tfSimd3iNot(TSimdInt32x3 value);
inline TSimdInt32x3 tfSimd3iAnd(TSimdInt32x3 arg1, TSimdInt32x3 arg2);
inline TSimdInt32x3 tfSimd3iAndNot(TSimdInt32x3 arg1, TSimdInt32x3 arg2);
inline TSimdInt32x3 tfSimd3iOr(TSimdInt32x3 arg1, TSimdInt32x3 arg2);
inline TSimdInt32x3 tfSimd3iXor(TSimdInt32x3 arg1, TSimdInt32x3 arg2);

inline TSimdFloat32x3 tfSimd3fFloor(TSimdFloat32x3 value);
inline TSimdFloat32x3 tfSimd3fCeil(TSimdFloat32x3 value);
inline TSimdFloat32x3 tfSimd3fRound(TSimdFloat32x3 value); // Ties to even (banker's rounding)
inline TSimdFloat32x3 tfSimd3fTruncate(TSimdFloat32x3 value);
inline TSimdFloat32x3 tfSimd3fMin(TSimdFloat32x3 arg1, TSimdFloat32x3 arg2);
inline TSimdFloat32x3 tfSimd3fMax(TSimdFloat32x3 arg1, TSimdFloat32x3 arg2);
inline TSimdFloat32x3 tfSimd3fClamp(TSimdFloat32x3 value, TSimdFloat32x3 min, TSimdFloat32x3 max);

inline TSimdInt32x3 tfSimd3iCmpEq(TSimdInt32x3 arg1, TSimdInt32x3 arg2);
inline TSimdInt32x3 tfSimd3iCmpNeq(TSimdInt32x3 arg1, TSimdInt32x3 arg2);
inline TSimdInt32x3 tfSimd3iCmpGt(TSimdInt32x3 arg1, TSimdInt32x3 arg2);
inline TSimdInt32x3 tfSimd3iCmpGtEq(TSimdInt32x3 arg1, TSimdInt32x3 arg2);
inline TSimdInt32x3 tfSimd3iCmpLt(TSimdInt32x3 arg1, TSimdInt32x3 arg2);
inline TSimdInt32x3 tfSimd3iCmpLtEq(TSimdInt32x3 arg1, TSimdInt32x3 arg2);

inline TSimdFloat32x3 tfSimd3fCmpEq(TSimdFloat32x3 arg1, TSimdFloat32x3 arg2);
inline TSimdFloat32x3 tfSimd3fCmpNeq(TSimdFloat32x3 arg1, TSimdFloat32x3 arg2);
inline TSimdFloat32x3 tfSimd3fCmpGt(TSimdFloat32x3 arg1, TSimdFloat32x3 arg2);
inline TSimdFloat32x3 tfSimd3fCmpGtEq(TSimdFloat32x3 arg1, TSimdFloat32x3 arg2);
inline TSimdFloat32x3 tfSimd3fCmpLt(TSimdFloat32x3 arg1, TSimdFloat32x3 arg2);
inline TSimdFloat32x3 tfSimd3fCmpLtEq(TSimdFloat32x3 arg1, TSimdFloat32x3 arg2);

inline bool tfSimd3iCmpAllEq(TSimdInt32x3 arg1, TSimdInt32x3 arg2);
inline bool tfSimd3fCmpAllEq(TSimdFloat32x3 arg1, TSimdFloat32x3 arg2);

// ----------------------------------------------------------------
// --------------------- Implementaion ----------------------------
// ----------------------------------------------------------------


#if defined(TF_FEATURE_CPU_SSE)
#include "Internal/TF_Simd3x32_sse.inl"
#elif defined(TF_FEATURE_CPU_NEON)
#include "Internal/TF_Simd3x32_neon.inl"
#else
#include "Internal/TF_Simd3x32_scalar.inl"
#endif

#endif
