#pragma once
#include"ViewProjection.h"
#include"WorldTransform.h"
#include"Input.h"
#include"VectorTransform.h"

class MainCamera
{
public:

	static MainCamera* GetInstance();

	static void Initialize();

	static void Update(WorldTransform w);

	static ViewProjection GetViewProjection(){ return MainCamera::GetInstance()->viewProjection; }

	static void SetParent(const WorldTransform* worldTransform) { MainCamera::GetInstance()->worldTransform_.parent = worldTransform; }
private:

	ViewProjection viewProjection{};
	WorldTransform worldTransform_{};
	
	float rotate = 0;
	const float speed = 0.2f;

	//Singleton
	MainCamera() = default;
	~MainCamera() = default;
	MainCamera(const MainCamera&) = delete;
	const MainCamera& operator=(const MainCamera&) = delete;
};



