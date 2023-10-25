#include "Player.h"
#include"GameObject/Enemy/Enemy.h"

void Player::Initialize()
{
	model_ = make_unique<Model>();
	model_->UseLight(HARF_LAMBERT);
	model_->Initialize(new ModelSphereState);
	texHandle = TextureManager::LoadTexture("Resources/Texture/player.png");
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
	SetCollisionMask(kCollisionMaskPlayer);
	
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
		GameAudio::PlayShotSound();
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
		Rvelocity.y = 0.0f;
		if (joyState.Gamepad.wButtons& XINPUT_GAMEPAD_DPAD_LEFT)
		{
			Rvelocity.y = -0.05f;
		}
		if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
		{
			Rvelocity.y = 0.05f;
		}
		//Rvelocity.y = Rvelocity.y * 0.1f;
		worldTransform_.rotation = VectorTransform::Add(worldTransform_.rotation, Rvelocity);
		
		//発射処理
		if (!MoveFlag && joyState.Gamepad.wButtons &XINPUT_GAMEPAD_A)
		{
			GameAudio::PlayShotSound();
			MoveFlag = true;
			Velocity = RPNormalize;
			Velocity = VectorTransform::Multiply(Velocity, speed);
		}

	}
#pragma endregion 
    
	//フラグ切り替え
	if (abs(Velocity.x)<0.5f && abs(Velocity.y)<0.5f && abs(Velocity.z)<0.5f)
	{
		MoveFlag = false;
	}
  

	// 敵に衝突した後の処理 ↓
	list<shared_ptr<Enemy>>& enemys = enemys_;

	if (isMove_) {

		for (shared_ptr<Enemy>& enemy : enemys) {

			pos_ = GetWorldPosition();
			enemyPos_ = enemy->GetWorldPosition();
			angle2 = atan2((worldTransform_.matWorld.m[3][2] - enemyPos_.z), (worldTransform_.matWorld.m[3][0] - enemyPos_.x));
			angle = atan2((enemyPos_.z - worldTransform_.matWorld.m[3][2]), (enemyPos_.x - worldTransform_.matWorld.m[3][0]));
			angle = angle * 180.0f / (float)M_PI;
			angle2 = angle2 * 180.0f / (float)M_PI;

			velocity_ = PhysicsFunc::SpeedComposition(pos_, enemyPos_, angle, angle2);
			HitVelo = get<0>(velocity_);
			Velocity = HitVelo;
			
		}

		isMove_ = false;

		
	}

	// ここまで ↑
  
	//摩擦
	FancFrictionCoefficient();
	//加算処理
	
	worldTransform_.translate = VectorTransform::Add(worldTransform_.translate, Velocity);
	
	

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
