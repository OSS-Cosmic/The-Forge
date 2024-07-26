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

#include "Forge/TF_FileSystem.h"

#include <stdbool.h>
#include <stdarg.h>

#ifndef FILENAME_NAME_LENGTH_LOG
#define FILENAME_NAME_LENGTH_LOG 23
#endif

#ifndef INDENTATION_SIZE_LOG
#define INDENTATION_SIZE_LOG 4
#endif

#ifndef LEVELS_LOG
#define LEVELS_LOG 6
#endif

#define CONCAT_STR_LOG_IMPL(a, b) a##b
#define CONCAT_STR_LOG(a, b)      CONCAT_STR_LOG_IMPL(a, b)

#ifndef ANONIMOUS_VARIABLE_LOG
#define ANONIMOUS_VARIABLE_LOG(str) CONCAT_STR_LOG(str, __LINE__)
#endif

// If you add more levels don't forget to change LOG_LEVELS macro to the actual number of levels
typedef enum LogLevel
{
    eNONE = 0,
    eRAW = 1,
    eDEBUG = 2,
    eINFO = 4,
    eWARNING = 8,
    eERROR = 16,
    eALL = ~0
} LogLevel;


typedef void (*LogCallbackFn)(void* user_data, const char* message);
typedef void (*LogCloseFn)(void* user_data);
typedef void (*LogFlushFn)(void* user_data);


#ifdef __cplusplus
extern "C"
{
#endif

    // Initialization/Exit functions are thread unsafe
    // appName   used to create appName.log. Pass NULL to disable
    // level     mask of LogLevel bits. Log is ignored if its level is missing in mask. Use eALL to enable full log
    FORGE_API void initLog(const char* appName, LogLevel level);
    FORGE_API void exitLog(void);

    FORGE_API void addLogFile(const char* filename, FileMode file_mode, LogLevel log_level);
    FORGE_API void addLogCallback(const char* id, uint32_t log_level, void* user_data, LogCallbackFn callback, LogCloseFn close,
                                  LogFlushFn flush);

    FORGE_API void writeLogVaList(uint32_t level, const char* filename, int line_number, const char* message, va_list args);
    //+V576, function:writeLog, format_arg:4, ellipsis_arg:5
    FORGE_API void writeLog(uint32_t level, const char* filename, int line_number, const char* message, ...);
    //+V576, function:writeRawLog, format_arg:3, ellipsis_arg:4
    FORGE_API void writeRawLog(uint32_t level, bool error, const char* message, ...);

    //+V576, function:_FailedAssert, format_arg:4, ellipsis_arg:5
    FORGE_API void _FailedAssert(const char* file, int line, const char* statement, const char* msg, ...);

    // Usage:
    // puts(humanReadableTime(ns).str);
    // printf("%s\n", humanReadableTime(ms * 1000).str);
    // humanReadableSize(9238412498).str;
    struct HumanReadableValue
    {
        char str[16];
    };
    FORGE_API struct HumanReadableValue humanReadableSSize(ssize_t size);
    FORGE_API struct HumanReadableValue humanReadableTimeD(double nanoseconds);

    static inline struct HumanReadableValue humanReadableSize(size_t size) { return humanReadableSSize((ssize_t)size); }
    static inline struct HumanReadableValue humanReadableTime(int64_t nanoseconds) { return humanReadableTimeD((double)nanoseconds); }

    FORGE_API void _EnableInteractiveMode(bool isInteractivenMode);
    FORGE_API bool _IsInteractiveMode(void);

#ifdef __cplusplus
} // extern "C"
#endif

