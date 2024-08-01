/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */
#include "TF_TestMain.h"
#include "utest.h"

#include "Forge/Math/TF_Simd32x3.h"
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
      {tfSimdInt3x32Load(INT32_MIN, INT32_MIN, INT32_MIN), tfSimdInt3x32Load(INT32_MAX, INT32_MAX, INT32_MAX), tfSimdInt3x32Load(TF_SIMD_FALSE, TF_SIMD_FALSE, TF_SIMD_FALSE)},
      {tfSimdInt3x32Load(INT32_MAX, INT32_MAX, INT32_MAX), tfSimdInt3x32Load(INT32_MIN, INT32_MIN, INT32_MIN), tfSimdInt3x32Load(TF_SIMD_TRUE, TF_SIMD_TRUE, TF_SIMD_TRUE)},
      // Mixed values:
      {tfSimdInt3x32Load(0, -1, 1), tfSimdInt3x32Load(1, 0, -1), tfSimdInt3x32Load(TF_SIMD_FALSE, TF_SIMD_FALSE, TF_SIMD_TRUE)},
      // All elements equal:
      {tfSimdInt3x32Load(42, 42, 42), tfSimdInt3x32Load(42, 42, 42), tfSimdInt3x32Load(TF_SIMD_FALSE, TF_SIMD_FALSE, TF_SIMD_FALSE)},
      // Different element types:
      {tfSimdInt3x32Load(0, 1, 2), tfSimdInt3x32Load(3, 2, 1), tfSimdInt3x32Load(TF_SIMD_FALSE, TF_SIMD_FALSE, TF_SIMD_TRUE)},
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
      {tfSimdInt3x32Load(12, 13, 14), tfSimdInt3x32Load(16, 17, 18), tfSimdInt3x32Load(TF_SIMD_TRUE, TF_SIMD_TRUE, TF_SIMD_TRUE)},
      // Mixed less than and equal
      {tfSimdInt3x32Load(125, -12, 153), tfSimdInt3x32Load(125, 13, 153), tfSimdInt3x32Load(TF_SIMD_FALSE, TF_SIMD_TRUE, TF_SIMD_FALSE)},
      // All elements greater than or equal
      {tfSimdInt3x32Load(1, 2, 3), tfSimdInt3x32Load(-1, 0, 1), tfSimdInt3x32Load(TF_SIMD_FALSE, TF_SIMD_FALSE, TF_SIMD_FALSE)},
      // Edge cases:
      {tfSimdInt3x32Load(INT32_MIN, INT32_MIN, INT32_MIN), tfSimdInt3x32Load(INT32_MAX, INT32_MAX, INT32_MAX), tfSimdInt3x32Load(TF_SIMD_TRUE, TF_SIMD_TRUE, TF_SIMD_TRUE)},
      {tfSimdInt3x32Load(INT32_MAX, INT32_MAX, INT32_MAX), tfSimdInt3x32Load(INT32_MIN, INT32_MIN, INT32_MIN), tfSimdInt3x32Load(TF_SIMD_FALSE, TF_SIMD_FALSE, TF_SIMD_FALSE)},
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
      {tfSimdInt3x32Load(12, 13, 14), tfSimdInt3x32Load(12, 13, 14), tfSimdInt3x32Load(TF_SIMD_TRUE, TF_SIMD_TRUE, TF_SIMD_TRUE)},
      // Mixed equal and unequal elements
      {tfSimdInt3x32Load(125, -12, 153), tfSimdInt3x32Load(125, -12, 14), tfSimdInt3x32Load(TF_SIMD_TRUE, TF_SIMD_TRUE, TF_SIMD_FALSE)},
      // All elements unequal
      {tfSimdInt3x32Load(1, 2, 3), tfSimdInt3x32Load(5, 6, 7), tfSimdInt3x32Load(TF_SIMD_FALSE, TF_SIMD_FALSE, TF_SIMD_FALSE)},
      // Edge cases:
      {tfSimdInt3x32Load(INT32_MIN, INT32_MIN, INT32_MIN), tfSimdInt3x32Load(INT32_MIN, INT32_MIN, INT32_MIN), tfSimdInt3x32Load(TF_SIMD_TRUE, TF_SIMD_TRUE, TF_SIMD_TRUE)},
      {tfSimdInt3x32Load(INT32_MAX, INT32_MAX, INT32_MAX), tfSimdInt3x32Load(INT32_MAX, INT32_MAX, INT32_MAX), tfSimdInt3x32Load(TF_SIMD_TRUE, TF_SIMD_TRUE, TF_SIMD_TRUE)},
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

    TSimdFloat32x3 value2 = tfSimdFloat3x32Load(5.1f, 1.0f, 2.0f);
    EXPECT_NEAR(tfSimd3fSelectIndex0(value2), 5.1f, DEFAULT_EPSILON);
    EXPECT_NEAR(tfSimd3fSelectIndex1(value2), 1.0f, DEFAULT_EPSILON);
    EXPECT_NEAR(tfSimd3fSelectIndex2(value2), 2.0f, DEFAULT_EPSILON);
}

UTEST(TF_Simd3, tfSimd3iNot) {
  struct {
    TSimdInt32x3 test;
    TSimdInt32x3 expect;
  } tests[] = {
       {tfSimdInt3x32Load(0xFFFFFFFF, 0x0000FFFF, 0xFFFF0000), tfSimdInt3x32Load(0, 0xFFFF0000, 0x0000FFFF)},
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
       {tfSimdInt3x32Load(10, 11, -13), tfSimdInt3x32Load(123, -149, 0), tfSimdInt3x32Load(0,0,0), tfSimdInt3x32Load(10, 11, -13)},
       {tfSimdInt3x32Load(10, 11, -13), tfSimdInt3x32Load(123, -149, 0), tfSimdInt3x32Load(TF_SIMD_TRUE,0,0), tfSimdInt3x32Load(123, 11, -13)},
       {tfSimdInt3x32Load(10, 11, -13), tfSimdInt3x32Load(123, -149, 0), tfSimdInt3x32Load(TF_SIMD_TRUE,0,TF_SIMD_TRUE), tfSimdInt3x32Load(123, 11, 0)},
       {tfSimdInt3x32Load(10, 11, -13), tfSimdInt3x32Load(123, -149, 0), tfSimdInt3x32Load(TF_SIMD_TRUE,TF_SIMD_TRUE,TF_SIMD_TRUE), tfSimdInt3x32Load(123, -149, 0)},
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
//       {tfSimdFloat4Load(10, 11, -13, 32), tfSimdFloat4Load(123, -149, 0, 12), tfSimdFloat4Load(0,0,0,0), tfSimdFloat4Load(10, 11, -13, 32)},
//       {tfSimdFloat4Load(10, 11, -13, 32), tfSimdFloat4Load(123, -149, 0, 12), tfSimdFloat4Load(TF_SIMD_TRUE,0,0,0), tfSimdFloat4Load(123, 11, -13, 32)},
//       {tfSimdFloat4Load(10, 11, -13, 32), tfSimdFloat4Load(123, -149, 0, 12), tfSimdFloat4Load(TF_SIMD_TRUE,0,TF_SIMD_TRUE,0), tfSimdFloat4Load(123, 11, 0, 32)},
//       {tfSimdFloat4Load(10, 11, -13, 32), tfSimdFloat4Load(123, -149, 0, 12), tfSimdFloat4Load(TF_SIMD_TRUE,TF_SIMD_TRUE,TF_SIMD_TRUE,TF_SIMD_TRUE), tfSimdFloat4Load(123, -149, 0, 12)},
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

