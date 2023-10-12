#include "Enemy.h"

/// <summary>
/// èâä˙âª
/// </summary>
void Enemy::Initialize(const Vector3& position) {

	model_ = make_unique<Model>();
	model_->Initialize(new ModelSphereState);

	worldTransform_.Initialize();
	worldTransform_.scale = { 1.0f,1.0f,1.0f };
	worldTransform_.translate = position;
	worldTransform_.UpdateMatrix();

	SetCollosionAttribute(kCollisionAttributeEnemy);
	SetCollisionMask(kCollisionAttributePlayer);
}

/// <summary>
/// çXêV
/// </summary>
void Enemy::Update() {

	EnemyMove();
	worldTransform_.UpdateMatrix();
}

/// <summary>
/// ï`âÊ
/// </summary>
void Enemy::Draw(ViewProjection viewProjection){
	model_->Draw(worldTransform_, viewProjection);
}

void Enemy::EnemyMove() {

	if (isMove_) {
		velocity = PhysicsFanc::Repulsiveforce(-0.5f, player_->GetWorldPosition(), GetWorldPosition());
		isMove_ = false;
		int a=0;
		a;
	}
	ImGui::Begin("Enemy");
	ImGui::Text("%f %f %f", velocity.x, velocity.y, velocity.z);
	ImGui::End();



	worldTransform_.translate = VectorTransform::Add(worldTransform_.translate, velocity);
}

Vector3 Enemy::GetWorldPosition() {
	Vector3 WorldPos;
	WorldPos.x = worldTransform_.matWorld.m[3][0];
	WorldPos.y = worldTransform_.matWorld.m[3][1];
	WorldPos.z = worldTransform_.matWorld.m[3][2];
	return WorldPos;
}

void Enemy::OnCollision(){
	isMove_ = true;
}

void Enemy::OnTopWall()
{
	if (worldTransform_.translate.z > static_cast<float>(FILD_MAP_SIZE_Z))
	{
		worldTransform_.translate.z = worldTransform_.translate.z - 0.1f;
	}
	velocity.z = velocity.z * -1;
}

void Enemy::OnBottomWall()
{
	if (worldTransform_.translate.z > static_cast<float>(FILD_MAP_SIZE_Z))
	{
		worldTransform_.translate.z = worldTransform_.translate.z + 0.1f;
	}
	velocity.z = velocity.z * -1;
}

void Enemy::OnLeftWall()
{
	if (worldTransform_.translate.x > static_cast<float>(FILD_MAP_SIZE_X))
	{
		worldTransform_.translate.x = worldTransform_.translate.x + 0.1f;
	}
	velocity.x = velocity.x * -1;
}

void Enemy::OnRightWall()
{
	if (worldTransform_.translate.x > -static_cast<float>(FILD_MAP_SIZE_X))
	{
		worldTransform_.translate.x = worldTransform_.translate.x - 0.1f;
	}
	velocity.x = velocity.x * -1;
}
