#pragma once
#include"IScene.h"
#include"GameManager.h"

#include "GameObject/TimeCount/TimeCount.h"
#include"GameObject/Player/Player.h"
#include"GameObject/Enemy/Enemy.h"
#include"GameObject/Camera/MainCamera.h"

#include"CollisionManager.h"
#include"FileLoader.h"
#include"GameObject/MapWall/MapWall.h"
#include"GameObject/MapWall/MapWallManager.h"


class GameScene : public IScene
{
public:
	GameScene() {};
	~GameScene() {};

	void Initialize()override;

	void Update(GameManager* scene)override;

	void Draw()override;

	/// <summary>
	/// �G����
	/// </summary>
	void LoadEnemyDate();
	void UpdateEnemyCommands();
	void EnemySpawn(const Vector3& position);
	void EnemyReset();
	
private:
	
	void Collision();

	void MapWallCollision();

	ViewProjection viewProjection{};

	unique_ptr<TimeCount>timeCount_ = nullptr;
	unique_ptr<CollisionManager> collisionManager_ = nullptr;

	unique_ptr<Player>player_ = nullptr;

	std::list<shared_ptr<Enemy>>enemys_;

	bool wait = false; 
	uint32_t waitTimer = 0;
	stringstream fileLoad;

	unique_ptr<MapWallManager>mapWallManager_ = nullptr;

};


