/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */
#include "TF_TestMain.h"
#include "utest.h"

#include "Forge/Math/TF_Simd3x32.h"
#include "TF_MathUtils.h"


UTEST(TF_Simd3, tfSimd3iCmpGt)
{
  struct {
    TSimdInt32x3 a;
    TSimdInt32x3 b;
    TSimdInt32x3 test;
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

UTEST(TF_Simd3, tfSimd3iCmpLt)
{
  struct {
    TSimdInt32x3 a;
    TSimdInt32x3 b;
    TSimdInt32x3 test;
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



UTEST(TF_Simd3, tfSimd3iCmpEq)
{
  struct {
    TSimdInt32x3 a;
    TSimdInt32x3 b;
    TSimdInt32x3 test;
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

UTEST(TF_Simd3, tfSimd3fZero)
{
    TSimdFloat32x3 value = tfSimd3fZero();
    EXPECT_NEAR(tfSimd3fSelectIndex0(value), 0.0f, DEFAULT_EPSILON);
    EXPECT_NEAR(tfSimd3fSelectIndex1(value), 0.0f, DEFAULT_EPSILON);
    EXPECT_NEAR(tfSimd3fSelectIndex2(value), 0.0f, DEFAULT_EPSILON);
}

UTEST(TF_Simd3, tfSimdSplat4f)
{
    TSimdFloat32x3 value = tfSimd3fSplat(23.f);
    EXPECT_NEAR(tfSimd3fSelectIndex0(value), 23.f, DEFAULT_EPSILON);
    EXPECT_NEAR(tfSimd3fSelectIndex1(value), 23.f, DEFAULT_EPSILON);
    EXPECT_NEAR(tfSimd3fSelectIndex2(value), 23.f, DEFAULT_EPSILON);
    TSimdFloat32x3 value1 = tfSimd3fSplat(5.1f);
    EXPECT_NEAR(tfSimd3fSelectIndex0(value1), 5.1f, DEFAULT_EPSILON);
    EXPECT_NEAR(tfSimd3fSelectIndex1(value1), 5.1f, DEFAULT_EPSILON);
    EXPECT_NEAR(tfSimd3fSelectIndex2(value1), 5.1f, DEFAULT_EPSILON);

    TSimdFloat32x3 value2 = tfSimd3fLoadImmediate(5.1f, 1.0f, 2.0f);
    EXPECT_NEAR(tfSimd3fSelectIndex0(value2), 5.1f, DEFAULT_EPSILON);
    EXPECT_NEAR(tfSimd3fSelectIndex1(value2), 1.0f, DEFAULT_EPSILON);
    EXPECT_NEAR(tfSimd3fSelectIndex2(value2), 2.0f, DEFAULT_EPSILON);
}

UTEST(TF_Simd3, tfSimd3iNot) {
  struct {
    TSimdInt32x3 test;
    TSimdInt32x3 expect;
  } tests[] = {
       {tfSimd3iLoadImmediate(0xFFFFFFFF, 0x0000FFFF, 0xFFFF0000), tfSimd3iLoadImmediate(0, 0xFFFF0000, 0x0000FFFF)},
  };   
  for (size_t i = 0; i < TF_ARRAY_COUNT(tests); i++)
  {
      EXPECT_TRUE(tfSimd3iCmpAllEq(tfSimd3iNot(tests[i].test), tests[i].expect));
  }
}

UTEST(TF_Simd3, tfSimd3iSelect) {
  struct {
    TSimdInt32x3 a;
    TSimdInt32x3 b;
    TSimdInt32x3 mask;
    TSimdInt32x3 expect;
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

//UTEST(TF_Simd3, tfSimd3fSelect) {
//  struct {
//    TSimdFloat32x3 a;
//    TSimdFloat32x3 b;
//    TSimdFloat32x3 mask;
//    TSimdFloat32x3 expect;
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
TF_UTEST_MAIN("TF_Simd3")

