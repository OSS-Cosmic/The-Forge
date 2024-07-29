/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */
#include "TF_TestMain.h"
#include "utest.h"

#include "Forge/Math/TF_Simd4x32.h"
#include "TF_MathUtils.h"


UTEST(TF_Simd4, tfSimd4iCmpGt)
{
  struct {
    TSimdInt4 a;
    TSimdInt4 b;
    TSimdInt4 test;
  } tests[] = {
      // ... existing test cases ...
      // Edge cases:
      {tfSimdInt4Load(INT32_MIN, INT32_MIN, INT32_MIN, INT32_MIN), tfSimdInt4Load(INT32_MAX, INT32_MAX, INT32_MAX, INT32_MAX), tfSimdInt4Load(TF_SIMD_FALSE, TF_SIMD_FALSE, TF_SIMD_FALSE, TF_SIMD_FALSE)},
      {tfSimdInt4Load(INT32_MAX, INT32_MAX, INT32_MAX, INT32_MAX), tfSimdInt4Load(INT32_MIN, INT32_MIN, INT32_MIN, INT32_MIN), tfSimdInt4Load(TF_SIMD_TRUE, TF_SIMD_TRUE, TF_SIMD_TRUE, TF_SIMD_TRUE)},
      // Mixed values:
      {tfSimdInt4Load(0, -1, 1, 0), tfSimdInt4Load(1, 0, -1, 0), tfSimdInt4Load(TF_SIMD_FALSE, TF_SIMD_FALSE, TF_SIMD_TRUE, TF_SIMD_FALSE)},
      // All elements equal:
      {tfSimdInt4Load(42, 42, 42, 42), tfSimdInt4Load(42, 42, 42, 42), tfSimdInt4Load(TF_SIMD_FALSE, TF_SIMD_FALSE, TF_SIMD_FALSE, TF_SIMD_FALSE)},
      // Different element types:
      {tfSimdInt4Load(0, 1, 2, 3), tfSimdInt4Load(3, 2, 1, 0), tfSimdInt4Load(TF_SIMD_FALSE, TF_SIMD_FALSE, TF_SIMD_TRUE, TF_SIMD_TRUE)},
  };
  for(size_t i = 0; i < TF_ARRAY_COUNT(tests); i++) {
    EXPECT_TRUE(tfSimd4iCmpAllEq(tfSimd4iCmpGt(tests[i].a, tests[i].b), tests[i].test));
  }
}

UTEST(TF_Simd4, tfSimd4iCmpLt)
{
  struct {
    TSimdInt4 a;
    TSimdInt4 b;
    TSimdInt4 test;
  } tests[] = {
      // Less than
      {tfSimdInt4Load(12, 13, 14, 15), tfSimdInt4Load(16, 17, 18, 19), tfSimdInt4Load(TF_SIMD_TRUE, TF_SIMD_TRUE, TF_SIMD_TRUE, TF_SIMD_TRUE)},
      // Mixed less than and equal
      {tfSimdInt4Load(125, -12, 153, 221), tfSimdInt4Load(125, 13, 153, 222), tfSimdInt4Load(TF_SIMD_FALSE, TF_SIMD_TRUE, TF_SIMD_FALSE, TF_SIMD_TRUE)},
      // All elements greater than or equal
      {tfSimdInt4Load(1, 2, 3, 4), tfSimdInt4Load(-1, 0, 1, 2), tfSimdInt4Load(TF_SIMD_FALSE, TF_SIMD_FALSE, TF_SIMD_FALSE, TF_SIMD_FALSE)},
      // Edge cases:
      {tfSimdInt4Load(INT32_MIN, INT32_MIN, INT32_MIN, INT32_MIN), tfSimdInt4Load(INT32_MAX, INT32_MAX, INT32_MAX, INT32_MAX), tfSimdInt4Load(TF_SIMD_TRUE, TF_SIMD_TRUE, TF_SIMD_TRUE, TF_SIMD_TRUE)},
      {tfSimdInt4Load(INT32_MAX, INT32_MAX, INT32_MAX, INT32_MAX), tfSimdInt4Load(INT32_MIN, INT32_MIN, INT32_MIN, INT32_MIN), tfSimdInt4Load(TF_SIMD_FALSE, TF_SIMD_FALSE, TF_SIMD_FALSE, TF_SIMD_FALSE)},
  };
  for(size_t i = 0; i < TF_ARRAY_COUNT(tests); i++) {
    EXPECT_TRUE(tfSimd4iCmpAllEq(tfSimd4iCmpLt(tests[i].a, tests[i].b), tests[i].test));
  }
}



