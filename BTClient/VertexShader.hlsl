//�������̴��� ���������� ����1�� ������ ó���ȴ�.

struct VS_INPUT {
	float4 p : POSITION;
	float2 t : TEXCOORD;
};
struct PS_INPUT {
	float4 p : SV_POSITION;
	float2 t : TEXCOORD0;
};
typedef PS_INPUT VS_OUTPUT;

VS_OUTPUT main(VS_INPUT Input) {
	VS_OUTPUT output = (VS_OUTPUT)0;
	output.p = Input.p;
	output.t = Input.t;
	return output;
}