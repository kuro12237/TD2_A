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

	playerPos_ = player_->GetWorldPosition();
	angle = atan2((worldTransform_.translate.z - playerPos_.z), (worldTransform_.translate.x - playerPos_.x));
	angle2 = atan2((playerPos_.z - worldTransform_.translate.z), (playerPos_.x - worldTransform_.translate.x));
	angle = angle * 180.0f / (float)M_PI;
	angle2 = angle2 * 180.0f / (float)M_PI;

		if (isMove_) {
			velocity_ = PhysicsFunc::SpeedComposition(playerPos_, worldTransform_.translate, angle, angle2);
			speed_ = get<1>(velocity_);
			speed_ = VectorTransform::Normalize(speed_);
			isMove_ = false;
			
		}
		else {
			worldTransform_.translate = VectorTransform::Add(worldTransform_.translate, speed_);
		}
	
}

Vector3 Enemy::GetWorldPosition() {
	Vector3 WorldPos;
	WorldPos.x = worldTransform_.matWorld.m[3][0];
	WorldPos.y = worldTransform_.matWorld.m[3][1];
	WorldPos.z = worldTransform_.matWorld.m[3][2];
	return WorldPos;
}

Vector3 Enemy::GetVelocity()
{
	Vector3 result;
	result.x = speed_.x;
	result.y = speed_.y;
	result.z = speed_.z;
	return result;
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
	//velocity_.z = velocity_.z * -1;
}

void Enemy::OnBottomWall()
{
	if (worldTransform_.translate.z > static_cast<float>(FILD_MAP_SIZE_Z))
	{
		worldTransform_.translate.z = worldTransform_.translate.z + 0.1f;
	}
	//velocity.z = velocity.z * -1;
}

void Enemy::OnLeftWall()
{
	if (worldTransform_.translate.x > static_cast<float>(FILD_MAP_SIZE_X))
	{
		worldTransform_.translate.x = worldTransform_.translate.x + 0.1f;
	}
	//velocity.x = velocity.x * -1;
}

void Enemy::OnRightWall()
{
	if (worldTransform_.translate.x > -static_cast<float>(FILD_MAP_SIZE_X))
	{
		worldTransform_.translate.x = worldTransform_.translate.x - 0.1f;
	}
	//velocity.x = velocity.x * -1;
}
