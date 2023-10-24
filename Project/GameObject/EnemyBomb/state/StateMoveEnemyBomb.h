#pragma once
#include"IstateEnemyBomb.h"
#include"GameObject/EnemyBomb/EnemyBomb.h"
#include"VectorTransform.h"
#include"MatrixTransform.h"


class stateMoveEnemyBomb : public IstateEnemyBomb
{
public:

	~stateMoveEnemyBomb() {};

	void Move(WorldTransform& worldTransform, EnemyBomb *state)override;

private:

	Vector3 LerpSpeed = {};

};


