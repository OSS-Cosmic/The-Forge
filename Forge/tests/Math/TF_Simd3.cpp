/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */
#include "TF_TestMain.h"
#include "utest.h"

#include "Forge/Math/Internal/Types.h"
#include "Forge/Math/TF_SimdMath3.h"
#include "TF_MathUtils.h"


UTEST(Vector4, tfSimd3iCmpGt)
{
  struct {
    Simd_Int32Type3 a;
    Simd_Int32Type3 b;
    Simd_Int32Type3 test;
  } tests[] = {
      // ... existing test cases ...
      // Edge cases:
      {tfSimd3iLoadImmediate(INT32_MIN, INT32_MIN, INT32_MIN), tfSimd3iLoadImmediate(INT32_MAX, INT32_MAX, INT32_MAX), tfSimd3iLoadImmediate(TF_SIMD_FALSE, TF_SIMD_FALSE, TF_SIMD_FALSE)},
      {tfSimd3iLoadImmediate(INT32_MAX, INT32_MAX, INT32_MAX), tfSimd3iLoadImmediate(INT32_MIN, INT32_MIN, INT32_MIN), tfSimd3iLoadImmediate(TF_SIMD_TRUE, TF_SIMD_TRUE, TF_SIMD_TRUE)},
      // Mixed values:
      {tfSimd3iLoadImmediate(0, -1, 1), tfSimd3iLoadImmediate(1, 0, -1), tfSimd3iLoadImmediate(TF_SIMD_FALSE, TF_SIMD_FALSE, TF_SIMD_TRUE)},
      // All elements equal:
      {tfSimd3iLoadImmediate(42, 42, 42), tfSimd3iLoadImmediate(42, 42, 42), tfSimd3iLoadImmediate(TF_SIMD_FALSE, TF_SIMD_FALSE, TF_SIMD_FALSE)},
      // Different element types:
      {tfSimd3iLoadImmediate(0, 1, 2), tfSimd3iLoadImmediate(3, 2, 1), tfSimd3iLoadImmediate(TF_SIMD_FALSE, TF_SIMD_FALSE, TF_SIMD_TRUE)},
  };
  for(size_t i = 0; i < TF_ARRAY_COUNT(tests); i++) {
    EXPECT_TRUE(tfSimd3iCmpAllEq(tfSimd3iCmpGt(tests[i].a, tests[i].b), tests[i].test));
  }
}

UTEST(Vector4, tfSimd3iCmpLt)
{
  struct {
    Simd_Int32Type3 a;
    Simd_Int32Type3 b;
    Simd_Int32Type3 test;
  } tests[] = {
      // Less than
      {tfSimd3iLoadImmediate(12, 13, 14), tfSimd3iLoadImmediate(16, 17, 18), tfSimd3iLoadImmediate(TF_SIMD_TRUE, TF_SIMD_TRUE, TF_SIMD_TRUE)},
      // Mixed less than and equal
      {tfSimd3iLoadImmediate(125, -12, 153), tfSimd3iLoadImmediate(125, 13, 153), tfSimd3iLoadImmediate(TF_SIMD_FALSE, TF_SIMD_TRUE, TF_SIMD_FALSE)},
      // All elements greater than or equal
      {tfSimd3iLoadImmediate(1, 2, 3), tfSimd3iLoadImmediate(-1, 0, 1), tfSimd3iLoadImmediate(TF_SIMD_FALSE, TF_SIMD_FALSE, TF_SIMD_FALSE)},
      // Edge cases:
      {tfSimd3iLoadImmediate(INT32_MIN, INT32_MIN, INT32_MIN), tfSimd3iLoadImmediate(INT32_MAX, INT32_MAX, INT32_MAX), tfSimd3iLoadImmediate(TF_SIMD_TRUE, TF_SIMD_TRUE, TF_SIMD_TRUE)},
      {tfSimd3iLoadImmediate(INT32_MAX, INT32_MAX, INT32_MAX), tfSimd3iLoadImmediate(INT32_MIN, INT32_MIN, INT32_MIN), tfSimd3iLoadImmediate(TF_SIMD_FALSE, TF_SIMD_FALSE, TF_SIMD_FALSE)},
  };
  for(size_t i = 0; i < TF_ARRAY_COUNT(tests); i++) {
    EXPECT_TRUE(tfSimd3iCmpAllEq(tfSimd3iCmpLt(tests[i].a, tests[i].b), tests[i].test));
  }
}



