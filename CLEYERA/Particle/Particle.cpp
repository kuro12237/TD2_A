#include"Particle/Particle.h"


void Particle::Initialize(IParticleState* state, const uint32_t NumInstance)
{
	state_ = state;
	NumInstance_ = NumInstance;
	state_->Initialize(this);

}

void Particle::Draw(list<Particle_param>particles, ViewProjection viewProjection)
{
	
	if (particles.size() >=NumInstance_ )
	{
		LogManager::Log("particles_Error");
		assert(0);
	}

	particles_ = particles;
	state_->Draw(this,viewProjection);

}