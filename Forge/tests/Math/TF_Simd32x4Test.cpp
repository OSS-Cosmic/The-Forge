/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */
#include "TF_TestMain.h"
#include "utest.h"

#include "Forge/Math/TF_Simd32x4.h"
#include "TF_MathUtils.h"

UTEST(Tsimd_f32x4_t, Zero)
{
  Tsimd_f32x4_t value = tfSimdZero_f32x4();
  EXPECT_NEAR(tfSimdSelect_f32x4(value, 0), 0, DEFAULT_EPSILON);
  EXPECT_NEAR(tfSimdSelect_f32x4(value, 1), 0, DEFAULT_EPSILON);
  EXPECT_NEAR(tfSimdSelect_f32x4(value, 2), 0, DEFAULT_EPSILON);
  EXPECT_NEAR(tfSimdSelect_f32x4(value, 3), 0, DEFAULT_EPSILON);

}

UTEST(Tsimd_f32x4_t, Load_Select)
{
  Tsimd_f32x4_t value = tfSimdLoad_f32x4(123.0,12.f,45.f,12.5f);

  EXPECT_NEAR(tfSimdSelect_f32x4(value, 0), 123.0f, DEFAULT_EPSILON);
  EXPECT_NEAR(tfSimdSelect_f32x4(value, 1), 12.0f, DEFAULT_EPSILON);
  EXPECT_NEAR(tfSimdSelect_f32x4(value, 2), 45.0f, DEFAULT_EPSILON);
  EXPECT_NEAR(tfSimdSelect_f32x4(value, 3), 12.5f, DEFAULT_EPSILON);

  EXPECT_NEAR(tfSimdSelect0_f32x4(value), 123.0f, DEFAULT_EPSILON);
  EXPECT_NEAR(tfSimdSelect1_f32x4(value), 12.0f, DEFAULT_EPSILON);
  EXPECT_NEAR(tfSimdSelect2_f32x4(value), 45.0f, DEFAULT_EPSILON);
  EXPECT_NEAR(tfSimdSelect3_f32x4(value), 12.5f, DEFAULT_EPSILON);
}

UTEST(Tsimd_i32x4_t, Splat) {
    Tsimd_i32x4_t value = tfSimdLoad_i32x4(123, 12, 45, 12);
    {
        Tsimd_i32x4_t test = tfSimdSplat_i32x4(123);
        EXPECT_NEAR(tfSimdSelect0_i32x4(test), 123, DEFAULT_EPSILON);
        EXPECT_NEAR(tfSimdSelect1_i32x4(test), 123, DEFAULT_EPSILON);
        EXPECT_NEAR(tfSimdSelect2_i32x4(test), 123, DEFAULT_EPSILON);
        EXPECT_NEAR(tfSimdSelect3_i32x4(test), 123, DEFAULT_EPSILON);
    }
    {
        Tsimd_i32x4_t test = tfSimdSplat0_i32x4(value);
        EXPECT_NEAR(tfSimdSelect0_i32x4(test), 123, DEFAULT_EPSILON);
        EXPECT_NEAR(tfSimdSelect1_i32x4(test), 123, DEFAULT_EPSILON);
        EXPECT_NEAR(tfSimdSelect2_i32x4(test), 123, DEFAULT_EPSILON);
        EXPECT_NEAR(tfSimdSelect3_i32x4(test), 123, DEFAULT_EPSILON);
    }

    {
        Tsimd_i32x4_t test = tfSimdSplat1_i32x4(value);
        EXPECT_NEAR(tfSimdSelect0_i32x4(test), 12, DEFAULT_EPSILON);
        EXPECT_NEAR(tfSimdSelect1_i32x4(test), 12, DEFAULT_EPSILON);
        EXPECT_NEAR(tfSimdSelect2_i32x4(test), 12, DEFAULT_EPSILON);
        EXPECT_NEAR(tfSimdSelect3_i32x4(test), 12, DEFAULT_EPSILON);
    }

    {
        Tsimd_i32x4_t test = tfSimdSplat2_i32x4(value);
        EXPECT_NEAR(tfSimdSelect0_i32x4(test), 45, DEFAULT_EPSILON);
        EXPECT_NEAR(tfSimdSelect1_i32x4(test), 45, DEFAULT_EPSILON);
        EXPECT_NEAR(tfSimdSelect2_i32x4(test), 45, DEFAULT_EPSILON);
        EXPECT_NEAR(tfSimdSelect3_i32x4(test), 45, DEFAULT_EPSILON);
    }

    {
        Tsimd_i32x4_t test = tfSimdSplat3_i32x4(value);
        EXPECT_NEAR(tfSimdSelect0_i32x4(test), 12, DEFAULT_EPSILON);
        EXPECT_NEAR(tfSimdSelect1_i32x4(test), 12, DEFAULT_EPSILON);
        EXPECT_NEAR(tfSimdSelect2_i32x4(test), 12, DEFAULT_EPSILON);
        EXPECT_NEAR(tfSimdSelect3_i32x4(test), 12, DEFAULT_EPSILON);
    }
}

UTEST(Tsimd_f32x4_t, Splat) {
  Tsimd_f32x4_t value = tfSimdLoad_f32x4(123.0,12.f,45.f,12.5f);
  {
      Tsimd_f32x4_t test = tfSimdSplat_f32x4(123.0f);
      EXPECT_NEAR(tfSimdSelect0_f32x4(test), 123.0f, DEFAULT_EPSILON);
      EXPECT_NEAR(tfSimdSelect1_f32x4(test), 123.0f, DEFAULT_EPSILON);
      EXPECT_NEAR(tfSimdSelect2_f32x4(test), 123.0f, DEFAULT_EPSILON);
      EXPECT_NEAR(tfSimdSelect3_f32x4(test), 123.0f, DEFAULT_EPSILON);

  }
  {
      Tsimd_f32x4_t test = tfSimdSplat0_f32x4(value);
      EXPECT_NEAR(tfSimdSelect0_f32x4(test), 123.0f, DEFAULT_EPSILON);
      EXPECT_NEAR(tfSimdSelect1_f32x4(test), 123.0f, DEFAULT_EPSILON);
      EXPECT_NEAR(tfSimdSelect2_f32x4(test), 123.0f, DEFAULT_EPSILON);
      EXPECT_NEAR(tfSimdSelect3_f32x4(test), 123.0f, DEFAULT_EPSILON);
  }

  {
      Tsimd_f32x4_t test = tfSimdSplat1_f32x4(value);
      EXPECT_NEAR(tfSimdSelect0_f32x4(test), 12.0f, DEFAULT_EPSILON);
      EXPECT_NEAR(tfSimdSelect1_f32x4(test), 12.0f, DEFAULT_EPSILON);
      EXPECT_NEAR(tfSimdSelect2_f32x4(test), 12.0f, DEFAULT_EPSILON);
      EXPECT_NEAR(tfSimdSelect3_f32x4(test), 12.0f, DEFAULT_EPSILON);
  }

  {
      Tsimd_f32x4_t test = tfSimdSplat2_f32x4(value);
      EXPECT_NEAR(tfSimdSelect0_f32x4(test), 45.0f, DEFAULT_EPSILON);
      EXPECT_NEAR(tfSimdSelect1_f32x4(test), 45.0f, DEFAULT_EPSILON);
      EXPECT_NEAR(tfSimdSelect2_f32x4(test), 45.0f, DEFAULT_EPSILON);
      EXPECT_NEAR(tfSimdSelect3_f32x4(test), 45.0f, DEFAULT_EPSILON);
  }

  {
      Tsimd_f32x4_t test = tfSimdSplat3_f32x4(value);
      EXPECT_NEAR(tfSimdSelect0_f32x4(test), 12.5f, DEFAULT_EPSILON);
      EXPECT_NEAR(tfSimdSelect1_f32x4(test), 12.5f, DEFAULT_EPSILON);
      EXPECT_NEAR(tfSimdSelect2_f32x4(test), 12.5f, DEFAULT_EPSILON);
      EXPECT_NEAR(tfSimdSelect3_f32x4(test), 12.5f, DEFAULT_EPSILON);
  }
}


