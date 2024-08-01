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

static inline TSimdFloat32x4 tfSimdFloat2To4Splat0(TSimdFloat32x2 value); 
static inline TSimdFloat32x4 tfSimdFloat2To4Splat1(TSimdFloat32x2 value); 

inline TSimdFloat32x2 tfSimd2fSelect(TSimdFloat32x2 arg0, TSimdFloat32x2 arg1, TSimdFloat32x2 mask);
inline TSimdInt32x2 tfSimd2iSelect(TSimdInt32x2 arg0, TSimdInt32x2 arg1, TSimdInt32x2 mask);

inline float tfSimd2fSelectIndex0(TSimdFloat32x2 value);
inline float tfSimd2fSelectIndex1(TSimdFloat32x2 value);

inline TSimdFloat32x2 tfSimdFloat2x32Load(float x, float y);
inline TSimdInt32x2   tfSimdInt2x32Load(int32_t x, int32_t y);

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

static inline bool tfSimdFloat32x2CmpAllLt(TSimdFloat32x2 a, TSimdFloat32x2 b);

#if defined(TF_FEATURE_CPU_SSE)
#include "Internal/TF_Simd32x2_sse.inl"
#elif defined(TF_FEATURE_CPU_NEON)
#include "Internal/TF_Simd32x2_neon.inl"
#else
#include "Internal/TF_Simd32x2_scalar.inl"
#endif


#endif
