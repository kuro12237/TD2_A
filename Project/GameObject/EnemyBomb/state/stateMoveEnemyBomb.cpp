#include "StateMoveEnemyBomb.h"


void stateMoveEnemyBomb::Move(WorldTransform& worldTransform, EnemyBomb* state)
{
	worldTransform.translate.x = worldTransform.translate.x + state->GetVelocity().x;
	worldTransform.translate.z = worldTransform.translate.z + state->GetVelocity().z;

	//worldTransform.translate = VectorTransform::Add(state->GetVelocity(), worldTransform.translate);
}
