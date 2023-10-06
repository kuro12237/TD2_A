#pragma once
#include"Model.h"

#define FILD_MAP_SIZE_X 16
#define FILD_MAP_SIZE_Z 16

struct sWall
{
	unique_ptr<Model>model = nullptr;
	WorldTransform worldTransform{};
};

class MapWall
{
public:
	MapWall();
	~MapWall();

	void Initialize();

	void Update();

	void Draw(ViewProjection view);

private:

	const Vector2 MaxFild = { FILD_MAP_SIZE_X,FILD_MAP_SIZE_Z };

	sWall Top_ = {};
	sWall Bottom_ = {};
	sWall Left_ = {};
	sWall Right_ = {};

};

