cbuffer testData : register(b0)
{
    float a;
    float b;
    float c;
    float d;
}

struct PS_IN
{
    float4 pos : SV_POSITION;
    float3 nor : NORMAL;
    float2 uv : TEXCOORD;
};

float4 main(PS_IN input) : SV_TARGET
{
	return float4(a, b, c, d);
}