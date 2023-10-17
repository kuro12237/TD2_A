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

	pos_ = pos2_;
	playerPos_ = player_->GetWorldPosition();
	angle = atan2((pos_.z - playerPos_.z), (pos_.x, -playerPos_.x));
	angle2 = atan2((playerPos_.z - pos_.z), (playerPos_.x - pos_.x));
	angle = angle * 180.0f / (float)M_PI;
	angle2 = angle2 * 180.0f / (float)M_PI;

	if (isMove_) {
		velocity_ = PhysicsFunc::SpeedComposition(playerPos_, pos_, angle, angle2);
		speed_ = get<1>(velocity_);
		speed_ = VectorTransform::Normalize(speed_);

		isMove_ = false;
	}

	worldTransform_.translate = VectorTransform::Add(worldTransform_.translate,speed_ );
}

Vector3 Enemy::GetWorldPosition() {
	Vector3 WorldPos;
	WorldPos.x = worldTransform_.matWorld.m[3][0];
	WorldPos.y = worldTransform_.matWorld.m[3][1];
	WorldPos.z = worldTransform_.matWorld.m[3][2];
	return WorldPos;
}

void Enemy::OnCollision(){
	pos2_ = VectorTransform::Add(worldTransform_.translate, GetNamingLerp());
	isMove_ = true;
}
