#include "Enemy.h"

/// <summary>
/// 
/// </summary>
void Enemy::Initialize(const Vector3& position, uint32_t texHandle) {

	model_ = make_unique<Model>();
	model_->Initialize(new ModelCubeState);
	model_->SetTexHandle(texHandle);
	model_->SetColor({ 1.0f,0.0f,0.0f,1.0f });
	worldTransform_.Initialize();
	worldTransform_.scale = { 1.0f,1.0f,1.0f };
	worldTransform_.translate = position;
	isMove_ = false;
	worldTransform_.UpdateMatrix();
	srand(static_cast<unsigned>(time(nullptr)));
	SetCollosionAttribute(kCollisionAttributeEnemy);
	SetCollisionMask(kCollisionMaskEnemy);
}

/// <summary>
/// 
/// </summary>
void Enemy::Update() {

	EnemyMove();
	RandomMove();
	if (SoundFlag&&!SoundLock)
	{
		GameAudio::PlayHitSound();
		KillCounter::AddCount();
		SoundLock = true;
	}

	worldTransform_.UpdateMatrix();
}

/// <summary>
/// 
/// </summary>
void Enemy::Draw(ViewProjection viewProjection){
	model_->Draw(worldTransform_, viewProjection);
	
}

void Enemy::EnemyMove() {

	if (worldTransform_.translate.y >= 0.6f) {
		worldTransform_.translate.y -= (fallSpeed_ * gravity_) * dt;
	}
	else if (worldTransform_.translate.y >= 0.6) {
		worldTransform_.translate.y = 0.5f;
	}


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

void Enemy::RandomMove(){

	int max = 20;
	int min = -20;

	randomX = min + rand() % (max - (min + 1));
	randomZ = min + rand() % (max - (min + 1));

	randomX = randomX / 10;
	randomZ = randomZ / 10;

	++count_;
	//480/510
	if (count_ >= 0 && speed_.x == 0.0f && speed_.z == 0.0f) {
		if (!RandFlag)
		{
			randomSpeed.x = float(randomX);
			randomSpeed.z = float(randomZ);
			randomSpeed = VectorTransform::Multiply(randomSpeed, 0.1f);
			randomSpeed.y = 0;
			RandFlag = true;
		}
	}

	if (worldTransform_.translate.x >= 28 || worldTransform_.translate.x <= -28 || worldTransform_.translate.z >= 28 || worldTransform_.translate.z <= -28) {
		randomSpeed = VectorTransform::Multiply(randomSpeed, -1.0f);
	}

	worldTransform_.translate = VectorTransform::Add(worldTransform_.translate, randomSpeed);

	if (count_ >= 120 && RandFlag) {
		randomX = 0;
		randomZ = 0;
		count_ = 0;
		randomSpeed = { 0,0,0 };
		RandFlag = false;
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
	SoundFlag = true;
}

void Enemy::OnTopWall()
{
	if (worldTransform_.translate.z > static_cast<float>(FILD_MAP_SIZE_Z))
	{
		worldTransform_.translate.z = worldTransform_.translate.z - 0.1f;
	}
	isDead_ = true;
	Score::AddScore(10);
}

void Enemy::OnBottomWall()
{
	if (worldTransform_.translate.z > static_cast<float>(FILD_MAP_SIZE_Z))
	{
		worldTransform_.translate.z = worldTransform_.translate.z + 0.1f;
	}
	isDead_ = true;
	Score::AddScore(10);
	//velocity.z = velocity.z * -1;
}

void Enemy::OnLeftWall()
{
	if (worldTransform_.translate.x > static_cast<float>(FILD_MAP_SIZE_X))
	{
		worldTransform_.translate.x = worldTransform_.translate.x + 0.1f;
	}
	//velocity.x = velocity.x * -1;
	Score::AddScore(10);
	isDead_ = true;
}

void Enemy::OnRightWall()
{
	if (worldTransform_.translate.x > -static_cast<float>(FILD_MAP_SIZE_X))
	{
		worldTransform_.translate.x = worldTransform_.translate.x - 0.1f;
	}

	isDead_ = true;
	Score::AddScore(10);
	//velocity.x = velocity.x * -1;
}