UTEST(Vector4, tfSimd3iCmpEq)
{
  struct {
    Simd_Int32Type3 a;
    Simd_Int32Type3 b;
    Simd_Int32Type3 test;
  } tests[] = {
       // Equal elements
      {tfSimd3iLoadImmediate(12, 13, 14), tfSimd3iLoadImmediate(12, 13, 14), tfSimd3iLoadImmediate(TF_SIMD_TRUE, TF_SIMD_TRUE, TF_SIMD_TRUE)},
      // Mixed equal and unequal elements
      {tfSimd3iLoadImmediate(125, -12, 153), tfSimd3iLoadImmediate(125, -12, 14), tfSimd3iLoadImmediate(TF_SIMD_TRUE, TF_SIMD_TRUE, TF_SIMD_FALSE)},
      // All elements unequal
      {tfSimd3iLoadImmediate(1, 2, 3), tfSimd3iLoadImmediate(5, 6, 7), tfSimd3iLoadImmediate(TF_SIMD_FALSE, TF_SIMD_FALSE, TF_SIMD_FALSE)},
      // Edge cases:
      {tfSimd3iLoadImmediate(INT32_MIN, INT32_MIN, INT32_MIN), tfSimd3iLoadImmediate(INT32_MIN, INT32_MIN, INT32_MIN), tfSimd3iLoadImmediate(TF_SIMD_TRUE, TF_SIMD_TRUE, TF_SIMD_TRUE)},
      {tfSimd3iLoadImmediate(INT32_MAX, INT32_MAX, INT32_MAX), tfSimd3iLoadImmediate(INT32_MAX, INT32_MAX, INT32_MAX), tfSimd3iLoadImmediate(TF_SIMD_TRUE, TF_SIMD_TRUE, TF_SIMD_TRUE)},
  };
  for (size_t i = 0; i < TF_ARRAY_COUNT(tests); i++)
  {
      EXPECT_TRUE(tfSimd3iCmpAllEq(tfSimd3iCmpEq(tests[i].a, tests[i].b), tests[i].test));
  }
}

UTEST(Vector4, tfSimd3fZero)
{
    Simd_FloatType3 value = tfSimd3fZero();
    EXPECT_NEAR(tfSimd3fSelectIndex0(value), 0.0f, DEFAULT_EPSILON);
    EXPECT_NEAR(tfSimd3fSelectIndex1(value), 0.0f, DEFAULT_EPSILON);
    EXPECT_NEAR(tfSimd3fSelectIndex2(value), 0.0f, DEFAULT_EPSILON);
}

UTEST(Vector4, tfSimdSplat4f)
{
    Simd_FloatType3 value = tfSimd3fSplat(23.f);
    EXPECT_NEAR(tfSimd3fSelectIndex0(value), 23.f, DEFAULT_EPSILON);
    EXPECT_NEAR(tfSimd3fSelectIndex1(value), 23.f, DEFAULT_EPSILON);
    EXPECT_NEAR(tfSimd3fSelectIndex2(value), 23.f, DEFAULT_EPSILON);
    Simd_FloatType3 value1 = tfSimd3fSplat(5.1f);
    EXPECT_NEAR(tfSimd3fSelectIndex0(value1), 5.1f, DEFAULT_EPSILON);
    EXPECT_NEAR(tfSimd3fSelectIndex1(value1), 5.1f, DEFAULT_EPSILON);
    EXPECT_NEAR(tfSimd3fSelectIndex2(value1), 5.1f, DEFAULT_EPSILON);

    Simd_FloatType3 value2 = tfSimd3fLoadImmediate(5.1f, 1.0f, 2.0f);
    EXPECT_NEAR(tfSimd3fSelectIndex0(value2), 5.1f, DEFAULT_EPSILON);
    EXPECT_NEAR(tfSimd3fSelectIndex1(value2), 1.0f, DEFAULT_EPSILON);
    EXPECT_NEAR(tfSimd3fSelectIndex2(value2), 2.0f, DEFAULT_EPSILON);
}