UTEST(Tsimd_i32x4_t, Load_Select)
{
  Tsimd_i32x4_t value = tfSimdLoad_i32x4(123,12,45,165);

  EXPECT_EQ(tfSimdSelect_i32x4(value, 0), 123);
  EXPECT_EQ(tfSimdSelect_i32x4(value, 1), 12);
  EXPECT_EQ(tfSimdSelect_i32x4(value, 2), 45);
  EXPECT_EQ(tfSimdSelect_i32x4(value, 3), 165);
  
  EXPECT_EQ(tfSimdSelect0_i32x4(value), 123);
  EXPECT_EQ(tfSimdSelect1_i32x4(value), 12);
  EXPECT_EQ(tfSimdSelect2_i32x4(value), 45);
  EXPECT_EQ(tfSimdSelect3_i32x4(value), 165);
}

UTEST(Tsimd_f32x4_t, tfSimdCmpGt_f32x4)
{
  struct {
    Tsimd_f32x4_t a;
    Tsimd_f32x4_t b;
    Tsimd_i32x4_t test;
  } tests[] = {
      // Mixed values:
        // Mixed values:
      {tfSimdLoad_f32x4(0, -1, 1, 0), tfSimdLoad_f32x4(1, 0, -1, 0), tfSimdLoad_i32x4(0, 0, -1, 0)},
      // All elements greater:
      {tfSimdLoad_f32x4(2, 3, 4, 5), tfSimdLoad_f32x4(1, 2, 3, 4), tfSimdLoad_i32x4(-1, -1, -1, -1)},
      // All elements equal:
      {tfSimdLoad_f32x4(1, 1, 1, 1), tfSimdLoad_f32x4(1, 1, 1, 1), tfSimdLoad_i32x4(0, 0, 0, 0)},
      // All elements less:
      {tfSimdLoad_f32x4(1, 2, 3, 4), tfSimdLoad_f32x4(2, 3, 4, 5), tfSimdLoad_i32x4(0, 0, 0, 0)},
      // Mixed positive and negative values:
      {tfSimdLoad_f32x4(-1, 2, -3, 4), tfSimdLoad_f32x4(-2, 1, -4, 3), tfSimdLoad_i32x4(-1, -1, -1, -1)},
      // Zero comparison:
      {tfSimdLoad_f32x4(0, 0, 0, 0), tfSimdLoad_f32x4(0, 0, 0, 0), tfSimdLoad_i32x4(0, 0, 0, 0)},
  };
  for(size_t i = 0; i < TF_ARRAY_COUNT(tests); i++) {
      Tsimd_i32x4_t result = tfSimd_f32x4_To_i32x4(tfSimdCmpGt_f32x4(tests[i].a, tests[i].b));
      DLOGF(LogLevel::eDEBUG,LOG_FORMAT_SIMD_32x4i(result));
      EXPECT_TRUE(tfSimdCmpAllEq_i32x4(result, tests[i].test));
  }
}

UTEST(Tsimd_f32x4_t, tfSimdCmpEq_f32x4)
{
  struct {
    Tsimd_f32x4_t a;
    Tsimd_f32x4_t b;
    Tsimd_i32x4_t test;
  } tests[] = {
      // Mixed values:
      {tfSimdLoad_f32x4(0, -1, 1, 0), tfSimdLoad_f32x4(1, 0, -1, 0), tfSimdLoad_i32x4(0, 0, 0, -1)},
      // All elements equal:
      {tfSimdLoad_f32x4(1, 1, 1, 1), tfSimdLoad_f32x4(1, 1, 1, 1), tfSimdLoad_i32x4(-1, -1, -1, -1)},
      // All elements different:
      {tfSimdLoad_f32x4(1, 2, 3, 4), tfSimdLoad_f32x4(5, 6, 7, 8), tfSimdLoad_i32x4(0, 0, 0, 0)},
      // Mixed positive and negative values:
      {tfSimdLoad_f32x4(-1, 2, -3, 4), tfSimdLoad_f32x4(-1, 2, -3, 4), tfSimdLoad_i32x4(-1, -1, -1, -1)},
      // Zero comparison:
      {tfSimdLoad_f32x4(0, 0, 0, 0), tfSimdLoad_f32x4(0, 0, 0, 0), tfSimdLoad_i32x4(-1, -1, -1, -1)},
  };
  for(size_t i = 0; i < TF_ARRAY_COUNT(tests); i++) {
      Tsimd_i32x4_t result = tfSimd_f32x4_To_i32x4(tfSimdCmpEq_f32x4(tests[i].a, tests[i].b));
      DLOGF(LogLevel::eDEBUG, LOG_FORMAT_SIMD_32x4i(result));
      EXPECT_TRUE(tfSimdCmpAllEq_i32x4(result, tests[i].test));
  }
}

UTEST(Tsimd_f32x4_t, tfSimdCmpNeq_f32x4)
{
  struct {
    Tsimd_f32x4_t a;
    Tsimd_f32x4_t b;
    Tsimd_i32x4_t test;
  } tests[] = {
      // Mixed values:
      {tfSimdLoad_f32x4(0, -1, 1, 0), tfSimdLoad_f32x4(1, 0, -1, 0), tfSimdLoad_i32x4(-1, -1, -1, 0)},
      // All elements equal:
      {tfSimdLoad_f32x4(1, 1, 1, 1), tfSimdLoad_f32x4(1, 1, 1, 1), tfSimdLoad_i32x4(0, 0, 0, 0)},
      // All elements different:
      {tfSimdLoad_f32x4(1, 2, 3, 4), tfSimdLoad_f32x4(5, 6, 7, 8), tfSimdLoad_i32x4(-1, -1, -1, -1)},
      // Mixed positive and negative values:
      {tfSimdLoad_f32x4(-1, 2, -3, 4), tfSimdLoad_f32x4(-1, 2, -3, 4), tfSimdLoad_i32x4(0, 0, 0, 0)},
      // Zero comparison:
      {tfSimdLoad_f32x4(0, 0, 0, 0), tfSimdLoad_f32x4(0, 0, 0, 0), tfSimdLoad_i32x4(0, 0, 0, 0)},
  };
  for(size_t i = 0; i < TF_ARRAY_COUNT(tests); i++) {
      Tsimd_i32x4_t result = tfSimd_f32x4_To_i32x4(tfSimdCmpNeq_f32x4(tests[i].a, tests[i].b));
      DLOGF(LogLevel::eDEBUG, LOG_FORMAT_SIMD_32x4i(result));
      EXPECT_TRUE(tfSimdCmpAllEq_i32x4(result, tests[i].test));
  }
}

