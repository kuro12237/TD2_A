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
	/// ������
	/// </summary>
	void Initialize(const Vector3& position);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="viewProjection"></param>
	void Draw(ViewProjection viewProjection);

	void EnemyMove();

	Vector3 GetWorldPosition()override;

	void OnCollision()override;
	
	// �x�N�g������
	
	void VelocityDecomposition(Vector3 velo, float angle); // velo = player�̑��x, angle = player��enemy�̊p�x


private:

	
	WorldTransform worldTransform_;
	unique_ptr<Model>model_;
	float speed = 3.0f;
	Vector3 velocity;
	Player* player_;
	bool isMove_;
};
