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
#include"GameObject/TransitionProcess/TransitionProcess.h"
#include"GameObject/HitParticle/HitParticle.h"
#include"GameObject/EnemyBomb/EnemyBomb.h"
#include "GameObject/Score/Score.h"
#include "GameObject/ShamWall/ShamWall.h"
#include "GameObject/Skydome/Skydome.h"
#include "GameObject/MapGround/MapGround.h"


class GameScene : public IScene
{
public:
	GameScene() {};
	~GameScene() {};

	void Initialize()override;

	void Update(GameManager* scene)override;

	void Back2dSpriteDraw()override;
	void Object3dDraw()override;
	void Flont2dSpriteDraw()override;

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

	unique_ptr<CollisionManager> collisionManager_ = nullptr;
	unique_ptr<TimeCount>timeCount_ = nullptr;
	unique_ptr<Player>player_ = nullptr;
	unique_ptr<HitParticle>hitparticle_ = nullptr;

	std::list<shared_ptr<Enemy>>enemys_;
	bool wait = false; 
	uint32_t waitTimer = 0;
    stringstream fileLoad;
	
	unique_ptr<EnemyBomb>testEnemyBomb = nullptr;

	//uint32_t testTime = 0;

	unique_ptr<MapWallManager>mapWallManager_ = nullptr;
	unique_ptr<ShamWall>shamWall_ = nullptr;
	unique_ptr<Skydome>skydome_ = nullptr;
	unique_ptr<MapGround>mapGround_ = nullptr;

};


