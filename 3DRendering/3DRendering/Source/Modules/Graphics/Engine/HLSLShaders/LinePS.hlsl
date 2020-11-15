float4 main(float4 input : SV_POSITION) : SV_TARGET
{
    return pow(float4(1.0f, 0.f, 0.f, 1.0f), float4(1.f / 2.2f, 1.f / 2.2f, 1.f / 2.2f, 1.f)); // Gamma correction
}