/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */
#include "TF_TestMain.h"
#include "utest.h"

#include "TF_MathUtils.h"
#include "Forge/Math/TF_Matrix.h"
#include "Forge/Math/TF_SimdFloat4.h"

#include "Forge/TF_Log.h"

static inline void debugPrintSimd4F(TSimdFloat4 input) {
  DLOGF(LogLevel::eDEBUG, "%.3f, %.3f, %.3f, %.3f",
          tfSimd4fSelectIndex0(input.mRow),
          tfSimd4fSelectIndex1(input.mRow),
          tfSimd4fSelectIndex2(input.mRow),
          tfSimd4fSelectIndex3(input.mRow));
}
static inline void debugPrintSimd4x4F(TSimdFloat4x4 input) {
    DLOGF(LogLevel::eDEBUG,"%.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f",
          tfSimd4fSelectIndex0(input.mCol0),
          tfSimd4fSelectIndex0(input.mCol1),
          tfSimd4fSelectIndex0(input.mCol2),
          tfSimd4fSelectIndex0(input.mCol3),

          tfSimd4fSelectIndex1(input.mCol0),
          tfSimd4fSelectIndex1(input.mCol1),
          tfSimd4fSelectIndex1(input.mCol2),
          tfSimd4fSelectIndex1(input.mCol3),
          
          tfSimd4fSelectIndex2(input.mCol0),
          tfSimd4fSelectIndex2(input.mCol1),
          tfSimd4fSelectIndex2(input.mCol2),
          tfSimd4fSelectIndex2(input.mCol3),
          
          tfSimd4fSelectIndex3(input.mCol0),
          tfSimd4fSelectIndex3(input.mCol1),
          tfSimd4fSelectIndex3(input.mCol2),
          tfSimd4fSelectIndex3(input.mCol3)
    );
}

UTEST(TF_Simd4, tfSetElemSimd4x4F) {
    TSimdFloat4x4 a = tfLoadIdentitySimd4x4F();

    // Set element at (0, 0)
    tfSetElemSimd4x4F(&a, 0, 0, 10.1f);
    debugPrintSimd4x4F(a);
    EXPECT_TRUE(tfIsCloseSimd4x4F(a, tfLoadSimd4x4F(10.1f, 0, 0, 0, 
                                                    0, 1.0f, 0, 0, 
                                                    0, 0, 1.0f, 0, 
                                                    0, 0, 0, 1.0f), DEFAULT_EPSILON));

    // Set element at (1, 2)
    tfSetElemSimd4x4F(&a, 1, 2, -5.2f);
    debugPrintSimd4x4F(a);
    EXPECT_TRUE(tfIsCloseSimd4x4F(a, tfLoadSimd4x4F(10.1f, 0, 0, 0, 
                                                    0, 1.0f, -5.2f, 0, 
                                                    0, 0, 1.0f, 0, 
                                                    0, 0, 0, 1.0f), DEFAULT_EPSILON));

    // Set element to zero
    tfSetElemSimd4x4F(&a, 1, 1, 0.0f);
    debugPrintSimd4x4F(a);
    EXPECT_TRUE(tfIsCloseSimd4x4F(a, tfLoadSimd4x4F(10.1f, 0, 0, 0, 
                                                    0, 0.0f, -5.2f, 0, 
                                                    0, 0, 1.0f, 0, 
                                                    0, 0, 0, 1.0f), DEFAULT_EPSILON));


}


UTEST(TF_Simd4, tfVectorMul4x4F)
{
    struct {
      TSimdFloat4x4 a;
      TSimdFloat4 b;
      TSimdFloat4 test;
    } tests[] = {

          // Identity matrix
          {tfLoadSimd4x4F(1,0,0,0, 
                          0,1,0,0, 
                          0,0,1,0, 
                          0,0,0,1), tfLoadSimd4F(1,2,3,4), tfLoadSimd4F(1,2,3,4)},

          // Diagonal matrix
          {tfLoadSimd4x4F(2,0,0,0, 
                          0,3,0,0, 
                          0,0,4,0, 
                          0,0,0,5), tfLoadSimd4F(1,2,3,4), tfLoadSimd4F(2,6,12,20)},

          // Zero vector
          {tfLoadSimd4x4F(1,2,3,4, 
                          5,6,7,8, 
                          9,10,11,12, 
                          13,14,15,16), tfLoadSimd4F(0,0,0,0), tfLoadSimd4F(0,0,0,0)},
          
          {tfLoadSimd4x4F(1,0,0,12, 
                          0,1,0,0, 
                          0,0,1,0, 
                          0,0,0,1), tfLoadSimd4F(4,0,0,1), tfLoadSimd4F(16,0,0,1)},

    };
    for (size_t i = 0; i < TF_ARRAY_COUNT(tests); i++)
    {
        TSimdFloat4 result = tfVectorMul4x4F(tests[i].a, tests[i].b);
        debugPrintSimd4F(result);
        EXPECT_TRUE(tfIsCloseSimd4F(result, tests[i].test, DEFAULT_EPSILON));
    }
}


#include "Forge/Mem/TF_Memory.h"
#include "Forge/TF_FileSystem.h"
UTEST_STATE();
TF_UTEST_MAIN("TF_TF_Simd2")



