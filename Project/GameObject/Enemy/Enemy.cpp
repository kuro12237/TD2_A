#include "Enemy.h"

/// <summary>
/// èâä˙âª
/// </summary>
void Enemy::Initialize(const Vector3& position) {

	model_ = make_unique<Model>();
	model_->Initialize(new ModelSphereState);
	texHandle_ = TextureManager::LoadTexture("Resources/uvChecker.png");
	model_->SetTexHandle(texHandle_);
	model_->SetColor({ 1.0f,0.0f,0.0f,1.0f });

	worldTransform_.Initialize();
	worldTransform_.scale = { 1.0f,1.0f,1.0f };
	worldTransform_.translate = position;
	isMove_ = false;
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
		velocity = PhysicsFunc::Repulsiveforce(-0.3f, player_->GetWorldPosition(), GetWorldPosition());
		isMove_ = false;
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
