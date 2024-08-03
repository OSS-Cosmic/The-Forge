
#if defined(__CLANGD__)
#include "../TF_SimdFloat4x4.h"
#endif

#include "SimdTypes.h"
#include "Forge/Math/TF_Simd32x4.h"

static inline struct Tsimd_f32x4x4_s tfSimdLoad_f32x4x4(
  float m00, float m01, float m02, float m03, 
  float m10, float m11, float m12, float m13,
  float m20, float m21, float m22, float m23, 
  float m30, float m31, float m32, float m33) {
    struct Tsimd_f32x4x4_s result;
    result.mCol0 = tfSimdLoad_f32x4(m00, m10, m20, m30);
    result.mCol1 = tfSimdLoad_f32x4(m01, m11, m21, m31);
    result.mCol2 = tfSimdLoad_f32x4(m02, m12, m22, m32);
    result.mCol3 = tfSimdLoad_f32x4(m03, m13, m23, m33);
    return result;
}

static inline struct Tsimd_f32x4x4_s tfSimdLoadIdentity_f32x4x4() {
  return tfSimdLoad_f32x4x4(
    1,0,0,0,
    0,1,0,0,
    0,0,1,0,
    0,0,0,1
  );
}

static inline bool tfSimdIsClose_f32x4x4(struct Tsimd_f32x4x4_s arg0,struct Tsimd_f32x4x4_s arg1, float epsilon) {
  return 
  tfSimdIsClose_f32x4(arg0.mCol0, arg1.mCol0, epsilon ) &&
  tfSimdIsClose_f32x4(arg0.mCol1, arg1.mCol1, epsilon ) &&
  tfSimdIsClose_f32x4(arg0.mCol2, arg1.mCol2, epsilon ) &&
  tfSimdIsClose_f32x4(arg0.mCol3, arg1.mCol3, epsilon ); 

}

static inline float tfSimdGet_f32x4x4(struct Tsimd_f32x4x4_s input, int column, int row) {
    return tfSimdGet_f32x4(input.mCol[column], row);
}

static inline Tsimd_f32x4_t tfSimdGetColumn_f32x4x4(struct Tsimd_f32x4x4_s input, int column){
  ASSERT(column >= 0 && column  < 4);
  return input.mCol[column]; 
}

static inline struct Tsimd_f32x4x4_s tfSimdReplace_f32x4x4(struct Tsimd_f32x4x4_s input, float value, uint column, uint row) {
    ASSERT(column < 4);
    input.mCol[column] = tfSimdReplace_f32_f32x4(row, input.mCol[column], value);
    return input;
}

static inline struct Tsimd_f32x4x4_s tfSimdLoadRotationYX(const float radiansY, const float radiansX) {
	// Note that:
	//  rotateYX(-y,-x)*rotateXY(x,y) == mat4::identity()
	// which means that
	//  inverse(rotateXY(x,y)) = rotateYX(-y,-x)

	//return mat4::rotationY(angleY) * mat4::rotationX(angleX);
	/*
	[	1,		 0,		 0,		 0]
	[	0,		 c,		-s,		 0]
	[	0,		 s,		 c,		 0]
	[	0,		 0,		 0,		 1]

	[ o, 0, i, 0]	[   o,		is,		ic,		0]
	[ 0, 1, 0, 0]	[   0,		c ,		-s,		0]
	[-i, 0, o, 0]	[  -i,		os,		oc,		0]
	[ 0, 0, 0, 1]	[   0,		0 ,		0 ,		1]
	*/
	const float cosX = cosf(radiansX), sinX = sinf(radiansX);
	const float cosY = cosf(radiansY), sinY = sinf(radiansY);
	return tfSimdLoad_f32x4x4(
	  cosY, sinX * sinY  , cosX *-sinY, 0,
	  0   , cosX         , sinX       , 0,
	  sinY, -sinX * cosY , cosX*cosY  , 0,
	  0   , 0            , 0          , 1
	);


}



