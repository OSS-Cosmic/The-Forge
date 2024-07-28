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
#include "Forge/Math/TF_SimdMath4.h"
#include "TF_MathUtils.h"


UTEST(Vector4, tfSimd4iCmpGt)
{
  struct {
    Simd_Int32Type4 a;
    Simd_Int32Type4 b;
    Simd_Int32Type4 test;
  } tests[] = {
      // ... existing test cases ...
      // Edge cases:
      {tfSimd4iLoadImmediate(INT32_MIN, INT32_MIN, INT32_MIN, INT32_MIN), tfSimd4iLoadImmediate(INT32_MAX, INT32_MAX, INT32_MAX, INT32_MAX), tfSimd4iLoadImmediate(TF_SIMD_FALSE, TF_SIMD_FALSE, TF_SIMD_FALSE, TF_SIMD_FALSE)},
      {tfSimd4iLoadImmediate(INT32_MAX, INT32_MAX, INT32_MAX, INT32_MAX), tfSimd4iLoadImmediate(INT32_MIN, INT32_MIN, INT32_MIN, INT32_MIN), tfSimd4iLoadImmediate(TF_SIMD_TRUE, TF_SIMD_TRUE, TF_SIMD_TRUE, TF_SIMD_TRUE)},
      // Mixed values:
      {tfSimd4iLoadImmediate(0, -1, 1, 0), tfSimd4iLoadImmediate(1, 0, -1, 0), tfSimd4iLoadImmediate(TF_SIMD_FALSE, TF_SIMD_FALSE, TF_SIMD_TRUE, TF_SIMD_FALSE)},
      // All elements equal:
      {tfSimd4iLoadImmediate(42, 42, 42, 42), tfSimd4iLoadImmediate(42, 42, 42, 42), tfSimd4iLoadImmediate(TF_SIMD_FALSE, TF_SIMD_FALSE, TF_SIMD_FALSE, TF_SIMD_FALSE)},
      // Different element types:
      {tfSimd4iLoadImmediate(0, 1, 2, 3), tfSimd4iLoadImmediate(3, 2, 1, 0), tfSimd4iLoadImmediate(TF_SIMD_FALSE, TF_SIMD_FALSE, TF_SIMD_TRUE, TF_SIMD_TRUE)},
  };
  for(size_t i = 0; i < TF_ARRAY_COUNT(tests); i++) {
    EXPECT_TRUE(tfSimd4iCmpAllEq(tfSimd4iCmpGt(tests[i].a, tests[i].b), tests[i].test));
  }
}

UTEST(Vector4, tfSimd4iCmpLt)
{
  struct {
    Simd_Int32Type4 a;
    Simd_Int32Type4 b;
    Simd_Int32Type4 test;
  } tests[] = {
      // Less than
      {tfSimd4iLoadImmediate(12, 13, 14, 15), tfSimd4iLoadImmediate(16, 17, 18, 19), tfSimd4iLoadImmediate(TF_SIMD_TRUE, TF_SIMD_TRUE, TF_SIMD_TRUE, TF_SIMD_TRUE)},
      // Mixed less than and equal
      {tfSimd4iLoadImmediate(125, -12, 153, 221), tfSimd4iLoadImmediate(125, 13, 153, 222), tfSimd4iLoadImmediate(TF_SIMD_FALSE, TF_SIMD_TRUE, TF_SIMD_FALSE, TF_SIMD_TRUE)},
      // All elements greater than or equal
      {tfSimd4iLoadImmediate(1, 2, 3, 4), tfSimd4iLoadImmediate(-1, 0, 1, 2), tfSimd4iLoadImmediate(TF_SIMD_FALSE, TF_SIMD_FALSE, TF_SIMD_FALSE, TF_SIMD_FALSE)},
      // Edge cases:
      {tfSimd4iLoadImmediate(INT32_MIN, INT32_MIN, INT32_MIN, INT32_MIN), tfSimd4iLoadImmediate(INT32_MAX, INT32_MAX, INT32_MAX, INT32_MAX), tfSimd4iLoadImmediate(TF_SIMD_TRUE, TF_SIMD_TRUE, TF_SIMD_TRUE, TF_SIMD_TRUE)},
      {tfSimd4iLoadImmediate(INT32_MAX, INT32_MAX, INT32_MAX, INT32_MAX), tfSimd4iLoadImmediate(INT32_MIN, INT32_MIN, INT32_MIN, INT32_MIN), tfSimd4iLoadImmediate(TF_SIMD_FALSE, TF_SIMD_FALSE, TF_SIMD_FALSE, TF_SIMD_FALSE)},
  };
  for(size_t i = 0; i < TF_ARRAY_COUNT(tests); i++) {
    EXPECT_TRUE(tfSimd4iCmpAllEq(tfSimd4iCmpLt(tests[i].a, tests[i].b), tests[i].test));
  }
}



