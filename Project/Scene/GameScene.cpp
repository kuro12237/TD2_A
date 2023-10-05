#include "GameScene.h"

void GameScene::Initialize(GameManager* scene)
{
	viewProjection.Initialize({ 0.2f,-0.6f,0.0f }, { 11.0f,5.0f,-15 });
	player_ = make_unique<Player>();
	player_->Initialize();
	scene;
	MainCamera::Initialize();
}

void GameScene::Update(GameManager* scene)
{
	ImGui::Begin("ChangeDebugScene");
	ImGui::Text("9 key");
	ImGui::End();

	if (Input::GetInstance()->PushKeyPressed(DIK_9))
	{
		scene->ChangeState(new DebugScene);
		return;
	}

	player_->Update();
	
	MainCamera::Update();

	viewProjection = MainCamera::GetViewProjection();

	viewProjection = DebugTools::ConvertViewProjection(viewProjection);
	
}

void GameScene::Draw(GameManager* scene)
{
	player_->Draw(viewProjection);
	scene;
}
