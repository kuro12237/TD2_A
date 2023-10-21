#include "StateMoveEnemyBomb.h"

void stateMoveEnemyBomb::Move(WorldTransform& worldTransform, EnemyBomb* state)
{
	
	
	worldTransform.translate = VectorTransform::Add({0.01f,0,0}, worldTransform.translate);
	

	state;
}
