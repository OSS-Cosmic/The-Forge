/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */
#include "TF_TestMain.h"
#include "utest.h"

#include "Forge/Math/TF_SimdFloat4.h"
#include "TF_MathUtils.h"


UTEST(TSimdFloat4 , tfLoadSimd4F)
{
  TSimdFloat4 value = tfLoadSimd4F(123.0,12.f,45.f,12.5f);

  EXPECT_NEAR(tfGetElemSimd4F(value, 0), 123.0f, DEFAULT_EPSILON);
  EXPECT_NEAR(tfGetElemSimd4F(value, 1), 12.0f, DEFAULT_EPSILON);
  EXPECT_NEAR(tfGetElemSimd4F(value, 2), 45.0f, DEFAULT_EPSILON);
  EXPECT_NEAR(tfGetElemSimd4F(value, 3), 12.5f, DEFAULT_EPSILON);

  EXPECT_NEAR(tfGetXSimd4F(value), 123.0f, DEFAULT_EPSILON);
  EXPECT_NEAR(tfGetYSimd4F(value), 12.0f, DEFAULT_EPSILON);
  EXPECT_NEAR(tfGetZSimd4F(value), 45.0f, DEFAULT_EPSILON);
  EXPECT_NEAR(tfGetWSimd4F(value), 12.5f, DEFAULT_EPSILON);
}

UTEST(TSimdFloat4, tfGetRowSimd4x4F) {
    TSimdFloat4x4 mat =
        tfLoadSimd4x4F(1.0f, 2.0f, 3.0f, 4.0f, 
                       5.0f, 6.0f, 7.0f, 8.0f, 
                       9.0f, 10.0f, 11.0f, 12.0f, 
                       13.0f, 14.0f, 15.0f, 16.0f);

    EXPECT_TRUE(tfIsCloseSimd4F(tfGetRowSimd4x4F(mat, 0), tfLoadSimd4F(1.0f, 2.0f, 3.0f, 4.0f), DEFAULT_EPSILON));
    EXPECT_TRUE(tfIsCloseSimd4F(tfGetRowSimd4x4F(mat, 1), tfLoadSimd4F(5.0f, 6.0f, 7.0f, 8.0f), DEFAULT_EPSILON));
    EXPECT_TRUE(tfIsCloseSimd4F(tfGetRowSimd4x4F(mat, 2), tfLoadSimd4F(9.0f, 10.0f, 11.0f, 12.0f), DEFAULT_EPSILON));
    EXPECT_TRUE(tfIsCloseSimd4F(tfGetRowSimd4x4F(mat, 3), tfLoadSimd4F(13.0f, 14.0f, 15.0f, 16.0f), DEFAULT_EPSILON));
}

//UTEST(TSimdFloat4, tfIsCloseSimd3x4F) {
//    TSimdFloat3x4 mat =
//        tfLoadSimd3x4F(1.0f, 2.0f, 3.0f,  
//                       5.0f, 6.0f, 7.0f,  
//                       9.0f, 10.0f, 11.0f,  
//                       13.0f, 14.0f, 15.0f );
//
//    EXPECT_TRUE(tfIsCloseSimd3F(tfGetRowSimd3x4F(mat, 0), tfLoadSimd4F(1.0f, 2.0f, 3.0f, 4.0f), DEFAULT_EPSILON));
//    EXPECT_TRUE(tfIsCloseSimd3F(tfGetRowSimd3x4F(mat, 1), tfLoadSimd4F(5.0f, 6.0f, 7.0f, 8.0f), DEFAULT_EPSILON));
//    EXPECT_TRUE(tfIsCloseSimd3F(tfGetRowSimd3x4F(mat, 2), tfLoadSimd4F(9.0f, 10.0f, 11.0f, 12.0f), DEFAULT_EPSILON));
//    EXPECT_TRUE(tfIsCloseSimd3F(tfGetRowSimd3x4F(mat, 3), tfLoadSimd4F(13.0f, 14.0f, 15.0f, 16.0f), DEFAULT_EPSILON));
//}


#include "Forge/Mem/TF_Memory.h"
#include "Forge/TF_FileSystem.h"
#include "Forge/TF_Log.h"
UTEST_STATE();
TF_UTEST_MAIN("TF_Simd4")

