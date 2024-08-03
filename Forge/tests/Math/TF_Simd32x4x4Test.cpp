/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */
#include "TF_TestMain.h"
#include "utest.h"

#include "Forge/TF_Log.h"

#include "TF_MathUtils.h"
#include "Forge/Math/TF_Simd32x4x4.h"

UTEST(Tsimd_f32x4_t, Load_Select)
{
    struct Tsimd_f32x4x4_s mat = tfSimdLoad_f32x4x4(
        -1, 2, -3, 4, 
        5, -6, 7, -8, 
        9, 10, -11, 12, 
        13, -14, 15, -16);

    EXPECT_TRUE(tfSimdCmpAllEq_f32x4(tfSimdGetRow_f32x4x4(mat, 0), tfSimdLoad_f32x4(-1, 2, -3, 4)));
    EXPECT_TRUE(tfSimdCmpAllEq_f32x4(tfSimdGetRow_f32x4x4(mat, 1), tfSimdLoad_f32x4(5, -6, 7, -8)));
    EXPECT_TRUE(tfSimdCmpAllEq_f32x4(tfSimdGetRow_f32x4x4(mat, 2), tfSimdLoad_f32x4(9, 10, -11, 12)));
    EXPECT_TRUE(tfSimdCmpAllEq_f32x4(tfSimdGetRow_f32x4x4(mat, 3), tfSimdLoad_f32x4(13, -14, 15, -16)));
    
    EXPECT_TRUE(tfSimdCmpAllEq_f32x4(tfSimdGetColumn_f32x4x4(mat, 0), tfSimdLoad_f32x4(-1, 5, 9, 13)));
    EXPECT_TRUE(tfSimdCmpAllEq_f32x4(tfSimdGetColumn_f32x4x4(mat, 1), tfSimdLoad_f32x4(2, -6, 10, -14)));
    EXPECT_TRUE(tfSimdCmpAllEq_f32x4(tfSimdGetColumn_f32x4x4(mat, 2), tfSimdLoad_f32x4(-3, 7, -11, 15)));
    EXPECT_TRUE(tfSimdCmpAllEq_f32x4(tfSimdGetColumn_f32x4x4(mat, 3), tfSimdLoad_f32x4(4, -8, 12, -16)));

    EXPECT_NEAR(tfSimdGet_f32x4x4(mat, 0, 0), -1.0f, DEFAULT_EPSILON);
    EXPECT_NEAR(tfSimdGet_f32x4x4(mat, 1, 0), 2.0f, DEFAULT_EPSILON);
    EXPECT_NEAR(tfSimdGet_f32x4x4(mat, 2, 0), -3.0f, DEFAULT_EPSILON);
    EXPECT_NEAR(tfSimdGet_f32x4x4(mat, 3, 0), 4.0f, DEFAULT_EPSILON);

    EXPECT_NEAR(tfSimdGet_f32x4x4(mat, 0, 1), 5.0f, DEFAULT_EPSILON);
    EXPECT_NEAR(tfSimdGet_f32x4x4(mat, 1, 1), -6.0f, DEFAULT_EPSILON);
    EXPECT_NEAR(tfSimdGet_f32x4x4(mat, 2, 1), 7.0f, DEFAULT_EPSILON);
    EXPECT_NEAR(tfSimdGet_f32x4x4(mat, 3, 1), -8.0f, DEFAULT_EPSILON);

    EXPECT_NEAR(tfSimdGet_f32x4x4(mat, 0, 2), 9.0f, DEFAULT_EPSILON);
    EXPECT_NEAR(tfSimdGet_f32x4x4(mat, 1, 2), 10.0f, DEFAULT_EPSILON);
    EXPECT_NEAR(tfSimdGet_f32x4x4(mat, 2, 2), -11.0f, DEFAULT_EPSILON);
    EXPECT_NEAR(tfSimdGet_f32x4x4(mat, 3, 2), 12.0f, DEFAULT_EPSILON);

    EXPECT_NEAR(tfSimdGet_f32x4x4(mat, 0, 3), 13.0f, DEFAULT_EPSILON);
    EXPECT_NEAR(tfSimdGet_f32x4x4(mat, 1, 3), -14.0f, DEFAULT_EPSILON);
    EXPECT_NEAR(tfSimdGet_f32x4x4(mat, 2, 3), 15.0f, DEFAULT_EPSILON);
    EXPECT_NEAR(tfSimdGet_f32x4x4(mat, 3, 3), -16.0f, DEFAULT_EPSILON);
        
}