UTEST(Tsimd_f32x4_t, tfSimdCmpGtEq_f32x4)
{
  struct {
    Tsimd_f32x4_t a;
    Tsimd_f32x4_t b;
    Tsimd_i32x4_t test;
  } tests[] = {
     // Mixed values:
      {tfSimdLoad_f32x4(12, 13, 14, 15), tfSimdLoad_f32x4(0, 0, 0, 0), tfSimdLoad_i32x4(-1, -1, -1, -1)},
      // All elements greater or equal:
      {tfSimdLoad_f32x4(2, 3, 4, 5), tfSimdLoad_f32x4(1, 2, 3, 4), tfSimdLoad_i32x4(-1, -1, -1, -1)},
      // All elements equal:
      {tfSimdLoad_f32x4(1, 1, 1, 1), tfSimdLoad_f32x4(1, 1, 1, 1), tfSimdLoad_i32x4(-1, -1, -1, -1)},
      // All elements less:
      {tfSimdLoad_f32x4(1, 2, 3, 4), tfSimdLoad_f32x4(2, 3, 4, 5), tfSimdLoad_i32x4(0, 0, 0, 0)},
      // Mixed positive and negative values:
      {tfSimdLoad_f32x4(-1, 2, -3, 4), tfSimdLoad_f32x4(-2, 1, -4, 3), tfSimdLoad_i32x4(-1, -1, -1, -1)},
      // Zero comparison:
      {tfSimdLoad_f32x4(0, 0, 0, 0), tfSimdLoad_f32x4(0, 0, 0, 0), tfSimdLoad_i32x4(-1, -1, -1, -1)},
  };
  for(size_t i = 0; i < TF_ARRAY_COUNT(tests); i++) {
      Tsimd_i32x4_t result = tfSimd_f32x4_To_i32x4(tfSimdCmpGtEq_f32x4(tests[i].a, tests[i].b));
      DLOGF(LogLevel::eDEBUG, LOG_FORMAT_SIMD_32x4i(result));
      EXPECT_TRUE(tfSimdCmpAllEq_i32x4(result, tests[i].test));
  }
}

UTEST(Tsimd_f32x4_t, tfSimdCmpLt_f32x4)
{
  struct {
    Tsimd_f32x4_t a;
    Tsimd_f32x4_t b;
    Tsimd_i32x4_t test;
  } tests[] = {
      // Mixed values:
      {tfSimdLoad_f32x4(0, -1, 1, 0), tfSimdLoad_f32x4(1, 0, -1, 0), tfSimdLoad_i32x4(-1, -1, 0, 0)},
      // All elements less:
      {tfSimdLoad_f32x4(1, 2, 3, 4), tfSimdLoad_f32x4(2, 3, 4, 5), tfSimdLoad_i32x4(-1, -1, -1, -1)},
      // All elements equal:
      {tfSimdLoad_f32x4(1, 1, 1, 1), tfSimdLoad_f32x4(1, 1, 1, 1), tfSimdLoad_i32x4(0, 0, 0, 0)},
      // All elements greater:
      {tfSimdLoad_f32x4(2, 3, 4, 5), tfSimdLoad_f32x4(1, 2, 3, 4), tfSimdLoad_i32x4(0, 0, 0, 0)},
      // Mixed positive and negative values:
      {tfSimdLoad_f32x4(-2, 1, -4, 3), tfSimdLoad_f32x4(-1, 2, -3, 4), tfSimdLoad_i32x4(-1, -1, -1, -1)},
      // Zero comparison:
      {tfSimdLoad_f32x4(0, 0, 0, 0), tfSimdLoad_f32x4(0, 0, 0, 0), tfSimdLoad_i32x4(0, 0, 0, 0)},
  };
  for(size_t i = 0; i < TF_ARRAY_COUNT(tests); i++) {
      Tsimd_i32x4_t result = tfSimd_f32x4_To_i32x4(tfSimdCmpLt_f32x4(tests[i].a, tests[i].b));
      DLOGF(LogLevel::eDEBUG, LOG_FORMAT_SIMD_32x4i(result));
      EXPECT_TRUE(tfSimdCmpAllEq_i32x4(result, tests[i].test));
  }
}

UTEST(Tsimd_f32x4_t, tfSimdCmpLtEq_f32x4)
{
  struct {
    Tsimd_f32x4_t a;
    Tsimd_f32x4_t b;
    Tsimd_i32x4_t test;
  } tests[] = {
      // Mixed values:
      {tfSimdLoad_f32x4(0, -1, 1, 0), tfSimdLoad_f32x4(1, 0, -1, 0), tfSimdLoad_i32x4(-1, -1, 0, -1)},
      // All elements less or equal:
      {tfSimdLoad_f32x4(1, 2, 3, 4), tfSimdLoad_f32x4(2, 3, 4, 5), tfSimdLoad_i32x4(-1, -1, -1, -1)},
      // All elements equal:
      {tfSimdLoad_f32x4(1, 1, 1, 1), tfSimdLoad_f32x4(1, 1, 1, 1), tfSimdLoad_i32x4(-1, -1, -1, -1)},
      // All elements greater:
      {tfSimdLoad_f32x4(2, 3, 4, 5), tfSimdLoad_f32x4(1, 2, 3, 4), tfSimdLoad_i32x4(0, 0, 0, 0)},
      // Mixed positive and negative values:
      {tfSimdLoad_f32x4(-2, 1, -4, 3), tfSimdLoad_f32x4(-1, 2, -3, 4), tfSimdLoad_i32x4(-1, -1, -1, -1)},
      // Zero comparison:
      {tfSimdLoad_f32x4(0, 0, 0, 0), tfSimdLoad_f32x4(0, 0, 0, 0), tfSimdLoad_i32x4(-1, -1, -1, -1)},
  };
  for(size_t i = 0; i < TF_ARRAY_COUNT(tests); i++) {
      Tsimd_i32x4_t result = tfSimd_f32x4_To_i32x4(tfSimdCmpLtEq_f32x4(tests[i].a, tests[i].b));
      DLOGF(LogLevel::eDEBUG, LOG_FORMAT_SIMD_32x4i(result));
      EXPECT_TRUE(tfSimdCmpAllEq_i32x4(result, tests[i].test));
  }
}


UTEST(Tsimd_i32x4_t, tfSimdCmpGt_i32x4)
{
  struct {
    Tsimd_i32x4_t a;
    Tsimd_i32x4_t b;
    Tsimd_i32x4_t test;
  } tests[] = {
      // Mixed values:
      {tfSimdLoad_i32x4(0, -1, 1, 0), tfSimdLoad_i32x4(1, 0, -1, 0), tfSimdLoad_i32x4(0, 0, -1, 0)},
      // All elements greater:
      {tfSimdLoad_i32x4(2, 3, 4, 5), tfSimdLoad_i32x4(1, 2, 3, 4), tfSimdLoad_i32x4(-1, -1, -1, -1)},
      // All elements equal:
      {tfSimdLoad_i32x4(1, 1, 1, 1), tfSimdLoad_i32x4(1, 1, 1, 1), tfSimdLoad_i32x4(0, 0, 0, 0)},
      // All elements less:
      {tfSimdLoad_i32x4(1, 2, 3, 4), tfSimdLoad_i32x4(2, 3, 4, 5), tfSimdLoad_i32x4(0, 0, 0, 0)},
      // Mixed positive and negative values:
      {tfSimdLoad_i32x4(-1, 2, -3, 4), tfSimdLoad_i32x4(-2, 1, -4, 3), tfSimdLoad_i32x4(-1, -1, -1, -1)},
      // Zero comparison:
      {tfSimdLoad_i32x4(0, 0, 0, 0), tfSimdLoad_i32x4(0, 0, 0, 0), tfSimdLoad_i32x4(0, 0, 0, 0)},
  };
  for(size_t i = 0; i < TF_ARRAY_COUNT(tests); i++) {
      Tsimd_i32x4_t result = tfSimdCmpGt_i32x4(tests[i].a, tests[i].b);
      DLOGF(LogLevel::eDEBUG, LOG_FORMAT_SIMD_32x4i(result));
      EXPECT_TRUE(tfSimdCmpAllEq_i32x4(result, tests[i].test));
  }
}

