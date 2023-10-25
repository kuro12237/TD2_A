#include "StateBreakEnemyBomb.h"

void StateBreakEnemyBomb::Move(WorldTransform& worldTransform, EnemyBomb* state)
{
	scaleTimer_++;
	state;
	worldTransform.rotation = VectorTransform::Add(worldTransform.rotation, RotateSoeed);


	color = VectorTransform::Subtruct(state->GetModel()->GetColor(), {0.005f,0.0075f,0.05f,0.0f});
	if (color.x <= 0.1f && color.y <= 0.1f && color.z <= 0.1f && color.w == 1.0f)
	{
		state->SetIsDead(true);
	}

	state->SetModelColor(color);

	if (scaleTimer_>=300)
	{
		return;
	}
	state->SetModelRadious(ScaleSpeed_.x);
	worldTransform.scale = VectorTransform::Add(worldTransform.scale, ScaleSpeed_);
}


void StateBreakEnemyBomb::ColorFanc()
{


}
