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

	Vector3 GetPlayerTranslate() { return player_->GetWorldPosition(); }
private:

	IstateEnemyBomb* state_ = nullptr;
	WorldTransform worldTransform_{};

	Player* player_ = nullptr;

	unique_ptr<Model>model = nullptr;
	uint32_t texHandle = 0;
	

};





