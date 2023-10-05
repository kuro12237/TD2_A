#pragma once
#include"IScene.h"
#include"GameManager.h"
#include "GameObject/TimeCount/TimeCount.h"

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

	// êßå¿éûä‘
	unique_ptr<TimeCount>timeCount_ = nullptr;
};

