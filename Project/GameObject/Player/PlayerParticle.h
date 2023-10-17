#pragma once

#include"Particle/Particle.h"
#include"Graphics/TextureManager/TextureManager.h"
#include"VectorTransform.h"


enum SParticleUV
{
	RT,
	RB,
	LT,
	LB
};

class PlayerParticle
{
public:
	PlayerParticle() {};
	~PlayerParticle() {};


	void Initialize();

	void Spown(Vector3 position);

	void Update();

	void Draw(ViewProjection view);
private:

	void ParticleUV(Vector3& s, Vector3& t);

	list<Particle_param> particles_param_{};
	unique_ptr<Particle>particle_{};

	random_device seedGenerator;

	uint32_t spownTime = 0;
	uint32_t texHandle = 0;
	
};


