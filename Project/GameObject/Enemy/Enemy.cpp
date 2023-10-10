#include "Enemy.h"

Enemy::Enemy(){}
Enemy::~Enemy(){}

/// <summary>
/// ‰Šú‰»
/// </summary>
void Enemy::Initialize(const Vector3& position) {

	model_ = make_unique<Model>();
	model_->Initialize(new ModelSphereState);

	worldTransform_.Initialize();
	worldTransform_.scale = { 1.0f,1.0f,1.0f };
	worldTransform_.translate = position;

}

/// <summary>
/// XV
/// </summary>
void Enemy::Update(){

	worldTransform_.UpdateMatrix();

}

/// <summary>
/// •`‰æ
/// </summary>
void Enemy::Draw(ViewProjection viewProjection){
	model_->Draw(worldTransform_, viewProjection);
}