#if defined(TF_TARGET_WINDOWS) || defined(XBOX)
#define CHECK_HRESULT(exp)                                                       \
    do                                                                           \
    {                                                                            \
        HRESULT hres = (exp);                                                    \
        if (!SUCCEEDED(hres))                                                    \
        {                                                                        \
            LOGF(eERROR, "%s: FAILED with HRESULT: 0x%X", #exp, (uint32_t)hres); \
            ASSERT(false);                                                       \
        }                                                                        \
    } while (0)
#endif

#if _MSC_VER >= 1400
// To make MSVC 2005 happy
#pragma warning(disable : 4996)
#define assume(x) __assume(x)
#define no_alias  __declspec(noalias)
#else
#define assume(x)
#define no_alias
#endif

// PVS-Studio isn't convinced an assert macro is real unless it branches on the value being asserted.
#if defined(FORGE_DEBUG) || defined(PVS_STUDIO)

// Checks that an expression if true. Becomes a no-op in release.
#define ASSERTMSG(b, msgFmt, ...)                                                                                \
    do                                                                                                           \
    {                                                                                                            \
        (void)sizeof(b); /* This sizeof must compile, otherwise when disabling ASSERTs the code won't compile */ \
        b ? (void)0 : _FailedAssert(__FILE__, __LINE__, #b, "" msgFmt, ##__VA_ARGS__);                           \
    } while (0)

// Version of ASSERT intended to be used in if statements.
// Expression is evaluated in both debug and release. Assertion only happens in debug.
#define VERIFYMSG(b, msgFmt, ...) ((b) || (_FailedAssert(__FILE__, __LINE__, #b, "" msgFmt, ##__VA_ARGS__), false))

#else

//-V:ASSERT:627
//-V:ASSERT:568
#define ASSERTMSG(b, msgFmt, ...) \
    do                            \
    {                             \
        ((void)sizeof(b));        \
    } while (0)
#define VERIFYMSG(b, msgFmt, ...) ((b) || (LOGF(eERROR, "VERIFY(" #b ") failed. " msgFmt, ##__VA_ARGS__), false))

#endif

#define ASSERT(b) ASSERTMSG((b), "")
#define VERIFY(b) VERIFYMSG((b), "")

// ASSERTFAIL() is ASSERT(false) that doesn't cause issues with PVS-Studio
#ifdef PVS_STUDIO
#define ASSERTFAIL(msgFmt, ...) \
    do                          \
    {                           \
    } while (0)
#else
#define ASSERTFAIL(msgFmt, ...) ASSERTMSG(false, msgFmt, ##__VA_ARGS__)
#endif

// Usage: LOGF(LogLevel::eINFO | LogLevel::eDEBUG, "Whatever string %s, this is an int %d", "This is a string", 1)
#define LOGF(log_level, ...) writeLog((log_level), __FILE__, __LINE__, __VA_ARGS__)
// Usage: LOGF_IF(LogLevel::eINFO | LogLevel::eDEBUG, boolean_value && integer_value == 5, "Whatever string %s, this is an int %d", "This is
// a string", 1)
#define LOGF_IF(log_level, condition, ...) \
    ((condition) ? writeLog((log_level), __FILE__, __LINE__, __VA_ARGS__) : (void)sizeof(condition)) //-V568
//
// #define LOGF_SCOPE(log_level, ...) LogLogScope ANONIMOUS_VARIABLE_LOG(scope_log_){ (log_level), __FILE__, __LINE__, __VA_ARGS__ }

// Usage: RAW_LOGF(LogLevel::eINFO | LogLevel::eDEBUG, "Whatever string %s, this is an int %d", "This is a string", 1)
#define RAW_LOGF(log_level, ...) writeRawLog((log_level), false, __VA_ARGS__)
// Usage: RAW_LOGF_IF(LogLevel::eINFO | LogLevel::eDEBUG, boolean_value && integer_value == 5, "Whatever string %s, this is an int %d",
// "This is a string", 1)
#define RAW_LOGF_IF(log_level, condition, ...) \
    ((condition) ? writeRawLog((log_level), false, __VA_ARGS__) : (void)sizeof(condition)) //-V568

#if defined(FORGE_DEBUG)

// Usage: DLOGF(LogLevel::eINFO | LogLevel::eDEBUG, "Whatever string %s, this is an int %d", "This is a string", 1)
#define DLOGF(log_level, ...)                   LOGF(log_level, __VA_ARGS__)
// Usage: DLOGF_IF(LogLevel::eINFO | LogLevel::eDEBUG, boolean_value && integer_value == 5, "Whatever string %s, this is an int %d", "This
// is a string", 1)
#define DLOGF_IF(log_level, condition, ...)     LOGF_IF(log_level, condition, __VA_ARGS__)

// Usage: DRAW_LOGF(LogLevel::eINFO | LogLevel::eDEBUG, "Whatever string %s, this is an int %d", "This is a string", 1)
#define DRAW_LOGF(log_level, ...)               RAW_LOGF(log_level, __VA_ARGS__)
// Usage: DRAW_LOGF_IF(LogLevel::eINFO | LogLevel::eDEBUG, boolean_value && integer_value == 5, "Whatever string %s, this is an int %d",
// "This is a string", 1)
#define DRAW_LOGF_IF(log_level, condition, ...) RAW_LOGF_IF(log_level, condition, __VA_ARGS__)

#else

// Usage: DLOGF(LogLevel::eINFO | LogLevel::eDEBUG, "Whatever string %s, this is an int %d", "This is a string", 1)
#define DLOGF(log_value, ...) \
    do                        \
    {                         \
    } while (0)
// Usage: DLOGF_IF(LogLevel::eINFO | LogLevel::eDEBUG, boolean_value && integer_value == 5, "Whatever string %s, this is an int %d", "This
// is a string", 1)
#define DLOGF_IF(log_value, condition, ...) \
    do                                      \
    {                                       \
        ((void)sizeof(condition));          \
    } while (0)

// Usage: DRAW_LOGF(LogLevel::eINFO | LogLevel::eDEBUG, "Whatever string %s, this is an int %d", "This is a string", 1)
#define DRAW_LOGF(log_level, ...) \
    do                            \
    {                             \
    } while (0)
// Usage: DRAW_LOGF_IF(LogLevel::eINFO | LogLevel::eDEBUG, boolean_value && integer_value == 5, "Whatever string %s, this is an int %d",
// "This is a string", 1)
#define DRAW_LOGF_IF(log_level, condition, ...) \
    do                                          \
    {                                           \
        ((void)sizeof(condition));              \
    } while (0)

#endif
