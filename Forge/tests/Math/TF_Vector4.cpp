/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#include "TF_TestMain.h"
#include "utest.h"
#include "Forge/Math/TF_VectorMath.h"
#include "Forge/Math/scalar/vectormath.hpp"
#include "TF_MathUtils.h"


UTEST(Vector4, Constructor)
{
  Vector4 v(0.0f);
  EXPECT_NEAR(0.0f, v.getX(), DEFAULT_EPSILON);
  EXPECT_NEAR(0.0f, v.getY(), DEFAULT_EPSILON);
  EXPECT_NEAR(0.0f, v.getZ(), DEFAULT_EPSILON);
  Vector4 v1(0.0f);
  EXPECT_NEAR(0.0f, v.getX(), DEFAULT_EPSILON);
  EXPECT_NEAR(0.0f, v.getY(), DEFAULT_EPSILON);
  EXPECT_NEAR(0.0f, v.getZ(), DEFAULT_EPSILON);
}


UTEST(Vector4, recipPerElem)
{
    EXPECT_NEAR_VECTOR4(recipPerElem(Vector4(2.0f, 4.0f, 5.0f, 10.0f)), Vector4(0.5f, 0.25f, 0.2f, 0.1f), DEFAULT_EPSILON);
    EXPECT_NEAR_VECTOR4(recipPerElem(Vector4(2.0f, 4.0f, 5.0f, 10.0f)), Vector4(0.5f, 0.25f, 0.2f, 0.1f), DEFAULT_EPSILON);
}


UTEST(Vector4, absPerElem)
{
    EXPECT_NEAR_VECTOR4(absPerElem(Vector4(-1.0f, 2.0f, -5.0f, 1.0f)), Vector4(1.0f, 2.0f, 5.0f, 1.0f), DEFAULT_EPSILON);
    EXPECT_NEAR_VECTOR4(absPerElem(Vector4(1.0f, -2.0f, 5.0f, -1.0f)), Vector4(1.0f, 2.0f, 5.0f, 1.0f), DEFAULT_EPSILON);
}

UTEST(Vector4, add)
{
    EXPECT_NEAR_VECTOR4((Vector4(1.0f, 2.0f, 3.0f, 4.0f) + Vector4(-1.0f, 4.0f, 5.0f, 2.0f)), Vector4(0.0f, 6.0f, 8.0f, 6.0f), DEFAULT_EPSILON);

    Vector4 v1(1.0f, 2.0f, 3.0f, 4.0f);
    v1 += Vector4(5.0f, 3.0f, -1.0f, 2.0f);
    EXPECT_NEAR_VECTOR4(v1, Vector4(6.0f, 5.0f, 2.0f, 6.0f), DEFAULT_EPSILON);
}


UTEST(Vector4, mul)
{
      EXPECT_NEAR_VECTOR4(mulPerElem(Vector4(1.0f, 2.0f, 3.0f, 4.0f), Vector4(-1.0f, 4.0f, 5.0f, 2.0f)), Vector4(-1.0f, 8.0f, 15.0f, 8.0f), DEFAULT_EPSILON);
      EXPECT_NEAR_VECTOR4(Vector4(1.0f, 2.0f, 3.0f, 4.0f) * 2.0f, Vector4(2.0f, 4.0f, 6.0f, 8.0f), DEFAULT_EPSILON);
      EXPECT_NEAR_VECTOR4(2.0f * Vector4(1.0f, 2.0f, 3.0f, 4.0f), Vector4(2.0f, 4.0f, 6.0f, 8.0f), DEFAULT_EPSILON);

      Vector4 v1(1.0f, 2.0f, 3.0f, 4.0f);
      v1 += Vector4(5.0f, 3.0f, -1.0f, 2.0f);
      v1 -= Vector4(2.0f, -1.0f, 3.0f, 1.0f);
      v1 *= 3.0f;
      EXPECT_NEAR_VECTOR4(v1, Vector4(12.0f, 18.0f, -3.0f, 15.0f), DEFAULT_EPSILON);
}


