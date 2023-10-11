#include"Particle/Particle.h"


void Particle::Initialize(IParticleState* state, const uint32_t NumInstance)
{
	state_ = state;
	NumInstance_ = NumInstance;
	state_->Initialize(this);

}

void Particle::Draw(ViewProjection viewProjection)
{
	
	if (particles_.size() >=NumInstance_ )
	{
		//Instance�̐���胊�X�g�̐���������ƃG���[
		LogManager::Log("particles_Error");
		assert(0);
	}

	state_->Draw(this,particles_,viewProjection);
}

void Particle::begin()
{
	particles_.clear();
}
