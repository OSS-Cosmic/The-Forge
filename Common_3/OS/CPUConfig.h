/*
 * Copyright (c) 2017-2024 The Forge Interactive Inc.
 *
 * This file is part of The-Forge
 * (see https://github.com/ConfettiFX/The-Forge).
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#pragma once
#include "Forge/Config.h"
#include <stdbool.h>

#include "cpu_features_macros.h"
#ifdef CPU_FEATURES_ARCH_AARCH64
#include "cpuinfo_aarch64.h"
#endif

#ifdef CPU_FEATURES_ARCH_X86_64
#include "cpuinfo_x86.h"
#endif


#if defined(__cplusplus)
#define CPU_FEATURE_PREFIX cpu_features::
#else
#define CPU_FEATURE_PREFIX 
#endif
    


typedef enum
{
    SIMD_SSE3,
    SIMD_SSE4_1,
    SIMD_SSE4_2,
    SIMD_AVX,
    SIMD_AVX2,
    SIMD_NEON
} SimdIntrinsic;

typedef struct
{
    char          mName[512];
    SimdIntrinsic mSimd;
#if defined(CPU_FEATURES_ARCH_AARCH64)
    CPU_FEATURE_PREFIX Aarch64Features mFeaturesAarch64;
#endif 

#if defined(CPU_FEATURES_ARCH_X86_64)
    CPU_FEATURE_PREFIX X86Features          mFeaturesX86;
    CPU_FEATURE_PREFIX X86Microarchitecture mArchitectureX86;
#endif

} CpuInfo;

#if defined(ANDROID)
#include <jni.h>
bool initCpuInfo(CpuInfo* outCpuInfo, JNIEnv* pJavaEnv);
#else
bool initCpuInfo(CpuInfo* outCpuInfo);
#endif

FORGE_API CpuInfo* getCpuInfo(void);
