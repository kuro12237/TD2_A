#include "MainCamera.h"

MainCamera* MainCamera::GetInstance()
{
	static MainCamera instance;
	return &instance;
}

void MainCamera::Initialize()
{
	MainCamera::GetInstance()->viewProjection.Initialize();
	MainCamera::GetInstance()->viewProjection.translation_ = { 0,38.0f,-73.0f };
	
	MainCamera::GetInstance()->viewProjection.rotation_ = { 0.5f,0.0f,0.0f };
}

void MainCamera::Update()
{
	MainCamera::GetInstance()->viewProjection.UpdateMatrix();
}
