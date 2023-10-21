#pragma once
#include"WorldTransform.h"
#include"ViewProjection.h"

class EnemyBomb;
class IstateEnemyBomb
{
public:
	virtual ~IstateEnemyBomb() {};

	virtual void Move(WorldTransform &worldTransform, EnemyBomb* state) = 0;

};

