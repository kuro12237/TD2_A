#include "GameScene.h"

void GameScene::Initialize()
{
	//Grid* grid = new Grid();
	//grid->Initialize();
	//GridCommandをセット
	//DebugTools::addCommand(grid, "Grid");
	DebugCamera* debugcamera = new DebugCamera();
	debugcamera->Initialize();
	DebugTools::addCommand(debugcamera, "DebugCamera");

	viewProjection.Initialize({ 0.2f,-0.6f,0.0f }, { 11.0f,5.0f,-15 });

	timeCount_ = make_unique<TimeCount>();
	timeCount_->Initialize();
	uint32_t useFade_BG = TextureManager::LoadTexture("Resources/Texture/BackGround/BackGround.png");

	//// フェードの処理
	TransitionProcess::Initialize();
	//// フェードに使う画像の設定
	TransitionProcess::GetInstance()->GetBG_Sprite()->SetTexHandle(useFade_BG);
	//// 色を黒くしておく
	TransitionProcess::GetInstance()->GetBG_Sprite()->SetColor({ 0.0f, 0.0f, 0.0f, 1.0f });
	//// フェードが明ける処理
	TransitionProcess::Fade_Out_Init();

	//// スコア
	Score::Initialize();

	player_ = make_unique<Player>();
	player_->Initialize();

	LoadEnemyDate();

	enemyTexHandle_ = TextureManager::LoadTexture("Resources/uvChecker.png");
	shared_ptr<StoppedEnemy> stpEnemy = make_shared<StoppedEnemy>();
	stpEnemy->Initialize({0.0f,0.0f,0.0f},enemyTexHandle_);
	stpEnemy->SetPlayer(player_.get());
	player_->SetStpEnemy(stpEnemys_);
	stpEnemys_.push_back(stpEnemy);


	MainCamera::Initialize();

	collisionManager_ = make_unique<CollisionManager>();
	mapWallManager_ = make_unique<MapWallManager>();
	mapWallManager_->Initialize();

	// 見かけの壁
	shamWall_ = make_unique<ShamWall>();
	shamWall_->Initialize();

	// 天球
	skydome_ = make_unique<Skydome>();
	skydome_->Initialize();

	// 床
	mapGround_ = make_unique<MapGround>();
	mapGround_->Initialize();


	hitparticle_ = make_unique<HitParticle>();
	hitparticle_->Initialize();

	
	enemyBombManager = make_shared<EnemyBombManager>();
	enemyBombManager->Initialize();

}

