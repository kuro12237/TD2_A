#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include"CollisionManager.h"
#include"ColliderConfig.h"
#include"VectorTransform.h"
#include"GameObject/Player/Player.h"
#include"GameObject/PhysicsFanc.h"
#include"GameObject/MapWall/IMapWall.h"

class Enemy : public Collider , public IMapWall
{
public:

	Enemy() {};
	~Enemy() {};

	/// <summary>
	/// ‰Šú‰»
	/// </summary>
	void Initialize(const Vector3& position);

	/// <summary>
	/// XV
	/// </summary>
	void Update();

	/// <summary>
	/// •`‰æ
	/// </summary>
	/// <param name="viewProjection"></param>
	void Draw(ViewProjection viewProjection);

	void EnemyMove();

	Vector3 GetWorldPosition()override;

	void SetPlayer(Player* player) { player_ = player; }

	void OnCollision()override;

	void OnTopWall()override;
	void OnBottomWall()override;
	void OnLeftWall()override;
	void OnRightWall()override;

private:


	WorldTransform worldTransform_ = {};
	unique_ptr<Model>model_ = nullptr;
	uint32_t texHandle_ = 0;
	Vector3 velocity = {};
	Player* player_ = nullptr;
	bool isMove_ = false;
};