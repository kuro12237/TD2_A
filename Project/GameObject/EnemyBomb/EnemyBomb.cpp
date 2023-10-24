#include "EnemyBomb.h"

void EnemyBomb::Initialize(Vector3 position, uint32_t texHandle)
{
	state_ =  new stateMoveEnemyBomb;
	worldTransform_.Initialize();
	worldTransform_.translate = position;
	worldTransform_.scale = { 0.5f,0.5f,0.5f };
	worldTransform_.UpdateMatrix();

	model = make_unique<Model>();
	
	model->Initialize(new ModelCubeState,{0,0},{3,3});
	model->SetColor({ 1.0f,0.5f,0.0f,1.0f });

	model->SetTexHandle(texHandle);
	SetCollosionAttribute(kCollisionAttributeEnemy);
	SetCollisionMask(kCollisionAttributePlayer);
}

void EnemyBomb::Update()
{
	SetRadious(Radious);
	ImGui::Begin("t");
	ImGui::Text("%f", Radious);
	ImGui::End();
	state_->Move(worldTransform_, this);
	
	worldTransform_.UpdateMatrix();
}

void EnemyBomb::Draw(ViewProjection view)
{
	model->Draw(worldTransform_, view);
}

Vector3 EnemyBomb::GetWorldPosition()
{
	Vector3 result{};
	result.x = worldTransform_.matWorld.m[3][0];
	result.y = worldTransform_.matWorld.m[3][1];
	result.z = worldTransform_.matWorld.m[3][2];
	return result;
}

void EnemyBomb::OnCollision()
{


}

Vector3 EnemyBomb::GetVelocity()
{
	return Vector3();
}

void EnemyBomb::ChangeState(IstateEnemyBomb* state)
{
	delete state_;
	state_ = state;
}
