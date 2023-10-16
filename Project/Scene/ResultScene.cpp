#include "ResultScene.h"



// 初期化処理
void ResultScene::Initialize() {

	// テクスチャの読み込み
	result_TexHD_ = TextureManager::LoadTexture("Resources/BackGround/Result_BagGround.png");

	// 座標
	result_Position_ = { 0.0f, 0.0f };
	result_WorldTransform_.Initialize();
	result_WorldTransform_.translate = { result_Position_.x, result_Position_.y, 0.0f };

	// スプライト
	result_Sprite_ = make_unique<Sprite>();
	result_Sprite_->Initialize(new SpriteBoxState, result_Position_, { 1280, 720 });
	result_Sprite_->SetTexHandle(result_TexHD_);
	result_Sprite_->SetColor(result_TexColor_);
}



// 更新処理
void ResultScene::Update(GameManager* scene) {

	// シーン遷移
	if (Input::GetInstance()->PushKeyPressed(DIK_9))
	{
		scene->ChangeState(new DebugScene);
		return;
	}


#ifdef _DEBUG

	ImGui::Begin("ResultScene");
	ImGui::Text("9 key = ChangeScene() -> DebugScene");
	ImGui::End();

#endif
}



// 描画処理
void ResultScene::Draw() {

	result_Sprite_->Draw(result_WorldTransform_);
}