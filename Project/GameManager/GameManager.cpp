#include "GameManager.h"

GameManager::GameManager()
{
	Cleyera::Initialize();
	Scene_ = new GameScene();
	Scene_->Initialize();
}

GameManager::~GameManager()
{
	DebugTools::ClearCommand();
	delete Scene_;
	Cleyera::Finalize();
}

void GameManager::Run()
{
	while (WinApp::WinMsg())
	{
		Cleyera::BeginFlame();
	
		ImGui::Begin("usedescripter");
		ImGui::Text("descripterIndex %d", DescriptorManager::GetIndex());
		ImGui::Text("tex %d", TextureManager::NumLoadTexture());
		ImGui::End();

		Scene_->Update(this);
		
		Scene_->Back2dSpriteDraw();
		Scene_->Object3dDraw();
		Scene_->Flont2dSpriteDraw();

		Cleyera::EndFlame();
	}
}

void GameManager::ChangeState(IScene *newScene)
{
	DebugTools::ClearCommand();
	Audio::SoundUnLoad();
	TextureManager::AllUnTexture();
	DescriptorManager::Clear();

	delete Scene_;
	Scene_ = newScene;
	Scene_->Initialize();
	return;
}
