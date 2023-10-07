#pragma once

class Particle;
class IParticleState
{
public:
	
	virtual ~IParticleState() {};

	virtual void Initialize(Particle *state) = 0;

	virtual void Draw(Particle *state) = 0;

private:

};