//static inline struct Tsimd_f32x4x4_s tfSimdSetRotationFromQuat_f32x4x4(struct Tsimd_f32x4x4_s ar0,Tsimd_f32x4_t quaternion) {
//    Tsimd_f32x4_t t2 = tfSimdMul_f32x4(quaternion, tfSimdSplat_f32_f32x4(2.0f));
//    Tsimd_f32x4_t t2xxxx = tfSimdSplat_f32x4_f32x4(t2, 0);
//    Tsimd_f32x4_t t2yyyy = tfSimdSplat_f32x4_f32x4(t2, 1);
//    Tsimd_f32x4_t t2zzzz = tfSimdSplat_f32x4_f32x4(t2, 2);
//}


static inline Tsimd_f32x4_t  tfSimdGetRow_f32x4x4(struct Tsimd_f32x4x4_s input, int row) {
  ASSERT(row >= 0 && row < 4);
  switch(row) {
    case 0: return tfSimdLoad_f32x4(
                    tfSimdGet_f32x4(input.mCol0, 0),
                    tfSimdGet_f32x4(input.mCol1, 0),
                    tfSimdGet_f32x4(input.mCol2, 0),
                    tfSimdGet_f32x4(input.mCol3, 0)
                    );
    case 1: return tfSimdLoad_f32x4(
                    tfSimdGet_f32x4(input.mCol0,1),
                    tfSimdGet_f32x4(input.mCol1,1),
                    tfSimdGet_f32x4(input.mCol2,1),
                    tfSimdGet_f32x4(input.mCol3,1));
    case 2: return tfSimdLoad_f32x4(
                    tfSimdGet_f32x4(input.mCol0,2),
                    tfSimdGet_f32x4(input.mCol1,2),
                    tfSimdGet_f32x4(input.mCol2,2),
                    tfSimdGet_f32x4(input.mCol3,2));
    case 3: return tfSimdLoad_f32x4(
                    tfSimdGet_f32x4(input.mCol0,3),
                    tfSimdGet_f32x4(input.mCol1,3),
                    tfSimdGet_f32x4(input.mCol2,3),
                    tfSimdGet_f32x4(input.mCol3,3));
  }
  return {};

}

static inline Tsimd_f32x4_t tfSimdMul_f32x4x4_f32x4x1(struct Tsimd_f32x4x4_s a0, Tsimd_f32x4_t a1) {
    Tsimd_f32x4_t xxxx = tfSimdSplat_f32x4_f32x4(a1, 0);
    Tsimd_f32x4_t yyyy = tfSimdSplat_f32x4_f32x4(a1, 1);
    Tsimd_f32x4_t zzzz = tfSimdSplat_f32x4_f32x4(a1, 2);
    Tsimd_f32x4_t wwww = tfSimdSplat_f32x4_f32x4(a1, 3);
    Tsimd_f32x4_t res = tfSimdMul_f32x4(a0.mCol0, xxxx);
    res = tfSimdMadd_f32x4(a0.mCol1, yyyy, res);
    res = tfSimdMadd_f32x4(a0.mCol2, zzzz, res);
    res = tfSimdMadd_f32x4(a0.mCol3, wwww, res);
    return res;
}

static inline Tsimd_f32x4x4_s tfSimdMul_f32x4x4_f32x4x4(struct Tsimd_f32x4x4_s a0, struct Tsimd_f32x4x4_s a1) {
  Tsimd_f32x4x4_s res;
  res.mCol0 = tfSimdMul_f32x4x4_f32x4x1(a0, a1.mCol0);
  res.mCol1 = tfSimdMul_f32x4x4_f32x4x1(a0, a1.mCol1);
  res.mCol2 = tfSimdMul_f32x4x4_f32x4x1(a0, a1.mCol2);
  res.mCol3 = tfSimdMul_f32x4x4_f32x4x1(a0, a1.mCol3);
  return res;
}

