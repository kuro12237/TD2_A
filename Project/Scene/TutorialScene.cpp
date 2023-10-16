#include "TutorialScene.h"



// 初期化処理
void TutorialScene::Initialize() {

	// テクスチャの読み込み
	tutorial_TexHD_ = TextureManager::LoadTexture("Resources/BackGround/Tutorial_BagGround.png");

	// 座標
	tutorial_Position_ = { 0.0f, 0.0f };
	tutorial_WorldTransform_.Initialize();
	tutorial_WorldTransform_.translate = { tutorial_Position_.x, tutorial_Position_.y, 0.0f };

	// スプライト
	tutorial_Sprite_ = make_unique<Sprite>();
	tutorial_Sprite_->Initialize(new SpriteBoxState, tutorial_Position_, { 1280,720 });
	tutorial_Sprite_->SetTexHandle(tutorial_TexHD_);
	tutorial_Sprite_->SetColor(tutorial_TexColor_);
}



// 更新処理
void TutorialScene::Update(GameManager* scene) {

	// シーン遷移
	if (Input::GetInstance()->PushKeyPressed(DIK_9))
	{
		scene->ChangeState(new GameScene);
		return;
	}


#ifdef _DEBUG

	ImGui::Begin("TutorialScene");
	ImGui::Text("9 key = ChangeScene() -> GameScene");
	ImGui::End();

#endif
}



// 描画処理
void TutorialScene::Draw() {

	tutorial_Sprite_->Draw(tutorial_WorldTransform_);
}