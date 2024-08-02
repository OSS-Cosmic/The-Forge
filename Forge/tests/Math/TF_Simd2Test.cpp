/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */
#include "TF_TestMain.h"
#include "utest.h"

#include "Forge/Math/TF_Simd32x2.h"
#include "TF_MathUtils.h"


UTEST(TF_Simd2, tfS32x2ICmpGt)
{
  struct {
    Tsimd_i32x2_t a;
    Tsimd_i32x2_t b;
    Tsimd_i32x2_t test;
  } tests[] = {
      // ... existing test cases ...
      // Edge cases:
      {tfS32x2ILoadImmediate(INT32_MIN, INT32_MIN), tfS32x2ILoadImmediate(INT32_MAX, INT32_MAX), tfS32x2ILoadImmediate(TF_SIMD_FALSE, TF_SIMD_FALSE)},
      {tfS32x2ILoadImmediate(INT32_MAX, INT32_MAX), tfS32x2ILoadImmediate(INT32_MIN, INT32_MIN), tfS32x2ILoadImmediate(TF_SIMD_TRUE, TF_SIMD_TRUE)},
      // Mixed values:
      {tfS32x2ILoadImmediate(0, -1), tfS32x2ILoadImmediate(1, 0), tfS32x2ILoadImmediate(TF_SIMD_FALSE, TF_SIMD_FALSE)},
      // All elements equal:
      {tfS32x2ILoadImmediate(42, 42), tfS32x2ILoadImmediate(42, 42), tfS32x2ILoadImmediate(TF_SIMD_FALSE, TF_SIMD_FALSE)},
      // Different element types:
      {tfS32x2ILoadImmediate(0, 1), tfS32x2ILoadImmediate(3, 2), tfS32x2ILoadImmediate(TF_SIMD_FALSE, TF_SIMD_FALSE)},
  };
  for(size_t i = 0; i < TF_ARRAY_COUNT(tests); i++) {
    EXPECT_TRUE(tfS32x2ICmpAllEq(tfS32x2ICmpGt(tests[i].a, tests[i].b), tests[i].test));
  }
}

UTEST(TF_Simd2, tfS32x2ICmpLt)
{
  struct {
    Tsimd_i32x2_t a;
    Tsimd_i32x2_t b;
    Tsimd_i32x2_t test;
  } tests[] = {
      // Less than
      {tfS32x2ILoadImmediate(12, 13), tfS32x2ILoadImmediate(16, 17), tfS32x2ILoadImmediate(TF_SIMD_TRUE, TF_SIMD_TRUE)},
      // Mixed less than and equal
      {tfS32x2ILoadImmediate(125, -12), tfS32x2ILoadImmediate(125, 13), tfS32x2ILoadImmediate(TF_SIMD_FALSE, TF_SIMD_TRUE)},
      // All elements greater than or equal
      {tfS32x2ILoadImmediate(1, 2), tfS32x2ILoadImmediate(-1, 0), tfS32x2ILoadImmediate(TF_SIMD_FALSE, TF_SIMD_FALSE)},
      // Edge cases:
      {tfS32x2ILoadImmediate(INT32_MIN, INT32_MIN), tfS32x2ILoadImmediate(INT32_MAX, INT32_MAX), tfS32x2ILoadImmediate(TF_SIMD_TRUE, TF_SIMD_TRUE)},
      {tfS32x2ILoadImmediate(INT32_MAX, INT32_MAX), tfS32x2ILoadImmediate(INT32_MIN, INT32_MIN), tfS32x2ILoadImmediate(TF_SIMD_FALSE, TF_SIMD_FALSE)},
  };
  for(size_t i = 0; i < TF_ARRAY_COUNT(tests); i++) {
    EXPECT_TRUE(tfS32x2ICmpAllEq(tfS32x2ICmpLt(tests[i].a, tests[i].b), tests[i].test));
  }
}



UTEST(TF_Simd2, tfS32x2ICmpEq)
{
  struct {
    Tsimd_i32x2_t a;
    Tsimd_i32x2_t b;
    Tsimd_i32x2_t test;
  } tests[] = {
       // Equal elements
      {tfS32x2ILoadImmediate(12, 13), tfS32x2ILoadImmediate(12, 13), tfS32x2ILoadImmediate(TF_SIMD_TRUE, TF_SIMD_TRUE)},
      // Mixed equal and unequal elements
      {tfS32x2ILoadImmediate(125, -12), tfS32x2ILoadImmediate(125, -12), tfS32x2ILoadImmediate(TF_SIMD_TRUE, TF_SIMD_TRUE)},
      // All elements unequal
      {tfS32x2ILoadImmediate(1, 2), tfS32x2ILoadImmediate(5, 6), tfS32x2ILoadImmediate(TF_SIMD_FALSE, TF_SIMD_FALSE)},
      // Edge cases:
      {tfS32x2ILoadImmediate(INT32_MIN, INT32_MIN), tfS32x2ILoadImmediate(INT32_MIN, INT32_MIN), tfS32x2ILoadImmediate(TF_SIMD_TRUE, TF_SIMD_TRUE)},
      {tfS32x2ILoadImmediate(INT32_MAX, INT32_MAX), tfS32x2ILoadImmediate(INT32_MAX, INT32_MAX), tfS32x2ILoadImmediate(TF_SIMD_TRUE, TF_SIMD_TRUE)},
  };
  for (size_t i = 0; i < TF_ARRAY_COUNT(tests); i++)
  {
      EXPECT_TRUE(tfS32x2ICmpAllEq(tfS32x2ICmpEq(tests[i].a, tests[i].b), tests[i].test));
  }
}

