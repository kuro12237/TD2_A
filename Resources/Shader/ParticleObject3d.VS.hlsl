#include"ParticleObject3d.hlsli"

struct TransformationMatrix {
	float32_t4x4 WVP;
};

StructuredBuffer<TransformationMatrix > gTransformationMatrix  : register(t0);

struct VertexShaderInput {
	float32_t4 position : POSITION0;
	float32_t2 texcoord : TEXCOORD0;
};

VertexShaderOutput main(VertexShaderInput input,uint32_t instanceId : SV_InstanceID) {
	VertexShaderOutput output;
	output.position = mul(input.position, gTransformationMatrix[instanceId].WVP);
	output.texcoord = input.texcoord;
	return output;
}