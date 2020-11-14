cbuffer testData : register(b0)
{
    float a;
    float b;
    float c;
    float d;
}

Texture2D g_diffuseTexture : register(t0);
SamplerState g_pointSampler : register(s0);


struct PS_IN
{
    float4 pos : SV_POSITION;
    float3 nor : NORMAL;
    float2 uv : TEXCOORD;
};

float4 main(PS_IN input) : SV_TARGET
{    
    float4 finalColor =  g_diffuseTexture.Sample(g_pointSampler, input.uv);
  
    
    return pow(finalColor, float4(1.f / 2.2f, 1.f / 2.2f, 1.f / 2.2f, 1.f));        // Gamma correction
    
    
    return float4(input.nor, 1.f);
    
	return float4(a, b, c, d);
}