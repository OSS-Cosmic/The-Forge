/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */
#include "TF_TestMain.h"
#include "utest.h"

#include "Forge/Math/TF_Simd2.h"
#include "TF_MathUtils.h"


UTEST(TF_Simd2, tfSimd2iCmpGt)
{
  struct {
    TSimdInt2 a;
    TSimdInt2 b;
    TSimdInt2 test;
  } tests[] = {
      // ... existing test cases ...
      // Edge cases:
      {tfSimd2iLoadImmediate(INT32_MIN, INT32_MIN), tfSimd2iLoadImmediate(INT32_MAX, INT32_MAX), tfSimd2iLoadImmediate(TF_SIMD_FALSE, TF_SIMD_FALSE)},
      {tfSimd2iLoadImmediate(INT32_MAX, INT32_MAX), tfSimd2iLoadImmediate(INT32_MIN, INT32_MIN), tfSimd2iLoadImmediate(TF_SIMD_TRUE, TF_SIMD_TRUE)},
      // Mixed values:
      {tfSimd2iLoadImmediate(0, -1), tfSimd2iLoadImmediate(1, 0), tfSimd2iLoadImmediate(TF_SIMD_FALSE, TF_SIMD_FALSE)},
      // All elements equal:
      {tfSimd2iLoadImmediate(42, 42), tfSimd2iLoadImmediate(42, 42), tfSimd2iLoadImmediate(TF_SIMD_FALSE, TF_SIMD_FALSE)},
      // Different element types:
      {tfSimd2iLoadImmediate(0, 1), tfSimd2iLoadImmediate(3, 2), tfSimd2iLoadImmediate(TF_SIMD_FALSE, TF_SIMD_FALSE)},
  };
  for(size_t i = 0; i < TF_ARRAY_COUNT(tests); i++) {
    EXPECT_TRUE(tfSimd2iCmpAllEq(tfSimd2iCmpGt(tests[i].a, tests[i].b), tests[i].test));
  }
}

UTEST(TF_Simd2, tfSimd2iCmpLt)
{
  struct {
    TSimdInt2 a;
    TSimdInt2 b;
    TSimdInt2 test;
  } tests[] = {
      // Less than
      {tfSimd2iLoadImmediate(12, 13), tfSimd2iLoadImmediate(16, 17), tfSimd2iLoadImmediate(TF_SIMD_TRUE, TF_SIMD_TRUE)},
      // Mixed less than and equal
      {tfSimd2iLoadImmediate(125, -12), tfSimd2iLoadImmediate(125, 13), tfSimd2iLoadImmediate(TF_SIMD_FALSE, TF_SIMD_TRUE)},
      // All elements greater than or equal
      {tfSimd2iLoadImmediate(1, 2), tfSimd2iLoadImmediate(-1, 0), tfSimd2iLoadImmediate(TF_SIMD_FALSE, TF_SIMD_FALSE)},
      // Edge cases:
      {tfSimd2iLoadImmediate(INT32_MIN, INT32_MIN), tfSimd2iLoadImmediate(INT32_MAX, INT32_MAX), tfSimd2iLoadImmediate(TF_SIMD_TRUE, TF_SIMD_TRUE)},
      {tfSimd2iLoadImmediate(INT32_MAX, INT32_MAX), tfSimd2iLoadImmediate(INT32_MIN, INT32_MIN), tfSimd2iLoadImmediate(TF_SIMD_FALSE, TF_SIMD_FALSE)},
  };
  for(size_t i = 0; i < TF_ARRAY_COUNT(tests); i++) {
    EXPECT_TRUE(tfSimd2iCmpAllEq(tfSimd2iCmpLt(tests[i].a, tests[i].b), tests[i].test));
  }
}



UTEST(TF_Simd2, tfSimd2iCmpEq)
{
  struct {
    TSimdInt2 a;
    TSimdInt2 b;
    TSimdInt2 test;
  } tests[] = {
       // Equal elements
      {tfSimd2iLoadImmediate(12, 13), tfSimd2iLoadImmediate(12, 13), tfSimd2iLoadImmediate(TF_SIMD_TRUE, TF_SIMD_TRUE)},
      // Mixed equal and unequal elements
      {tfSimd2iLoadImmediate(125, -12), tfSimd2iLoadImmediate(125, -12), tfSimd2iLoadImmediate(TF_SIMD_TRUE, TF_SIMD_TRUE)},
      // All elements unequal
      {tfSimd2iLoadImmediate(1, 2), tfSimd2iLoadImmediate(5, 6), tfSimd2iLoadImmediate(TF_SIMD_FALSE, TF_SIMD_FALSE)},
      // Edge cases:
      {tfSimd2iLoadImmediate(INT32_MIN, INT32_MIN), tfSimd2iLoadImmediate(INT32_MIN, INT32_MIN), tfSimd2iLoadImmediate(TF_SIMD_TRUE, TF_SIMD_TRUE)},
      {tfSimd2iLoadImmediate(INT32_MAX, INT32_MAX), tfSimd2iLoadImmediate(INT32_MAX, INT32_MAX), tfSimd2iLoadImmediate(TF_SIMD_TRUE, TF_SIMD_TRUE)},
  };
  for (size_t i = 0; i < TF_ARRAY_COUNT(tests); i++)
  {
      EXPECT_TRUE(tfSimd2iCmpAllEq(tfSimd2iCmpEq(tests[i].a, tests[i].b), tests[i].test));
  }
}

