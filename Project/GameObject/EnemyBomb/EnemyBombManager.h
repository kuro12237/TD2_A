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

	list<shared_ptr<EnemyBomb>>GetEnemys() { return enemys_; }

private:

	uint32_t texHandle = 0;
	list<shared_ptr<EnemyBomb>>enemys_;
};

