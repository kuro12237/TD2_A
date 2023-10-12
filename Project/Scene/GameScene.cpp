﻿#include "GameScene.h"

void GameScene::Initialize()
{
	Grid* grid = new Grid();
	grid->Initialize();
	//GridCommandをセット
	DebugTools::addCommand(grid, "Grid");
	DebugCamera* debugcamera = new DebugCamera();
	debugcamera->Initialize();
	DebugTools::addCommand(debugcamera, "DebugCamera");

	viewProjection.Initialize({ 0.2f,-0.6f,0.0f }, { 11.0f,5.0f,-15 });

	timeCount_ = make_unique<TimeCount>();
	timeCount_->Initialize();

	player_ = make_unique<Player>();
	player_->Initialize();

	LoadEnemyDate();
	enemy_ = make_unique<Enemy>();
	enemy_->Initialize({ 5,0.5,0 });

	MainCamera::Initialize();

	collisionManager_ = make_unique<CollisionManager>();
	mapWallManager_ = make_unique<MapWallManager>();
	mapWallManager_->Initialize();

	texHandle = TextureManager::LoadTexture("Resources/mob.png");
	testSprite = make_unique<Sprite>();
	testSprite->SetTexHandle(texHandle);
	testSprite->Initialize(new SpriteBoxState,{0,0},{320,320});
	testSpriteWorldTransform.Initialize();
}

void GameScene::Update(GameManager* scene)
{
	DebugTools::UpdateExecute(0);
	DebugTools::UpdateExecute(1);

	if (Input::GetInstance()->PushKeyPressed(DIK_9))
	{
		scene->ChangeState(new DebugScene);
		return;
	}
	
	timeCount_->Update();
	// 時間切れ時の処理
	if (!timeCount_->GetIsTimeUp()) {
		//GameObjectの基本更新
		//時間切れになったらifを抜ける
		player_->Update();
		enemy_->Update();
	}
	
	EnemyReset();
	UpdateEnemyCommands();
	//マップの壁との当たり判定
	MapWallCollision();
	//壁のupdate
	mapWallManager_->Update();
	//当たり判定
	Collision();
	//カメラ
	MainCamera::Update(player_->GetWorldTransform());

	viewProjection.UpdateMatrix();
	viewProjection = MainCamera::GetViewProjection();
	viewProjection = DebugTools::ConvertViewProjection(viewProjection);
}

void GameScene::Back2dSpriteDraw()
{
}

void GameScene::Object3dDraw()
{
	DebugTools::DrawExecute(0);
	DebugTools::DrawExecute(1);

	player_->Draw(viewProjection);
	enemy_->Draw(viewProjection);
	mapWallManager_->Draw(viewProjection);
}

void GameScene::Flont2dSpriteDraw()
{
	timeCount_->Draw();
	testSprite->Draw(testSpriteWorldTransform);
}

void GameScene::Collision()
{
	collisionManager_->ClliderClear();
	//Set
	collisionManager_->ClliderPush(player_.get());
	collisionManager_->ClliderPush(enemy_.get());
	//Check
	collisionManager_->CheckAllCollision();
}

void GameScene::MapWallCollision()
{
	mapWallManager_->ListClear();
	mapWallManager_->SetObject(player_.get());
	mapWallManager_->CheckMapWall();
}

// enemyのデータをロード(CSVで)
void GameScene::LoadEnemyDate() {
    fileLoad = FileLoader::CSVLoadFile("enemySpawn.csv");
}

// データを読み込む
void GameScene::UpdateEnemyCommands() {
	// �ҋ@����
	if (wait) {
		waitTimer--;
		if (waitTimer <= 0) {
			wait = false;
		}
		return;
	}

	std::string line;

	while (getline(fileLoad, line)) {
	
		std::istringstream line_stream(line);
		std::string word;
		
		getline(line_stream, word, ',');

		if (word.find("//") == 0) {
			
			continue;
		}

		if (word.find("SPAWN") == 0) {
	
			getline(line_stream, word, ',');
			float x = (float)std::atof(word.c_str());

			getline(line_stream, word, ',');
			float y = (float)std::atof(word.c_str());

			getline(line_stream, word, ',');
			float z = (float)std::atof(word.c_str());

			EnemySpawn(Vector3(x, y, z));
		}
		else if (word.find("WAIT") == 0) {
			getline(line_stream, word, ',');

			int32_t waitTime = atoi(word.c_str());

			wait = true;
			waitTimer = waitTime;

			break;
		}
	}

}

// enemy発生
void GameScene::EnemySpawn(const Vector3& position) {
	enemy_ = make_unique<Enemy>();
	enemy_->Initialize(position);
	enemy_->SetPlayer(player_.get());
}

// enemyのreset
void GameScene::EnemyReset() {
	if (Input::GetInstance()->PushKeyPressed(DIK_R)) {
		enemy_.reset();
		LoadEnemyDate();
		enemy_ = make_unique<Enemy>();
		enemy_->Initialize({ 5,0.5,0 });
	}
}

