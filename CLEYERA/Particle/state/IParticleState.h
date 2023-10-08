#pragma once
#include"WorldTransform.h"
#include"ViewProjection.h"

class Particle;
class IParticleState
{
public:
	
	virtual ~IParticleState() {};

	virtual void Initialize(Particle *state) = 0;

	virtual void Draw(Particle *state, WorldTransform worldTransform, ViewProjection viewprojection) = 0;

private:

};

