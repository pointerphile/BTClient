Texture2D g_txDiffuse : register(t0);
SamplerState sample0 : register(s0);

struct PS_INPUT {
	float4 p : SV_POSITION;
	float2 t : TEXCOORD0;
};

float4 main(PS_INPUT input) : SV_Target{
	return g_txDiffuse.Sample(sample0, input.t);
}