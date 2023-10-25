#include "ResultScene.h"



// 初期化処理
void ResultScene::Initialize() {

	// テクスチャの読み込み
	result_.TexHD[0] = TextureManager::LoadTexture("Resources/Texture/BackGround/Result/Result_Back.png");
	result_.TexHD[1] = TextureManager::LoadTexture("Resources/Texture/BackGround/Result/Result_front.png");
	result_.TexHD[2] = TextureManager::LoadTexture("Resources/Texture/BackGround/Result/MojiUI.png");
	uint32_t useFade_BG = TextureManager::LoadTexture("Resources/Texture/BackGround/BackGround.png");
	uint32_t scoreTexHD_ = TextureManager::LoadTexture("Resources/Texture/UI/Score.png");

	// 座標
	result_.position = { 0.0f, 0.0f };

	// スプライト
	for (int Index = 0; Index < 3; Index++) {
		result_.worldTransform[Index].Initialize();
		result_.sprite[Index] = make_unique<Sprite>();
		result_.sprite[Index]->Initialize(new SpriteBoxState, result_.position, { 1280.0f, 720.0f });
		result_.sprite[Index]->SetTexHandle(result_.TexHD[Index]);
		result_.sprite[Index]->SetColor(result_TexColor_);
	}

	// フェードの処理
	TransitionProcess::Initialize();
	// フェードに使う画像の設定
	TransitionProcess::GetInstance()->GetBG_Sprite()->SetTexHandle(useFade_BG);
	// 色を黒くしておく
	TransitionProcess::GetInstance()->GetBG_Sprite()->SetColor({ 0.0f, 0.0f, 0.0f, 1.0f });
	// フェードが明ける処理
	TransitionProcess::Fade_Out_Init();

	// スコアの処理
	score_ = Score::GetInstance()->GetScore();
	Score::Initialize();
	Score::GetInstance()->GetBG_Sprite0()->SetTexHandle(scoreTexHD_);
	Score::GetInstance()->GetBG_Sprite1()->SetTexHandle(scoreTexHD_);
	Score::GetInstance()->GetBG_Sprite2()->SetTexHandle(scoreTexHD_);
	Score::GetInstance()->GetBG_Sprite3()->SetTexHandle(scoreTexHD_);

	count_ = KillCounter::GetInstance()->GetCount();
	KillCounter::Initialize();
	KillCounter::GetInstance()->GetBG_Sprite0()->SetTexHandle(scoreTexHD_);
	KillCounter::GetInstance()->GetBG_Sprite1()->SetTexHandle(scoreTexHD_);
}



// 更新処理
void ResultScene::Update(GameManager* scene) {

	Score::UpdateResult(score_);
	KillCounter::Update(count_);

	// シーン遷移
	XINPUT_STATE joyState{};
	Input::NoneJoyState(joyState);
	if (Input::GetInstance()->GetJoystickState(joyState))
	{
		//発射処理
		if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_A)
		{
			TransitionProcess::Fade_In_Init();
		}

	}
	if (Input::GetInstance()->PushKeyPressed(DIK_SPACE))
	{
		TransitionProcess::Fade_In_Init();
	}
	// フェードの処理が終わったらシーン遷移
	if (TransitionProcess::Fade_In()) {
		scene->ChangeState(new TitleScene);
		return;
	}

	// フェードが明ける処理
	TransitionProcess::Fade_In();
	TransitionProcess::Fade_Out();

	for (int Index = 0; Index < 3; Index++) {
		result_.worldTransform[Index].UpdateMatrix();
	}

	float time = float(clock() / 1000.0);
	result_.sprite[1]->SetColor(CalculateColorGradient(time));
}

void ResultScene::Back2dSpriteDraw()
{
}

void ResultScene::Object3dDraw()
{
}

void ResultScene::Flont2dSpriteDraw()
{
	for (int Index = 0; Index < 3; Index++) {
		result_.sprite[Index]->Draw(result_.worldTransform[Index]);
	}
	Score::DrawResult();
	KillCounter::Draw();
	TransitionProcess::Draw();
}


// グラデーションする処理
Vector4 ResultScene::CalculateColorGradient(float time) {
	Vector4 color{};
	color.x = 0.5f + 0.5f * std::sin(0.7f * time);
	color.y = 0.5f + 0.5f * std::sin(0.7f * time + 2.0f);
	color.z = 0.5f + 0.5f * std::sin(0.7f * time + 4.0f);
	color.w = 1.0f;
	return color;
}