#include"Particle/Particle.h"


void Particle::Initialize(IParticleState* state)
{
	state_ = state;

	state_->Initialize(this);

}

void Particle::Draw(WorldTransform worldTransform, ViewProjection viewProjection)
{
	worldTransform;
	viewProjection;
}