UTEST(Vector4, tfSimd4iCmpEq)
{
  struct {
    Simd_Int32Type4 a;
    Simd_Int32Type4 b;
    Simd_Int32Type4 test;
  } tests[] = {
       // Equal elements
      {tfSimd4iLoadImmediate(12, 13, 14, 15), tfSimd4iLoadImmediate(12, 13, 14, 15), tfSimd4iLoadImmediate(TF_SIMD_TRUE, TF_SIMD_TRUE, TF_SIMD_TRUE, TF_SIMD_TRUE)},
      // Mixed equal and unequal elements
      {tfSimd4iLoadImmediate(125, -12, 153, 221), tfSimd4iLoadImmediate(125, -12, 14, 221), tfSimd4iLoadImmediate(TF_SIMD_TRUE, TF_SIMD_TRUE, TF_SIMD_FALSE, TF_SIMD_TRUE)},
      // All elements unequal
      {tfSimd4iLoadImmediate(1, 2, 3, 4), tfSimd4iLoadImmediate(5, 6, 7, 8), tfSimd4iLoadImmediate(TF_SIMD_FALSE, TF_SIMD_FALSE, TF_SIMD_FALSE, TF_SIMD_FALSE)},
      // Edge cases:
      {tfSimd4iLoadImmediate(INT32_MIN, INT32_MIN, INT32_MIN, INT32_MIN), tfSimd4iLoadImmediate(INT32_MIN, INT32_MIN, INT32_MIN, INT32_MIN), tfSimd4iLoadImmediate(TF_SIMD_TRUE, TF_SIMD_TRUE, TF_SIMD_TRUE, TF_SIMD_TRUE)},
      {tfSimd4iLoadImmediate(INT32_MAX, INT32_MAX, INT32_MAX, INT32_MAX), tfSimd4iLoadImmediate(INT32_MAX, INT32_MAX, INT32_MAX, INT32_MAX), tfSimd4iLoadImmediate(TF_SIMD_TRUE, TF_SIMD_TRUE, TF_SIMD_TRUE, TF_SIMD_TRUE)},
  };
  for (size_t i = 0; i < TF_ARRAY_COUNT(tests); i++)
  {
      EXPECT_TRUE(tfSimd4iCmpAllEq(tfSimd4iCmpEq(tests[i].a, tests[i].b), tests[i].test));
  }
}

UTEST(Vector4, tfSimd4fZero)
{
    Simd_FloatType4 value = tfSimd4fZero();
    EXPECT_NEAR(tfSimd4fSelectIndex0(value), 0.0f, DEFAULT_EPSILON);
    EXPECT_NEAR(tfSimd4fSelectIndex1(value), 0.0f, DEFAULT_EPSILON);
    EXPECT_NEAR(tfSimd4fSelectIndex2(value), 0.0f, DEFAULT_EPSILON);
    EXPECT_NEAR(tfSimd4fSelectIndex3(value), 0.0f, DEFAULT_EPSILON);
}

UTEST(Vector4, tfSimdSplat4f)
{
    Simd_FloatType4 value = tfSimd4fSplat(23.f);
    EXPECT_NEAR(tfSimd4fSelectIndex0(value), 23.f, DEFAULT_EPSILON);
    EXPECT_NEAR(tfSimd4fSelectIndex1(value), 23.f, DEFAULT_EPSILON);
    EXPECT_NEAR(tfSimd4fSelectIndex2(value), 23.f, DEFAULT_EPSILON);
    EXPECT_NEAR(tfSimd4fSelectIndex3(value), 23.f, DEFAULT_EPSILON);
    Simd_FloatType4 value1 = tfSimd4fSplat(5.1f);
    EXPECT_NEAR(tfSimd4fSelectIndex0(value1), 5.1f, DEFAULT_EPSILON);
    EXPECT_NEAR(tfSimd4fSelectIndex1(value1), 5.1f, DEFAULT_EPSILON);
    EXPECT_NEAR(tfSimd4fSelectIndex2(value1), 5.1f, DEFAULT_EPSILON);
    EXPECT_NEAR(tfSimd4fSelectIndex3(value1), 5.1f, DEFAULT_EPSILON);

    Simd_FloatType4 value2 = tfSimd4fLoadImmediate(5.1f, 1.0f, 2.0f, 3.0f);
    EXPECT_NEAR(tfSimd4fSelectIndex0(value2), 5.1f, DEFAULT_EPSILON);
    EXPECT_NEAR(tfSimd4fSelectIndex1(value2), 1.0f, DEFAULT_EPSILON);
    EXPECT_NEAR(tfSimd4fSelectIndex2(value2), 2.0f, DEFAULT_EPSILON);
    EXPECT_NEAR(tfSimd4fSelectIndex3(value2), 3.0f, DEFAULT_EPSILON);
}

