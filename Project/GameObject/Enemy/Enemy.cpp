#include "Enemy.h"

Enemy::Enemy(){}
Enemy::~Enemy(){}

/// <summary>
/// ������
/// </summary>
void Enemy::Initialize(const Vector3& position) {

	model_ = make_unique<Model>();
	model_->Initialize(new ModelSphereState);
	//isMove_ = false;

	worldTransform_.Initialize();
	worldTransform_.scale = { 1.0f,1.0f,1.0f };
	worldTransform_.translate = position;

	SetCollosionAttribute(kCollisionAttributeEnemy);
	SetCollisionMask(kCollisionAttributePlayer);
}

/// <summary>
/// �X�V
/// </summary>
void Enemy::Update() {

	//EnemyMove();
	worldTransform_.UpdateMatrix();
}

/// <summary>
/// �`��
/// </summary>
void Enemy::Draw(ViewProjection viewProjection){
	model_->Draw(worldTransform_, viewProjection);
}

void Enemy::VelocityDecomposition(Vector3 velo, float angle) {
	speed = sqrt(velo.x * velo.x + velo.y * velo.y + velo.z * velo.z); // �Ίp���̒���
	angle;
}

void Enemy::EnemyMove() {
	/*
	if(isMove_){
		velocity = VectorTransform::Normalize(player_->GetVelocity()); // player�̈ړ��x�N�g���𐳋K�����đ��
		velocity = VectorTransform::Multiply(velocity, speed); // �ړ��x�N�g���Ƒ��x��������
		worldTransform_.translate = VectorTransform::Add(worldTransform_.translate, velocity); // �ړ�
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
	model_->SetColor({ 1.0f,0.0f,0.0f,1.0f });
}
