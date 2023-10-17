#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include"CollisionManager.h"
#include"ColliderConfig.h"
#include"VectorTransform.h"
#include"GameObject/Player/Player.h"
#include"GameObject/PhysicsFunc/PhysicsFunc.h"


class Enemy : public Collider {
public:

	Enemy() {};
	~Enemy() {};

	/// <summary>
	/// èâä˙âª
	/// </summary>
	void Initialize(const Vector3& position);

	/// <summary>
	/// çXêV
	/// </summary>
	void Update();

	/// <summary>
	/// ï`âÊ
	/// </summary>
	/// <param name="viewProjection"></param>
	void Draw(ViewProjection viewProjection);

	void EnemyMove();

	Vector3 GetWorldPosition()override;

	void SetPlayer(Player* player) { player_ = player; }

	void OnCollision()override;

private:


	WorldTransform worldTransform_ = {};
	unique_ptr<Model>model_ = nullptr;
	uint32_t texHandle_ = 0;
	Vector3 velocity = {};
	Player* player_ = nullptr;
	bool isMove_ = false;
};