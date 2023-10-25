#include "TitleScene.h"



// 初期化処理
void TitleScene::Initialize() {

	GameAudio::Initialize();
	// テクスチャの読み込み

	//title_TexHD_ = TextureManager::LoadTexture("Resources/Title.png");
	titleBg_.TexHD = TextureManager::LoadTexture("Resources/Title.png");
	pushBg_.TexHD = TextureManager::LoadTexture("Resources/Texture/BackGround/Title/titlePush.png");

	uint32_t useFade_BG = TextureManager::LoadTexture("Resources/Texture/BackGround/BackGround.png");


	// 座標
	titleBg_.worldTransform.Initialize();
	titleBg_.Position = { 0.0f, 0.0f };
	pushBg_.worldTransform.Initialize();
	titleBg_.Position = { 0.0f, 0.0f };


	// スプライト
	titleBg_.Sprite = make_unique<Sprite>();
	titleBg_.Sprite->Initialize(new SpriteBoxState, titleBg_.Position, { 1280.0f, 720.0f });
	titleBg_.Sprite->SetTexHandle(titleBg_.TexHD);
	titleBg_.Sprite->SetColor(TexColor_);
	pushBg_.Sprite = make_unique<Sprite>();
	pushBg_.Sprite->Initialize(new SpriteBoxState, pushBg_.Position, { 1280.0f, 720.0f });
	pushBg_.Sprite->SetTexHandle(pushBg_.TexHD);
	pushBg_.Sprite->SetColor(TexColor_);


	// フェードの処理
	TransitionProcess::Initialize();
	// フェードに使う画像の設定
	TransitionProcess::GetInstance()->GetBG_Sprite()->SetTexHandle(useFade_BG);
	// 色を黒くしておく
	TransitionProcess::GetInstance()->GetBG_Sprite()->SetColor({ 0.0f, 0.0f, 0.0f, 1.0f });
	// フェードが明ける処理
	TransitionProcess::Fade_Out_Init();

	viewProjection_.Initialize({ 0.2f,-0.7f,0.0f }, { 50.0f,20.0f,-50 });
	
	shamWall_ = make_unique<ShamWall>();
	shamWall_->Initialize();

	// 天球
	skydome_ = make_unique<Skydome>();
	skydome_->Initialize();
	MainCamera::SetOffset({ 0.0f,3.0f,-70.0f });
	// 床
	mapGround_ = make_unique<MapGround>();
	mapGround_->Initialize();
	MainCamera::Initialize();
	CenterWorldTransform.Initialize();

}

// 更新処理
void TitleScene::Update(GameManager* scene) {

	shamWall_->Update();
	// 天球
	skydome_->Update();
	// 床
	mapGround_->Updatea();

	titleBg_.worldTransform.UpdateMatrix();

	pushBg_.worldTransform.UpdateMatrix();

	CenterWorldTransform.rotation.y+=0.001f;

	viewProjection_.UpdateMatrix();
	MainCamera::Update(CenterWorldTransform);
	viewProjection_= MainCamera::GetViewProjection();


	// フェードが明ける処理
	TransitionProcess::Fade_Out();
	if (TransitionProcess::Fade_Out()) {

		// シーン遷移
		// スペースでフェードスタート
		XINPUT_STATE joyState{};
		Input::NoneJoyState(joyState);
		if (Input::GetInstance()->GetJoystickState(joyState))
		{
			//発射処理
			if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_A)
			{
				GameAudio::PlaySelectSound();
				TransitionProcess::Fade_In_Init();
			}

		}
		if (Input::GetInstance()->PushKeyPressed(DIK_SPACE)) {
			GameAudio::PlaySelectSound();
			TransitionProcess::Fade_In_Init();
		}
		TransitionProcess::Fade_In();
		// フェードの処理が終わったらシーン遷移
		if (TransitionProcess::Fade_In()) {
			scene->ChangeState(new TutorialScene);
			return;
		}
	}


#ifdef _DEBUG

	ImGui::Begin("TitleScene");
	ImGui::Text("9 key = ChangeScene() -> GameScene");
	ImGui::Text("space key = ChangeScene() -> TutorialScene");
	ImGui::End();

#endif
}



// 描画処理
void TitleScene::Back2dSpriteDraw()
{
}
void TitleScene::Object3dDraw()
{
	skydome_->Draw(viewProjection_);

	mapGround_->Draw(viewProjection_);
	shamWall_->Draw(viewProjection_);
}
void TitleScene::Flont2dSpriteDraw()
{

	//title_Sprite_->Draw(title_WorldTransform_);

	titleBg_.Sprite->Draw(titleBg_.worldTransform);
	pushBg_.Sprite->Draw(pushBg_.worldTransform);

	TransitionProcess::Draw();
}