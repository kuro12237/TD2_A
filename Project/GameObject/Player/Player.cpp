#include "Player.h"

void Player::Initialize()
{
	model_ = make_unique<Model>();
	model_->Initialize(new ModelSphereState);


	texHandle = TextureManager::LoadTexture("Resources/uvChecker.png");
	model_->SetTexHandle(texHandle);

	reticleTestModel = make_unique<Model>();
	reticleTestModel->Initialize(new ModelSphereState);
	reticleTestModel->SetTexHandle(texHandle);

	worldTransform_.Initialize();
	worldTransform_.scale = { 1.0f,1.0f,1.0f };
	
	reticleWorldTransform.Initialize();
	
	PlaneworldTransform_.Initialize();
	PlaneworldTransform_.parent = &worldTransform_;
	PlaneworldTransform_.scale = { 10,10,10, };

	PlaneModel_ = make_unique<Model>();
	PlaneModel_->CreateFromObj("TestPlane");


}

void Player::Update()
{
	Reticle();
	Move();
	

	ImGui::Begin("plane");
	ImGui::Text("RPLERP : %f,%f,%f", RPLerp);
	ImGui::DragFloat3("rotate", &PlaneworldTransform_.rotation.x, 0.1f);
	ImGui::End();
	
	PlaneworldTransform_.UpdateMatrix();
	reticleWorldTransform.UpdateMatrix();
	worldTransform_.UpdateMatrix();
}

void Player::Draw(ViewProjection view)
{
	model_->Draw(worldTransform_, view);
	reticleTestModel->Draw(reticleWorldTransform, view);
	PlaneModel_->Draw(PlaneworldTransform_, view);
}

Vector3 Player::GetWorldPosition()
{
	Vector3 result;
	result.x = worldTransform_.matWorld.m[3][0];
	result.y = worldTransform_.matWorld.m[3][1];
	result.z = worldTransform_.matWorld.m[3][2];
	return result;
}

void Player::Move()
{
	if (Input::GetInstance()->PushKey(DIK_A))
	{
		worldTransform_.rotation.y += 0.1f;
	}
	else if(Input::GetInstance()->PushKey(DIK_D))
	{
		worldTransform_.rotation.y -= 0.1f;
	}


	if (!MoveFlag&&Input::GetInstance()->PushKey(DIK_SPACE))
	{
		MoveFlag = true;
		Velocity = RPLerp;
	}
	
	MoveCoolTime++;
	if (MoveCoolTime > 300)
	{
		MoveCoolTime = 0;
		MoveFlag = false;
	}

	//‰ÁŽZˆ—
	FancFrictionCoefficient();

	worldTransform_.translate.x += Velocity.x;
	worldTransform_.translate.y += Velocity.y;
	worldTransform_.translate.z += Velocity.z;


	ImGui::Begin("Debug");
	ImGui::Text("Speed : %f  %f  %f", Velocity.x, Velocity.y, Velocity.z);
	ImGui::Text("RPLerp : %f %f %f", RPLerp.x, RPLerp.y, RPLerp.z);
	ImGui::End();

	//ˆÚ“®‰ÁŽZ
	
	
	//‰ñ“]

}

void Player::Reticle()
{
	if (!MoveFlag)
	{
		Vector3 Ppos{};
		Ppos.x = worldTransform_.matWorld.m[3][0];
		Ppos.y = worldTransform_.matWorld.m[3][1];
		Ppos.z = worldTransform_.matWorld.m[3][2];
		worldTransform_.UpdateMatrix();

		{
			const float kDistancePlayerTo3DReticle = 40.0f;
			Vector3 offset = { 0.0f, 0.0f, 1.0f };

			offset = VectorTransform::TransformNormal(offset, worldTransform_.matWorld);
			offset = VectorTransform::Normalize(offset);

			offset.x *= kDistancePlayerTo3DReticle;
			offset.y *= kDistancePlayerTo3DReticle;
			offset.z *= kDistancePlayerTo3DReticle;

			reticleWorldTransform.translate.x = offset.x + Ppos.x;
			reticleWorldTransform.translate.y = offset.y + Ppos.y;
			reticleWorldTransform.translate.z = offset.z + Ppos.z;
			reticleWorldTransform.UpdateMatrix();

			Vector3 Rpos{};
			Rpos.x = reticleWorldTransform.matWorld.m[3][0];
			Rpos.y = reticleWorldTransform.matWorld.m[3][1];
			Rpos.z = reticleWorldTransform.matWorld.m[3][2];

			RPLerp.x = Rpos.x - Ppos.x;
			RPLerp.y = Rpos.y - Ppos.y;
			RPLerp.z = Rpos.z - Ppos.z;

			RPLerp = VectorTransform::Normalize(RPLerp);
		}
	}
}

void Player::FancFrictionCoefficient()
{
	if (Velocity.x > 0.0f)
	{
		Velocity.x -= 0.1f * Velocity.x;
	}
	else if (Velocity.x< 0.0f)
	{
		Velocity.x += 0.1f * -Velocity.x;
	}

	if (Velocity.z > 0.0f)
	{
		Velocity.z -= 0.1f * Velocity.z;
	}
	else if (Velocity.z < 0.0f)
	{
		Velocity.z += 0.1f * -Velocity.z;
	}
}

Vector3 Player::NoramalizeLerp(Vector3 v1, Vector3 v2)
{
	Vector3 result = VectorTransform::Lerp(v1, v2, 1);
	result = VectorTransform::Normalize(result);
	return result;
}
