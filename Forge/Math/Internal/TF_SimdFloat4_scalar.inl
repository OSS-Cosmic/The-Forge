#if defined(__CLANGD__)
#define TF_FEATURE_CPU_SCALAR
#include "Forge/TF_Config.h"
#include "../TF_SimdFloat4.h"
#endif

static inline float tfVectorDot4F(TSimdFloat4 a0, TSimdFloat4  a1) {
  return (a0.mRow.v[0] * a1.mRow.v[0]) +
          (a0.mRow.v[1] * a1.mRow.v[1]) +
          (a0.mRow.v[2] * a1.mRow.v[2]) +
          (a0.mRow.v[3] * a1.mRow.v[3]); 

}
