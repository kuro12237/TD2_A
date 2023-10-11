#include"Particle/Particle.h"


void Particle::Initialize(IParticleState* state, const uint32_t NumInstance)
{
	state_ = state;
	NumInstance_ = NumInstance;

	state_->Initialize(this);

}

void Particle::Draw(WorldTransform worldTransform, ViewProjection viewProjection)
{
	

	worldTransform_ = worldTransform;

	state_->Draw(this,viewProjection);

}