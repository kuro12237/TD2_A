#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include"CollisionManager.h"
#include"ColliderConfig.h"
#include"VectorTransform.h"
#include"GameObject/Player/Player.h"

class Enemy : public Collider {
public:

	Enemy();
	~Enemy();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(const Vector3& position);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="viewProjection"></param>
	void Draw(ViewProjection viewProjection);

	void EnemyMove();

	Vector3 GetWorldPosition()override;

	void OnCollision()override;
	
	// ベクトル分解
	void VelocityDecomposition(Vector3 velo, float angle); // velo = playerの速度, angle = playerとenemyの角度


private:

	
	WorldTransform worldTransform_;
	unique_ptr<Model>model_;
	float speed = 3.0f;
	Vector3 velocity;
	Player* player_;
	bool isMove_;
};
