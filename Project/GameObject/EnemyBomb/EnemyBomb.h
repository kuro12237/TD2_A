#pragma once
#include"Model.h"
#include"state/StateMoveEnemyBomb.h"
#include"state/StateBreakEnemyBomb.h"
#include"state/StateSpownEnemyBomb.h"
#include"GameObject/Player/Player.h"
#include"GameObject/Score/Score.h"

class EnemyBomb: public Collider
{
public:
	EnemyBomb() {};
	~EnemyBomb() { delete state_; }

	void Initialize(Vector3 position,uint32_t texHandle);

	void SetPlayer(Player* player) { player_ = player; }

	void Update();

	void Draw(ViewProjection view);

	Vector3 GetWorldPosition()override;
	void OnCollision()override;
	Vector3 GetVelocity()override;

	void SetIsDead(bool f) { IsDead = f; }
	bool GetIsDead() { return IsDead; }

	void ChangeState(IstateEnemyBomb* state);
	void SetModelRadious(float r) { Radious += r; }
	float GetModelRadions() {return Radious; }

	void SetModelColor(Vector4 c) { model->SetColor(c);}

	Player* GetPlayer() { return player_; }
	Vector3 GetPlayerTranslate() { return player_->GetWorldPosition(); }

	Model* GetModel() { return model.get(); }
private:

	IstateEnemyBomb* state_ = nullptr;
	WorldTransform worldTransform_{};

	Player* player_ = nullptr;

	unique_ptr<Model>model = nullptr;
	uint32_t texHandle = 0;
	
	bool IsDead = false;

	float Radious = 0.5f;
	bool SceneChangeFlag = false;
};





