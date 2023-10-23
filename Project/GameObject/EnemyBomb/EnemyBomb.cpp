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
	Vector3 Ppos = player_->GetWorldPosition();
	Vector3 Epos{};
	Epos.x = worldTransform_.matWorld.m[3][0];
	Epos.y = worldTransform_.matWorld.m[3][1];
	Epos.z = worldTransform_.matWorld.m[3][2];

	velocity_ = VectorTransform::Subtruct(Ppos,Epos);
	velocity_ = VectorTransform::Normalize(velocity_);
	velocity_.x = velocity_.x * 0.1f;
	velocity_.y = velocity_.y * 0.1f;
	velocity_.z = velocity_.z * 0.1f;

	state_->Move(worldTransform_, this);
	
	worldTransform_.UpdateMatrix();
}

void EnemyBomb::Draw(ViewProjection view)
{
	model->Draw(worldTransform_, view);
}
