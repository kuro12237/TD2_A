#include "GameManager.h"

GameManager::GameManager()
{
	Cleyera::Initialize();
	Scene_ = new TutorialScene();
	Scene_->Initialize();

	Grid* grid = new Grid();
	grid->Initialize();
	//GridCommand���Z�b�g
	DebugTools::addCommand(grid,"Grid");

	DebugCamera* debugcamera = new DebugCamera();
	debugcamera->Initialize();
	DebugTools::addCommand(debugcamera,"DebugCamera");
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
	
		DebugTools::UpdateExecute(0);
		DebugTools::UpdateExecute(1);
		Scene_->Update(this);
	
		DebugTools::DrawExecute(0);
		DebugTools::DrawExecute(1);
		Scene_->Draw();

		Cleyera::EndFlame();
	}
}

void GameManager::ChangeState(IScene *newScene)
{
	TextureManager::AllUnTexture();
	delete Scene_;
	Scene_ = newScene;
	Scene_->Initialize();

}
