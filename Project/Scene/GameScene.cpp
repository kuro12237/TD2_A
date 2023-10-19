#include "GameScene.h"

void GameScene::Initialize()
{
	viewProjection.Initialize({ 0.2f,-0.6f,0.0f }, { 11.0f,5.0f,-15 });

	
	timeCount_ = make_unique<TimeCount>();
	timeCount_->Initialize();
	uint32_t useFade_BG = TextureManager::LoadTexture("Resources/BackGround/BackGround.png");
	// フェードの処理
	TransitionProcess::Initialize();
	// フェードに使う画像の設定
	TransitionProcess::GetInstance()->GetBG_Sprite()->SetTexHandle(useFade_BG);
	// 色を黒くしておく
	TransitionProcess::GetInstance()->GetBG_Sprite()->SetColor({ 0.0f, 0.0f, 0.0f, 1.0f });
	// フェードが明ける処理
	TransitionProcess::Fade_Out_Init();

	player_ = make_unique<Player>();
	player_->Initialize();


	LoadEnemyDate();
	enemy_ = make_unique<Enemy>();
	enemy_->Initialize({ 0,0,0 });
	MainCamera::Initialize();

	collisionManager_ = make_unique<CollisionManager>();
	mapWallManager_ = make_unique<MapWallManager>();
	mapWallManager_->Initialize();
}

void GameScene::Update(GameManager* scene)
{
	if (Input::GetInstance()->PushKeyPressed(DIK_9))
	{
		TransitionProcess::Fade_In_Init();
	}
	// フェードの処理が終わったらシーン遷移
	if (TransitionProcess::Fade_In()) {
		scene->ChangeState(new ResultScene);
		return;
	}
	
	MapWallCollision();

	// フェードが明ける処理
	TransitionProcess::Fade_In();
	TransitionProcess::Fade_Out();
	// フェードが明けたらゲーム処理に入る
	if (TransitionProcess::Fade_Out()) {

		timeCount_->Update();

		// 時間切れ時の処理
		if (timeCount_->GetIsTimeUp() == false) {
			player_->Update();
			enemy_->Update();
		}
	}



	UpdateEnemyCommands();
	
	mapWallManager_->Update();
	Collision();

	MainCamera::Update(player_->GetWorldTransform());

	viewProjection.UpdateMatrix();

	viewProjection = MainCamera::GetViewProjection();

	viewProjection = DebugTools::ConvertViewProjection(viewProjection);

	/*ImGui::Begin("ChangeDebugScene");
	ImGui::Text("9 key");
	ImGui::End();*/
}

void GameScene::Draw()
{

	player_->Draw(viewProjection);
	enemy_->Draw(viewProjection);

	mapWallManager_->Draw(viewProjection);

	timeCount_->Draw();

	TransitionProcess::Draw();
	
}

void GameScene::Collision()
{
	collisionManager_->ClliderClear();

	//Set
	collisionManager_->ClliderPush(player_.get());

	//Check
	collisionManager_->CheckAllCollision();

}

void GameScene::MapWallCollision()
{
	mapWallManager_->ListClear();
	mapWallManager_->SetObject(player_.get());
	mapWallManager_->CheckMapWall();
}

// �G�̃��[�hcsv��
void GameScene::LoadEnemyDate() {
    fileLoad = FileLoader::CSVLoadFile("enemySpawn.csv");
}

// �G�����̍X�V
void GameScene::UpdateEnemyCommands() {
	// �ҋ@����
	if (wait) {
		waitTimer--;
		if (waitTimer <= 0) {
			// �ҋ@����
			wait = false;
		}
		return;
	}

	// 1�s���̕����������ϐ�
	std::string line;

	// �R�}���h���s���[�v
	while (getline(fileLoad, line)) {
		// 1�s���̕�������X�g���[���ɕϊ����ĉ�͂��₷������
		std::istringstream line_stream(line);

		std::string word;
		// ,��؂�ōs�̐擪��������擾
		getline(line_stream, word, ',');

		// "//"����n�܂�s�̓R�����g
		if (word.find("//") == 0) {
			// �R�����g�s���΂�
			continue;
		}

		// POP�R�}���h
		if (word.find("SPAWN") == 0) {
			// x���W
			getline(line_stream, word, ',');
			float x = (float)std::atof(word.c_str());

			// y���W
			getline(line_stream, word, ',');
			float y = (float)std::atof(word.c_str());

			// z���W
			getline(line_stream, word, ',');
			float z = (float)std::atof(word.c_str());

			EnemySpawn(Vector3(x, y, z));


		}
		else if (word.find("WAIT") == 0) {
			getline(line_stream, word, ',');

			// �҂�����
			int32_t waitTime = atoi(word.c_str());

			// �ҋ@�J�n
			wait = true;
			waitTimer = waitTime;

			// �R�}���h���[�v�𔲂���
			break;
		}
	}

}

// �G�̔���
void GameScene::EnemySpawn(const Vector3& position) {
	enemy_ = make_unique<Enemy>();
	enemy_->Initialize(position);
}

