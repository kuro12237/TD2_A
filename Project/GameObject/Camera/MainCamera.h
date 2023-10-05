#pragma once
#include"ViewProjection.h"

class MainCamera
{
public:

	static MainCamera* GetInstance();

	static void Initialize();

	static void Update();

	static ViewProjection GetViewProjection() { return MainCamera::GetInstance()->viewProjection; }

private:

	ViewProjection viewProjection;

	//Singleton
	MainCamera() = default;
	~MainCamera() = default;
	MainCamera(const MainCamera&) = delete;
	const MainCamera& operator=(const MainCamera&) = delete;
};



