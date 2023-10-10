#pragma once
#include"IParticleState.h"
#include"CreateResource.h"

#include"GraphicsPipelineManager.h"
#include"Particle/Particle.h"
#include"Graphics/TextureManager/TextureManager.h"

class ParticlePlaneState: public IParticleState
{
public:
	ParticlePlaneState() {};
	~ParticlePlaneState() {};

	void Initialize(Particle* state)override;

	void Draw(Particle* state, WorldTransform worldTransform, ViewProjection viewprojection)override;


private:

	void CommandCall(uint32_t TexHandle);
	
	uint32_t NumInstansing = 0;
	bool NumInstansingLock = false;

	uint32_t dsvIndex = 0;

	Vector4 testColor = { 1,1,1,1 };

	Vector3 testRotate = { };
	Vector3 testTrans = {};

	Vector4 pos = { 0,0,0,1 };
	float size = 0.5f;

	const uint32_t VertexSize = 4;
	const uint32_t IndexSize = 6;
	ResourcePeroperty resource_ = {};

};



