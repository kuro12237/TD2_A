#pragma once
#include"GameObject/EnemyBomb/EnemyBomb.h"
#include"GameObject/EnemyBomb/state/IstateEnemyBomb.h"

class StateBreakEnemyBomb: public IstateEnemyBomb
{
public:
	~StateBreakEnemyBomb() {};

	void Move(WorldTransform& worldTransform, EnemyBomb* state)override;

private:
	void ColorFanc();

	const Vector3 ScaleSpeed_ = {0.0125f,0.0125f,0.0125f};
	const Vector3 RotateSoeed = { 0.0f,0.02f,0.0f };

	const Vector4 MaxColor = { 0,0,0,0.0};
	Vector4 color = { 1,0.5f,0,1 };

	uint32_t scaleTimer_ = 0;
};

