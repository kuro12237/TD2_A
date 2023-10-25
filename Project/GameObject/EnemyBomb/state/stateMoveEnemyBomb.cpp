#include "StateMoveEnemyBomb.h"

void stateMoveEnemyBomb::Move(WorldTransform& worldTransform, EnemyBomb* state)
{
	StateChangeTimer++;

	Vector3 Ppos = state->GetPlayer()->GetWorldPosition();
	Vector3 Epos = state->GetWorldPosition();
	Vector3 v{};
	v = VectorTransform::Subtruct(Ppos, Epos);
	v = VectorTransform::Normalize(v);
	v = VectorTransform::Multiply(v, 0.1f);

	worldTransform.translate.x = worldTransform.translate.x + v.x;
	worldTransform.translate.z = worldTransform.translate.z + v.z;
}
