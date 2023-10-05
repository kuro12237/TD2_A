#pragma once
#include"Model.h"
#include"WorldTransform.h"
#include"Input.h"
#include"VectorTransform.h"
#include"Collider.h"
#include"ColliderConfig.h"

#define MAX_MOVE_COOLTIME 120

class Player: public Collider
{
public:
	Player() {};
	~Player() {};

	void Initialize();

	void Update();

	void Draw(ViewProjection view);

	void OnCollision()override;

#pragma region get

	Vector3 GetWorldPosition()override;


#pragma endregion


private:

	void Move();
	
	void Reticle();
	
	void FancFrictionCoefficient();
	
	Vector3 NoramalizeLerp(Vector3 v1, Vector3 v2);

	unique_ptr<Model>model_ = nullptr;
	unique_ptr<Model>PlaneModel_ = nullptr;
	unique_ptr<Model>reticleTestModel = nullptr;

	WorldTransform worldTransform_ = {};
	WorldTransform reticleWorldTransform{};
	WorldTransform PlaneworldTransform_ = {};

	Vector3 Velocity = { 0.0f,0.0f,0.0f};
	
	/// <summary>
	/// reticle�gplayer�̃x�N�g��
	/// </summary>
	Vector3 RPNormalize = {};

	/// <summary>
	/// ���C
	/// </summary>
	const float frictionCoefficient = 0.05f;

	uint32_t MoveCoolTime = 0;
	bool MoveFlag = false;
	const float speed = 4.0f;

	uint32_t texHandle = 0;
};
