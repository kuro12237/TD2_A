#include "TitleScene.h"



// 初期化処理
void TitleScene::Initialize() {

	// テクスチャの読み込み
	title_TexHD_ = TextureManager::LoadTexture("Resources/BackGround/Title_BagGround.png");

	// 座標
	title_Position_ = { 0.0f, 0.0f };
	title_WorldTransform_.Initialize();
	title_WorldTransform_.translate = { title_Position_.x, title_Position_.y, 0.0f };

	// スプライト
	title_Sprite_ = make_unique<Sprite>();
	title_Sprite_->Initialize(new SpriteBoxState, title_Position_, { 1280,720 });
	title_Sprite_->SetTexHandle(title_TexHD_);
	title_Sprite_->SetColor(title_TexColor_);


}



// 更新処理
void TitleScene::Update(GameManager* scene) {

	// シーン遷移
	if (Input::GetInstance()->PushKeyPressed(DIK_9))
	{
		scene->ChangeState(new TutorialScene);
		return;
	}

#ifdef _DEBUG

	ImGui::Begin("TitleScene");
	ImGui::Text("9 key = ChangeScene() -> TutorialScene");
	ImGui::End();

#endif
}



// 描画処理
void TitleScene::Draw() {

	title_Sprite_->Draw(title_WorldTransform_);
}