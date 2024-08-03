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


UTEST(TF_Simd3, tfS32x3iCmpGt)
{
  struct {
    Tsimd_i32x3_t a;
    Tsimd_i32x3_t b;
    Tsimd_i32x3_t test;
  } tests[] = {
      // ... existing test cases ...
      // Edge cases:
      {tfSimd3x32ILoad(INT32_MIN, INT32_MIN, INT32_MIN), tfSimd3x32ILoad(INT32_MAX, INT32_MAX, INT32_MAX), tfSimd3x32ILoad(TF_SIMD_FALSE, TF_SIMD_FALSE, TF_SIMD_FALSE)},
      {tfSimd3x32ILoad(INT32_MAX, INT32_MAX, INT32_MAX), tfSimd3x32ILoad(INT32_MIN, INT32_MIN, INT32_MIN), tfSimd3x32ILoad(TF_SIMD_TRUE, TF_SIMD_TRUE, TF_SIMD_TRUE)},
      // Mixed values:
      {tfSimd3x32ILoad(0, -1, 1), tfSimd3x32ILoad(1, 0, -1), tfSimd3x32ILoad(TF_SIMD_FALSE, TF_SIMD_FALSE, TF_SIMD_TRUE)},
      // All elements equal:
      {tfSimd3x32ILoad(42, 42, 42), tfSimd3x32ILoad(42, 42, 42), tfSimd3x32ILoad(TF_SIMD_FALSE, TF_SIMD_FALSE, TF_SIMD_FALSE)},
      // Different element types:
      {tfSimd3x32ILoad(0, 1, 2), tfSimd3x32ILoad(3, 2, 1), tfSimd3x32ILoad(TF_SIMD_FALSE, TF_SIMD_FALSE, TF_SIMD_TRUE)},
  };
  for(size_t i = 0; i < TF_ARRAY_COUNT(tests); i++) {
    EXPECT_TRUE(tfS32x3iCmpAllEq(tfS32x3iCmpGt(tests[i].a, tests[i].b), tests[i].test));
  }
}

UTEST(TF_Simd3, tfS32x3iCmpLt)
{
  struct {
    Tsimd_i32x3_t a;
    Tsimd_i32x3_t b;
    Tsimd_i32x3_t test;
  } tests[] = {
      // Less than
      {tfSimd3x32ILoad(12, 13, 14), tfSimd3x32ILoad(16, 17, 18), tfSimd3x32ILoad(TF_SIMD_TRUE, TF_SIMD_TRUE, TF_SIMD_TRUE)},
      // Mixed less than and equal
      {tfSimd3x32ILoad(125, -12, 153), tfSimd3x32ILoad(125, 13, 153), tfSimd3x32ILoad(TF_SIMD_FALSE, TF_SIMD_TRUE, TF_SIMD_FALSE)},
      // All elements greater than or equal
      {tfSimd3x32ILoad(1, 2, 3), tfSimd3x32ILoad(-1, 0, 1), tfSimd3x32ILoad(TF_SIMD_FALSE, TF_SIMD_FALSE, TF_SIMD_FALSE)},
      // Edge cases:
      {tfSimd3x32ILoad(INT32_MIN, INT32_MIN, INT32_MIN), tfSimd3x32ILoad(INT32_MAX, INT32_MAX, INT32_MAX), tfSimd3x32ILoad(TF_SIMD_TRUE, TF_SIMD_TRUE, TF_SIMD_TRUE)},
      {tfSimd3x32ILoad(INT32_MAX, INT32_MAX, INT32_MAX), tfSimd3x32ILoad(INT32_MIN, INT32_MIN, INT32_MIN), tfSimd3x32ILoad(TF_SIMD_FALSE, TF_SIMD_FALSE, TF_SIMD_FALSE)},
  };
  for(size_t i = 0; i < TF_ARRAY_COUNT(tests); i++) {
    EXPECT_TRUE(tfS32x3iCmpAllEq(tfS32x3iCmpLt(tests[i].a, tests[i].b), tests[i].test));
  }
}



