#include "Player.h"
#include"GameObject/Enemy/Enemy.h"

void Player::Initialize()
{
	model_ = make_unique<Model>();
	model_->UseLight(HARF_LAMBERT);
	model_->Initialize(new ModelSphereState);
	texHandle = TextureManager::LoadTexture("Resources/Green.png");
	model_->SetTexHandle(texHandle);

	MoveEffect = make_unique<PlayerParticle>();
	MoveEffect->Initialize();

	reticleTestModel = make_unique<Model>();
	reticleTestModel->Initialize(new ModelSphereState);
	reticleTestModel->SetColor({ 0,1,0,1 });

	LineModel_ = make_unique<Model>();
	LineModel_->Initialize(new ModelLineState, { 0,0,0,1 }, { 0,0,4,1 });

	worldTransform_.Initialize();
	worldTransform_.SRTSetting({ 1,1,1 }, { 0,0,0 }, { 0,0.5f,0 });

	reticleWorldTransform.Initialize();
	
	LineWorldTransform_.Initialize();
	LineWorldTransform_.parent = &worldTransform_;
	LineWorldTransform_.translate.y = 0.5f;

	isMove_ = false;
	SetCollosionAttribute(kCollisionAttributePlayer);
	SetCollisionMask(kCollisionAttributeEnemy);
	
	SetSize(model_->GetSize());
}

void Player::Update()
{
	HitFlag = false;
	Reticle();
	SetVelosity(Velocity);
	Move();
	if (MoveFlag)
	{
		MoveEffect->Spown(worldTransform_.translate);
	}
	MoveEffect->Update();

	LineWorldTransform_.UpdateMatrix();
	reticleWorldTransform.UpdateMatrix();
	worldTransform_.UpdateMatrix();
}

void Player::Draw(ViewProjection view)
{
	model_->Draw(worldTransform_, view);
	LineModel_->Draw(worldTransform_, view);
	MoveEffect->Draw(view);
}

void Player::OnCollision()
{
	HitFlag = true;
	isMove_ = true;
}

void Player::OnTopWall()
{
	if (worldTransform_.translate.z > static_cast<float>(FILD_MAP_SIZE_Z))
	{
    	worldTransform_.translate.z = worldTransform_.translate.z - 0.1f;
	}
	Velocity.z = Velocity.z * -1;
}

void Player::OnBottomWall()
{
	if (worldTransform_.translate.z > static_cast<float>(FILD_MAP_SIZE_Z))
	{
		worldTransform_.translate.z = worldTransform_.translate.z + 0.1f;
	}
	Velocity.z = Velocity.z * -1;
}

void Player::OnLeftWall()
{
	if (worldTransform_.translate.x > static_cast<float>(FILD_MAP_SIZE_X))
	{
		worldTransform_.translate.x = worldTransform_.translate.x + 0.1f;
	}
	Velocity.x = Velocity.x * -1;	
}

void Player::OnRightWall()
{
	if (worldTransform_.translate.x > -static_cast<float>(FILD_MAP_SIZE_X))
	{
		worldTransform_.translate.x = worldTransform_.translate.x - 0.1f;
	}
	Velocity.x = Velocity.x * -1;	
}

Vector3 Player::GetWorldPosition()
{
	Vector3 result;
	result.x = worldTransform_.matWorld.m[3][0];
	result.y = worldTransform_.matWorld.m[3][1];
	result.z = worldTransform_.matWorld.m[3][2];
	return result;
}

Vector3 Player::GetVelocity()
{
	Vector3 result;
	result.x = Velocity.x;
	result.y = Velocity.y;
	result.z = Velocity.z;
	return result;
}

