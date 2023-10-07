#pragma once
#include"WorldTransform.h"
#include"ViewProjection.h"
#include"state/ParticlePlaneState.h"


class Particle
{
public:
	Particle() {};
	~Particle() { delete state_; }

	void Initialize(IParticleState *state);


	void Draw(WorldTransform worldTransform,ViewProjection viewProjection);

private:

	WorldTransform worldTransform_ = {};
	ViewProjection viewProjection = {};

	IParticleState* state_ = nullptr;
	
};