UTEST(TF_Simd2, tfSimd2fZero)
{
    TSimdFloat2 value = tfSimd2fZero();
    EXPECT_NEAR(tfSimd2fSelectIndex0(value), 0.0f, DEFAULT_EPSILON);
    EXPECT_NEAR(tfSimd2fSelectIndex1(value), 0.0f, DEFAULT_EPSILON);
}

UTEST(TF_Simd2, tfSimd2fSplat)
{
    TSimdFloat2 value = tfSimd2fSplat(23.f);
    EXPECT_NEAR(tfSimd2fSelectIndex0(value), 23.f, DEFAULT_EPSILON);
    EXPECT_NEAR(tfSimd2fSelectIndex1(value), 23.f, DEFAULT_EPSILON);
    TSimdFloat2 value1 = tfSimd2fSplat(5.1f);
    EXPECT_NEAR(tfSimd2fSelectIndex0(value1), 5.1f, DEFAULT_EPSILON);
    EXPECT_NEAR(tfSimd2fSelectIndex1(value1), 5.1f, DEFAULT_EPSILON);

    TSimdFloat2 value2 = tfSimd2fLoadImmediate(5.1f, 1.0f);
    EXPECT_NEAR(tfSimd2fSelectIndex0(value2), 5.1f, DEFAULT_EPSILON);
    EXPECT_NEAR(tfSimd2fSelectIndex1(value2), 1.0f, DEFAULT_EPSILON);
}

UTEST(TF_Simd2, tfSimd3iNot) {
  struct {
    TSimdInt2 test;
    TSimdInt2 expect;
  } tests[] = {
       {tfSimd2iLoadImmediate(0xFFFFFFFF, 0x0000FFFF), tfSimd2iLoadImmediate(0, 0xFFFF0000)},
  };   
  for (size_t i = 0; i < TF_ARRAY_COUNT(tests); i++)
  {
      EXPECT_TRUE(tfSimd2iCmpAllEq(tfSimd2iNot(tests[i].test), tests[i].expect));
  }
}

UTEST(TF_Simd2, tfSimd2iSelect) {
  struct {
    TSimdInt2 a;
    TSimdInt2 b;
    TSimdInt2 mask;
    TSimdInt2 expect;
  } tests[] = {
       {tfSimd2iLoadImmediate(10, 11), tfSimd2iLoadImmediate(123, -149), tfSimd2iLoadImmediate(0,0), tfSimd2iLoadImmediate(10, 11)},
       {tfSimd2iLoadImmediate(10, 11), tfSimd2iLoadImmediate(123, -149), tfSimd2iLoadImmediate(TF_SIMD_TRUE,0), tfSimd2iLoadImmediate(123, 11)},
       {tfSimd2iLoadImmediate(10, 11), tfSimd2iLoadImmediate(123, -149), tfSimd2iLoadImmediate(TF_SIMD_TRUE,0), tfSimd2iLoadImmediate(123, 11)},
       {tfSimd2iLoadImmediate(10, 11), tfSimd2iLoadImmediate(123, -149), tfSimd2iLoadImmediate(TF_SIMD_TRUE,TF_SIMD_TRUE), tfSimd2iLoadImmediate(123, -149)},
  };   
  for (size_t i = 0; i < TF_ARRAY_COUNT(tests); i++)
  {
      EXPECT_TRUE(tfSimd2iCmpAllEq(tfSimd2iSelect(tests[i].a, tests[i].b, tests[i].mask), tests[i].expect));
  }
}

//UTEST(TF_Simd2, tfSimd3fSelect) {
//  struct {
//    TSimdFloat4 a;
//    TSimdFloat4 b;
//    TSimdFloat4 mask;
//    TSimdFloat4 expect;
//  } tests[] = {
//       {tfSimd3fLoadImmediate(10, 11, -13, 32), tfSimd3fLoadImmediate(123, -149, 0, 12), tfSimd3fLoadImmediate(0,0,0,0), tfSimd3fLoadImmediate(10, 11, -13, 32)},
//       {tfSimd3fLoadImmediate(10, 11, -13, 32), tfSimd3fLoadImmediate(123, -149, 0, 12), tfSimd3fLoadImmediate(TF_SIMD_TRUE,0,0,0), tfSimd3fLoadImmediate(123, 11, -13, 32)},
//       {tfSimd3fLoadImmediate(10, 11, -13, 32), tfSimd3fLoadImmediate(123, -149, 0, 12), tfSimd3fLoadImmediate(TF_SIMD_TRUE,0,TF_SIMD_TRUE,0), tfSimd3fLoadImmediate(123, 11, 0, 32)},
//       {tfSimd3fLoadImmediate(10, 11, -13, 32), tfSimd3fLoadImmediate(123, -149, 0, 12), tfSimd3fLoadImmediate(TF_SIMD_TRUE,TF_SIMD_TRUE,TF_SIMD_TRUE,TF_SIMD_TRUE), tfSimd3fLoadImmediate(123, -149, 0, 12)},
//  };   
//  for (size_t i = 0; i < TF_ARRAY_COUNT(tests); i++)
//  {
//      //EXPECT_TRUE(tfSimd3fCmp(tfSimd2iSelect(tests[i].a, tests[i].b, tests[i].mask), tests[i].expect));
//  }
//}


#include "Forge/Mem/TF_Memory.h"
#include "Forge/TF_FileSystem.h"
#include "Forge/TF_Log.h"
UTEST_STATE();
TF_UTEST_MAIN("TF_TF_Simd2")


