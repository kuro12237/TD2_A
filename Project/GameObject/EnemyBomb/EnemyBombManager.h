#pragma once
#include"EnemyBomb.h"


class EnemyBombManager
{
public:
	EnemyBombManager();
	~EnemyBombManager();

	void Initialize();

	void Update(Player*player);

	void Draw(ViewProjection view);

	void SpownFanc();

	list<shared_ptr<EnemyBomb>>GetEnemys() { return enemys_; }

private:

	uint32_t spownTimer_ = 0;
	uint32_t MaxSpownTimer_ = 300;

	uint32_t texHandle = 0;
	list<shared_ptr<EnemyBomb>>enemys_;
};

