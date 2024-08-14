/* Copyright (c) 2021 Hans-Kristian Arntzen
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#ifndef R_HASHER_H
#define R_HASHER_H

//#include "Forge/TF_String.h"
#include "Forge/TF_Types.h"

typedef uint64_t hash64_t;
typedef uint32_t hash32_t;
static hash64_t const TF_HASH_INITIAL_VALUE_64 = 0xcbf29ce484222325ull;
static hash32_t const TF_HASH_INITIAL_VALUE_32 = 0xcbf29ce4ul;

static inline hash64_t tfHash64_u32(hash64_t hash, uint32_t value) { return (hash * 0x100000001b3ull) ^ value; }
static inline hash64_t tfHash64_s32(hash64_t hash, int32_t value) { return tfHash64_u32(hash, value); }
static inline hash64_t tfHash64_u64(hash64_t hash, uint64_t value) {
    hash = tfHash64_u32(hash, value & 0xffffffffu);
    hash = tfHash64_u32(hash, value >> 32);
    return hash;
}

static inline hash64_t hash64_f32(hash64_t hash, float value) {
    union {
        float    f32;
        uint32_t u32;
    } u;
    u.f32 = value;
    return tfHash64_u32(hash, u.u32);
}

static inline hash64_t tfHash64_data(hash64_t hash, const void* data, size_t size) {
    for (size_t i = 0; i < size; i++)
        hash = (hash * 0x100000001b3ull) ^ ((uint8_t*)data)[i];
    return hash;
}

static inline hash32_t tfHash32_u32(hash32_t hash, uint32_t value) { return (hash * 0x100000001b3ull) ^ value; }
static inline hash32_t tfHash32_s32(hash32_t hash, int32_t value) { return tfHash32_u32(hash, value); }
static inline hash32_t tfHash32_u64(hash32_t hash, uint64_t value) {
    hash = tfHash32_u32(hash, value & 0xffffffffu);
    hash = tfHash32_u32(hash, value >> 32);
    return hash;
}

static inline hash32_t hash32_f32(hash32_t hash, float value) {
    union {
        float    f32;
        uint32_t u32;
    } u;
    u.f32 = value;
    return tfHash32_u32(hash, u.u32);
}

static inline hash32_t tfHash32_data(hash32_t hash, const void* data, size_t size) {
    for (size_t i = 0; i < size; i++)
        hash = (hash * 0x100000001b3ull) ^ ((uint8_t*)data)[i];
    return hash;
}


#endif
