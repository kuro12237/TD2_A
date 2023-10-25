#include "GameScene.h"

void GameScene::Initialize()
{
	//カウンターをリセット
	KillCounter::ClearCount();

	viewProjection.Initialize({ 0.2f,-0.6f,0.0f }, { 11.0f,5.0f,-15 });
	GameAudio::Initialize();

	timeCount_ = make_unique<TimeCount>();
	timeCount_->Initialize();
	uint32_t useFade_BG = TextureManager::LoadTexture("Resources/Texture/BackGround/BackGround.png");

	// 天球
	skydome_ = make_unique<Skydome>();
	skydome_->Initialize();

	//// フェードの処理
	TransitionProcess::Initialize();
	//// フェードに使う画像の設定
	TransitionProcess::GetInstance()->GetBG_Sprite()->SetTexHandle(useFade_BG);
	//// 色を黒くしておく
	TransitionProcess::GetInstance()->GetBG_Sprite()->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });

	//// スコア
	Score::Initialize();

	player_ = make_unique<Player>();
	player_->Initialize();

	LoadEnemyDate();
	enemyTexHandle_ = TextureManager::LoadTexture("Resources/Enemy.png");
	stopeedEnemyTexHandle_ = TextureManager::LoadTexture("Resources/StoppedEnemy.png");
	MainCamera::Initialize();
	MainCamera::SetOffset({ 0.0f,3.0f,-50.0f });

	collisionManager_ = make_unique<CollisionManager>();
	mapWallManager_ = make_unique<MapWallManager>();
	mapWallManager_->Initialize();

	// 見かけの壁
	shamWall_ = make_unique<ShamWall>();
	shamWall_->Initialize();

	// 床
	mapGround_ = make_unique<MapGround>();
	mapGround_->Initialize();


	hitparticle_ = make_unique<HitParticle>();
	hitparticle_->Initialize();


	enemyBombManager = make_shared<EnemyBombManager>();
	enemyBombManager->Initialize();


	isGame_ = true;
	TransitionProcess::Fade_Out_Init();
}

void GameScene::Update(GameManager* scene)
{
	scene;

	///// ゲームの処理に入る
	if (isGame_) {

		if (TransitionProcess::Fade_Out()) {

			if (player_->GetHitFlag())
			{
				hitparticle_->Spown(player_->GetWorldTransform().translate);
				MainCamera::SetIsShake(true);
			}


			/* ---------- スタートカウント---------- */

		

			/* ---------- 制限時間 --------- */

			// 制限時間の処理
			timeCount_->Update();
			// 時間切れ時の処理
			if (timeCount_->GetIsTimeUp())
			{
				XINPUT_STATE joyState{};
				Input::NoneJoyState(joyState);
				if (Input::GetInstance()->GetJoystickState(joyState))
				{
					//発射処理
					if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_A)
					{
						TransitionProcess::Fade_In_Init();
					}

				}
				if (Input::GetInstance()->PushKeyPressed(DIK_SPACE))
				{
					TransitionProcess::Fade_In_Init();
				}
			}
			else if (!timeCount_->GetIsTimeUp()) {

				/* ---------- プレイヤー ---------- */
				
				// プレイヤーの更新処理
				player_->Update();

				// プレイヤーにエネミーを送る 
				player_->SetEnemy(enemys_);

				// プレイヤーのスコアの処理
				Score::Update();
				player_->SetEnemy(enemys_);

				// 多分プレイヤーのパーティクル
				hitparticle_->Update();



				/* ---------- エネミー ---------- */

				// エネミーの更新処理諸々
				for (shared_ptr<Enemy>& enemy : enemys_) {
					enemy->RandomMove();
					enemy->SetPlayer(player_.get());
					enemy->Update();
				}

				// これは何かしらん
				enemyBombManager->Update(player_.get());

				// 多分CSV読んでエネミーをリスさせてる
				UpdateEnemyCommands();



				/* ---------- 壁 --------- */

				//マップの壁との当たり判定
				MapWallCollision();

				//壁のupdate
				mapWallManager_->Update();
				shamWall_->Update();



				/* ---------- 床 --------- */

				// 床の更新処理
				mapGround_->Updatea();



				/* ---------- 天球 --------- */

				// 天球の更新処理
				skydome_->Update();



				/* ---------- 当たり判定 --------- */

				//当たり判定
				Collision();

			}
		}
	}

	player_->SetStpEnemy(stpEnemys_);

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
  
	/* ---------- フェード---------- */

	// フェードが入る処理
	TransitionProcess::Fade_In();
	// フェードに入り終わったらシーンチェンジ
	if (TransitionProcess::Fade_In()) {
		GameAudio::PlaySelectSound();
		scene->ChangeState(new ResultScene);
		return;
	}


	//カメラ
	MainCamera::Update(player_->GetWorldTransform());

	viewProjection.UpdateMatrix();
	viewProjection = MainCamera::GetViewProjection();
}

void GameScene::Back2dSpriteDraw()
{
}

void GameScene::Object3dDraw()
{
	// 天球
	skydome_->Draw(viewProjection);

	// 床
	mapGround_->Draw(viewProjection);

	// 壁
	shamWall_->Draw(viewProjection);

	// プレイヤー
	player_->Draw(viewProjection);

	// エネミー
	for (shared_ptr<Enemy>& enemy : enemys_) {
		enemy->Draw(viewProjection);
	}

	RandomSpawn();

	for (shared_ptr<StoppedEnemy>& stpEnemy : stpEnemys_) {
		stpEnemy->Draw(viewProjection);
	}

	hitparticle_->Draw(viewProjection);

	enemyBombManager->Draw(viewProjection);

	// パーティクル
	hitparticle_->Draw(viewProjection);
}

void GameScene::Flont2dSpriteDraw()
{
	// フェードが明けたら描画
	if (TransitionProcess::Fade_Out()) {

		// スタート時のカウント
		//startCount_->Draw();

		// スコアの描画
		Score::Draw();

		// 制限時間の描画
		timeCount_->Draw();
	}

	// フェード 
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

void GameScene::RandomSpawn()
{

	spawnTimer_++;

	if (spawnTimer_ >= 180) {
		mt19937 randomEngine(seedGenerator());
		uniform_real_distribution<float>distribution(-25.0f, 25.0f);
		shared_ptr<StoppedEnemy>enemy = nullptr;
		enemy = make_shared<StoppedEnemy>();
		enemy->Initialize({ float(distribution(randomEngine)),-6.0,float(distribution(randomEngine)) }, stopeedEnemyTexHandle_);
		stpEnemys_.push_back(enemy);
		spawnTimer_ = 0;
	}
	
}