UTEST(Vector4, tfSimd3iNot) {
  struct {
    Simd_Int32Type3 test;
    Simd_Int32Type3 expect;
  } tests[] = {
       {tfSimd3iLoadImmediate(0xFFFFFFFF, 0x0000FFFF, 0xFFFF0000), tfSimd3iLoadImmediate(0, 0xFFFF0000, 0x0000FFFF)},
  };   
  for (size_t i = 0; i < TF_ARRAY_COUNT(tests); i++)
  {
      EXPECT_TRUE(tfSimd3iCmpAllEq(tfSimd3iNot(tests[i].test), tests[i].expect));
  }
}

UTEST(Vector4, tfSimd3iSelect) {
  struct {
    Simd_Int32Type3 a;
    Simd_Int32Type3 b;
    Simd_Int32Type3 mask;
    Simd_Int32Type3 expect;
  } tests[] = {
       {tfSimd3iLoadImmediate(10, 11, -13), tfSimd3iLoadImmediate(123, -149, 0), tfSimd3iLoadImmediate(0,0,0), tfSimd3iLoadImmediate(10, 11, -13)},
       {tfSimd3iLoadImmediate(10, 11, -13), tfSimd3iLoadImmediate(123, -149, 0), tfSimd3iLoadImmediate(TF_SIMD_TRUE,0,0), tfSimd3iLoadImmediate(123, 11, -13)},
       {tfSimd3iLoadImmediate(10, 11, -13), tfSimd3iLoadImmediate(123, -149, 0), tfSimd3iLoadImmediate(TF_SIMD_TRUE,0,TF_SIMD_TRUE), tfSimd3iLoadImmediate(123, 11, 0)},
       {tfSimd3iLoadImmediate(10, 11, -13), tfSimd3iLoadImmediate(123, -149, 0), tfSimd3iLoadImmediate(TF_SIMD_TRUE,TF_SIMD_TRUE,TF_SIMD_TRUE), tfSimd3iLoadImmediate(123, -149, 0)},
  };   
  for (size_t i = 0; i < TF_ARRAY_COUNT(tests); i++)
  {
      EXPECT_TRUE(tfSimd3iCmpAllEq(tfSimd3iSelect(tests[i].a, tests[i].b, tests[i].mask), tests[i].expect));
  }
}

//UTEST(Vector4, tfSimd3fSelect) {
//  struct {
//    Simd_FloatType4 a;
//    Simd_FloatType4 b;
//    Simd_FloatType4 mask;
//    Simd_FloatType4 expect;
//  } tests[] = {
//       {tfSimd3fLoadImmediate(10, 11, -13, 32), tfSimd3fLoadImmediate(123, -149, 0, 12), tfSimd3fLoadImmediate(0,0,0,0), tfSimd3fLoadImmediate(10, 11, -13, 32)},
//       {tfSimd3fLoadImmediate(10, 11, -13, 32), tfSimd3fLoadImmediate(123, -149, 0, 12), tfSimd3fLoadImmediate(TF_SIMD_TRUE,0,0,0), tfSimd3fLoadImmediate(123, 11, -13, 32)},
//       {tfSimd3fLoadImmediate(10, 11, -13, 32), tfSimd3fLoadImmediate(123, -149, 0, 12), tfSimd3fLoadImmediate(TF_SIMD_TRUE,0,TF_SIMD_TRUE,0), tfSimd3fLoadImmediate(123, 11, 0, 32)},
//       {tfSimd3fLoadImmediate(10, 11, -13, 32), tfSimd3fLoadImmediate(123, -149, 0, 12), tfSimd3fLoadImmediate(TF_SIMD_TRUE,TF_SIMD_TRUE,TF_SIMD_TRUE,TF_SIMD_TRUE), tfSimd3fLoadImmediate(123, -149, 0, 12)},
//  };   
//  for (size_t i = 0; i < TF_ARRAY_COUNT(tests); i++)
//  {
//      //EXPECT_TRUE(tfSimd3fCmp(tfSimd3iSelect(tests[i].a, tests[i].b, tests[i].mask), tests[i].expect));
//  }
//}


#include "Forge/Mem/TF_Memory.h"
#include "Forge/TF_FileSystem.h"
#include "Forge/TF_Log.h"
UTEST_STATE();
TF_UTEST_MAIN("TF_Vector4")

