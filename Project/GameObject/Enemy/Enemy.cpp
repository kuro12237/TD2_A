#include "Enemy.h"

/// <summary>
/// ������
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
/// �X�V
/// </summary>
void Enemy::Update() {

	EnemyMove();
	worldTransform_.UpdateMatrix();
}

/// <summary>
/// �`��
/// </summary>
void Enemy::Draw(ViewProjection viewProjection){
	model_->Draw(worldTransform_, viewProjection);
}

void Enemy::EnemyMove() {

	if (isMove_) {
		velocity = PhysicsFanc::Repulsiveforce(-0.1f, player_->GetWorldPosition(), GetWorldPosition());
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
