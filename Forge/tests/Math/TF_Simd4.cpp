/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#include "TF_TestMain.h"
#include "utest.h"

#include "Forge/Math/TF_SimdMath4.h"
#include "TF_MathUtils.h"



UTEST(Vector4, tfSimd4fReplaceIndex0Simd4) {
  Simd_FloatType4 value0 = tfSimd4fLoadImmediate(5.1f, 1.0f, 2.0f, 3.0f);
  Simd_FloatType4 value1 = tfSimd4fLoadImmediate(1.f, 2.f, 3.f, 4.0f);
  Simd_FloatType4 value2 = tfSimd4fReplaceIndex0Simd4(value0, value1);
  EXPECT_NEAR(tfSimd4fSelectIndex0(value2), 1.0f, DEFAULT_EPSILON );
  EXPECT_NEAR(tfSimd4fSelectIndex1(value2), 1.0f, DEFAULT_EPSILON );
  EXPECT_NEAR(tfSimd4fSelectIndex2(value2), 2.0f, DEFAULT_EPSILON );
  EXPECT_NEAR(tfSimd4fSelectIndex3(value2), 3.0f, DEFAULT_EPSILON );
}

UTEST(Vector4, tfSimd4fReplaceIndex1Simd4) {
  Simd_FloatType4 value0 = tfSimd4fLoadImmediate(5.1f, 1.0f, 2.0f, 3.0f);
  Simd_FloatType4 value1 = tfSimd4fLoadImmediate(1.f, 2.f, 3.f, 4.0f);
  Simd_FloatType4 value2 = tfSimd4fReplaceIndex1Simd4(value0, value1);
  EXPECT_NEAR(tfSimd4fSelectIndex0(value2), 5.1f, DEFAULT_EPSILON );
  EXPECT_NEAR(tfSimd4fSelectIndex1(value2), 2.0f, DEFAULT_EPSILON );
  EXPECT_NEAR(tfSimd4fSelectIndex2(value2), 2.0f, DEFAULT_EPSILON );
  EXPECT_NEAR(tfSimd4fSelectIndex3(value2), 3.0f, DEFAULT_EPSILON );
}

UTEST(Vector4, tfSimd4fReplaceIndex2Simd4) {
  Simd_FloatType4 value0 = tfSimd4fLoadImmediate(5.1f, 1.0f, 32.0f, 3.0f);
  Simd_FloatType4 value1 = tfSimd4fLoadImmediate(1.f, 2.f, 6.f, 4.0f);
  Simd_FloatType4 value2 = tfSimd4fReplaceIndex2Simd4(value0, value1);
  EXPECT_NEAR(tfSimd4fSelectIndex0(value2), 5.1f, DEFAULT_EPSILON );
  EXPECT_NEAR(tfSimd4fSelectIndex1(value2), 1.0f, DEFAULT_EPSILON );
  EXPECT_NEAR(tfSimd4fSelectIndex2(value2), 6.0f, DEFAULT_EPSILON );
  EXPECT_NEAR(tfSimd4fSelectIndex3(value2), 3.0f, DEFAULT_EPSILON );
}

UTEST(Vector4, tfSimd4fReplaceIndex3Simd4) {
  Simd_FloatType4 value0 = tfSimd4fLoadImmediate(5.1f, 1.0f, 32.0f, 3.0f);
  Simd_FloatType4 value1 = tfSimd4fLoadImmediate(1.f, 2.f, 6.f, 4.0f);
  Simd_FloatType4 value2 = tfSimd4fReplaceIndex3Simd4(value0, value1);
  EXPECT_NEAR(tfSimd4fSelectIndex0(value2), 5.1f, DEFAULT_EPSILON );
  EXPECT_NEAR(tfSimd4fSelectIndex1(value2), 1.0f, DEFAULT_EPSILON );
  EXPECT_NEAR(tfSimd4fSelectIndex2(value2), 32.0f, DEFAULT_EPSILON );
  EXPECT_NEAR(tfSimd4fSelectIndex3(value2), 4.0f, DEFAULT_EPSILON );
}


UTEST(Vector4, tfSimdSplat4f)
{
  Simd_FloatType4 value = tfSimd4fSplat(23.f);
  EXPECT_NEAR(tfSimd4fSelectIndex0(value), 23.f, DEFAULT_EPSILON );
  EXPECT_NEAR(tfSimd4fSelectIndex1(value), 23.f, DEFAULT_EPSILON );
  EXPECT_NEAR(tfSimd4fSelectIndex2(value), 23.f, DEFAULT_EPSILON );
  EXPECT_NEAR(tfSimd4fSelectIndex3(value), 23.f, DEFAULT_EPSILON );
  Simd_FloatType4 value1 = tfSimd4fSplat(5.1f);
  EXPECT_NEAR(tfSimd4fSelectIndex0(value1), 5.1f, DEFAULT_EPSILON );
  EXPECT_NEAR(tfSimd4fSelectIndex1(value1), 5.1f, DEFAULT_EPSILON );
  EXPECT_NEAR(tfSimd4fSelectIndex2(value1), 5.1f, DEFAULT_EPSILON );
  EXPECT_NEAR(tfSimd4fSelectIndex3(value1), 5.1f, DEFAULT_EPSILON );
  
  Simd_FloatType4 value2 = tfSimd4fLoadImmediate(5.1f, 1.0f, 2.0f, 3.0f);
  EXPECT_NEAR(tfSimd4fSelectIndex0(value2), 5.1f, DEFAULT_EPSILON );
  EXPECT_NEAR(tfSimd4fSelectIndex1(value2), 1.0f, DEFAULT_EPSILON );
  EXPECT_NEAR(tfSimd4fSelectIndex2(value2), 2.0f, DEFAULT_EPSILON );
  EXPECT_NEAR(tfSimd4fSelectIndex3(value2), 3.0f, DEFAULT_EPSILON );
}


#include "Forge/TF_FileSystem.h"
#include "Forge/Mem/TF_Memory.h"
#include "Forge/TF_Log.h"
UTEST_STATE();
TF_UTEST_MAIN("TF_Vector4")



