cbuffer AlwaysChangingBuffer : register(b0)
{
    Matrix g_worldMatrix;
    Matrix g_viewMatrix;
}

cbuffer SometimesChangingBuffer : register(b1)
{
    Matrix g_projectionMatrix;
}

cbuffer BoundingBoxBuffer : register(b2)
{
    float4 g_center;
    float x, y, z;
    Matrix g_rotationMatrix;
}

struct GSOutput
{
	float4 pos : SV_POSITION;
};

//static const float4 quad[4] =
//{
//    float4(-1, 1, 0, 0),
//    float4(1, 1, 0, 0),
//    float4(-1, -1, 0, 0),
//    float4(1, -1, 0, 0),
//};

[maxvertexcount(19)]
void main(point float4 input[1] : POSITION, inout LineStream< GSOutput > output)
{
    float4 wsPos = mul(g_worldMatrix, input[0]);
    wsPos = g_center;
    //float wsPos = float4(0.f, 0.f, 0.f, 1.f);
    
    //float x = 2.f;
    //float y = 2.f;
    //float z = 2.f;
	
	// Get all the 8 corners
    float4 wsPositions[] =
    {
        wsPos + mul(g_rotationMatrix, float4(x, y, z, 0.f)),
        wsPos + mul(g_rotationMatrix, float4(-x, y, z, 0.f)),
        wsPos + mul(g_rotationMatrix, float4(-x, y, -z, 0.f)),
        wsPos + mul(g_rotationMatrix, float4(x, y, -z, 0.f)),
        wsPos + mul(g_rotationMatrix, float4(x, y, z, 0.f)),
        
        wsPos + mul(g_rotationMatrix, float4(x, -y, z, 0.f)),
        wsPos + mul(g_rotationMatrix, float4(-x, -y, z, 0.f)),
        wsPos + mul(g_rotationMatrix, float4(-x, -y, -z, 0.f)),
        wsPos + mul(g_rotationMatrix, float4(x, -y, -z, 0.f)),
        wsPos + mul(g_rotationMatrix, float4(x, -y, z, 0.f)),
        
        // vertical lines
        wsPos + mul(g_rotationMatrix, float4(x, y, z, 0.f)),
        wsPos + mul(g_rotationMatrix, float4(x, -y, z, 0.f)),
               
        wsPos + mul(g_rotationMatrix, float4(-x, y, z, 0.f)),
        wsPos + mul(g_rotationMatrix, float4(-x, -y, z, 0.f)),
          
        wsPos + mul(g_rotationMatrix, float4(-x, y, -z, 0.f)),
        wsPos + mul(g_rotationMatrix, float4(-x, -y, -z, 0.f)),
               
        wsPos + mul(g_rotationMatrix, float4(x, y, -z, 0.f)),
        wsPos + mul(g_rotationMatrix, float4(x, -y, -z, 0.f)),
              
        wsPos + mul(g_rotationMatrix, float4(x, y, z, 0.f))

    };


    // top and bottom
    for (uint i = 0; i < 10; ++i)
    {
        float4 csPos = mul(g_projectionMatrix, mul(g_viewMatrix, wsPositions[i]));
        
        GSOutput element;
        element.pos = csPos;
        output.Append(element);
        
        if (i == 4)
            output.RestartStrip();
    }

    
    output.RestartStrip();
    
    // vertical lines
    for (uint a = 0; a < 8; ++a)
    {
        float4 csPos = mul(g_projectionMatrix, mul(g_viewMatrix, wsPositions[a + 10]));
        
        GSOutput element;
        element.pos = csPos;
        output.Append(element);
        
        if ((a + 1) % 2 == 0 && a != 0)
        {
            output.RestartStrip();

        }
    
    }

}