UTEST(Tsimd_i32x4_t, tfSimdCmpGtEq_i32x4)
{
  struct {
    Tsimd_i32x4_t a;
    Tsimd_i32x4_t b;
    Tsimd_i32x4_t test;
  } tests[] = {
      // Mixed values:
      {tfSimdLoad_i32x4(0, -1, 1, 0), tfSimdLoad_i32x4(1, 0, -1, 0), tfSimdLoad_i32x4(0, 0, -1, -1)},
      // All elements greater or equal:
      {tfSimdLoad_i32x4(2, 3, 4, 5), tfSimdLoad_i32x4(1, 2, 3, 4), tfSimdLoad_i32x4(-1, -1, -1, -1)},
      // All elements equal:
      {tfSimdLoad_i32x4(1, 1, 1, 1), tfSimdLoad_i32x4(1, 1, 1, 1), tfSimdLoad_i32x4(-1, -1, -1, -1)},
      // All elements less:
      {tfSimdLoad_i32x4(1, 2, 3, 4), tfSimdLoad_i32x4(2, 3, 4, 5), tfSimdLoad_i32x4(0, 0, 0, 0)},
      // Mixed positive and negative values:
      {tfSimdLoad_i32x4(-1, 2, -3, 4), tfSimdLoad_i32x4(-2, 1, -4, 3), tfSimdLoad_i32x4(-1, -1, -1, -1)},
      // Zero comparison:
      {tfSimdLoad_i32x4(0, 0, 0, 0), tfSimdLoad_i32x4(0, 0, 0, 0), tfSimdLoad_i32x4(-1, -1, -1, -1)},
  };
  for(size_t i = 0; i < TF_ARRAY_COUNT(tests); i++) {
      Tsimd_i32x4_t result = tfSimdCmpGtEq_i32x4(tests[i].a, tests[i].b);
      DLOGF(LogLevel::eDEBUG, LOG_FORMAT_SIMD_32x4i(result));
      EXPECT_TRUE(tfSimdCmpAllEq_i32x4(result, tests[i].test));
  }
}

UTEST(Tsimd_i32x4_t, tfSimdCmpLtEq_i32x4)
{
  struct {
    Tsimd_i32x4_t a;
    Tsimd_i32x4_t b;
    Tsimd_i32x4_t test;
  } tests[] = {
      // Mixed values:
      {tfSimdLoad_i32x4(0, -1, 1, 0), tfSimdLoad_i32x4(1, 0, -1, 0), tfSimdLoad_i32x4(-1, -1, 0, -1)},
      // All elements less or equal:
      {tfSimdLoad_i32x4(1, 2, 3, 4), tfSimdLoad_i32x4(2, 3, 4, 5), tfSimdLoad_i32x4(-1, -1, -1, -1)},
      // All elements equal:
      {tfSimdLoad_i32x4(1, 1, 1, 1), tfSimdLoad_i32x4(1, 1, 1, 1), tfSimdLoad_i32x4(-1, -1, -1, -1)},
      // All elements greater:
      {tfSimdLoad_i32x4(2, 3, 4, 5), tfSimdLoad_i32x4(1, 2, 3, 4), tfSimdLoad_i32x4(0, 0, 0, 0)},
      // Mixed positive and negative values:
      {tfSimdLoad_i32x4(-1, 2, -3, 4), tfSimdLoad_i32x4(-2, 1, -4, 3), tfSimdLoad_i32x4(0, 0, 0, 0)},
      // Zero comparison:
      {tfSimdLoad_i32x4(0, 0, 0, 0), tfSimdLoad_i32x4(0, 0, 0, 0), tfSimdLoad_i32x4(-1, -1, -1, -1)},
  };
  for(size_t i = 0; i < TF_ARRAY_COUNT(tests); i++) {
      Tsimd_i32x4_t result = tfSimdCmpLtEq_i32x4(tests[i].a, tests[i].b);
      DLOGF(LogLevel::eDEBUG, LOG_FORMAT_SIMD_32x4i(result));
      EXPECT_TRUE(tfSimdCmpAllEq_i32x4(result, tests[i].test));
  }
}

UTEST(Tsimd_i32x4_t, tfSimdCmpLt_i32x4)
{
  struct {
    Tsimd_i32x4_t a;
    Tsimd_i32x4_t b;
    Tsimd_i32x4_t test;
  } tests[] = {
      // Mixed values:
      {tfSimdLoad_i32x4(0, -1, 1, 0), tfSimdLoad_i32x4(1, 0, -1, 0), tfSimdLoad_i32x4(-1, -1, 0, 0)},
      // All elements less:
      {tfSimdLoad_i32x4(1, 2, 3, 4), tfSimdLoad_i32x4(2, 3, 4, 5), tfSimdLoad_i32x4(-1, -1, -1, -1)},
      // All elements equal:
      {tfSimdLoad_i32x4(1, 1, 1, 1), tfSimdLoad_i32x4(1, 1, 1, 1), tfSimdLoad_i32x4(0, 0, 0, 0)},
      // All elements greater:
      {tfSimdLoad_i32x4(2, 3, 4, 5), tfSimdLoad_i32x4(1, 2, 3, 4), tfSimdLoad_i32x4(0, 0, 0, 0)},
      // Mixed positive and negative values:
      {tfSimdLoad_i32x4(-1, 2, -3, 4), tfSimdLoad_i32x4(-2, 1, -4, 3), tfSimdLoad_i32x4(0, 0, 0, 0)},
      // Zero comparison:
      {tfSimdLoad_i32x4(0, 0, 0, 0), tfSimdLoad_i32x4(0, 0, 0, 0), tfSimdLoad_i32x4(0, 0, 0, 0)},
  };
  for(size_t i = 0; i < TF_ARRAY_COUNT(tests); i++) {
      Tsimd_i32x4_t result = tfSimdCmpLt_i32x4(tests[i].a, tests[i].b);
      DLOGF(LogLevel::eDEBUG, LOG_FORMAT_SIMD_32x4i(result));
      EXPECT_TRUE(tfSimdCmpAllEq_i32x4(result, tests[i].test));
  }
}


UTEST(Tsimd_i32x4_t, tfSimdCmpEq_i32x4)
{
  struct {
    Tsimd_i32x4_t a;
    Tsimd_i32x4_t b;
    Tsimd_i32x4_t test;
  } tests[] = {
      // Mixed values:
      {tfSimdLoad_i32x4(0, -1, 1, 0), tfSimdLoad_i32x4(1, 0, -1, 0), tfSimdLoad_i32x4(0, 0, 0, -1)},
      // All elements equal:
      {tfSimdLoad_i32x4(1, 1, 1, 1), tfSimdLoad_i32x4(1, 1, 1, 1), tfSimdLoad_i32x4(-1, -1, -1, -1)},
      // All elements not equal:
      {tfSimdLoad_i32x4(2, 3, 4, 5), tfSimdLoad_i32x4(1, 2, 3, 4), tfSimdLoad_i32x4(0, 0, 0, 0)},
      // Mixed positive and negative values:
      {tfSimdLoad_i32x4(-1, 2, -3, 4), tfSimdLoad_i32x4(-1, 2, -3, 4), tfSimdLoad_i32x4(-1, -1, -1, -1)},
      // Zero comparison:
      {tfSimdLoad_i32x4(0, 0, 0, 0), tfSimdLoad_i32x4(0, 0, 0, 0), tfSimdLoad_i32x4(-1, -1, -1, -1)},
  };
  for(size_t i = 0; i < TF_ARRAY_COUNT(tests); i++) {
      Tsimd_i32x4_t result = tfSimdCmpEq_i32x4(tests[i].a, tests[i].b);
      DLOGF(LogLevel::eDEBUG, LOG_FORMAT_SIMD_32x4i(result));
      EXPECT_TRUE(tfSimdCmpAllEq_i32x4(result, tests[i].test));
  }
}


