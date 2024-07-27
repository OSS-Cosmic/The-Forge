#include "Forge/Math/Internal/Types.h"

inline Simd_FloatType4 tfSimdSplat4f(float value);
inline Simd_Int32Type4 tfSimdSplat4i(int32_t value);

inline Simd_FloatType  tfSimd4ToSimd1(Simd_FloatType4 value);
inline Simd_FloatType2 tfSimd4ToSimd2(Simd_FloatType4 value);
inline Simd_FloatType3 tfSimd4ToSimd3(Simd_FloatType4 value);

inline Simd_FloatType4 tfSimd4SplatIndex0(Simd_FloatType4 value);
inline Simd_FloatType4 tfSimd4SplatIndex1(Simd_FloatType4 value);
inline Simd_FloatType4 tfSimd4SplatIndex2(Simd_FloatType4 value);
inline Simd_FloatType4 tfSimd4SplatIndex3(Simd_FloatType4 value);

inline float tfSimd4SelectIndex0(Simd_FloatType4 value);
inline float tfSimd4SelectIndex1(Simd_FloatType4 value);
inline float tfSimd4SelectIndex2(Simd_FloatType4 value);
inline float tfSimd4SelectIndex3(Simd_FloatType4 value);


inline float tfSimd4SelectIndex0(Simd_FloatType4 value) { 
#if defined(TF_FEATURE_CPU_SSE)
  return _mm_cvtss_f32(value);
#elif defined(TF_FEATURE_CPU_SCALAR)
  return value.v[0];
#endif
}
inline float tfSimd4SelectIndex1(Simd_FloatType4 value) { return tfSimd4SelectIndex0(tfSimd4SplatIndex1(value)); }
inline float tfSimd4SelectIndex2(Simd_FloatType4 value) { return tfSimd4SelectIndex0(tfSimd4SplatIndex2(value)); }
inline float tfSimd4SelectIndex3(Simd_FloatType4 value) { return tfSimd4SelectIndex0(tfSimd4SplatIndex3(value)); }

inline Simd_FloatType tfSimd4ToSimd1(Simd_FloatType4 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return value;
#endif
}

inline Simd_FloatType2 tfSimd4ToSimd2(Simd_FloatType4 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return value;
#endif
}
inline Simd_FloatType3 tfSimd4ToSimd3(Simd_FloatType4 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return value;
#endif
}

inline Simd_FloatType4 tfSimd4SplatIndex0(Simd_FloatType4 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_shuffle_ps(value, value, _MM_SHUFFLE(0, 0, 0, 0));
#endif
}

inline Simd_FloatType4 tfSimd4SplatIndex1(Simd_FloatType4 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_shuffle_ps(value, value, _MM_SHUFFLE(1, 1, 1, 1));
#endif
}

inline Simd_FloatType4 tfSimd4SplatIndex2(Simd_FloatType4 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_shuffle_ps(value, value, _MM_SHUFFLE(2, 2, 2, 2));
#endif
}

inline Simd_FloatType4 tfSimd4SplatIndex3(Simd_FloatType4 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_shuffle_ps(value, value, _MM_SHUFFLE(3, 3, 3, 3));
#endif
}

//float tfSimd4SelectIndex0(Simd_FloatType4 value) { 
//  return _mm_shuffle_ps(value, value, _MM_SHUFFLE(0, 0, 0, 0)); 
//}
//float tfSimd4SelectIndex1(Simd_FloatType4 value){}
//float tfSimd4SelectIndex2(Simd_FloatType4 value){}
//float tfSimd4SelectIndex3(Simd_FloatType4 value){}


inline Simd_FloatType4 tfSimdSplat4f(float value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_set1_ps(value);
#else
    return { value, value, value, value };
#endif
}

inline Simd_Int32Type4 tfSimdSplat4i(int32_t value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_set1_epi32(value);
#else
    return { value, value, value, value };
#endif
}