void GameScene::Update(GameManager* scene)
{
	scene;
	DebugTools::UpdateExecute(0);
	//DebugTools::UpdateExecute(1);

	if (Input::GetInstance()->PushKeyPressed(DIK_9))
	{
		TransitionProcess::Fade_In_Init();
	}
	if (Input::GetInstance()->PushKeyPressed(DIK_5))
	{
		Score::AddScore(100);
	}
	// フェードの処理が終わったらシーン遷移
	if (TransitionProcess::Fade_In()) {
		scene->ChangeState(new ResultScene);
		return;
	}

	// フェードが明ける処理
	TransitionProcess::Fade_In();
	TransitionProcess::Fade_Out();

	// フェードが明けたらゲーム処理に入る
	if (!TransitionProcess::Fade_Out()) {
		return;
	}
	if (player_->GetHitFlag())
	{
		hitparticle_->Spown(player_->GetWorldTransform().translate);
		MainCamera::SetIsShake(true);
	}

	Score::Update();
	timeCount_->Update();
	// 時間切れ時の処理
	if (!timeCount_->GetIsTimeUp())
	{
		//GameObjectの基本更新
		//時間切れになったらifを抜ける     
	}

	player_->SetEnemy(enemys_);
	for (shared_ptr<Enemy>& enemy : enemys_) {
		enemy->RandomMove();
		enemy->SetPlayer(player_.get());
		enemy->Update();

	}

	for (shared_ptr<StoppedEnemy>& stpEnemy : stpEnemys_) {
		stpEnemy->SetPlayer(player_.get());
		stpEnemy->Update();
	}

	stpEnemys_.remove_if([](shared_ptr<StoppedEnemy>& stpEnemy) {
		if (stpEnemy->IsDead()) {
			stpEnemy.reset();
			return true;
		}
		return false;
	});

	enemyCount_++;

	if (enemyCount_ >= 900) {
		LoadEnemyDate();
		enemyCount_ = 0;
	}

	enemys_.remove_if([](shared_ptr<Enemy>& enemy) {
		if (enemy->IsDead()) {
			enemy.reset();
			return true;
		}
		return false;
	});


	enemyBombManager->Update(player_.get());
	
	player_->Update();
	
	hitparticle_->Update();

	EnemyReset();

	UpdateEnemyCommands();
	//マップの壁との当たり判定
	MapWallCollision();
	//壁のupdate
	mapWallManager_->Update();
	shamWall_->Update();
	
	// 天球
	skydome_->Update();

	// 床
	mapGround_->Updatea();
	
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
	//DebugTools::DrawExecute(1);

	skydome_->Draw(viewProjection);

	mapGround_->Draw(viewProjection);

	player_->Draw(viewProjection);
	enemyBombManager->Draw(viewProjection);


	// 敵
	for (shared_ptr<Enemy>& enemy : enemys_) {
		enemy->Draw(viewProjection);
	}

	for (shared_ptr<StoppedEnemy>& stpEnemy : stpEnemys_) {
		stpEnemy->Draw(viewProjection);
	}

	hitparticle_->Draw(viewProjection);

	//mapWallManager_->Draw(viewProjection);
	shamWall_->Draw(viewProjection);
}

void GameScene::Flont2dSpriteDraw()
{
	
	timeCount_->Draw();
	Score::Draw();
	TransitionProcess::Draw();
	
}

void GameScene::Collision()
{
	collisionManager_->ClliderClear();
	//Set
	collisionManager_->ClliderPush(player_.get());

	for (shared_ptr<Enemy>& enemy : enemys_) {
		collisionManager_->ClliderPush(enemy.get());
	}

	for (shared_ptr<StoppedEnemy>& stpEnemy : stpEnemys_) {
		collisionManager_->ClliderPush(stpEnemy.get());
	}
	
	for (shared_ptr<EnemyBomb>& enemy : enemyBombManager->GetEnemys())
	{
		collisionManager_->ClliderPush(enemy.get());
	}

	//Check
	collisionManager_->CheckAllCollision();
}

void GameScene::MapWallCollision()
{
	mapWallManager_->ListClear();
	mapWallManager_->SetObject(player_.get());

	for (shared_ptr<Enemy>& enemy : enemys_) {
		mapWallManager_->SetObject(enemy.get());
	}

	for (shared_ptr<StoppedEnemy>& stpEnemy : stpEnemys_) {
		mapWallManager_->SetObject(stpEnemy.get());
	}

	mapWallManager_->CheckMapWall();
}

// enemyのデータをロード(CSVで)
void GameScene::LoadEnemyDate() {
	fileLoad = FileLoader::CSVLoadFile("resources/enemySpawn.csv");
}

// データを読み込む
void GameScene::UpdateEnemyCommands() {
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

	shared_ptr<Enemy> enemy = make_shared<Enemy>();
	enemy->Initialize(position, enemyTexHandle_);
	enemy->SetPlayer(player_.get());
	player_->SetEnemy(enemys_);
	enemys_.push_back(enemy);
}

// enemyのreset
void GameScene::EnemyReset() {
	if (Input::GetInstance()->PushKeyPressed(DIK_R)) {
		enemys_.clear();
		for (shared_ptr<Enemy>& enemy : enemys_) {
			enemy = make_shared<Enemy>();
			enemy->Initialize({ 0,0.5,0 }, enemyTexHandle_);
		}

		LoadEnemyDate();
	}
}

