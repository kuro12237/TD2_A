#include "GameScene.h"

void GameScene::Initialize(GameManager* scene)
{
	viewProjection.Initialize({ 0.2f,-0.6f,0.0f }, { 11.0f,5.0f,-15 });
	player_ = make_unique<Player>();
	player_->Initialize();
	LoadEnemyDate();
	scene;
	MainCamera::Initialize();
	//make_unique<
	collisionManager_ = make_unique<CollisionManager>();
	
}

void GameScene::Update(GameManager* scene)
{
	ImGui::Begin("ChangeDebugScene");
	ImGui::Text("9 key");
	ImGui::End();

	if (Input::GetInstance()->PushKeyPressed(DIK_9))
	{
		scene->ChangeState(new DebugScene);
		return;
	}

	player_->Update();
	enemy_->Update();
	UpdateEnemyCommands();
	
	Collision();

	MainCamera::Update();

	viewProjection = MainCamera::GetViewProjection();
	viewProjection = DebugTools::ConvertViewProjection(viewProjection);
}

void GameScene::Draw(GameManager* scene)
{
	player_->Draw(viewProjection);
	enemy_->Draw(viewProjection);
	scene;
}

void GameScene::Collision()
{
	collisionManager_->ClliderClear();

	//Set
	collisionManager_->ClliderPush(player_.get());

	//Check
	collisionManager_->CheckAllCollision();

}

// 敵のロードcsvで
void GameScene::LoadEnemyDate() {
    fileLoad = FileLoader::CSVLoadFile("enemySpawn.csv");
}

// 敵発生の更新
void GameScene::UpdateEnemyCommands() {
	// 待機処理
	if (wait) {
		waitTimer--;
		if (waitTimer <= 0) {
			// 待機完了
			wait = false;
		}
		return;
	}

	// 1行分の文字列を入れる変数
	std::string line;

	// コマンド実行ループ
	while (getline(fileLoad, line)) {
		// 1行分の文字列をストリームに変換して解析しやすくする
		std::istringstream line_stream(line);

		std::string word;
		// ,区切りで行の先頭文字列を取得
		getline(line_stream, word, ',');

		// "//"から始まる行はコメント
		if (word.find("//") == 0) {
			// コメント行を飛ばす
			continue;
		}

		// POPコマンド
		if (word.find("SPAWN") == 0) {
			// x座標
			getline(line_stream, word, ',');
			float x = (float)std::atof(word.c_str());

			// y座標
			getline(line_stream, word, ',');
			float y = (float)std::atof(word.c_str());

			// z座標
			getline(line_stream, word, ',');
			float z = (float)std::atof(word.c_str());

			EnemySpawn(Vector3(x, y, z));


		}
		else if (word.find("WAIT") == 0) {
			getline(line_stream, word, ',');

			// 待ち時間
			int32_t waitTime = atoi(word.c_str());

			// 待機開始
			wait = true;
			waitTimer = waitTime;

			// コマンドループを抜ける
			break;
		}
	}

}

// 敵の発生
void GameScene::EnemySpawn(const Vector3& position) {
	enemy_ = make_unique<Enemy>();
	enemy_->Initialize(position);
}