UTEST(Vector4, tfSimd4iNot) {
  struct {
    Simd_Int32Type4 test;
    Simd_Int32Type4 expect;
  } tests[] = {
       {tfSimd4iLoadImmediate(0xFFFFFFFF, 0x0000FFFF, 0xFFFF0000, 0x000000FF), tfSimd4iLoadImmediate(0, 0xFFFF0000, 0x0000FFFF, 0xFFFFFF00)},
  };   
  for (size_t i = 0; i < TF_ARRAY_COUNT(tests); i++)
  {
      EXPECT_TRUE(tfSimd4iCmpAllEq(tfSimd4iNot(tests[i].test), tests[i].expect));
  }
}

UTEST(Vector4, tfSimd4iSelect) {
  struct {
    Simd_Int32Type4 a;
    Simd_Int32Type4 b;
    Simd_Int32Type4 mask;
    Simd_Int32Type4 expect;
  } tests[] = {
       {tfSimd4iLoadImmediate(10, 11, -13, 32), tfSimd4iLoadImmediate(123, -149, 0, 12), tfSimd4iLoadImmediate(0,0,0,0), tfSimd4iLoadImmediate(10, 11, -13, 32)},
       {tfSimd4iLoadImmediate(10, 11, -13, 32), tfSimd4iLoadImmediate(123, -149, 0, 12), tfSimd4iLoadImmediate(TF_SIMD_TRUE,0,0,0), tfSimd4iLoadImmediate(123, 11, -13, 32)},
       {tfSimd4iLoadImmediate(10, 11, -13, 32), tfSimd4iLoadImmediate(123, -149, 0, 12), tfSimd4iLoadImmediate(TF_SIMD_TRUE,0,TF_SIMD_TRUE,0), tfSimd4iLoadImmediate(123, 11, 0, 32)},
       {tfSimd4iLoadImmediate(10, 11, -13, 32), tfSimd4iLoadImmediate(123, -149, 0, 12), tfSimd4iLoadImmediate(TF_SIMD_TRUE,TF_SIMD_TRUE,TF_SIMD_TRUE,TF_SIMD_TRUE), tfSimd4iLoadImmediate(123, -149, 0, 12)},
  };   
  for (size_t i = 0; i < TF_ARRAY_COUNT(tests); i++)
  {
      EXPECT_TRUE(tfSimd4iCmpAllEq(tfSimd4iSelect(tests[i].a, tests[i].b, tests[i].mask), tests[i].expect));
  }
}

//UTEST(Vector4, tfSimd4fSelect) {
//  struct {
//    Simd_FloatType4 a;
//    Simd_FloatType4 b;
//    Simd_FloatType4 mask;
//    Simd_FloatType4 expect;
//  } tests[] = {
//       {tfSimd4fLoadImmediate(10, 11, -13, 32), tfSimd4fLoadImmediate(123, -149, 0, 12), tfSimd4fLoadImmediate(0,0,0,0), tfSimd4fLoadImmediate(10, 11, -13, 32)},
//       {tfSimd4fLoadImmediate(10, 11, -13, 32), tfSimd4fLoadImmediate(123, -149, 0, 12), tfSimd4fLoadImmediate(TF_SIMD_TRUE,0,0,0), tfSimd4fLoadImmediate(123, 11, -13, 32)},
//       {tfSimd4fLoadImmediate(10, 11, -13, 32), tfSimd4fLoadImmediate(123, -149, 0, 12), tfSimd4fLoadImmediate(TF_SIMD_TRUE,0,TF_SIMD_TRUE,0), tfSimd4fLoadImmediate(123, 11, 0, 32)},
//       {tfSimd4fLoadImmediate(10, 11, -13, 32), tfSimd4fLoadImmediate(123, -149, 0, 12), tfSimd4fLoadImmediate(TF_SIMD_TRUE,TF_SIMD_TRUE,TF_SIMD_TRUE,TF_SIMD_TRUE), tfSimd4fLoadImmediate(123, -149, 0, 12)},
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
TF_UTEST_MAIN("TF_Vector4")
