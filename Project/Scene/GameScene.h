#pragma once
#include"IScene.h"
#include"GameManager.h"
#include"GameObject/Player/Player.h"
#include"GameObject/Enemy/Enemy.h"
#include"GameObject/Camera/MainCamera.h"
#include"CollisionManager.h"

#include"FileLoader.h"
#include"GameObject/MapWall/MapWall.h"


class GameScene : public IScene
{
public:
	GameScene() {};
	~GameScene() {};

	void Initialize(GameManager* scene)override;

	void Update(GameManager* scene)override;

	void Draw(GameManager* scene)override;

	/// <summary>
	/// �G����
	/// </summary>
	void LoadEnemyDate();
	void UpdateEnemyCommands();
	void EnemySpawn(const Vector3& position);			
	
private:
	
	void Collision();

	ViewProjection viewProjection{};

	unique_ptr<CollisionManager> collisionManager_ = nullptr;

	unique_ptr<Player>player_ = nullptr;

	Player* player = nullptr;

	unique_ptr<Enemy>enemy_ = nullptr; // �G
	bool wait = false; // �ҋ@���t���O
	uint32_t waitTimer = 0; // �ҋ@���^�C�}�[
	stringstream fileLoad;

	unique_ptr<MapWall>mapwall_ = nullptr;

};


