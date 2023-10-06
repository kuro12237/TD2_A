#pragma once
#include"IScene.h"
#include"GameManager.h"
#include"GameObject/Player/Player.h"
#include"GameObject/Camera/MainCamera.h"
#include"CollisionManager.h"
#include"GameObject/MapWall/MapWall.h"

class GameScene : public IScene
{
public:
	GameScene() {};
	~GameScene() {};

	void Initialize(GameManager* scene)override;

	void Update(GameManager* scene)override;

	void Draw(GameManager* scene)override;

private:
	
	void Collision();

	ViewProjection viewProjection{};

	unique_ptr<CollisionManager> collisionManager_ = nullptr;

	unique_ptr<Player>player_ = nullptr;

	unique_ptr<MapWall>mapwall_ = nullptr;
};

