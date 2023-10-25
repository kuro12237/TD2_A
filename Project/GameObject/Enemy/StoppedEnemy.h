#pragma once
#include "math/VectorTransform.h"
#include"Model.h"
#include"WorldTransform.h"
#include"VectorTransform.h"
#include"Collider.h"
#include"ColliderConfig.h"
#include"GameObject/MapWall/MapWall.h"
#include"GameObject/MapWall/IMapWall.h"
#include"GameObject/Player/Player.h"
#include"GameObject/PhysicsFunc/PhysicsFunc.h"
#include <GameObject/Score/Score.h>

class StoppedEnemy : public Collider, public IMapWall {
public:
	void Initialize(const Vector3& pos, uint32_t texHandle);

	void Update();

	void Draw(ViewProjection viewProjection);

	void RandomSpawn(uint32_t texHandle);

	void Move();

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
	float angle = 0;
	float angle2 = 0;
	Player* player_ = nullptr;
	bool isMove_ = false;
	bool isDead_ = false;
	random_device seedGenerator;
	list<shared_ptr<StoppedEnemy>>enemys_;
};