UTEST(Tsimd_f32x4_t, tfSimdCmpAllGt_f32x4)
{
    EXPECT_TRUE(tfSimdCmpAllGt_f32x4(tfSimdLoad_f32x4(16, 16, 17.1f, 13.0f), tfSimdLoad_f32x4(2, 3, 4, 5)));
    EXPECT_FALSE(tfSimdCmpAllGt_f32x4(tfSimdLoad_f32x4(2.0f, 0, 0, 0), tfSimdLoad_f32x4(2.0f, 3, 4, 5)));
    EXPECT_FALSE(tfSimdCmpAllGt_f32x4(tfSimdLoad_f32x4(5, 6, 7, 8), tfSimdLoad_f32x4(4, 7, 6, 9)));
    EXPECT_FALSE(tfSimdCmpAllGt_f32x4(tfSimdLoad_f32x4(1, 1, 1, 1), tfSimdLoad_f32x4(1, 1, 1, 1)));
    EXPECT_FALSE(tfSimdCmpAllGt_f32x4(tfSimdLoad_f32x4(1, 2, 3, 4), tfSimdLoad_f32x4(2, 3, 4, 5)));
    EXPECT_TRUE(tfSimdCmpAllGt_f32x4(tfSimdLoad_f32x4(1, -2, 3, -4), tfSimdLoad_f32x4(0, -3, 2, -5)));
    EXPECT_FALSE(tfSimdCmpAllGt_f32x4(tfSimdLoad_f32x4(0, 0, 0, 0), tfSimdLoad_f32x4(0, 0, 0, 0)));
}

UTEST(Tsimd_f32x4_t, tfSimdCmpAllEq_f32x4)
{
    EXPECT_TRUE(tfSimdCmpAllEq_f32x4(tfSimdLoad_f32x4(1, 1, 1, 1), tfSimdLoad_f32x4(1, 1, 1, 1)));
    EXPECT_FALSE(tfSimdCmpAllEq_f32x4(tfSimdLoad_f32x4(1, 2, 3, 4), tfSimdLoad_f32x4(1, 2, 3, 5)));
    EXPECT_TRUE(tfSimdCmpAllEq_f32x4(tfSimdLoad_f32x4(0, 0, 0, 0), tfSimdLoad_f32x4(0, 0, 0, 0)));
}

UTEST(Tsimd_f32x4_t, tfSimdCmpAllNeq_f32x4)
{
    EXPECT_FALSE(tfSimdCmpAllNeq_f32x4(tfSimdLoad_f32x4(1, 1, 1, 1), tfSimdLoad_f32x4(1, 1, 1, 1)));
    EXPECT_FALSE(tfSimdCmpAllLt_f32x4(tfSimdLoad_f32x4(0,0,0,0), tfSimdLoad_f32x4(0, 12, 33, 44)));
    EXPECT_TRUE(tfSimdCmpAllNeq_f32x4(tfSimdLoad_f32x4(32, 45, 13, 4), tfSimdLoad_f32x4(1, 2, 3, 5)));
    EXPECT_FALSE(tfSimdCmpAllNeq_f32x4(tfSimdLoad_f32x4(0, 0, 0, 0), tfSimdLoad_f32x4(0, 0, 0, 0)));
}

UTEST(Tsimd_f32x4_t, tfSimdCmpAllGtEq_f32x4)
{
    EXPECT_TRUE(tfSimdCmpAllGtEq_f32x4(tfSimdLoad_f32x4(2, 3, 4, 5), tfSimdLoad_f32x4(1, 2, 3, 4)));
    EXPECT_FALSE(tfSimdCmpAllGtEq_f32x4(tfSimdLoad_f32x4(1, 2, 3, 4), tfSimdLoad_f32x4(1, 2, 3, 5)));
    EXPECT_TRUE(tfSimdCmpAllGtEq_f32x4(tfSimdLoad_f32x4(1, 1, 1, 1), tfSimdLoad_f32x4(1, 1, 1, 1)));
}

UTEST(Tsimd_f32x4_t, tfSimdCmpAllLt_f32x4)
{
    EXPECT_TRUE(tfSimdCmpAllLt_f32x4(tfSimdLoad_f32x4(1, 2, 3, 4), tfSimdLoad_f32x4(2, 3, 4, 5)));
    EXPECT_FALSE(tfSimdCmpAllLt_f32x4(tfSimdLoad_f32x4(2, 3, 4, 5), tfSimdLoad_f32x4(1, 2, 3, 4)));
    EXPECT_FALSE(tfSimdCmpAllLt_f32x4(tfSimdLoad_f32x4(1, 1, 1, 1), tfSimdLoad_f32x4(1, 1, 1, 1)));
}

UTEST(Tsimd_f32x4_t, tfSimdCmpAllLtEq_f32x4)
{
    EXPECT_TRUE(tfSimdCmpAllLtEq_f32x4(tfSimdLoad_f32x4(1, 2, 3, 4), tfSimdLoad_f32x4(2, 3, 4, 5)));
    EXPECT_FALSE(tfSimdCmpAllLtEq_f32x4(tfSimdLoad_f32x4(2, 3, 4, 5), tfSimdLoad_f32x4(1, 2, 3, 4)));
    EXPECT_TRUE(tfSimdCmpAllLtEq_f32x4(tfSimdLoad_f32x4(1, 1, 1, 1), tfSimdLoad_f32x4(1, 1, 1, 1)));
}

UTEST(Tsimd_i32x4_t, tfSimdCmpAllGt_i32x4)
{
    EXPECT_TRUE(tfSimdCmpAllGt_i32x4(tfSimdLoad_i32x4(16, 16, 17, 13), tfSimdLoad_i32x4(2, 3, 4, 5)));
    EXPECT_FALSE(tfSimdCmpAllGt_i32x4(tfSimdLoad_i32x4(2, 0, 0, 0), tfSimdLoad_i32x4(2, 3, 4, 5)));
    EXPECT_FALSE(tfSimdCmpAllGt_i32x4(tfSimdLoad_i32x4(5, 6, 7, 8), tfSimdLoad_i32x4(4, 7, 6, 9)));
    EXPECT_FALSE(tfSimdCmpAllGt_i32x4(tfSimdLoad_i32x4(1, 1, 1, 1), tfSimdLoad_i32x4(1, 1, 1, 1)));
    EXPECT_FALSE(tfSimdCmpAllGt_i32x4(tfSimdLoad_i32x4(1, 2, 3, 4), tfSimdLoad_i32x4(2, 3, 4, 5)));
    EXPECT_TRUE(tfSimdCmpAllGt_i32x4(tfSimdLoad_i32x4(1, -2, 3, -4), tfSimdLoad_i32x4(0, -3, 2, -5)));
    EXPECT_FALSE(tfSimdCmpAllGt_i32x4(tfSimdLoad_i32x4(0, 0, 0, 0), tfSimdLoad_i32x4(0, 0, 0, 0)));
}

