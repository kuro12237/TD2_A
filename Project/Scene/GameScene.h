#pragma once
#include"IScene.h"
#include"GameManager.h"
#include"GameObject/Player/Player.h"
#include"GameObject/Camera/MainCamera.h"

class GameScene : public IScene
{
public:
	GameScene() {};
	~GameScene() {};

	void Initialize(GameManager* scene)override;

	void Update(GameManager* scene)override;

	void Draw(GameManager* scene)override;

private:
	ViewProjection viewProjection{};

	unique_ptr<Player>player_ = nullptr;
};

