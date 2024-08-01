/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */
#include "TF_TestMain.h"
#include "utest.h"

#include "Forge/Math/TF_SimdFloat.h"
#include "TF_MathUtils.h"

UTEST(TSimdFloat3 , tfLoadSimd3F)
{
  TSimdFloat3 value = tfLoadSimd3F(123.0,12.f,45.f);

  EXPECT_NEAR(tfGetElemSimd3F(value, 0), 123.0f, DEFAULT_EPSILON);
  EXPECT_NEAR(tfGetElemSimd3F(value, 1), 12.0f, DEFAULT_EPSILON);
  EXPECT_NEAR(tfGetElemSimd3F(value, 2), 45.0f, DEFAULT_EPSILON);

  EXPECT_NEAR(tfGetXSimd3F(value), 123.0f, DEFAULT_EPSILON);
  EXPECT_NEAR(tfGetYSimd3F(value), 12.0f, DEFAULT_EPSILON);
  EXPECT_NEAR(tfGetZSimd3F(value), 45.0f, DEFAULT_EPSILON);
}



#include "Forge/Mem/TF_Memory.h"
#include "Forge/TF_FileSystem.h"
#include "Forge/TF_Log.h"
UTEST_STATE();
TF_UTEST_MAIN("TF_Simd4")


