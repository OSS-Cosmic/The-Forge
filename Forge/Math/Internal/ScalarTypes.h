#pragma once
#ifndef TF_MATH_INTERNAL_SCALAR_TYPES_H
#define TF_MATH_INTERNAL_SCALAR_TYPES_H
#include <cstdint>
#include "Forge/TF_Types.h"

struct Tf32x4_s {
    union
    {
        struct
        {
            float x, y, z, w;
        };
        struct
        {
            float r, g, b, a;
        };
        float v[4];
    };
};
TF_COMPILE_ASSERT(sizeof(struct Tf32x4_s) == 4 * 4);

struct Tf32x3_s {
    union
    {
        struct
        {
            float x, y, z;
        };
        struct
        {
            float r, g, b;
        };
        float v[3];
    };

};
TF_COMPILE_ASSERT(sizeof(struct Tf32x3_s) == 3 * 4);

struct Tf64x4_s{
    union
    {
        struct
        {
            double x, y, z, w;
        };
        double v[4];
    };
};
TF_COMPILE_ASSERT(sizeof(struct Tf64x4_s) == 8 * 4);

struct Tu8x3_s {
    union
    {
        struct
        {
            uint8_t x, y, z;
        };
        uint8_t v[3];
    };

};

struct Tf64x3_s{
    union
    {
        struct
        {
            double x, y, z;
        };
        double v[3];
    };
};

struct half
{
};

struct half2
{
};

struct half3
{
};

struct half4
{
};

#endif