UTEST(TF_Simd4, tfSimd4iCmpEq)
{
  struct {
    TSimdInt4 a;
    TSimdInt4 b;
    TSimdInt4 test;
  } tests[] = {
       // Equal elements
      {tfSimdInt4Load(12, 13, 14, 15), tfSimdInt4Load(12, 13, 14, 15), tfSimdInt4Load(TF_SIMD_TRUE, TF_SIMD_TRUE, TF_SIMD_TRUE, TF_SIMD_TRUE)},
      // Mixed equal and unequal elements
      {tfSimdInt4Load(125, -12, 153, 221), tfSimdInt4Load(125, -12, 14, 221), tfSimdInt4Load(TF_SIMD_TRUE, TF_SIMD_TRUE, TF_SIMD_FALSE, TF_SIMD_TRUE)},
      // All elements unequal
      {tfSimdInt4Load(1, 2, 3, 4), tfSimdInt4Load(5, 6, 7, 8), tfSimdInt4Load(TF_SIMD_FALSE, TF_SIMD_FALSE, TF_SIMD_FALSE, TF_SIMD_FALSE)},
      // Edge cases:
      {tfSimdInt4Load(INT32_MIN, INT32_MIN, INT32_MIN, INT32_MIN), tfSimdInt4Load(INT32_MIN, INT32_MIN, INT32_MIN, INT32_MIN), tfSimdInt4Load(TF_SIMD_TRUE, TF_SIMD_TRUE, TF_SIMD_TRUE, TF_SIMD_TRUE)},
      {tfSimdInt4Load(INT32_MAX, INT32_MAX, INT32_MAX, INT32_MAX), tfSimdInt4Load(INT32_MAX, INT32_MAX, INT32_MAX, INT32_MAX), tfSimdInt4Load(TF_SIMD_TRUE, TF_SIMD_TRUE, TF_SIMD_TRUE, TF_SIMD_TRUE)},
  };
  for (size_t i = 0; i < TF_ARRAY_COUNT(tests); i++)
  {
      EXPECT_TRUE(tfSimd4iCmpAllEq(tfSimd4iCmpEq(tests[i].a, tests[i].b), tests[i].test));
  }
}

UTEST(TF_Simd4, tfSimd4fZero)
{
    TSimdFloat4 value = tfSimd4fZero();
    EXPECT_NEAR(tfSimd4fSelectIndex0(value), 0.0f, DEFAULT_EPSILON);
    EXPECT_NEAR(tfSimd4fSelectIndex1(value), 0.0f, DEFAULT_EPSILON);
    EXPECT_NEAR(tfSimd4fSelectIndex2(value), 0.0f, DEFAULT_EPSILON);
    EXPECT_NEAR(tfSimd4fSelectIndex3(value), 0.0f, DEFAULT_EPSILON);
}

UTEST(TF_Simd4, tfSimdSplat4f)
{
    TSimdFloat4 value = tfSimd4fSplat(23.f);
    EXPECT_NEAR(tfSimd4fSelectIndex0(value), 23.f, DEFAULT_EPSILON);
    EXPECT_NEAR(tfSimd4fSelectIndex1(value), 23.f, DEFAULT_EPSILON);
    EXPECT_NEAR(tfSimd4fSelectIndex2(value), 23.f, DEFAULT_EPSILON);
    EXPECT_NEAR(tfSimd4fSelectIndex3(value), 23.f, DEFAULT_EPSILON);
    TSimdFloat4 value1 = tfSimd4fSplat(5.1f);
    EXPECT_NEAR(tfSimd4fSelectIndex0(value1), 5.1f, DEFAULT_EPSILON);
    EXPECT_NEAR(tfSimd4fSelectIndex1(value1), 5.1f, DEFAULT_EPSILON);
    EXPECT_NEAR(tfSimd4fSelectIndex2(value1), 5.1f, DEFAULT_EPSILON);
    EXPECT_NEAR(tfSimd4fSelectIndex3(value1), 5.1f, DEFAULT_EPSILON);

    TSimdFloat4 value2 = tfSimdFloat4Load(5.1f, 1.0f, 2.0f, 3.0f);
    EXPECT_NEAR(tfSimd4fSelectIndex0(value2), 5.1f, DEFAULT_EPSILON);
    EXPECT_NEAR(tfSimd4fSelectIndex1(value2), 1.0f, DEFAULT_EPSILON);
    EXPECT_NEAR(tfSimd4fSelectIndex2(value2), 2.0f, DEFAULT_EPSILON);
    EXPECT_NEAR(tfSimd4fSelectIndex3(value2), 3.0f, DEFAULT_EPSILON);
}

