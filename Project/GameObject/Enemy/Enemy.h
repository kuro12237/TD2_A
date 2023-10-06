#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"

class Enemy {
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

private:

	WorldTransform worldTransform_;
	unique_ptr<Model>model_;
};