static inline struct Tsimd_f32x4x4_s tfSimdLoadOrthographicRH_f32x4x4(float left, float right, float bottom, float top, float zNear, float zFar) {
    struct Tsimd_f32x4x4_s result = tfSimdLoadOrthographicLH_f32x4x4(left, right, bottom, top, zNear, zFar);
    result.mCol2 = tfSimdSub_f32x4(tfSimdZero_f32x4(), result.mCol2);
    return result;
}

static inline struct Tsimd_f32x4x4_s tfSimdLoadOrthographicLH_ReverseZ_f32x4x4(float left, float right, float bottom, float top, float zNear, float zFar) {
    struct Tsimd_f32x4x4_s result = tfSimdLoadOrthographicLH_f32x4x4(left, right, bottom, top, zNear, zFar);
    result.mCol2 = tfSimdReplace_f32_f32x4(result.mCol2,2, -tfSimdGet_f32x4(result.mCol2,2));
    result.mCol3 = tfSimdReplace_f32_f32x4(result.mCol3,2, -tfSimdGet_f32x4(result.mCol3,2));
    return result;
}



//static inline TSimdFloat4 tfGetRowSimd4x4F(TSimdFloat4x4 input, int row) {
//  ASSERT(row >= 0 && row < 4);
//  switch(row) {
//    case 0: return {tfS32x4FLoad(
//                    tfSimd4fSelectIndex0(input.mCol0),
//                    tfSimd4fSelectIndex0(input.mCol1),
//                    tfSimd4fSelectIndex0(input.mCol2),
//                    tfSimd4fSelectIndex0(input.mCol3)
//                    )};
//    case 1: return {tfS32x4FLoad(
//                    tfS32x4FSelectIndex1(input.mCol0),
//                    tfS32x4FSelectIndex1(input.mCol1),
//                    tfS32x4FSelectIndex1(input.mCol2),
//                    tfS32x4FSelectIndex1(input.mCol3))};
//    case 2: return {tfS32x4FLoad(
//                    tfS32x4FSelectIndex2(input.mCol0),
//                    tfS32x4FSelectIndex2(input.mCol1),
//                    tfS32x4FSelectIndex2(input.mCol2),
//                   tfS32x4FSelectIndex2(input.mCol3))};
//    case 3: return {tfS32x4FLoad(
//                    tfS32x4FSelectIndex3(input.mCol0),
//                    tfS32x4FSelectIndex3(input.mCol1),
//                    tfS32x4FSelectIndex3(input.mCol2),
//                    tfS32x4FSelectIndex3(input.mCol3))};
//  }
//  return {};
//}
//
//static inline void tfSetRowSimd4x4F(TSimdFloat4x4* input, int row, TSimdFloat4 value) {
//   // ASSERT(row >= 0 && row < 4);
//   // switch (row) {
//   // case 0:
//   //     input->mCol0 = tfS32x4FReplaceIndex0(input->mCol0, tfS32x4FSplatIndex0(value));
//   // }
//    return {};
//}
//static inline TSimdFloat4 tfGetColumnSimd4x4F(int column);
//static inline void tfSetColumnSimd4x4F(TSimdFloat4x4* input, int row);
//static inline void tfSetElemSimd4x4F(TSimdFloat4x4* input, int col, int row, float value);
//
//
////static inline void tfSetElemSimd3x4F(TSimdFloat4x3* input, int col, int row, float value){
////  ASSERT(col >= 0 && col < 3);
////  ASSERT(row >= 0 && row < 4);
////  switch (row)
////  {
////    case 0: input->mCol[col] = tfSimd4fReplaceIndex0ByValue(input->mCol[col], value); break;
////    case 1: input->mCol[col] = tfSimd4fReplaceIndex1ByValue(input->mCol[col], value); break;
////    case 2: input->mCol[col] = tfSimd4fReplaceIndex2ByValue(input->mCol[col], value); break;
////    case 3: input->mCol[col] = tfSimd4fReplaceIndex3ByValue(input->mCol[col], value); break;
////  }
////}
//
//
//static inline TSimdFloat4 tfVectorMulSimd4x4F(const TSimdFloat4x4 a0, const TSimdFloat4 a1) {
//    Tsimd_f32x4_t xxxx = tfSimd4fSplatIndex0(a1.mRow);
//    Tsimd_f32x4_t yyyy = tfSimd4fSplatIndex1(a1.mRow);
//    Tsimd_f32x4_t zzzz = tfSimd4fSplatIndex2(a1.mRow);
//    Tsimd_f32x4_t wwww = tfSimd4fSplatIndex3(a1.mRow);
//    Tsimd_f32x4_t res = tfSimd4fMul(a0.mCol0, xxxx);
//    res = tfSimd4fMadd(a0.mCol1, yyyy, res);
//    res = tfSimd4fMadd(a0.mCol2, zzzz, res);
//    res = tfSimd4fMadd(a0.mCol3, wwww, res);
//    return { res };
//}
//
//static inline TSimdFloat4x4 tfLoadZeroSimd4x4F()
//{
//    TSimdFloat4x4 value;
//    value.mCol0 = tfSimd4fZero();
//    value.mCol1 = tfSimd4fZero();
//    value.mCol2 = tfSimd4fZero();
//    value.mCol3 = tfSimd4fZero();
//    return value;
//}
//
//static inline TSimdFloat4x4 tfLoadIdentitySimd4x4F()
//{
//    TSimdFloat4x4 value;
//    value.mCol0 = tfSimdFloat4x32Load(1, 0, 0, 0);
//    value.mCol1 = tfSimdFloat4x32Load(0, 1, 0, 0);
//    value.mCol2 = tfSimdFloat4x32Load(0, 0, 1, 0);
//    value.mCol3 = tfSimdFloat4x32Load(0, 0, 0, 1);
//    return value;
//}
//
//static inline TSimdFloat4x4 tfMulSimd4x4F_4x4F(TSimdFloat4x4 a0, TSimdFloat4x4 a1) {
//    TSimdFloat4x4 res;
//    res.mCol0 = tfVectorMulSimd4x4F(a0, TSimdFloat4{ a1.mCol0 }).mRow;
//    res.mCol1 = tfVectorMulSimd4x4F(a0, TSimdFloat4{ a1.mCol1 }).mRow;
//    res.mCol2 = tfVectorMulSimd4x4F(a0, TSimdFloat4{ a1.mCol2 }).mRow;
//    res.mCol3 = tfVectorMulSimd4x4F(a0, TSimdFloat4{ a1.mCol3 }).mRow;
//    return res;
//}
//
//static inline TSimdFloat4x3 tfMulSimd4x4F_3x4F(TSimdFloat4x4 a0, TSimdFloat4x3 a1) {
//    TSimdFloat4x3 res;
//    res.mCol0 = tfVectorMulSimd4x4F(a0, TSimdFloat4{ a1.mCol0 }).mRow;
//    res.mCol1 = tfVectorMulSimd4x4F(a0, TSimdFloat4{ a1.mCol1 }).mRow;
//    res.mCol2 = tfVectorMulSimd4x4F(a0, TSimdFloat4{ a1.mCol2 }).mRow;
//    return res;
//}
//static inline TSimdFloat4x2 tfMulSimd4x4F_2x4F(TSimdFloat4x4 a0, TSimdFloat4x2 a1) {
//    TSimdFloat4x2 res;
//    res.mCol0 = tfVectorMulSimd4x4F(a0, TSimdFloat4{ a1.mCol0 }).mRow;
//    res.mCol1 = tfVectorMulSimd4x4F(a0, TSimdFloat4{ a1.mCol1 }).mRow;
//    return res;
//}
//static inline TSimdFloat4x1 tfMulSimd4x4F_1x4F(TSimdFloat4x4 a0, TSimdFloat4x1 a1) {
//    TSimdFloat4x1 res;
//    res.mCol0 = tfVectorMulSimd4x4F(a0, TSimdFloat4{ a1.mCol0 }).mRow;
//    return res;
//}
