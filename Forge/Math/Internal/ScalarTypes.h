#pragma once
#ifndef TF_MATH_INTERNAL_SCALAR_TYPES_H
#define TF_MATH_INTERNAL_SCALAR_TYPES_H


struct float4
{
    union
    {
        struct
        {
            float x, y, z, w;
        };
        float v[4];
    };
};

struct float4x1 {
  float4 mCol0;
};

struct float4x2
{
  float4 mCol0;
  float4 mCol1;
};

struct float4x3
{
  float4 mCol0;
  float4 mCol1;
  float4 mCol2;
};

struct float4x4
{

  float4 mCol0;
  float4 mCol1;
  float4 mCol2;
  float4 mCol3;
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