UTEST(TF_Simd3, tfS32x3iCmpEq)
{
  struct {
    Tsimd_i32x3_t a;
    Tsimd_i32x3_t b;
    Tsimd_i32x3_t test;
  } tests[] = {
       // Equal elements
      {tfSimd3x32ILoad(12, 13, 14), tfSimd3x32ILoad(12, 13, 14), tfSimd3x32ILoad(TF_SIMD_TRUE, TF_SIMD_TRUE, TF_SIMD_TRUE)},
      // Mixed equal and unequal elements
      {tfSimd3x32ILoad(125, -12, 153), tfSimd3x32ILoad(125, -12, 14), tfSimd3x32ILoad(TF_SIMD_TRUE, TF_SIMD_TRUE, TF_SIMD_FALSE)},
      // All elements unequal
      {tfSimd3x32ILoad(1, 2, 3), tfSimd3x32ILoad(5, 6, 7), tfSimd3x32ILoad(TF_SIMD_FALSE, TF_SIMD_FALSE, TF_SIMD_FALSE)},
      // Edge cases:
      {tfSimd3x32ILoad(INT32_MIN, INT32_MIN, INT32_MIN), tfSimd3x32ILoad(INT32_MIN, INT32_MIN, INT32_MIN), tfSimd3x32ILoad(TF_SIMD_TRUE, TF_SIMD_TRUE, TF_SIMD_TRUE)},
      {tfSimd3x32ILoad(INT32_MAX, INT32_MAX, INT32_MAX), tfSimd3x32ILoad(INT32_MAX, INT32_MAX, INT32_MAX), tfSimd3x32ILoad(TF_SIMD_TRUE, TF_SIMD_TRUE, TF_SIMD_TRUE)},
  };
  for (size_t i = 0; i < TF_ARRAY_COUNT(tests); i++)
  {
      EXPECT_TRUE(tfS32x3iCmpAllEq(tfS32x3iCmpEq(tests[i].a, tests[i].b), tests[i].test));
  }
}

UTEST(TF_Simd3, tfS32x3FZero)
{
    Tsimd_f32x3_t value = tfS32x3FZero();
    EXPECT_NEAR(tfS32x3FSelectIndex0(value), 0.0f, DEFAULT_EPSILON);
    EXPECT_NEAR(tfS32x3FSelectIndex1(value), 0.0f, DEFAULT_EPSILON);
    EXPECT_NEAR(tfS32x3FSelectIndex2(value), 0.0f, DEFAULT_EPSILON);
}

UTEST(TF_Simd3, tfSimdSplat4f)
{
    Tsimd_f32x3_t value = tfS32x3FSplat(23.f);
    EXPECT_NEAR(tfS32x3FSelectIndex0(value), 23.f, DEFAULT_EPSILON);
    EXPECT_NEAR(tfS32x3FSelectIndex1(value), 23.f, DEFAULT_EPSILON);
    EXPECT_NEAR(tfS32x3FSelectIndex2(value), 23.f, DEFAULT_EPSILON);
    Tsimd_f32x3_t value1 = tfS32x3FSplat(5.1f);
    EXPECT_NEAR(tfS32x3FSelectIndex0(value1), 5.1f, DEFAULT_EPSILON);
    EXPECT_NEAR(tfS32x3FSelectIndex1(value1), 5.1f, DEFAULT_EPSILON);
    EXPECT_NEAR(tfS32x3FSelectIndex2(value1), 5.1f, DEFAULT_EPSILON);

    Tsimd_f32x3_t value2 = tfSimd3x32FLoad(5.1f, 1.0f, 2.0f);
    EXPECT_NEAR(tfS32x3FSelectIndex0(value2), 5.1f, DEFAULT_EPSILON);
    EXPECT_NEAR(tfS32x3FSelectIndex1(value2), 1.0f, DEFAULT_EPSILON);
    EXPECT_NEAR(tfS32x3FSelectIndex2(value2), 2.0f, DEFAULT_EPSILON);
}

