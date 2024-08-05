#pragma once
#ifndef TF_AFFINE_TRANSFORM_H
#define TF_AFFINE_TRANSFORM_H

#include "Forge/Math/TF_Simd32x4x4.h"
#include "Forge/Math/TF_Simd32x4.h"

struct AffineTransform {
  Tsimd_f32x3_t translation; 
  Tsimd_f32x4_t rotation;
  Tsimd_f32x3_t scale;
};

#endif
