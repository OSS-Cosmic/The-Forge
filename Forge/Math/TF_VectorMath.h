
// ================================================================================================
// -*- C++ -*-
// File: vectormath/vectormath.hpp
// Author: Guilherme R. Lampert
// Created on: 30/12/16
// Brief: This header exposes the Sony Vectormath library types and functions into the global scope.
// ================================================================================================

#ifndef VECTORMATH_HPP
#define VECTORMATH_HPP

#include "Forge/Config.h"
#include "Forge/TF_Config.h"
#include "vectormath_settings.hpp"

// Sony's library includes:
#if defined(TF_FEATURE_CPU_SSE) // SSE
    #include "sse/vectormath.hpp"
    using namespace Vectormath::SSE;
#elif defined(TF_FEATURE_CPU_NEON) 
	#include "neon/vectormath.hpp"
	using namespace Vectormath::Neon;
#else 
    #include "scalar/vectormath.hpp"
    using namespace Vectormath::Scalar;
#endif // Vectormath mode selection

//========================================= #TheForgeMathExtensionsBegin ================================================
//========================================= #TheForgeAnimationMathExtensionsBegin =======================================
#include "soa/soa.hpp"
using namespace Vectormath::Soa;
//========================================= #TheForgeAnimationMathExtensionsEnd =======================================
//========================================= #TheForgeMathExtensionsEnd ================================================

#include "vec2d.hpp"  // - Extended 2D vector and point classes; not aligned and always in scalar floats mode.
#include "common.hpp" // - Miscellaneous helper functions.

using namespace Vectormath;

#endif // VECTORMATH_HPP
