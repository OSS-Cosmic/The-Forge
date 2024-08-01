#if defined(__CLANGD__)
#define TF_FEATURE_CPU_NEON
#include "Forge/TF_Config.h"
#include "../TF_SimdFloat4.h"
#endif

static inline float tfVectorDot4F(TSimdFloat4 a0, TSimdFloat4  a1) {
  return vaddvq_f32(vmulq_f32(a0, a1));
}

