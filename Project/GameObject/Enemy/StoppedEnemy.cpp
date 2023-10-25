#include "GameObject/Enemy/StoppedEnemy.h"

void StoppedEnemy::Initialize(const Vector3& position, uint32_t texHandle){

	model_ = make_unique<Model>();
	model_->Initialize(new ModelCubeState);
	model_->SetTexHandle(texHandle);
	model_->SetColor({ 1.0f,0.0f,0.0f,1.0f });
	worldTransform_.Initialize();
	worldTransform_.scale = { 1.0f,1.0f,1.0f };
	worldTransform_.translate = position;
	worldTransform_.UpdateMatrix();
	srand(static_cast<unsigned>(time(nullptr)));
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

void StoppedEnemy::RandomSpawn(){

	

}

void StoppedEnemy::Move(){

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