UTEST(Tsimd_f32x4x4_s, tfSimdMul_f32x4x4_f32x4x1)
{
    struct {
      struct Tsimd_f32x4x4_s a;
      Tsimd_f32x4_t b;
      Tsimd_f32x4_t test;
    } tests[] = {

            {tfSimdLoad_f32x4x4(1,0,0,0, 
                                0,1,0,0, 
                                0,0,1,0, 
                                0,0,0,1), tfSimdLoad_f32x4(1,2,3,4), tfSimdLoad_f32x4(1,2,3,4)},
            {tfSimdLoad_f32x4x4(2,0,0,0, 
                                0,2,0,0, 
                                0,0,2,0, 
                                0,0,0,2), tfSimdLoad_f32x4(1,2,3,4), tfSimdLoad_f32x4(2,4,6,8)},
            {tfSimdLoad_f32x4x4(1,2,3,4, 
                                5,6,7,8, 
                                9,10,11,12, 
                                13,14,15,16), tfSimdLoad_f32x4(1,1,1,1), tfSimdLoad_f32x4(10,26,42,58)},
            {tfSimdLoad_f32x4x4(0,1,0,0, 
                                1,0,0,0, 
                                0,0,1,0, 
                                0,0,0,1), tfSimdLoad_f32x4(1,2,3,4), tfSimdLoad_f32x4(2,1,3,4)},
            {tfSimdLoad_f32x4x4(1,1,1,1, 
                                1,1,1,1, 
                                1,1,1,1, 
                                1,1,1,1), tfSimdLoad_f32x4(1,1,1,1), tfSimdLoad_f32x4(4,4,4,4)},
    };
    for (size_t i = 0; i < TF_ARRAY_COUNT(tests); i++)
    {
        Tsimd_f32x4_t  result = tfSimdMul_f32x4x4_f32x4x1(tests[i].a, tests[i].b);
        EXPECT_TRUE(tfSimdIsClose_f32x4(result, tests[i].test, DEFAULT_EPSILON));
    }
}



UTEST(Tsimd_f32x4x4_s, tfSimdTranspose_f32x4x4)
{
    struct
    {
        struct Tsimd_f32x4x4_s  a;
        struct Tsimd_f32x4x4_s  test;
    } tests[] = { { tfSimdLoad_f32x4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1),
                    tfSimdLoad_f32x4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1) },
                  { tfSimdLoad_f32x4x4(-1, 2, -3, 4, 
                                   5, -6, 7, -8, 
                                   9, 10, -11, 12, 
                                   13, -14, 15, -16),
                    tfSimdLoad_f32x4x4(-1, 5, 9, 13, 
                                   2, -6, 10, -14, 
                                   -3, 7, -11, 15, 
                                   4, -8, 12, -16) } };

    for (size_t i = 0; i < TF_ARRAY_COUNT(tests); i++)
    {
        struct Tsimd_f32x4x4_s result = tfSimdTranspose_f32x4x4(tests[i].a);
        DLOGF(LogLevel::eDEBUG, LOG_FORMAT_SIMD_32x4x4f(result));
        EXPECT_TRUE(tfSimdIsClose_f32x4x4(result, tests[i].test, DEFAULT_EPSILON));
    }
}

UTEST(Tsimd_f32x4x4_t, tfSimdLoadOrthographicLH_f32x4x4)
{
    struct Tsimd_f32x4x4_s result = tfSimdLoadOrthographicLH_f32x4x4(-1.0f, 1.0f, -1.0f, 1.0f,0.1f,100.f);
    DLOGF(LogLevel::eDEBUG, LOG_FORMAT_SIMD_32x4x4f(result));

    EXPECT_TRUE(tfSimdIsClose_f32x4x4(result, tfSimdLoad_f32x4x4(
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.01f,-0.001f,
        0.0f, 0.0f, 0.0f, 1.0f
    ), DEFAULT_EPSILON));
}

