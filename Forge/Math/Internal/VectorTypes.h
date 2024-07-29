

#pragma once
#ifndef TF_MATH_INTERNAL_VECTORTYPE_H_
#define TF_MATH_INTERNAL_VECTORTYPE_H_

#include "SimdTypes.h"

struct TVector3i {
  TSimdi32x4 mValue;
};

struct TVector3f {
  TSimdf32x3 mValue;
};

struct TVector2i {
  TSimdu32x2 mValue;
};

struct TVector2f {
  TSimdf32x2 mValue;
};

struct TVector4i {
  TSimdu32x4 mValue;
};

struct TVector4f {
  TSimdf32x4 mValue;
};

#endif
