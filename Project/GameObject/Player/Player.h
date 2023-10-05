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
	
	void AddfrictionCoefficient();
	
	Vector3 NoramalizeLerp(Vector3 v1, Vector3 v2);

	
	unique_ptr<Model>model_ = nullptr;
	unique_ptr<Model>PlaneModel_ = nullptr;
	unique_ptr<Model>reticleTestModel = nullptr;

	WorldTransform worldTransform_ = {};
	WorldTransform reticleWorldTransform{};
	WorldTransform PlaneworldTransform_ = {};

	Vector3 speed = { 0.0f,0.0f,0.0f};
	Vector3 RPLerp = {};
	/// <summary>
	/// –€ŽC
	/// </summary>
	const float frictionCoefficient = 0.05f;

	

	uint32_t frictionCoefficientTimer = 0;

	uint32_t texHandle = 0;
};
