#pragma once
#include"WorldTransform.h"
#include"ViewProjection.h"
#include"state/ParticlePlaneState.h"

struct Particle_param
{
	WorldTransform worldTransform_;
};

class Particle
{
public:
	Particle() {};
	~Particle() { delete state_; }

	void Initialize(IParticleState *state ,const uint32_t NumInstance = 1);

	void Draw(WorldTransform worldTransform,ViewProjection viewProjection);

	void SetTexHandle(uint32_t tex) { texhandle = tex; }

#pragma region get

	uint32_t GetTexhandle() { return texhandle; }
	const uint32_t GetNumInstance() const{ return NumInstance_; }
	WorldTransform GetWorldTransform() { return worldTransform_; }
	const uint32_t NumInstancig() { return NumInstance_; }

#pragma endregion 
private:

	WorldTransform worldTransform_ = {};
	ViewProjection viewProjection = {};

	IParticleState* state_ = nullptr;
	uint32_t NumInstance_ = 20;

	uint32_t texhandle = 0;
	
	
};




