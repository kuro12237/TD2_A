#include "EnemyBomb.h"

void EnemyBomb::Initialize(Vector3 position)
{
	state_ =  new stateMoveEnemyBomb;
	worldTransform_.Initialize();
	worldTransform_.translate = position;
	worldTransform_.UpdateMatrix();

	model = make_unique<Model>();
	model->Initialize(new ModelSphereState);
	
	texHandle = TextureManager::LoadTexture("Resources/uvChecker.png");
	model->SetTexHandle(texHandle);
}

void EnemyBomb::Update()
{
	state_->Move(worldTransform_, this);
	worldTransform_.UpdateMatrix();
}

void EnemyBomb::Draw(ViewProjection view)
{
	model->Draw(worldTransform_, view);
}
