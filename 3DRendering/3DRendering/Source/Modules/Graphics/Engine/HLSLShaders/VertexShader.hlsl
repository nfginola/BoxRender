static const float4 CUBE[3] =
{
    float4(-1.f, -1.f, 0.03f, 1.f),
    float4(0.f, 1.f, 0.03f, 1.f),
    float4(1.f, -1.f, 0.03f, 1.f)

};

cbuffer testData : register(b0)
{
    float a;    
    float b;
    float c;
    float d;
}

cbuffer AlwaysChangingBuffer : register(b1)
{
    Matrix g_worldMatrix;
    Matrix g_viewMatrix;
}

cbuffer SometimesChangingBuffer : register(b2)
{
    Matrix g_projectionMatrix;
}

struct VS_IN
{
    float4 pos : POSITION;
    float3 nor : NORMAL;
    float2 uv : TEXCOORD;
};

struct VS_OUT
{
    float4 pos : SV_POSITION;
    float3 nor : NORMAL;
    float2 uv : TEXCOORD;
};

VS_OUT main(VS_IN input)
{
    VS_OUT output = (VS_OUT) 0;
    
    output.pos = mul(g_projectionMatrix, mul(g_viewMatrix, mul(g_worldMatrix, input.pos)));
    output.nor = normalize(mul(g_worldMatrix, normalize(float4(input.nor, 0.f))));
    output.uv = input.uv;
    
    return output;
}
