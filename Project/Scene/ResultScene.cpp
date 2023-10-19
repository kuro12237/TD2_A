#include "ResultScene.h"



// 初期化処理
void ResultScene::Initialize() {

	// テクスチャの読み込み
	result_TexHD_ = TextureManager::LoadTexture("Resources/BackGround/Result_BagGround.png");
	uint32_t useFade_BG = TextureManager::LoadTexture("Resources/BackGround/BackGround.png");

	// 座標
	result_Position_ = { 0.0f, 0.0f };
	result_WorldTransform_.Initialize();
	result_WorldTransform_.translate = { result_Position_.x, result_Position_.y, 0.0f };

	// スプライト
	result_Sprite_ = make_unique<Sprite>();
	result_Sprite_->Initialize(new SpriteBoxState, result_Position_, { 1280, 720 });
	result_Sprite_->SetTexHandle(result_TexHD_);
	result_Sprite_->SetColor(result_TexColor_);

	// フェードの処理
	TransitionProcess::Initialize();
	// フェードに使う画像の設定
	TransitionProcess::GetInstance()->GetBG_Sprite()->SetTexHandle(useFade_BG);
	// 色を黒くしておく
	TransitionProcess::GetInstance()->GetBG_Sprite()->SetColor({ 0.0f, 0.0f, 0.0f, 1.0f });
	// フェードが明ける処理
	TransitionProcess::Fade_Out_Init();
}



// 更新処理
void ResultScene::Update(GameManager* scene) {

	// シーン遷移
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

#ifdef _DEBUG

	ImGui::Begin("ResultScene");
	ImGui::Text("9 key = ChangeScene() -> GameScene");
	ImGui::End();

#endif
}

void ResultScene::Back2dSpriteDraw()
{
}

void ResultScene::Object3dDraw()
{
}

void ResultScene::Flont2dSpriteDraw()
{
	result_Sprite_->Draw(result_WorldTransform_);
	TransitionProcess::Draw();
}


