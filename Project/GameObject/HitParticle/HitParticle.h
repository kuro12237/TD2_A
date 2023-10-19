#pragma once
#include"Particle/Particle.h"
#include"VectorTransform.h"

class HitParticle
{
public:
	HitParticle() {};
	~HitParticle() {};

	void Initialize();

	void Update();

	void Draw(ViewProjection view);

	void Spown(Vector3 position);

private:

	void Move();

	list<Particle_param> ListParticle_{};
	unique_ptr<Particle> particle_ = nullptr;
	uint32_t texHandle = 0;

	random_device randSeed{};
};

