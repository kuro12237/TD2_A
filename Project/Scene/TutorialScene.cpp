#include "TutorialScene.h"

// 初期化処理
void TutorialScene::Initialize() {

	GameAudio::Initialize();
	// テクスチャの読み込み
	tutorial_.TexHD[0] = TextureManager::LoadTexture("Resources/Texture/BackGround/Tutorial/Tutorial1.png");
	tutorial_.TexHD[1] = TextureManager::LoadTexture("Resources/Texture/BackGround/Tutorial/Tutorial2.png");
	uint32_t useFade_BG = TextureManager::LoadTexture("Resources/Texture/BackGround/BackGround.png");


	tutorial_.position = { 0.0f, 0.0f };
	for (int Index = 0; Index < 2; Index++) {

		// 座標
		tutorial_.worldTansform[Index].Initialize();

		// スプライト
		tutorial_.sprite[Index] = make_unique<Sprite>();
		tutorial_.sprite[Index]->Initialize(new SpriteBoxState, tutorial_.position, { 1280.0f, 720.0f });
		tutorial_.sprite[Index]->SetTexHandle(tutorial_.TexHD[Index]);
		tutorial_.sprite[Index]->SetColor(TexColor);
	}

	// フェードの処理
	TransitionProcess::Initialize();
	// フェードに使う画像の設定
	TransitionProcess::GetInstance()->GetBG_Sprite()->SetTexHandle(useFade_BG);
	// 色を黒くしておく
	TransitionProcess::GetInstance()->GetBG_Sprite()->SetColor({ 0.0f, 0.0f, 0.0f, 1.0f });
	// フェードが明ける処理
	TransitionProcess::Fade_Out_Init();

	nowPage_ = 0;
	fade_ = false;
}



// 更新処理
void TutorialScene::Update(GameManager* scene)
{

	// フェードが明ける処理
	TransitionProcess::Fade_In();
	TransitionProcess::Fade_Out();


	// Aボタンでスタート
	XINPUT_STATE joyState{};
	Input::NoneJoyState(joyState);
	TransitionProcess::Fade_In();
	// フェードの処理が終わったらシーン遷移
	if (TransitionProcess::Fade_In()) {

		scene->ChangeState(new GameScene);
		return;
	}
	if (nowPage_ == 0) {
		if (Input::GetInstance()->GetJoystickState(joyState)) {
			if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_A)
			{
				GameAudio::PlaySelectSound();
				nowPage_ = 1;
				timer_ = 80;
			}
		}
		if (Input::GetInstance()->PushKeyPressed(DIK_SPACE)) {
			GameAudio::PlaySelectSound();
			nowPage_ = 1;
			timer_ = 80;
		}
	}
	else if (nowPage_ == 1) {

		timer_--;

		if (timer_ <= 0)
		{
			timer_ = 0;
			fade_ = true;
		}

		if (fade_)
		{
			if (Input::GetInstance()->GetJoystickState(joyState)) {
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
		}
	}
	// フェードの処理が終わったらシーン遷移
	if (TransitionProcess::Fade_In()) {
		scene->ChangeState(new GameScene);
		return;
	}
}



// 描画処理
void TutorialScene::Back2dSpriteDraw()
{
}

void TutorialScene::Object3dDraw()
{
}
void TutorialScene::Flont2dSpriteDraw()
{
	tutorial_.sprite[nowPage_]->Draw(tutorial_.worldTansform[nowPage_]);
	TransitionProcess::Draw();
}