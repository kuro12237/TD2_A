#include "Enemy.h"

/// <summary>
/// ‰Šú‰»
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
/// XV
/// </summary>
void Enemy::Update() {

	EnemyMove();
	worldTransform_.UpdateMatrix();
}

/// <summary>
/// •`‰æ
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

void Enemy::OnTopWall()
{
	if (worldTransform_.translate.z > static_cast<float>(FILD_MAP_SIZE_Z))
	{
		worldTransform_.translate.z = worldTransform_.translate.z - 0.1f;
	}
	speed_.z = speed_.z * -1;
}

void Enemy::OnBottomWall()
{
	if (worldTransform_.translate.z > static_cast<float>(FILD_MAP_SIZE_Z))
	{
		worldTransform_.translate.z = worldTransform_.translate.z + 0.1f;
	}
	speed_.z = speed_.z * -1;
	//velocity.z = velocity.z * -1;
}

void Enemy::OnLeftWall()
{
	if (worldTransform_.translate.x > static_cast<float>(FILD_MAP_SIZE_X))
	{
		worldTransform_.translate.x = worldTransform_.translate.x + 0.1f;
	}
	//velocity.x = velocity.x * -1;
	speed_.x = speed_.x * -1;
}

void Enemy::OnRightWall()
{
	if (worldTransform_.translate.x > -static_cast<float>(FILD_MAP_SIZE_X))
	{
		worldTransform_.translate.x = worldTransform_.translate.x - 0.1f;
	}

	speed_.x = speed_.x * -1;
	
	//velocity.x = velocity.x * -1;
}