void Player::Move()
{
#pragma region keybord
	//回転
	if (Input::GetInstance()->PushKey(DIK_A)){
		worldTransform_.rotation.y -= rotateSpeed;
	}else if(Input::GetInstance()->PushKey(DIK_D)){
		worldTransform_.rotation.y += rotateSpeed;
	}
	//覇者
	if (!MoveFlag && Input::GetInstance()->PushKey(DIK_SPACE))
	{
		MoveFlag = true;
		Velocity = RPNormalize;
		Velocity = VectorTransform::Multiply(Velocity, speed);
	}
#pragma endregion 

#pragma region Controler

	XINPUT_STATE joyState{};
	Input::NoneJoyState(joyState);
	if (Input::GetInstance()->GetJoystickState(joyState))
	{
		//回転
		Rvelocity.x = 0.0f;
		Rvelocity.z = 0.0f;
		Rvelocity.y = float(joyState.Gamepad.sThumbLX / SHRT_MAX);
		Rvelocity.y = Rvelocity.y * 0.1f;
		worldTransform_.rotation = VectorTransform::Add(worldTransform_.rotation, Rvelocity);
		
		//発射処理
		if (!MoveFlag && joyState.Gamepad.wButtons &XINPUT_GAMEPAD_A)
		{
			MoveFlag = true;
			Velocity = RPNormalize;
			Velocity = VectorTransform::Multiply(Velocity, speed);
		}

	}
#pragma endregion 
    
	//フラグ切り替え
	if (abs(Velocity.x)<0.05f && abs(Velocity.y)<0.05f && abs(Velocity.z)<0.05f)
	{
		MoveFlag = false;
	}
  
	if (MoveCoolTime > MAX_MOVE_COOLTIME)
	{
		MoveCoolTime = 0;
		
		//MoveFlag = false;
	}

	// 敵に衝突した後の処理 ↓
	list<shared_ptr<Enemy>>& enemys = enemys_;

	for (shared_ptr<Enemy>& enemy : enemys) {

		enemyPos_ = enemy->GetWorldPosition();
		angle = atan2((worldTransform_.translate.z - enemyPos_.z), (worldTransform_.translate.x, enemyPos_.x));
		angle2 = atan2((enemyPos_.z - worldTransform_.translate.z), (enemyPos_.x - worldTransform_.translate.x));
		angle = angle * 180.0f / (float)M_PI;
		angle2 = angle2 * 180.0f / (float)M_PI;

			if (isMove_) {

				velocity_ = PhysicsFunc::SpeedComposition(enemyPos_, worldTransform_.translate, angle, angle2);
				HitVelo = get<0>(velocity_);
				HitVelo = VectorTransform::Normalize(HitVelo);
				Velocity = HitVelo;
				isMove_ = false;
			}
			
		

	}
	// ここまで ↑
  
	//摩擦
	FancFrictionCoefficient();
	//加算処理
	worldTransform_.translate = VectorTransform::Add(worldTransform_.translate, Velocity);

	
	ImGui::Begin("Player_param");
	ImGui::Text("WorldPos : %f %f %f", worldTransform_.translate.x, worldTransform_.translate.y, worldTransform_.translate.z);
	ImGui::Text("Normalize : %f %f %f", RPNormalize.x, RPNormalize.y, RPNormalize.z);
	ImGui::Text("Velocity : %f %f %f", Velocity.x, Velocity.y, Velocity.z);
	ImGui::End();

}

void Player::Reticle()
{
	if (MoveFlag)
	{
		return;
	}
	Vector3 Ppos{};
   	Ppos.x = worldTransform_.matWorld.m[3][0];
	Ppos.y = worldTransform_.matWorld.m[3][1];
	Ppos.z = worldTransform_.matWorld.m[3][2];
	worldTransform_.UpdateMatrix();

	const float kDistancePlayerTo3DReticle = 40.0f;
	Vector3 offset = { 0.0f, 0.0f, 1.0f };

	offset = VectorTransform::TransformNormal(offset, worldTransform_.matWorld);
	offset = VectorTransform::Normalize(offset);
	offset = VectorTransform::Multiply(offset, kDistancePlayerTo3DReticle);

	reticleWorldTransform.translate = VectorTransform::Add(offset, Ppos);
	reticleWorldTransform.UpdateMatrix();

	Vector3 Rpos{};
	Rpos.x = reticleWorldTransform.matWorld.m[3][0];
	Rpos.y = reticleWorldTransform.matWorld.m[3][1];
	Rpos.z = reticleWorldTransform.matWorld.m[3][2];

	RPNormalize = VectorTransform::Subtruct(Rpos, Ppos);
	RPNormalize = VectorTransform::Normalize(RPNormalize);
	
}

void Player::FancFrictionCoefficient()
{
	//x
	if (Velocity.x > 0.0f)
	{
		Velocity.x -= frictionCoefficient * Velocity.x;
	}
	else if (Velocity.x< 0.0f)
	{
		Velocity.x += frictionCoefficient * -Velocity.x;
	}
	//z
	if (Velocity.z > 0.0f)
	{
		Velocity.z -= frictionCoefficient * Velocity.z;
	}
	else if (Velocity.z < 0.0f)
	{
		Velocity.z += frictionCoefficient * -Velocity.z;
	}
}

Vector3 Player::NoramalizeLerp(Vector3 v1, Vector3 v2)
{
	Vector3 result = VectorTransform::Lerp(v1, v2, 1);
	result = VectorTransform::Normalize(result);
	return result;
}
