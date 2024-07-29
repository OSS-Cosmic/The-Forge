

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


