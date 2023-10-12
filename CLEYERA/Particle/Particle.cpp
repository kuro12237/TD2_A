#include"Particle/Particle.h"

void Particle::Initialize(IParticleState* state, const uint32_t NumInstance)
{
	if (InitializeLock){
		//Initialize�����Ăяo����Ă���
		LogManager::Log("Particle Initialize ERROR " + name_+"\n");
		//assert(0);
	}
	state_ = state;
	NumInstance_ = NumInstance;
	state_->Initialize(this);
	InitializeLock = true;
}

void Particle::Draw(ViewProjection viewProjection)
{
	if (particles_.size() >=NumInstance_ )
	{
		//Instance�̐���胊�X�g�̐���������ƃG���[
		LogManager::Log("Particle Draw ERROR "+ name_+"\n");
		assert(0);
	}

	state_->Draw(this,particles_,viewProjection);
}

list<Particle_param> Particle::begin()
{
	//�����X�g�ɓo�^���Ă��镨�������ă��X�g������
	//�܂��o�^���Ȃ���
	list<Particle_param> p = particles_;
	particles_.clear();
	return p;
}