UTEST(TF_Simd2, tfS32x2FZero)
{
    Tsimd_f32x2_t value = tfS32x2FZero();
    EXPECT_NEAR(tfS32x2FSelectIndex0(value), 0.0f, DEFAULT_EPSILON);
    EXPECT_NEAR(tfS32x2FSelectIndex1(value), 0.0f, DEFAULT_EPSILON);
}

UTEST(TF_Simd2, tfS32x2FSplat)
{
    Tsimd_f32x2_t value = tfS32x2FSplat(23.f);
    EXPECT_NEAR(tfS32x2FSelectIndex0(value), 23.f, DEFAULT_EPSILON);
    EXPECT_NEAR(tfS32x2FSelectIndex1(value), 23.f, DEFAULT_EPSILON);
    Tsimd_f32x2_t value1 = tfS32x2FSplat(5.1f);
    EXPECT_NEAR(tfS32x2FSelectIndex0(value1), 5.1f, DEFAULT_EPSILON);
    EXPECT_NEAR(tfS32x2FSelectIndex1(value1), 5.1f, DEFAULT_EPSILON);

    Tsimd_f32x2_t value2 = tfSimdFloat2Load(5.1f, 1.0f);
    EXPECT_NEAR(tfS32x2FSelectIndex0(value2), 5.1f, DEFAULT_EPSILON);
    EXPECT_NEAR(tfS32x2FSelectIndex1(value2), 1.0f, DEFAULT_EPSILON);
}

UTEST(TF_Simd2, tfS32x3iNot) {
  struct {
    Tsimd_i32x2_t test;
    Tsimd_i32x2_t expect;
  } tests[] = {
       {tfS32x2ILoadImmediate(0xFFFFFFFF, 0x0000FFFF), tfS32x2ILoadImmediate(0, 0xFFFF0000)},
  };   
  for (size_t i = 0; i < TF_ARRAY_COUNT(tests); i++)
  {
      EXPECT_TRUE(tfS32x2ICmpAllEq(tfS32x2INot(tests[i].test), tests[i].expect));
  }
}

UTEST(TF_Simd2, tfS32x2ISelect) {
  struct {
    Tsimd_i32x2_t a;
    Tsimd_i32x2_t b;
    Tsimd_i32x2_t mask;
    Tsimd_i32x2_t expect;
  } tests[] = {
       {tfS32x2ILoadImmediate(10, 11), tfS32x2ILoadImmediate(123, -149), tfS32x2ILoadImmediate(0,0), tfS32x2ILoadImmediate(10, 11)},
       {tfS32x2ILoadImmediate(10, 11), tfS32x2ILoadImmediate(123, -149), tfS32x2ILoadImmediate(TF_SIMD_TRUE,0), tfS32x2ILoadImmediate(123, 11)},
       {tfS32x2ILoadImmediate(10, 11), tfS32x2ILoadImmediate(123, -149), tfS32x2ILoadImmediate(TF_SIMD_TRUE,0), tfS32x2ILoadImmediate(123, 11)},
       {tfS32x2ILoadImmediate(10, 11), tfS32x2ILoadImmediate(123, -149), tfS32x2ILoadImmediate(TF_SIMD_TRUE,TF_SIMD_TRUE), tfS32x2ILoadImmediate(123, -149)},
  };   
  for (size_t i = 0; i < TF_ARRAY_COUNT(tests); i++)
  {
      EXPECT_TRUE(tfS32x2ICmpAllEq(tfS32x2ISelect(tests[i].a, tests[i].b, tests[i].mask), tests[i].expect));
  }
}

//UTEST(TF_Simd2, tfS32x3FSelect) {
//  struct {
//    TSimd32fx4 a;
//    TSimd32fx4 b;
//    TSimd32fx4 mask;
//    TSimd32fx4 expect;
//  } tests[] = {
//       {tfS32x3FLoadImmediate(10, 11, -13, 32), tfS32x3FLoadImmediate(123, -149, 0, 12), tfS32x3FLoadImmediate(0,0,0,0), tfS32x3FLoadImmediate(10, 11, -13, 32)},
//       {tfS32x3FLoadImmediate(10, 11, -13, 32), tfS32x3FLoadImmediate(123, -149, 0, 12), tfS32x3FLoadImmediate(TF_SIMD_TRUE,0,0,0), tfS32x3FLoadImmediate(123, 11, -13, 32)},
//       {tfS32x3FLoadImmediate(10, 11, -13, 32), tfS32x3FLoadImmediate(123, -149, 0, 12), tfS32x3FLoadImmediate(TF_SIMD_TRUE,0,TF_SIMD_TRUE,0), tfS32x3FLoadImmediate(123, 11, 0, 32)},
//       {tfS32x3FLoadImmediate(10, 11, -13, 32), tfS32x3FLoadImmediate(123, -149, 0, 12), tfS32x3FLoadImmediate(TF_SIMD_TRUE,TF_SIMD_TRUE,TF_SIMD_TRUE,TF_SIMD_TRUE), tfS32x3FLoadImmediate(123, -149, 0, 12)},
//  };   
//  for (size_t i = 0; i < TF_ARRAY_COUNT(tests); i++)
//  {
//      //EXPECT_TRUE(tfS32x3FCmp(tfS32x2ISelect(tests[i].a, tests[i].b, tests[i].mask), tests[i].expect));
//  }
//}


#include "Forge/Mem/TF_Memory.h"
#include "Forge/TF_FileSystem.h"
#include "Forge/TF_Log.h"
UTEST_STATE();
TF_UTEST_MAIN("TF_TF_Simd2")