UTEST(TF_Simd4, tfSimd4iNot) {
  struct {
    TSimdInt4 test;
    TSimdInt4 expect;
  } tests[] = {
       {tfSimdInt4Load(0xFFFFFFFF, 0x0000FFFF, 0xFFFF0000, 0x000000FF), tfSimdInt4Load(0, 0xFFFF0000, 0x0000FFFF, 0xFFFFFF00)},
  };   
  for (size_t i = 0; i < TF_ARRAY_COUNT(tests); i++)
  {
      EXPECT_TRUE(tfSimd4iCmpAllEq(tfSimd4iNot(tests[i].test), tests[i].expect));
  }
}

UTEST(TF_Simd4, tfSimd4iSelect) {
  struct {
    TSimdInt4 a;
    TSimdInt4 b;
    TSimdInt4 mask;
    TSimdInt4 expect;
  } tests[] = {
       {tfSimdInt4Load(10, 11, -13, 32), tfSimdInt4Load(123, -149, 0, 12), tfSimdInt4Load(0,0,0,0), tfSimdInt4Load(10, 11, -13, 32)},
       {tfSimdInt4Load(10, 11, -13, 32), tfSimdInt4Load(123, -149, 0, 12), tfSimdInt4Load(TF_SIMD_TRUE,0,0,0), tfSimdInt4Load(123, 11, -13, 32)},
       {tfSimdInt4Load(10, 11, -13, 32), tfSimdInt4Load(123, -149, 0, 12), tfSimdInt4Load(TF_SIMD_TRUE,0,TF_SIMD_TRUE,0), tfSimdInt4Load(123, 11, 0, 32)},
       {tfSimdInt4Load(10, 11, -13, 32), tfSimdInt4Load(123, -149, 0, 12), tfSimdInt4Load(TF_SIMD_TRUE,TF_SIMD_TRUE,TF_SIMD_TRUE,TF_SIMD_TRUE), tfSimdInt4Load(123, -149, 0, 12)},
  };   
  for (size_t i = 0; i < TF_ARRAY_COUNT(tests); i++)
  {
      EXPECT_TRUE(tfSimd4iCmpAllEq(tfSimd4iSelect(tests[i].a, tests[i].b, tests[i].mask), tests[i].expect));
  }
}

//UTEST(TF_Simd4, tfSimd4fSelect) {
//  struct {
//    TSimdFloat4 a;
//    TSimdFloat4 b;
//    TSimdFloat4 mask;
//    TSimdFloat4 expect;
//  } tests[] = {
//       {tfSimdFloat4Load(10, 11, -13, 32), tfSimdFloat4Load(123, -149, 0, 12), tfSimdFloat4Load(0,0,0,0), tfSimdFloat4Load(10, 11, -13, 32)},
//       {tfSimdFloat4Load(10, 11, -13, 32), tfSimdFloat4Load(123, -149, 0, 12), tfSimdFloat4Load(TF_SIMD_TRUE,0,0,0), tfSimdFloat4Load(123, 11, -13, 32)},
//       {tfSimdFloat4Load(10, 11, -13, 32), tfSimdFloat4Load(123, -149, 0, 12), tfSimdFloat4Load(TF_SIMD_TRUE,0,TF_SIMD_TRUE,0), tfSimdFloat4Load(123, 11, 0, 32)},
//       {tfSimdFloat4Load(10, 11, -13, 32), tfSimdFloat4Load(123, -149, 0, 12), tfSimdFloat4Load(TF_SIMD_TRUE,TF_SIMD_TRUE,TF_SIMD_TRUE,TF_SIMD_TRUE), tfSimdFloat4Load(123, -149, 0, 12)},
//  };   
//  for (size_t i = 0; i < TF_ARRAY_COUNT(tests); i++)
//  {
//      //EXPECT_TRUE(tfSimd4fCmp(tfSimd4iSelect(tests[i].a, tests[i].b, tests[i].mask), tests[i].expect));
//  }
//}


#include "Forge/Mem/TF_Memory.h"
#include "Forge/TF_FileSystem.h"
#include "Forge/TF_Log.h"
UTEST_STATE();
TF_UTEST_MAIN("TF_Simd4")
