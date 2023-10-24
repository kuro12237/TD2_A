#pragma once
#include"Model.h"
#include"state/StateMoveEnemyBomb.h"
#include"GameObject/Player/Player.h"

class EnemyBomb
{
public:
	EnemyBomb() {};
	~EnemyBomb() { delete state_; }

	void Initialize(Vector3 position);

	void SetPlayer(Player* player) { player_ = player; }

	void Update();

	void Draw(ViewProjection view);

	Player* GetPlayer() { return player_; }

	Vector3 GetPlayerTranslate() { return player_->GetWorldPosition(); }
	Vector3 GetVelocity() { return velocity_; }
private:

	IstateEnemyBomb* state_ = nullptr;
	WorldTransform worldTransform_{};

	Player* player_ = nullptr;

	unique_ptr<Model>model = nullptr;
	uint32_t texHandle = 0;
	Vector3 velocity_ = {};
	uint32_t LerpTime = 0;

};





