
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

#define LOG_FORMAT_SIMD_32x4f(input) \
    "%.3f, %.3f, %.3f, %.3f", tfSimdSelect0_f32x4(input), tfSimdSelect1_f32x4(input), tfSimdSelect2_f32x4(input), tfSimdSelect3_f32x4(input)
#define LOG_FORMAT_SIMD_32x4i(input) \
    "%d, %d, %d, %d", tfSimdSelect0_i32x4(input), tfSimdSelect1_i32x4(input), tfSimdSelect2_i32x4(input), tfSimdSelect3_i32x4(input)

#define LOG_SIMD_32x4x4f(input, LOG, ...)                                                                                            \
    LOG(__VA_ARGS__, "%.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f", tfSimdSelectIndex0_f32x4(input.mCol0), \
        tfSimdSelectIndex1_f32x4(input.mCol1), tfSimdSelectIndex2_f32x4(input.mCol2), tfSimdSelectIndex3_f32x4(input.mCol3),            \
        tfSimdSelectIndex0_f32x4(input.mCol0), tfSimdSelectIndex1_f32x4(input.mCol1), tfSimdSelectIndex2_f32x4(input.mCol2),            \
        tfSimdSelectIndex3_f32x4(input.mCol3), tfSimdSelectIndex0_f32x4(input.mCol0), tfSimdSelectIndex1_f32x4(input.mCol1),            \
        tfSimdSelectIndex2_f32x4(input.mCol2), tfSimdSelectIndex3_f32x4(input.mCol3), tfSimdSelectIndex0_f32x4(input.mCol0),            \
        tfSimdSelectIndex1_f32x4(input.mCol1), tfSimdSelectIndex2_f32x4(input.mCol2), tfSimdSelectIndex3_f32x4(input.mCol3))

static inline void debugPrintSimd4F(Tsimd_f32x4_t input) {
 // DLOGF(LogLevel::eDEBUG, "%.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f",
 //         tfSimdSelectIndex0_f32x4(input),
 //         tfSimdSelectIndex1_f32x4(input),
 //         tfSimdSelectIndex2_f32x4(input),
 //         tfSimdSelectIndex3_f32x4(input));
}
static inline void debugPrintSimd4x4F(struct Tsimd_f32x4x4_s  input) {
   // DLOGF(LogLevel::eDEBUG,"%.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f",
   //       tfSimdSelectIndex0_f32x4(input.mCol0),
   //       tfSimdSelectIndex1_f32x4(input.mCol1),
   //       tfSimdSelectIndex2_f32x4(input.mCol2),
   //       tfSimdSelectIndex3_f32x4(input.mCol3),

   //       tfSimdSelectIndex0_f32x4(input.mCol0),
   //       tfSimdSelectIndex1_f32x4(input.mCol1),
   //       tfSimdSelectIndex2_f32x4(input.mCol2),
   //       tfSimdSelectIndex3_f32x4(input.mCol3),
   //       
   //       tfSimdSelectIndex0_f32x4(input.mCol0),
   //       tfSimdSelectIndex1_f32x4(input.mCol1),
   //       tfSimdSelectIndex2_f32x4(input.mCol2),
   //       tfSimdSelectIndex3_f32x4(input.mCol3),
   //       
   //       tfSimdSelectIndex0_f32x4(input.mCol0),
   //       tfSimdSelectIndex1_f32x4(input.mCol1),
   //       tfSimdSelectIndex2_f32x4(input.mCol2),
   //       tfSimdSelectIndex3_f32x4(input.mCol3)
   // );
}

