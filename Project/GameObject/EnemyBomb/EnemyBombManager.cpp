#include"EnemyBombManager.h"


EnemyBombManager::EnemyBombManager()
{
}

EnemyBombManager::~EnemyBombManager()
{
}

void EnemyBombManager::Initialize()
{
	texHandle = TextureManager::LoadTexture("Resources/EnemyBomb.png");

}

void EnemyBombManager::Update(Player* player)
{
	SpownFanc();
	enemys_.remove_if([](std::shared_ptr<EnemyBomb>& e) {
		if (e->GetIsDead())
		{
			e.reset();
			return true;
		}
		return false;
	});


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

void EnemyBombManager::SpownFanc()
{
	spownTimer_++;

	if (spownTimer_>MaxSpownTimer_)
	{
		mt19937 randomEngine(seedGenerator());
		uniform_real_distribution<float>distribution(-30.0f, 30.0f);
		shared_ptr<EnemyBomb>enemy = nullptr;
		enemy = make_shared<EnemyBomb>();
		enemy->Initialize({ float(distribution(randomEngine)),-10,float(distribution(randomEngine))}, texHandle);
		enemys_.push_back(enemy);
		spownTimer_ = 0;
	}

}
