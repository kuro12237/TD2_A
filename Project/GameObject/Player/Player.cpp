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
	worldTransform_.translate.y = 0.5;

	reticleWorldTransform.Initialize();

	reticleWorldTransform.parent = &worldTransform_;
	reticleWorldTransform.translate.z = reticleWorldTransform.translate.z + 5.0f;
	reticleWorldTransform.translate.y = 0.5;
	
	PlaneworldTransform_.Initialize();
	PlaneworldTransform_.parent = &worldTransform_;
	PlaneworldTransform_.scale = { 10,10,10, };

	PlaneModel_ = make_unique<Model>();
	PlaneModel_->CreateFromObj("TestPlane");


}

void Player::Update()
{
	Move();
	Reticle();

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

	if (Input::GetInstance()->PushKeyPressed(DIK_SPACE))
	{
		speed = RPLerp;
	}
	
	//–€ŽC
	frictionCoefficientTimer++;
	if (isSpeed())
	{
		if (frictionCoefficientTimer > 4)
		{
			AddfrictionCoefficient();
			frictionCoefficientTimer = 0;
		}
	}

	//ˆÚ“®‰ÁŽZ
	worldTransform_.translate.x += speed.x;
	worldTransform_.translate.z += speed.z;
	//worldTransform_.translate = VectorTransform::Add(worldTransform_.translate, speed);
	//‰ñ“]
	//worldTransform_.rotation.x += speed.z;
	//worldTransform_.rotation.z += speed.x;
}

void Player::Reticle()
{
	//Vector3 Rpos = GetReticleWorldTransform();
	Vector3 Ppos = GetWorldPosition();

 	//RPLerp = NoramalizeLerp(Rpos, Ppos);
}

bool Player::isSpeed()
{
	if (speed.z>0.0f||speed.y>0.0f||speed.z>0.0f)
	{
		return true;
	}

	return false;
}

void Player::AddfrictionCoefficient()
{
	if (speed.x > 0.0f)
	{
		speed.x -= frictionCoefficient;
	}
	if (speed.y > 0.0f)
	{
		speed.y -= frictionCoefficient;
	}
	if (speed.z > 0.0f)
	{
		speed.z -= frictionCoefficient;
	}
}

Vector3 Player::NoramalizeLerp(Vector3 v1, Vector3 v2)
{
	Vector3 result = VectorTransform::Lerp(v1, v2, 1);
	result = VectorTransform::Normalize(result);
	return result;
}
