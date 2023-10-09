#include "Enemy.h"

Enemy::Enemy(){}
Enemy::~Enemy(){}

/// <summary>
/// 初期化
/// </summary>
void Enemy::Initialize(const Vector3& position) {

	model_ = make_unique<Model>();
	model_->Initialize(new ModelSphereState);
	isMove_ = false;

	worldTransform_.Initialize();
	worldTransform_.scale = { 1.0f,1.0f,1.0f };
	worldTransform_.translate = position;

	SetCollosionAttribute(kCollisionAttributeEnemy);
	SetCollisionMask(kCollisionAttributePlayer);
}

/// <summary>
/// 更新
/// </summary>
void Enemy::Update() {

	//EnemyMove();
	worldTransform_.UpdateMatrix();
}

/// <summary>
/// 描画
/// </summary>
void Enemy::Draw(ViewProjection viewProjection){
	model_->Draw(worldTransform_, viewProjection);
}

void Enemy::VelocityDecomposition(Vector3 velo, float angle) {
	speed = sqrt(velo.x * velo.x + velo.y * velo.y + velo.z * velo.z); // 対角線の長さ
}

void Enemy::EnemyMove() {
	/*
	if(isMove_){
		velocity = VectorTransform::Normalize(player_->GetVelocity()); // playerの移動ベクトルを正規化して代入
		velocity = VectorTransform::Multiply(velocity, speed); // 移動ベクトルと速度をかける
		worldTransform_.translate = VectorTransform::Add(worldTransform_.translate, velocity); // 移動
	}
	*/
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
