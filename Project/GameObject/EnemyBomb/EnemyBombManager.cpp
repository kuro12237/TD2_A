#include"EnemyBombManager.h"


EnemyBombManager::EnemyBombManager()
{
}

EnemyBombManager::~EnemyBombManager()
{
}

void EnemyBombManager::Initialize()
{

	texHandle = TextureManager::LoadTexture("Resources/uvChecker.png");
	for (int i = 0; i < 5; i++)
	{
		//shared_ptr<EnemyBomb>enemy = nullptr;
		//enemy = make_unique<EnemyBomb>();
		//enemy->Initialize({ float(i * 2),0,20.0f }, texHandle);
		//enemys_.push_back(enemy);
	
	}
}

void EnemyBombManager::Update(Player* player)
{
	player;
	enemys_.remove_if([](std::shared_ptr<EnemyBomb>& e) {
		if (e->GetIsDead())
		{
			e.reset();
			return true;
		}
		return false;
	});

	if (Input::GetInstance()->PushKeyPressed(DIK_U))
	{
		
		shared_ptr<EnemyBomb>enemy = nullptr;
		enemy = make_shared<EnemyBomb>();
		enemy->Initialize({ 0,0,20.0f }, texHandle);
		enemys_.push_back(enemy);
		
	}

	for (shared_ptr<EnemyBomb>e:enemys_)
	{
		e->SetPlayer(player);
		e->Update();
	}
}

void EnemyBombManager::Draw(ViewProjection view)
{
	for (shared_ptr<EnemyBomb>e : enemys_)
	{
		e->Draw(view);
	}
}