UTEST(Tsimd_i32x4_t, tfSimdCmpAllEq_i32x4)
{
    EXPECT_TRUE(tfSimdCmpAllEq_i32x4(tfSimdLoad_i32x4(1, 1, 1, 1), tfSimdLoad_i32x4(1, 1, 1, 1)));
    EXPECT_FALSE(tfSimdCmpAllEq_i32x4(tfSimdLoad_i32x4(1, 2, 3, 4), tfSimdLoad_i32x4(1, 2, 3, 5)));
    EXPECT_TRUE(tfSimdCmpAllEq_i32x4(tfSimdLoad_i32x4(0, 0, 0, 0), tfSimdLoad_i32x4(0, 0, 0, 0)));
}

UTEST(Tsimd_i32x4_t, tfSimdCmpAllNeq_i32x4)
{
    EXPECT_FALSE(tfSimdCmpAllNeq_i32x4(tfSimdLoad_i32x4(1, 1, 1, 1), tfSimdLoad_i32x4(1, 1, 1, 1)));
    EXPECT_FALSE(tfSimdCmpAllNeq_i32x4(tfSimdLoad_i32x4(0, 0, 0, 0), tfSimdLoad_i32x4(0, 12, 33, 44)));
    EXPECT_TRUE(tfSimdCmpAllNeq_i32x4(tfSimdLoad_i32x4(32, 45, 13, 4), tfSimdLoad_i32x4(1, 2, 3, 5)));
    EXPECT_FALSE(tfSimdCmpAllNeq_i32x4(tfSimdLoad_i32x4(0, 0, 0, 0), tfSimdLoad_i32x4(0, 0, 0, 0)));
}

UTEST(Tsimd_i32x4_t, tfSimdCmpAllGtEq_i32x4)
{
    EXPECT_TRUE(tfSimdCmpAllGtEq_i32x4(tfSimdLoad_i32x4(2, 3, 4, 5), tfSimdLoad_i32x4(1, 2, 3, 4)));
    EXPECT_FALSE(tfSimdCmpAllGtEq_i32x4(tfSimdLoad_i32x4(1, 2, 3, 4), tfSimdLoad_i32x4(1, 2, 3, 5)));
    EXPECT_TRUE(tfSimdCmpAllGtEq_i32x4(tfSimdLoad_i32x4(1, 1, 1, 1), tfSimdLoad_i32x4(1, 1, 1, 1)));
}

UTEST(Tsimd_i32x4_t, tfSimdCmpAllLt_i32x4)
{
    EXPECT_TRUE(tfSimdCmpAllLt_i32x4(tfSimdLoad_i32x4(1, 2, 3, 4), tfSimdLoad_i32x4(2, 3, 4, 5)));
    EXPECT_FALSE(tfSimdCmpAllLt_i32x4(tfSimdLoad_i32x4(2, 3, 4, 5), tfSimdLoad_i32x4(1, 2, 3, 4)));
    EXPECT_FALSE(tfSimdCmpAllLt_i32x4(tfSimdLoad_i32x4(1, 1, 1, 1), tfSimdLoad_i32x4(1, 1, 1, 1)));
}

UTEST(Tsimd_i32x4_t, tfSimdCmpAllLtEq_i32x4)
{
    EXPECT_TRUE(tfSimdCmpAllLtEq_i32x4(tfSimdLoad_i32x4(1, 2, 3, 4), tfSimdLoad_i32x4(2, 3, 4, 5)));
    EXPECT_FALSE(tfSimdCmpAllLtEq_i32x4(tfSimdLoad_i32x4(2, 3, 4, 5), tfSimdLoad_i32x4(1, 2, 3, 4)));
    EXPECT_TRUE(tfSimdCmpAllLtEq_i32x4(tfSimdLoad_i32x4(1, 1, 1, 1), tfSimdLoad_i32x4(1, 1, 1, 1)));
}


UTEST(Tsimd_i32x4_t, tfSimdNot_i32x4)
{
    struct {
        Tsimd_i32x4_t input;
        Tsimd_i32x4_t expected;
    } tests[] = {
        {tfSimdLoad_i32x4(0, 0, 0, 0), tfSimdLoad_i32x4(~0, ~0, ~0, ~0)},
        {tfSimdLoad_i32x4(1, 2, 3, 4), tfSimdLoad_i32x4(~1, ~2, ~3, ~4)},
        {tfSimdLoad_i32x4(-1, -2, -3, -4), tfSimdLoad_i32x4(~-1, ~-2, ~-3, ~-4)},
        {tfSimdLoad_i32x4(123, 456, 789, 101112), tfSimdLoad_i32x4(~123, ~456, ~789, ~101112)},
        {tfSimdLoad_i32x4(0xFFFFFFFF, 0xFFFFFFFE, 0xFFFFFFFD, 0xFFFFFFFC), tfSimdLoad_i32x4(~0xFFFFFFFF, ~0xFFFFFFFE, ~0xFFFFFFFD, ~0xFFFFFFFC)},
    };

    for (size_t i = 0; i < TF_ARRAY_COUNT(tests); i++) {
        Tsimd_i32x4_t result = tfSimdNot_i32x4(tests[i].input);
        EXPECT_TRUE(tfSimdCmpAllEq_i32x4(result, tests[i].expected));
    }
}


UTEST(Tsimd_i32x4_t, tfSimdAnd_i32x4)
{
  struct {
    Tsimd_i32x4_t arg1;
    Tsimd_i32x4_t arg2;
    Tsimd_i32x4_t expected;
  } tests[] = {
    {tfSimdLoad_i32x4(0, 0, 0, 0), tfSimdLoad_i32x4(0, 0, 0, 0), tfSimdLoad_i32x4(0, 0, 0, 0)},
    {tfSimdLoad_i32x4(1, 2, 3, 4), tfSimdLoad_i32x4(4, 3, 2, 1), tfSimdLoad_i32x4(0, 2, 2, 0)},
    {tfSimdLoad_i32x4(-1, -2, -3, -4), tfSimdLoad_i32x4(1, 2, 3, 4), tfSimdLoad_i32x4(1, 2, 1, 4)},
    {tfSimdLoad_i32x4(0xFFFFFFFF, 0xFFFFFFFE, 0xFFFFFFFD, 0xFFFFFFFC), tfSimdLoad_i32x4(0xFFFFFFFB, 0xFFFFFFFA, 0xFFFFFFF9, 0xFFFFFFF8), tfSimdLoad_i32x4(0xFFFFFFFB, 0xFFFFFFFA, 0xFFFFFFF9, 0xFFFFFFF8)},
  };

  for (size_t i = 0; i < TF_ARRAY_COUNT(tests); i++) {
    Tsimd_i32x4_t result = tfSimdAnd_i32x4(tests[i].arg1, tests[i].arg2);
    DLOGF(LogLevel::eDEBUG, LOG_FORMAT_SIMD_32x4i(result));
    EXPECT_TRUE(tfSimdCmpAllEq_i32x4(result, tests[i].expected));
  }
}


