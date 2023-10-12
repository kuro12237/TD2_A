#pragma once
#include"WorldTransform.h"
#include"ViewProjection.h"
#include"state/ParticlePlaneState.h"
#include"SParticle.h"


class Particle
{
public:
	Particle() {};
	~Particle() { delete state_; }

	void Initialize(IParticleState *state ,const uint32_t NumInstance = 1);

	void Draw(ViewProjection viewProjection);

	void begin();

#pragma region Set
	void SetTexHandle(uint32_t tex) { texhandle = tex; }
	void SetList(Particle_param particle) { particles_.push_back(particle);}

	void SetListparticles(list<Particle_param> particles) { particles_ = particles; }
#pragma endregion 

#pragma region get

	uint32_t GetTexhandle() { return texhandle; }
	const uint32_t GetNumInstancing() const{ return NumInstance_; }

	list<Particle_param> GetParticles() { return particles_; }
#pragma endregion 
private:



	IParticleState* state_ = nullptr;
	
	uint32_t NumInstance_ = 20;

	uint32_t texhandle = 0;
	
	list<Particle_param> particles_{};
};




