#pragma once
#include"ViewProjection.h"
#include"WorldTransform.h"

class MainCamera
{
public:

	static MainCamera* GetInstance();

	static void Initialize();

	static void Update();

	static ViewProjection GetViewProjection(){ return MainCamera::GetInstance()->viewProjection; }

	static void SetParent(const WorldTransform* worldTransform) { MainCamera::GetInstance()->worldTransform_.parent = worldTransform; }
private:

	ViewProjection viewProjection{};
	WorldTransform worldTransform_{};

	//Singleton
	MainCamera() = default;
	~MainCamera() = default;
	MainCamera(const MainCamera&) = delete;
	const MainCamera& operator=(const MainCamera&) = delete;
};



