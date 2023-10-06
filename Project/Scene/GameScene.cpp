#include "GameScene.h"

void GameScene::Initialize(GameManager* scene)
{
	viewProjection.Initialize({ 0.2f,-0.6f,0.0f }, { 11.0f,5.0f,-15 });
	player_ = make_unique<Player>();
	player_->Initialize();


	LoadEnemyDate();
	enemy_ = make_unique<Enemy>();
	enemy_->Initialize({ 0,0,0 });
  
	mapwall_ = make_unique<MapWall>();
	mapwall_->Initialize();

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
	

	mapwall_->Update();

	Collision();

	MainCamera::Update();

	viewProjection = MainCamera::GetViewProjection();
	viewProjection = DebugTools::ConvertViewProjection(viewProjection);
}

void GameScene::Draw(GameManager* scene)
{
	player_->Draw(viewProjection);

	enemy_->Draw(viewProjection);
  
	mapwall_->Draw(viewProjection);

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

