#pragma once
#include"IScene.h"
#include"GameManager.h"
#include"Cleyera.h"

#include"GameScene.h"
#include"Input.h"
#include"Audio.h"
#include"FileLoader.h"

#include"GameObject/PlayerSphere.h"
#include"GameObject/EnemySphere.h"
#include"CollisionManager.h"

class DebugScene:public IScene
{
public:
	DebugScene() {};
	~DebugScene();


	void Initialize(GameManager* Scene)override;

	void Update(GameManager* Scene)override;

	void Draw(GameManager* Scene)override;

private:
	void TestCsvFile();

	void CheckAllCollision();
	
	ViewProjection viewProjection{};
	uint32_t soundHandle_  = 0;

	unique_ptr<Sprite>sprite_ = nullptr;
	WorldTransform spriteWorldTransform_{};
	
	unique_ptr<Sprite>sprite2_ = nullptr;
	WorldTransform sprite2WorldTransform_{};

	uint32_t SpriteTexHandle = 0;
	Vector4 color = { 1,1,1,1 };

	bool NoneFlag = true;
	bool AddFlag = false;
	bool MultiplyFlag = false;
	bool SubtractFlag = false;
	bool ScreenFlag = false;

};
