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

#include "Forge/TF_Log.h"

#include "TF_MathUtils.h"


UTEST(TF_SimdFloat4x4, tfMatTranpose4x4F)
{
    struct
    {
        TSimdFloat4x4 a;
        TSimdFloat4x4 test;
    } tests[] = { { tfLoadSimd4x4F(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1),
                    tfLoadSimd4x4F(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1) },
                  { tfLoadSimd4x4F(-1, 2, -3, 4, 
                                   5, -6, 7, -8, 
                                   9, 10, -11, 12, 
                                   13, -14, 15, -16),
                    tfLoadSimd4x4F(-1, 5, 9, 13, 
                                   2, -6, 10, -14, 
                                   -3, 7, -11, 15, 
                                   4, -8, 12, -16) } };

    for (size_t i = 0; i < TF_ARRAY_COUNT(tests); i++)
    {
        TSimdFloat4x4 result = tfTransposeSimd4x4F(tests[i].a);
        debugPrintSimd4x4F(result);
        EXPECT_TRUE(tfIsCloseSimd4x4F(result, tests[i].test, DEFAULT_EPSILON));
    }
}


UTEST(TF_SimdFloat4x4, tfMatMul4x4F_4x4F)
{
    struct
    {
        TSimdFloat4x4 a;
        TSimdFloat4x4 b;
        TSimdFloat4x4 test;
    } tests[] = {
        { tfLoadSimd4x4F(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1), 
          tfLoadSimd4x4F(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1),
          tfLoadSimd4x4F(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1) },
        // Scaling matrices
        { tfLoadSimd4x4F(2, 0, 0, 0, 0, 3, 0, 0, 0, 0, 4, 0, 0, 0, 0, 1), 
          tfLoadSimd4x4F(5, 0, 0, 0, 0, 6, 0, 0, 0, 0, 7, 0, 0, 0, 0, 1),
          tfLoadSimd4x4F(10, 0, 0, 0, 0, 18, 0, 0, 0, 0, 28, 0, 0, 0, 0, 1) },
        { tfLoadSimd4x4F(0.5, 0, 0, 0, 0, 0.25, 0, 0, 0, 0, 0.125, 0, 0, 0, 0, 1),
          tfLoadSimd4x4F(2, 0, 0, 0, 0, 4, 0, 0, 0, 0, 8, 0, 0, 0, 0, 1), 
          tfLoadSimd4x4F(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1) },


        { tfLoadSimd4x4F(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f),
          tfLoadSimd4x4F(7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f, 17.0f, 18.0f, 19.0f, 20.0f, 21.0f, 22.0f), 
          tfLoadSimd4x4F(150.0f, 160.0f, 170.0f, 180.0f, 358.0f, 384.0f, 410.0f, 436.0f, 566.0f, 608.0f, 650.0f, 692.0f, 774.0f, 832.0f, 890.0f, 948.0f) },
    };

    for (size_t i = 0; i < TF_ARRAY_COUNT(tests); i++)
    {
        TSimdFloat4x4 result = tfMulSimd4x4F_4x4F(tests[i].a, tests[i].b);
        debugPrintSimd4x4F(result);
        EXPECT_TRUE(tfIsCloseSimd4x4F(result, tests[i].test, DEFAULT_EPSILON));
    }
}

UTEST(TF_SimdFloat4x4, tfSetElemSimd4x4F) {
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
                                                    0, 1.0f, 0.0f, 0, 
                                                    0, -5.2f, 1.0f, 0, 
                                                    0, 0, 0, 1.0f), DEFAULT_EPSILON));

    // Set element to zero
    tfSetElemSimd4x4F(&a, 1, 1, 0.0f);
    debugPrintSimd4x4F(a);
    EXPECT_TRUE(tfIsCloseSimd4x4F(a, tfLoadSimd4x4F(10.1f, 0, 0, 0, 
                                                    0, 0.0f, 0 , 0, 
                                                    0, -5.2f, 1.0f, 0, 
                                                    0, 0, 0, 1.0f), DEFAULT_EPSILON));
}


UTEST(TF_SimdFloat4x4, tfVectorMul4x4F)
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
        TSimdFloat4 result = tfVectorMulSimd4x4F(tests[i].a, tests[i].b);
        debugPrintSimd4F(result);
        EXPECT_TRUE(tfIsCloseSimd4F(result, tests[i].test, DEFAULT_EPSILON));
    }
}


#include "Forge/Mem/TF_Memory.h"
#include "Forge/TF_FileSystem.h"
UTEST_STATE();
TF_UTEST_MAIN("TF_TF_Simd2")




