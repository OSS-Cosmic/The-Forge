
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



