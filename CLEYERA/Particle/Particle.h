#pragma once
#include"WorldTransform.h"
#include"ViewProjection.h"
#include"state/ParticlePlaneState.h"


class Particle
{
public:
	Particle() {};
	~Particle() { delete state_; }

	void Initialize(IParticleState *state ,const uint32_t NumInstance = 1);


	void Draw(WorldTransform worldTransform,ViewProjection viewProjection);

#pragma region get

	const uint32_t GetNumInstance() const{ return NumInstance_; }

#pragma endregion 
private:

	WorldTransform worldTransform_ = {};
	ViewProjection viewProjection = {};

	IParticleState* state_ = nullptr;
	uint32_t NumInstance_ = 1;
	
};




