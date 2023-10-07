#pragma once
#include"IParticleState.h"
#include"CreateResource.h"

class ParticlePlaneState: public IParticleState
{
public:
	ParticlePlaneState() {};
	~ParticlePlaneState() {};

	void Initialize(Particle* state)override;

	void Draw(Particle* state)override;


private:

	list<SModelData>modelData_ = {};


};