//UTEST(TF_SimdFloat4x4, tfMatMul4x4F_4x4F)
//{
//    struct
//    {
//        TSimdFloat4x4 a;
//        TSimdFloat4x4 b;
//        TSimdFloat4x4 test;
//    } tests[] = {
//        { tfLoadSimd4x4F(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1), 
//          tfLoadSimd4x4F(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1),
//          tfLoadSimd4x4F(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1) },
//        // Scaling matrices
//        { tfLoadSimd4x4F(2, 0, 0, 0, 0, 3, 0, 0, 0, 0, 4, 0, 0, 0, 0, 1), 
//          tfLoadSimd4x4F(5, 0, 0, 0, 0, 6, 0, 0, 0, 0, 7, 0, 0, 0, 0, 1),
//          tfLoadSimd4x4F(10, 0, 0, 0, 0, 18, 0, 0, 0, 0, 28, 0, 0, 0, 0, 1) },
//        { tfLoadSimd4x4F(0.5, 0, 0, 0, 0, 0.25, 0, 0, 0, 0, 0.125, 0, 0, 0, 0, 1),
//          tfLoadSimd4x4F(2, 0, 0, 0, 0, 4, 0, 0, 0, 0, 8, 0, 0, 0, 0, 1), 
//          tfLoadSimd4x4F(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1) },
//
//
//        { tfLoadSimd4x4F(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f),
//          tfLoadSimd4x4F(7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f, 17.0f, 18.0f, 19.0f, 20.0f, 21.0f, 22.0f), 
//          tfLoadSimd4x4F(150.0f, 160.0f, 170.0f, 180.0f, 358.0f, 384.0f, 410.0f, 436.0f, 566.0f, 608.0f, 650.0f, 692.0f, 774.0f, 832.0f, 890.0f, 948.0f) },
//    };
//
//    for (size_t i = 0; i < TF_ARRAY_COUNT(tests); i++)
//    {
//        TSimdFloat4x4 result = tfMulSimd4x4F_4x4F(tests[i].a, tests[i].b);
//        debugPrintSimd4x4F(result);
//        EXPECT_TRUE(tfIsCloseSimd4x4F(result, tests[i].test, DEFAULT_EPSILON));
//    }
//}
//
//UTEST(TF_SimdFloat4x4, tfSetElemSimd4x4F) {
//    TSimdFloat4x4 a = tfLoadIdentitySimd4x4F();
//
//    // Set element at (0, 0)
//    tfSetElemSimd4x4F(&a, 0, 0, 10.1f);
//    debugPrintSimd4x4F(a);
//    EXPECT_TRUE(tfIsCloseSimd4x4F(a, tfLoadSimd4x4F(10.1f, 0, 0, 0, 
//                                                    0, 1.0f, 0, 0, 
//                                                    0, 0, 1.0f, 0, 
//                                                    0, 0, 0, 1.0f), DEFAULT_EPSILON));
//
//    // Set element at (1, 2)
//    tfSetElemSimd4x4F(&a, 1, 2, -5.2f);
//    debugPrintSimd4x4F(a);
//    EXPECT_TRUE(tfIsCloseSimd4x4F(a, tfLoadSimd4x4F(10.1f, 0, 0, 0, 
//                                                    0, 1.0f, 0.0f, 0, 
//                                                    0, -5.2f, 1.0f, 0, 
//                                                    0, 0, 0, 1.0f), DEFAULT_EPSILON));
//
//    // Set element to zero
//    tfSetElemSimd4x4F(&a, 1, 1, 0.0f);
//    debugPrintSimd4x4F(a);
//    EXPECT_TRUE(tfIsCloseSimd4x4F(a, tfLoadSimd4x4F(10.1f, 0, 0, 0, 
//                                                    0, 0.0f, 0 , 0, 
//                                                    0, -5.2f, 1.0f, 0, 
//                                                    0, 0, 0, 1.0f), DEFAULT_EPSILON));
//}
//
//


#include "Forge/Mem/TF_Memory.h"
#include "Forge/TF_FileSystem.h"
UTEST_STATE();
TF_UTEST_MAIN("TF_TF_Simd2")




