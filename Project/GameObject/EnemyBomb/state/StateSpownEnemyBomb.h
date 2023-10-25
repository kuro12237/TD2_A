#pragma once
#include"IstateEnemyBomb.h"
#include"GameObject/EnemyBomb/EnemyBomb.h"
#include"VectorTransform.h"
#include"MatrixTransform.h"

class stateSpownEnemyBomb : public IstateEnemyBomb
{
public:

	~stateSpownEnemyBomb() {};

	void Move(WorldTransform& worldTransform, EnemyBomb* state)override;

private:


};