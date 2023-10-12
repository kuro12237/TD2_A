#pragma once

#include"Particle/Particle.h"
#include"Graphics/TextureManager/TextureManager.h"

class PlayerParticle
{
public:
	PlayerParticle() {};
	~PlayerParticle() {};


	void Initialize();

	void Update(Vector3 position);

	void Draw(ViewProjection view);


private:


	list<Particle_param> particles_param_{};
	unique_ptr<Particle>particle_{};

	uint32_t spownTime = 0;

	uint32_t texHandle = 0;
};


