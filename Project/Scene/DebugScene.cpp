#include "DebugScene.h"

DebugScene::~DebugScene()
{
	Audio::SoundUnLoad();	
}

void DebugScene::Initialize()
{
	viewProjection.Initialize({0,0,0.0f }, { 0.0f,0.0f,-10.0f });
	soundHandle_ = Audio::SoundLoadWave("Resources/Select.wav");
	
	sprite_ = make_unique<Sprite>();

	SpriteTexHandle = TextureManager::LoadTexture("Resources/uvChecker.png");
	sprite_->SetTexHandle(SpriteTexHandle);
	sprite_->Initialize(new SpriteBoxState,{0,0},{320,320});

	sprite2_ = make_unique<Sprite>();
	sprite2_->SetTexHandle(SpriteTexHandle);
	sprite2_->Initialize(new SpriteBoxState,{640,0},{320,320});
	
	
	sprite2WorldTransform_.Initialize();
	spriteWorldTransform_.Initialize();
	sprite2WorldTransform_.parent= &spriteWorldTransform_;


	particle_ = make_unique<Particle>();
	particle_->SetTexHandle(SpriteTexHandle);
	particle_->Initialize(new ParticlePlaneState,20);
	


}

void DebugScene::Update(GameManager* Scene)
{
	ImGui::Begin("MainCamera");
	ImGui::SliderFloat3("trans", &viewProjection.translation_.x, -15, 15);
	ImGui::SliderFloat3("rotate", &viewProjection.rotation_.x, -1, 1);
	ImGui::End();

	ImGui::Begin("key");
	ImGui::Text("0 Pushkey PlayAudio");
	ImGui::Text("9 Pushkey StateChange");
	ImGui::End();

	ImGui::Begin("Sprite");
	ImGui::ColorPicker4("color", &color.x);
	ImGui::DragFloat3("Rotate", &spriteWorldTransform_.rotation.x, 0.1f);
	ImGui::Checkbox("NONE", &NoneFlag);
	ImGui::Checkbox("Add", &AddFlag);
	ImGui::Checkbox("Subtract", &SubtractFlag);
	ImGui::Checkbox("Multiply", &MultiplyFlag);
	ImGui::Checkbox("Screen", &ScreenFlag);
	ImGui::End();


#pragma region 
	{
		if (NoneFlag)
		{
			sprite_->SetBlendMode(BlendNone);
			AddFlag = false;
			SubtractFlag = false;
			MultiplyFlag = false;
			ScreenFlag = false;
		}
		if (AddFlag)
		{
			sprite_->SetBlendMode(BlendAdd);
			NoneFlag = false;
			SubtractFlag = false;
			MultiplyFlag = false;
			ScreenFlag = false;
		}
		if (SubtractFlag)
		{
			sprite_->SetBlendMode(BlendSubtruct);
			AddFlag = false;
			NoneFlag = false;
			MultiplyFlag = false;
			ScreenFlag = false;
		}
		if (MultiplyFlag)
		{
			sprite_->SetBlendMode(BlendMultiply);
			AddFlag = false;
			SubtractFlag = false;
			NoneFlag = false;
			ScreenFlag = false;
		}
		if (ScreenFlag)
		{
			sprite_->SetBlendMode(BlendScreen);
			AddFlag = false;
			SubtractFlag = false;
			MultiplyFlag = false;
			NoneFlag = false;
		}
	}
#pragma endregion

	sprite_->SetColor(color);


	if (Input::GetInstance()->PushKeyPressed(DIK_9))
	{
		Scene->ChangeState(new GameScene);
		return;
	}
	if (Input::GetInstance()->PushKeyPressed(DIK_0))
	{
		Audio::AudioPlayWave(soundHandle_);
	}

	{//TestTranslate
		if (Input::GetInstance()->PushKey(DIK_W))
		{
			viewProjection.translation_.z += 0.01f;
		}
		if (Input::GetInstance()->PushKey(DIK_S))
		{
			viewProjection.translation_.z -= 0.01f;
		}

		if (Input::GetInstance()->PushKey(DIK_R))
		{
			viewProjection.translation_.y += 0.01f;
		}
		if (Input::GetInstance()->PushKey(DIK_F))
		{
			viewProjection.translation_.y -= 0.01f;
		}
	}
	{//TestRotate
		if (Input::GetInstance()->PushKey(DIK_A))
		{
			viewProjection.translation_.x += 0.01f;
		}if (Input::GetInstance()->PushKey(DIK_D))
		{
			viewProjection.translation_.x -= 0.01f;
		}


		if (Input::GetInstance()->PushKey(DIK_O))
		{
			viewProjection.rotation_.x += 0.01f;
		}if (Input::GetInstance()->PushKey(DIK_L))
		{
			viewProjection.rotation_.x -= 0.01f;
		}

		if (Input::GetInstance()->PushKey(DIK_LEFT))
		{
			viewProjection.rotation_.y -= 0.01f;
		}if (Input::GetInstance()->PushKey(DIK_RIGHT))
		{
			viewProjection.rotation_.y += 0.01f;
		}
	}

	spriteWorldTransform_.UpdateMatrix();
	sprite2WorldTransform_.UpdateMatrix();
	Testparticle();

	viewProjection.UpdateMatrix();
	viewProjection = DebugTools::ConvertViewProjection(viewProjection);

}

void DebugScene::Draw()
{
	sprite2_->Draw(sprite2WorldTransform_);
	sprite_->Draw(spriteWorldTransform_);

	particle_->Draw(viewProjection);
}

void DebugScene::Testparticle()
{
	ImGui::Begin("SpownParticle");
	ImGui::SliderFloat3("translate", &TestParticlesTranslate.x, 3.0f, -3.0f);
	ImGui::SliderFloat4("color", &TestParticleColor.x, 1.0f, -0.0f);
	ImGui::End();

	if (Input::GetInstance()->PushKeyPressed(DIK_P))
	{
		Particle_param p1{};
		p1.worldTransform_.Initialize();
		p1.worldTransform_.translate = TestParticlesTranslate;
		p1.color_ = TestParticleColor;
		particle_->SetList(p1);
	}

}


