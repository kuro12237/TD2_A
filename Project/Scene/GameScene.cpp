#include "GameScene.h"

void GameScene::Initialize(GameManager* scene)
{
	viewProjection.Initialize({ 0.2f,-0.6f,0.0f }, { 11.0f,5.0f,-15 });
	scene;
	timeCount_ = make_unique<TimeCount>();
	timeCount_->Initialize();
}

void GameScene::Update(GameManager* scene)
{
	if (Input::GetInstance()->PushKeyPressed(DIK_9))
	{
		scene->ChangeState(new DebugScene);
		return;
	}


	timeCount_->Update();

	viewProjection.UpdateMatrix();
	viewProjection = DebugTools::ConvertViewProjection(viewProjection);

	/*ImGui::Begin("ChangeDebugScene");
	ImGui::Text("9 key");
	ImGui::End();*/
}

void GameScene::Draw(GameManager* scene)
{
	timeCount_->Draw();
	scene;
}