UTEST(Tsimd_i32x4_t, tfSimdAndNot_i32x4)
{
  struct {
    Tsimd_i32x4_t arg1;
    Tsimd_i32x4_t arg2;
    Tsimd_i32x4_t expected;
  } tests[] = {
    {tfSimdLoad_i32x4(0, 0, 0, 0), tfSimdLoad_i32x4(0, 0, 0, 0), tfSimdLoad_i32x4(0, 0, 0, 0)},
    {tfSimdLoad_i32x4(1, 2, 3, 4), tfSimdLoad_i32x4(4, 3, 2, 1), tfSimdLoad_i32x4(4, 1, 0, 1)},
    {tfSimdLoad_i32x4(-1, -2, -3, -4), tfSimdLoad_i32x4(1, 2, 3, 4), tfSimdLoad_i32x4(0, 0, 2, 0)},
    {tfSimdLoad_i32x4(123, 456, 789, 101112), tfSimdLoad_i32x4(654, 321, 987, 654321), tfSimdLoad_i32x4(644, 1, 202, 553217)},
  };

  for (size_t i = 0; i < TF_ARRAY_COUNT(tests); i++) {
    Tsimd_i32x4_t result = tfSimdAndNot_i32x4(tests[i].arg1, tests[i].arg2);
    DLOGF(LogLevel::eDEBUG, LOG_FORMAT_SIMD_32x4i(result));
    EXPECT_TRUE(tfSimdCmpAllEq_i32x4(result, tests[i].expected));
  }
}

UTEST(Tsimd_i32x4_t, tfSimdOr_i32x4)
{
  struct {
    Tsimd_i32x4_t arg1;
    Tsimd_i32x4_t arg2;
    Tsimd_i32x4_t expected;
  } tests[] = {
    {tfSimdLoad_i32x4(0, 0, 0, 0), tfSimdLoad_i32x4(0, 0, 0, 0), tfSimdLoad_i32x4(0, 0, 0, 0)},
    {tfSimdLoad_i32x4(1, 2, 3, 4), tfSimdLoad_i32x4(4, 3, 2, 1), tfSimdLoad_i32x4(5, 3, 3, 5)},
    {tfSimdLoad_i32x4(-1, -2, -3, -4), tfSimdLoad_i32x4(1, 2, 3, 4), tfSimdLoad_i32x4(-1, -2, -1, -4)},
  };

  for (size_t i = 0; i < TF_ARRAY_COUNT(tests); i++) {
    Tsimd_i32x4_t result = tfSimdOr_i32x4(tests[i].arg1, tests[i].arg2);
    DLOGF(LogLevel::eDEBUG, LOG_FORMAT_SIMD_32x4i(result));
    EXPECT_TRUE(tfSimdCmpAllEq_i32x4(result, tests[i].expected));
  }
}


UTEST(Tsimd_i32x4_t, tfSimdXor_i32x4)
{
  struct {
    Tsimd_i32x4_t arg1;
    Tsimd_i32x4_t arg2;
    Tsimd_i32x4_t expected;
  } tests[] = {
    {tfSimdLoad_i32x4(0, 0, 0, 0), tfSimdLoad_i32x4(0, 0, 0, 0), tfSimdLoad_i32x4(0, 0, 0, 0)},
    {tfSimdLoad_i32x4(1, 2, 3, 4), tfSimdLoad_i32x4(4, 3, 2, 1), tfSimdLoad_i32x4(5, 1, 1, 5)},
    {tfSimdLoad_i32x4(-1, -2, -3, -4), tfSimdLoad_i32x4(1, 2, 3, 4), tfSimdLoad_i32x4(-2, -4, -2, -8)},
    {tfSimdLoad_i32x4(123, 456, 789, 101112), tfSimdLoad_i32x4(654, 321, 987, 654321), tfSimdLoad_i32x4(757,137,206,553225)},
  };

  for (size_t i = 0; i < TF_ARRAY_COUNT(tests); i++) {
    Tsimd_i32x4_t result = tfSimdXor_i32x4(tests[i].arg1, tests[i].arg2);
    DLOGF(LogLevel::eDEBUG, LOG_FORMAT_SIMD_32x4i(result));
    EXPECT_TRUE(tfSimdCmpAllEq_i32x4(result, tests[i].expected));
  }
}

UTEST(Tsimd_f32x4_t, tfSimdAdd_f32x4)
{
  struct {
    Tsimd_f32x4_t a;
    Tsimd_f32x4_t b;
    Tsimd_f32x4_t expected;
  } tests[] = {
    {tfSimdLoad_f32x4(0.0f, 0.0f, 0.0f, 0.0f), tfSimdLoad_f32x4(0.0f, 0.0f, 0.0f, 0.0f), tfSimdLoad_f32x4(0.0f, 0.0f, 0.0f, 0.0f)},
    {tfSimdLoad_f32x4(1.0f, 2.0f, 3.0f, 4.0f), tfSimdLoad_f32x4(4.0f, 3.0f, 2.0f, 1.0f), tfSimdLoad_f32x4(5.0f, 5.0f, 5.0f, 5.0f)},
    {tfSimdLoad_f32x4(-1.0f, -2.0f, -3.0f, -4.0f), tfSimdLoad_f32x4(1.0f, 2.0f, 3.0f, 4.0f), tfSimdLoad_f32x4(0.0f, 0.0f, 0.0f, 0.0f)},
    {tfSimdLoad_f32x4(123.45f, 456.78f, 789.01f, 101112.13f), tfSimdLoad_f32x4(654.32f, 321.09f, 987.65f, 654321.98f), tfSimdLoad_f32x4(777.77f, 777.87f, 1776.66f, 755434.11f)},
    {tfSimdLoad_f32x4(0.1f, 0.2f, 0.3f, 0.4f), tfSimdLoad_f32x4(0.9f, 0.8f, 0.7f, 0.6f), tfSimdLoad_f32x4(1.0f, 1.0f, 1.0f, 1.0f)},
  };

  for (size_t i = 0; i < TF_ARRAY_COUNT(tests); i++) {
    Tsimd_f32x4_t result = tfSimdAdd_f32x4(tests[i].a, tests[i].b);
    EXPECT_TRUE(tfSimdCmpAllEq_f32x4(result, tests[i].expected));
  }
}

UTEST(Tsimd_f32x4_t, tfSimdMul_f32x4)
{
  struct {
    Tsimd_f32x4_t a;
    Tsimd_f32x4_t b;
    Tsimd_f32x4_t expected;
  } tests[] = {
    {tfSimdLoad_f32x4(1.0f, 2.0f, 3.0f, 4.0f), tfSimdLoad_f32x4(1.0f, 2.0f, 3.0f, 4.0f), tfSimdLoad_f32x4(1.0f, 4.0f, 9.0f, 16.0f)},
    {tfSimdLoad_f32x4(0.0f, 0.0f, 0.0f, 0.0f), tfSimdLoad_f32x4(1.0f, 2.0f, 3.0f, 4.0f), tfSimdLoad_f32x4(0.0f, 0.0f, 0.0f, 0.0f)},
    {tfSimdLoad_f32x4(-1.0f, -2.0f, -3.0f, -4.0f), tfSimdLoad_f32x4(1.0f, 2.0f, 3.0f, 4.0f), tfSimdLoad_f32x4(-1.0f, -4.0f, -9.0f, -16.0f)},
    {tfSimdLoad_f32x4(1.5f, 2.5f, 3.5f, 4.5f), tfSimdLoad_f32x4(2.0f, 2.0f, 2.0f, 2.0f), tfSimdLoad_f32x4(3.0f, 5.0f, 7.0f, 9.0f)},
    {tfSimdLoad_f32x4(1.0f, 0.0f, -1.0f, 0.0f), tfSimdLoad_f32x4(0.0f, 1.0f, 0.0f, -1.0f), tfSimdLoad_f32x4(0.0f, 0.0f, 0.0f, 0.0f)},
  };

  for (size_t i = 0; i < TF_ARRAY_COUNT(tests); i++) {
    Tsimd_f32x4_t result = tfSimdMul_f32x4(tests[i].a, tests[i].b);
    EXPECT_TRUE(tfSimdCmpAllEq_f32x4(result, tests[i].expected));
  }
}

