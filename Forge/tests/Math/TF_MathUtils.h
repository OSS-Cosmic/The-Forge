
#include "Forge/Math/TF_Simd32x4.h"

#define DEFAULT_EPSILON 1e-3f
#define EXPECT_NEAR_VECTOR4(a, b, epsilon) do { \
  Vector4 __a = a; \
  Vector4 __b = b; \
  EXPECT_NEAR(__a.getX(), __b.getX(), epsilon); \
  EXPECT_NEAR(__a.getY(), __b.getY(), epsilon); \
  EXPECT_NEAR(__a.getZ(), __b.getZ(), epsilon); \
  EXPECT_NEAR(__a.getW(), __b.getW(), epsilon); \
} while(false);
#define EXPECT_NEAR_VECTOR4_INT(a, b) do { \
  Vector4Int __a = a; \
  Vector4Int  __b = b; \
  EXPECT_EQ(__a.getX(), __b.getX()); \
  EXPECT_EQ(__a.getY(), __b.getY()); \
  EXPECT_EQ(__a.getZ(), __b.getZ()); \
  EXPECT_EQ(__a.getW(), __b.getW()); \
} while(false);


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

