cbuffer AlwaysChangingBuffer : register(b0)
{
    Matrix g_worldMatrix;
    Matrix g_viewMatrix;
}

cbuffer SometimesChangingBuffer : register(b1)
{
    Matrix g_projectionMatrix;
}

cbuffer AABBBuffer : register(b2)
{
    float x, y, z;
}

struct GSOutput
{
	float4 pos : SV_POSITION;
};

[maxvertexcount(8)]
void main(point float4 input[1] : POSITION, inout LineStream< GSOutput > output)
{
    float4 wsPos = mul(g_worldMatrix, input[0]);
	
	// Get all the 8 corners
    float4 wsPositions[8] =
    {
        wsPos + float4(x, y, z, 0.f),
        wsPos + float4(-x, y, z, 0.f),
        wsPos + float4(-x, y, -z, 0.f),
        wsPos + float4(x, y, -z, 0.f),
        
        wsPos + float4(x, -y, z, 0.f),
        wsPos + float4(-x, -y, z, 0.f),
        wsPos + float4(-x, -y, -z, 0.f),
        wsPos + float4(x, -y, -z, 0.f)
    };

	
    for (uint x = 0; x < 8; ++x)
    {
        float4 csPos = mul(g_projectionMatrix, mul(g_viewMatrix, wsPositions[x]));
        
        GSOutput element;
        element.pos = csPos;
        output.Append(element);
    }

}