UTEST(Tsimd_f32x4_t, tfSimdDiv_f32x4)
{
  struct {
    Tsimd_f32x4_t a;
    Tsimd_f32x4_t b;
    Tsimd_f32x4_t expected;
  } tests[] = {
    {tfSimdLoad_f32x4(4.0f, 9.0f, 16.0f, 25.0f), tfSimdLoad_f32x4(2.0f, 3.0f, 4.0f, 5.0f), tfSimdLoad_f32x4(2.0f, 3.0f, 4.0f, 5.0f)},
    {tfSimdLoad_f32x4(1.0f, 1.0f, 1.0f, 1.0f), tfSimdLoad_f32x4(1.0f, 1.0f, 1.0f, 1.0f), tfSimdLoad_f32x4(1.0f, 1.0f, 1.0f, 1.0f)},
    {tfSimdLoad_f32x4(-4.0f, -9.0f, -16.0f, -25.0f), tfSimdLoad_f32x4(2.0f, 3.0f, 4.0f, 5.0f), tfSimdLoad_f32x4(-2.0f, -3.0f, -4.0f, -5.0f)},
    {tfSimdLoad_f32x4(0.0f, 0.0f, 0.0f, 0.0f), tfSimdLoad_f32x4(1.0f, 2.0f, 3.0f, 4.0f), tfSimdLoad_f32x4(0.0f, 0.0f, 0.0f, 0.0f)},
    {tfSimdLoad_f32x4(1.0f, 2.0f, 3.0f, 4.0f), tfSimdLoad_f32x4(1.0f, 2.0f, 3.0f, 4.0f), tfSimdLoad_f32x4(1.0f, 1.0f, 1.0f, 1.0f)},
  };

  for (size_t i = 0; i < TF_ARRAY_COUNT(tests); i++) {
    Tsimd_f32x4_t result = tfSimdDiv_f32x4(tests[i].a, tests[i].b);
    EXPECT_TRUE(tfSimdCmpAllEq_f32x4(result, tests[i].expected));
  }
}

UTEST(Tsimd_f32x4_t, tfSimdAbs_f32x4)
{
  struct {
    Tsimd_f32x4_t input;
    Tsimd_f32x4_t expected;
  } tests[] = {
    {tfSimdLoad_f32x4(-1.0f, -2.0f, -3.0f, -4.0f), tfSimdLoad_f32x4(1.0f, 2.0f, 3.0f, 4.0f)},
    {tfSimdLoad_f32x4(1.0f, -2.0f, 3.0f, -4.0f), tfSimdLoad_f32x4(1.0f, 2.0f, 3.0f, 4.0f)},
    {tfSimdLoad_f32x4(0.0f, -0.0f, 0.0f, -0.0f), tfSimdLoad_f32x4(0.0f, 0.0f, 0.0f, 0.0f)},
    {tfSimdLoad_f32x4(5.0f, -6.0f, 7.0f, -8.0f), tfSimdLoad_f32x4(5.0f, 6.0f, 7.0f, 8.0f)},
    {tfSimdLoad_f32x4(-9.0f, 10.0f, -11.0f, 12.0f), tfSimdLoad_f32x4(9.0f, 10.0f, 11.0f, 12.0f)},
  };

  for (size_t i = 0; i < TF_ARRAY_COUNT(tests); i++) {
    Tsimd_f32x4_t result = tfSimdAbs_f32x4(tests[i].input);
    EXPECT_TRUE(tfSimdCmpAllEq_f32x4(result, tests[i].expected));
  }
}

UTEST(Tsimd_f32x4_t, tfSimdMadd_f32x4)
{
  struct {
    Tsimd_f32x4_t a;
    Tsimd_f32x4_t b;
    Tsimd_f32x4_t c;
    Tsimd_f32x4_t expected;
  } tests[] = {
    {tfSimdLoad_f32x4(1.0f, 2.0f, 3.0f, 4.0f), tfSimdLoad_f32x4(5.0f, 6.0f, 7.0f, 8.0f), tfSimdLoad_f32x4(9.0f, 10.0f, 11.0f, 12.0f), tfSimdLoad_f32x4(14.0f, 22.0f, 32.0f, 44.0f)},
    {tfSimdLoad_f32x4(-1.0f, -2.0f, -3.0f, -4.0f), tfSimdLoad_f32x4(5.0f, 6.0f, 7.0f, 8.0f), tfSimdLoad_f32x4(9.0f, 10.0f, 11.0f, 12.0f), tfSimdLoad_f32x4(4.0f, -2.0f, -10.0f, -20.0f)},
    {tfSimdLoad_f32x4(0.0f, 0.0f, 0.0f, 0.0f), tfSimdLoad_f32x4(5.0f, 6.0f, 7.0f, 8.0f), tfSimdLoad_f32x4(9.0f, 10.0f, 11.0f, 12.0f), tfSimdLoad_f32x4(9.0f, 10.0f, 11.0f, 12.0f)},
    {tfSimdLoad_f32x4(1.0f, 2.0f, 3.0f, 4.0f), tfSimdLoad_f32x4(0.0f, 0.0f, 0.0f, 0.0f), tfSimdLoad_f32x4(9.0f, 10.0f, 11.0f, 12.0f), tfSimdLoad_f32x4(9.0f, 10.0f, 11.0f, 12.0f)},
    {tfSimdLoad_f32x4(1.0f, 2.0f, 3.0f, 4.0f), tfSimdLoad_f32x4(5.0f, 6.0f, 7.0f, 8.0f), tfSimdLoad_f32x4(0.0f, 0.0f, 0.0f, 0.0f), tfSimdLoad_f32x4(5.0f, 12.0f, 21.0f, 32.0f)},
  };

  for (size_t i = 0; i < TF_ARRAY_COUNT(tests); i++) {
    Tsimd_f32x4_t result = tfSimdMadd_f32x4(tests[i].a, tests[i].b, tests[i].c);
    EXPECT_TRUE(tfSimdCmpAllEq_f32x4(result, tests[i].expected));
  }
}

UTEST(Tsimd_f32x4_t, tfSimdDot_f32x4)
{
    Tsimd_f32x4_t a = tfSimdLoad_f32x4(1.0f, 2.0f, 3.0f, 4.0f);
    Tsimd_f32x4_t b = tfSimdLoad_f32x4(5.0f, 6.0f, 7.0f, 8.0f);
    Tsimd_f32x4_t result = tfSimdDot_f32x4(a, b);
    Tsimd_f32x4_t expected = tfSimdLoad_f32x4(70.0f, 70.0f, 70.0f, 70.0f); // 1*5 + 2*6 + 3*7 + 4*8 = 70

    EXPECT_TRUE(tfSimdCmpAllEq_f32x4(result, expected));
}

UTEST(Tsimd_f32x4_t, tfSimdDot_f32x4_f32)
{
    Tsimd_f32x4_t a = tfSimdLoad_f32x4(1.0f, 2.0f, 3.0f, 4.0f);
    Tsimd_f32x4_t b = tfSimdLoad_f32x4(5.0f, 6.0f, 7.0f, 8.0f);
    float result = tfSimdDot_f32x4_f32(a, b);
    float expected = 70.0f; // 1*5 + 2*6 + 3*7 + 4*8 = 70

    EXPECT_EQ(result, expected);
}

#include "Forge/Mem/TF_Memory.h"
#include "Forge/TF_FileSystem.h"
#include "Forge/TF_Log.h"
UTEST_STATE();
TF_UTEST_MAIN("TF_Simd4")

