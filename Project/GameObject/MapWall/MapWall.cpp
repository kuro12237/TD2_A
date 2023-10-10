#include"MapWall.h"

MapWall::MapWall()
{
}

MapWall::~MapWall()
{
}

void MapWall::Initialize()
{
	Top_.model = make_unique<Model>();
	Top_.model->CreateFromObj("TestWallHeight");
	Top_.worldTransform.Initialize();
	Top_.worldTransform.scale = { 0.1f,2,4 };
	Top_.worldTransform.translate.x = MaxFild.x;

	Bottom_.model = make_unique<Model>();
	Bottom_.model->CreateFromObj("TestWallHeight");
	Bottom_.worldTransform.Initialize();
	Bottom_.worldTransform.scale = { 0.1f,2,4 };
	Bottom_.worldTransform.translate.x = -(MaxFild.x);

	Right_.model = make_unique<Model>();
	Right_.model->CreateFromObj("TestWallWidth");
	Right_.worldTransform.Initialize();
	Right_.worldTransform.scale = { 4,2,0.1f };
	Right_.worldTransform.translate.z = MaxFild.y;

	Left_.model = make_unique<Model>();
	Left_.model->CreateFromObj("TestWallWidth");
	Left_.worldTransform.Initialize();
	Left_.worldTransform.scale = { 4,2,0.1f };
	Left_.worldTransform.translate.z = -(MaxFild.y);

}

void MapWall::Update()
{
	Top_.worldTransform.UpdateMatrix();
	Bottom_.worldTransform.UpdateMatrix();
	Right_.worldTransform.UpdateMatrix();
	Left_.worldTransform.UpdateMatrix();
}

void MapWall::Draw(ViewProjection view)
{
	Top_.model->Draw(Top_.worldTransform,view);
	Bottom_.model->Draw(Bottom_.worldTransform, view);

	Right_.model->Draw(Right_.worldTransform, view);
	Left_.model->Draw(Left_.worldTransform, view);

}
