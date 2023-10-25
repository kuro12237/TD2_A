#include "GameObject/Enemy/StoppedEnemy.h"


void StoppedEnemy::Initialize(const Vector3& pos, uint32_t texHandle){

	model_ = make_unique<Model>();
	model_->Initialize(new ModelCubeState);
	model_->SetTexHandle(texHandle);
	model_->SetColor({ 1.0f,0.0f,0.0f,1.0f });
	worldTransform_.Initialize();
	worldTransform_.scale = { 1.0f,1.0f,1.0f };
	worldTransform_.translate = pos;
	worldTransform_.UpdateMatrix();
	SetCollosionAttribute(kCollisionAttributeEnemy);
	SetCollisionMask(kCollisionAttributePlayer);
}

void StoppedEnemy::Update(){

	Move();
	worldTransform_.UpdateMatrix();
}

void StoppedEnemy::Draw(ViewProjection viewProjection){
	model_->Draw(worldTransform_, viewProjection);
}

void StoppedEnemy::Move(){

	if (worldTransform_.translate.y <= 0.4f) {
		worldTransform_.translate.y += 0.05f;
	}
	else if (worldTransform_.translate.y >= 0.4f) {
		worldTransform_.translate.y = 0.5f;
	}

	
	

	if (isMove_) {

		playerPos_ = player_->GetWorldPosition();
		pos_ = GetWorldPosition();
		angle = atan2((worldTransform_.matWorld.m[3][2] - playerPos_.z), (worldTransform_.matWorld.m[3][0] - playerPos_.x));
		angle2 = atan2((playerPos_.z - worldTransform_.matWorld.m[3][2]), (playerPos_.x - worldTransform_.matWorld.m[3][0]));
		angle = angle * 180.0f / (float)M_PI;
		angle2 = angle2 * 180.0f / (float)M_PI;
		velocity_ = PhysicsFunc::SpeedComposition(playerPos_, pos_, angle, angle2);

		KillCounter::AddCount();
		GameAudio::PlayHitSound();
		velocity_ = PhysicsFunc::SpeedComposition(playerPos_, worldTransform_.translate, angle, angle2);

		speed_ = get<1>(velocity_);

		isMove_ = false;

	}
	
	
	worldTransform_.translate = VectorTransform::Add(worldTransform_.translate, speed_);
	
	
}

Vector3 StoppedEnemy::GetWorldPosition()
{
	Vector3 WorldPos;
	WorldPos.x = worldTransform_.matWorld.m[3][0];
	WorldPos.y = worldTransform_.matWorld.m[3][1];
	WorldPos.z = worldTransform_.matWorld.m[3][2];
	return WorldPos;
}

Vector3 StoppedEnemy::GetVelocity()
{
	Vector3 result;
	result.x = speed_.x;
	result.y = speed_.y;
	result.z = speed_.z;
	return result;
}

void StoppedEnemy::OnCollision()
{
	isMove_ = true;
}

void StoppedEnemy::OnTopWall()
{
	if (worldTransform_.translate.z > static_cast<float>(FILD_MAP_SIZE_Z))
	{
		worldTransform_.translate.z = worldTransform_.translate.z - 0.1f;
	}
	isDead_ = true;
	Score::AddScore(10);
}

void StoppedEnemy::OnBottomWall()
{
	if (worldTransform_.translate.z > static_cast<float>(FILD_MAP_SIZE_Z))
	{
		worldTransform_.translate.z = worldTransform_.translate.z + 0.1f;
	}
	isDead_ = true;
	Score::AddScore(10);
	//velocity.z = velocity.z * -1;
}

void StoppedEnemy::OnLeftWall()
{
	if (worldTransform_.translate.x > static_cast<float>(FILD_MAP_SIZE_X))
	{
		worldTransform_.translate.x = worldTransform_.translate.x + 0.1f;
	}
	//velocity.x = velocity.x * -1;
	Score::AddScore(10);
	isDead_ = true;
}

void StoppedEnemy::OnRightWall()
{
	if (worldTransform_.translate.x > -static_cast<float>(FILD_MAP_SIZE_X))
	{
		worldTransform_.translate.x = worldTransform_.translate.x - 0.1f;
	}

	isDead_ = true;
	Score::AddScore(10);
	//velocity.x = velocity.x * -1;
}
