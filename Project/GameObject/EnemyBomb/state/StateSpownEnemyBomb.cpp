#include "StateSpownEnemyBomb.h"

void stateSpownEnemyBomb::Move(WorldTransform& worldTransform, EnemyBomb* state)
{
	worldTransform.translate.y += 0.01f;
	
	if (worldTransform.translate.y>=1)
	{
		state->ChangeState(new stateMoveEnemyBomb);
	}
}
