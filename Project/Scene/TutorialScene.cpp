#include "TutorialScene.h"



// 初期化処理
void TutorialScene::Initialize() {

	// テクスチャの読み込み
	tutorial_TexHD_ = TextureManager::LoadTexture("Resources/BackGround/Tutorial_BagGround.png");
	uint32_t useFade_BG = TextureManager::LoadTexture("Resources/BackGround/BackGround.png");

	// 座標
	tutorial_Position_ = { 0.0f, 0.0f };
	tutorial_WorldTransform_.Initialize();
	tutorial_WorldTransform_.translate = { tutorial_Position_.x, tutorial_Position_.y, 0.0f };

	// スプライト
	tutorial_Sprite_ = make_unique<Sprite>();
	tutorial_Sprite_->Initialize(new SpriteBoxState, tutorial_Position_, { 1280,720 });
	tutorial_Sprite_->SetTexHandle(tutorial_TexHD_);
	tutorial_Sprite_->SetColor(tutorial_TexColor_);

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
void TutorialScene::Update(GameManager* scene) {

	// フェードが明ける処理
	TransitionProcess::Fade_Out();
	if (TransitionProcess::Fade_Out()) {

		// シーン遷移
		if (Input::GetInstance()->PushKeyPressed(DIK_9))
		{
			scene->ChangeState(new GameScene);
			return;
		}

		// スペースでフェードスタート
		if (Input::GetInstance()->PushKeyPressed(DIK_SPACE)) {
			TransitionProcess::Fade_In_Init();
		}
		TransitionProcess::Fade_In();
		// フェードの処理が終わったらシーン遷移
		if (TransitionProcess::Fade_In()) {
			scene->ChangeState(new GameScene);
			return;
		}
	}


#ifdef _DEBUG

	ImGui::Begin("TutorialScene");
	ImGui::Text("space key = ChangeScene() -> GameScene");
	ImGui::End();

#endif
}



// 描画処理
void TutorialScene::Draw() {

	tutorial_Sprite_->Draw(tutorial_WorldTransform_);
	TransitionProcess::Draw();
}