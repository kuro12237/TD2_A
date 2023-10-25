#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include"CollisionManager.h"
#include"ColliderConfig.h"
#include"VectorTransform.h"
#include"GameObject/Player/Player.h"
#include"GameObject/PhysicsFunc/PhysicsFunc.h"
#include"GameObject/MapWall/IMapWall.h"
#include"GameObject/Score/Score.h"

class Enemy : public Collider , public IMapWall
{
public:

	Enemy() {};
	~Enemy() {};

	/// <summary>
	/// ‰Šú‰»
	/// </summary>
	void Initialize(const Vector3& position, uint32_t texHundle);

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
	void RandomMove();

	Vector3 GetWorldPosition()override;

	Vector3 GetVelocity()override;

	void SetPlayer(Player* player) { player_ = player; }
	
	bool IsDead() const { return isDead_; }


	void OnCollision()override;

	void OnTopWall()override;
	void OnBottomWall()override;
	void OnLeftWall()override;
	void OnRightWall()override;

private:

	Vector3 pos_;
	Vector3 playerPos_;
	WorldTransform worldTransform_ = {};
	unique_ptr<Model>model_ = nullptr;
	uint32_t texHandle_ = 0;
	tuple<Vector3, Vector3> velocity_ = {};
	Vector3 speed_ = {};
	Vector3 playerVelo_;
	const float gravity_ = 9.8f;
	const float fallSpeed_ = 1.0f;
	int count_ = 0;
	bool RandFlag = false;
	Vector3 randomSpeed = {};
	int randomX = 0;
	int randomZ = 0;
	float dt = 1.0f / 60.0f;
	float angle = 0;
	float angle2 = 0;
	Player* player_ = nullptr;
	bool isMove_ = false;
	bool isDead_ = false;
};