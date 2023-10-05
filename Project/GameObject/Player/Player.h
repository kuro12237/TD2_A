#pragma once
#include"Model.h"
#include"WorldTransform.h"
#include"Input.h"
#include"VectorTransform.h"

class Player
{
public:
	Player() {};
	~Player() {};

	void Initialize();

	void Update();

	void Draw(ViewProjection view);
#pragma region get

	Vector3 GetWorldPosition();

#pragma endregion


private:

	void Move();
	
	void Reticle();

	bool isSpeed();
	
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
	/// reticleƒgplayer‚Ì•âŠÔ
	/// </summary>
	Vector3 RPLerp = {};

	/// <summary>
	/// –€ŽC
	/// </summary>
	const float frictionCoefficient = 0.1f;

	uint32_t MoveCoolTime = 0;
	bool MoveFlag = false;

	
	uint32_t texHandle = 0;
};