UTEST(TF_Simd3, tfS32x3iNot) {
  struct {
    Tsimd_i32x3_t test;
    Tsimd_i32x3_t expect;
  } tests[] = {
       {tfSimd3x32ILoad(0xFFFFFFFF, 0x0000FFFF, 0xFFFF0000), tfSimd3x32ILoad(0, 0xFFFF0000, 0x0000FFFF)},
  };   
  for (size_t i = 0; i < TF_ARRAY_COUNT(tests); i++)
  {
      EXPECT_TRUE(tfS32x3iCmpAllEq(tfS32x3iNot(tests[i].test), tests[i].expect));
  }
}

UTEST(TF_Simd3, tfS32x3iSelect) {
  struct {
    Tsimd_i32x3_t a;
    Tsimd_i32x3_t b;
    Tsimd_i32x3_t mask;
    Tsimd_i32x3_t expect;
  } tests[] = {
       {tfSimd3x32ILoad(10, 11, -13), tfSimd3x32ILoad(123, -149, 0), tfSimd3x32ILoad(0,0,0), tfSimd3x32ILoad(10, 11, -13)},
       {tfSimd3x32ILoad(10, 11, -13), tfSimd3x32ILoad(123, -149, 0), tfSimd3x32ILoad(TF_SIMD_TRUE,0,0), tfSimd3x32ILoad(123, 11, -13)},
       {tfSimd3x32ILoad(10, 11, -13), tfSimd3x32ILoad(123, -149, 0), tfSimd3x32ILoad(TF_SIMD_TRUE,0,TF_SIMD_TRUE), tfSimd3x32ILoad(123, 11, 0)},
       {tfSimd3x32ILoad(10, 11, -13), tfSimd3x32ILoad(123, -149, 0), tfSimd3x32ILoad(TF_SIMD_TRUE,TF_SIMD_TRUE,TF_SIMD_TRUE), tfSimd3x32ILoad(123, -149, 0)},
  };   
  for (size_t i = 0; i < TF_ARRAY_COUNT(tests); i++)
  {
      EXPECT_TRUE(tfS32x3iCmpAllEq(tfS32x3iSelect(tests[i].a, tests[i].b, tests[i].mask), tests[i].expect));
  }
}

//UTEST(TF_Simd3, tfS32x3FSelect) {
//  struct {
//    Tsimd_f32x3_t a;
//    Tsimd_f32x3_t b;
//    Tsimd_f32x3_t mask;
//    Tsimd_f32x3_t expect;
//  } tests[] = {
//       {tfSimdFloat4Load(10, 11, -13, 32), tfSimdFloat4Load(123, -149, 0, 12), tfSimdFloat4Load(0,0,0,0), tfSimdFloat4Load(10, 11, -13, 32)},
//       {tfSimdFloat4Load(10, 11, -13, 32), tfSimdFloat4Load(123, -149, 0, 12), tfSimdFloat4Load(TF_SIMD_TRUE,0,0,0), tfSimdFloat4Load(123, 11, -13, 32)},
//       {tfSimdFloat4Load(10, 11, -13, 32), tfSimdFloat4Load(123, -149, 0, 12), tfSimdFloat4Load(TF_SIMD_TRUE,0,TF_SIMD_TRUE,0), tfSimdFloat4Load(123, 11, 0, 32)},
//       {tfSimdFloat4Load(10, 11, -13, 32), tfSimdFloat4Load(123, -149, 0, 12), tfSimdFloat4Load(TF_SIMD_TRUE,TF_SIMD_TRUE,TF_SIMD_TRUE,TF_SIMD_TRUE), tfSimdFloat4Load(123, -149, 0, 12)},
//  };   
//  for (size_t i = 0; i < TF_ARRAY_COUNT(tests); i++)
//  {
//      //EXPECT_TRUE(tfS32x3FCmp(tfS32x3iSelect(tests[i].a, tests[i].b, tests[i].mask), tests[i].expect));
//  }
//}


#include "Forge/Mem/TF_Memory.h"
#include "Forge/TF_FileSystem.h"
#include "Forge/TF_Log.h"
UTEST_STATE();
TF_UTEST_MAIN("TF_Simd3")