UTEST(Vector4, sub)
{
    EXPECT_NEAR_VECTOR4((Vector4(1.0f, 2.0f, 3.0f, 4.0f) - Vector4(-1.0f, 4.0f, 5.0f, 2.0f)), Vector4(2.0f, -2.0f, -2.0f, 2.0f), DEFAULT_EPSILON);

    Vector4 v1(1.0f, 2.0f, 3.0f, 4.0f);
    v1 += Vector4(5.0f, 3.0f, -1.0f, 2.0f);
    v1 -= Vector4(2.0f, -1.0f, 3.0f, 1.0f);
    EXPECT_NEAR_VECTOR4(v1, Vector4(4.0f, 6.0f, -1.0f, 5.0f), DEFAULT_EPSILON);
}

UTEST(Vector4, GetAndSet)
{
      Vector4 v1;
      v1.setElem(0, 5.0f);
      v1.setElem(1, 6.0f);
      v1.setElem(2, 7.0f);
      v1.setElem(3, 8.0f);
      EXPECT_NEAR(v1.getElem(0), 5.0f, DEFAULT_EPSILON);
      EXPECT_NEAR(v1.getElem(1), 6.0f, DEFAULT_EPSILON);
      EXPECT_NEAR(v1.getElem(2), 7.0f, DEFAULT_EPSILON);
      EXPECT_NEAR(v1.getElem(3), 8.0f, DEFAULT_EPSILON);
}


UTEST(Vector4, normalize)
{
    EXPECT_NEAR_VECTOR4(normalize(Vector4(0.0f, 3.0f, 4.0f, 0.0f)),Vector4(0.0f, 3.0f / 5.0f, 4.0f / 5.0f, 0.0f), DEFAULT_EPSILON);
}


UTEST(Vector4, div)
{
    EXPECT_NEAR_VECTOR4(divPerElem(Vector4(1.0f, 2.0f, 3.0f, 4.0f), Vector4(-1.0f, 4.0f, 5.0f, 2.0f)), Vector4(-1.0f, 0.5f, 3.0f / 5.0f, 2.0f), DEFAULT_EPSILON);
    EXPECT_NEAR_VECTOR4(Vector4(1.0f, 2.0f, 3.0f, 4.0f) / 2.0f, Vector4(0.5f, 1.0f, 1.5f, 2.0f), DEFAULT_EPSILON);

    Vector4 v1(1.0f, 2.0f, 3.0f, 4.0f);
    v1 += Vector4(5.0f, 3.0f, -1.0f, 2.0f);
    v1 -= Vector4(2.0f, -1.0f, 3.0f, 1.0f);
    v1 *= 3.0f;
    v1 /= 2.0f;
    EXPECT_NEAR_VECTOR4(v1, Vector4(6.0f, 9.0f, -1.5f, 7.5f), DEFAULT_EPSILON);
}

UTEST(Vector4, cmpGt)
{
    //EXPECT_NEAR_VECTOR4_INT(cmpGt(Vector4(1.0f, 2.0f, 3.0f, 4.0f),Vector4(0.0f, 1.0f, 2.0f, 3.0f)), vector4int::Load(1));
    //EXPECT_NEAR_VECTOR4_INT(cmpGt(Vector4(1.0f, 2.0f, 3.0f, 4.0f),Vector4(0.0f, 3.0f, 2.0f, 3.0f))));
    //EXPECT_NEAR_VECTOR4_INT(cmpGt(Vector4(1.0f, 2.0f, 3.0f, 4.0f),Vector4(0.0f, 2.0f, 2.0f, 3.0f))));
}


#include "Forge/TF_FileSystem.h"
#include "Forge/Mem/TF_Memory.h"
#include "Forge/TF_Log.h"
UTEST_STATE();
TF_UTEST_MAIN("TF_Vector4")


