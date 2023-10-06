#pragma once
#include"IScene.h"
#include"GameManager.h"
#include"GameObject/Player/Player.h"
#include"GameObject/Enemy/Enemy.h"
#include"GameObject/Camera/MainCamera.h"
#include"CollisionManager.h"
#include"FileLoader.h"

class GameScene : public IScene
{
public:
	GameScene() {};
	~GameScene() {};

	void Initialize(GameManager* scene)override;

	void Update(GameManager* scene)override;

	void Draw(GameManager* scene)override;

	/// <summary>
	/// 敵発生
	/// </summary>
	void LoadEnemyDate();
	void UpdateEnemyCommands();
	void EnemySpawn(const Vector3& position);			
	
private:
	
	void Collision();

	ViewProjection viewProjection{};

	unique_ptr<CollisionManager> collisionManager_ = nullptr;

	unique_ptr<Player>player_ = nullptr;

	unique_ptr<Enemy>enemy_ = nullptr; // 敵
	bool wait = false; // 待機中フラグ
	uint32_t waitTimer = 0; // 待機中タイマー
	stringstream fileLoad;
};


