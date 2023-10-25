#include "TitleScene.h"



// 初期化処理
void TitleScene::Initialize() {

	// テクスチャの読み込み
	title_TexHD_ = TextureManager::LoadTexture("Resources/Texture/BackGround/Title_BagGround.png");
	uint32_t useFade_BG = TextureManager::LoadTexture("Resources/Texture/BackGround/BackGround.png");


	// 座標
	title_Position_ = { 0.0f, 0.0f };
	title_WorldTransform_.Initialize();
	title_WorldTransform_.translate = { title_Position_.x, title_Position_.y, 0.0f };

	// スプライト
	title_Sprite_ = make_unique<Sprite>();
	title_Sprite_->Initialize(new SpriteBoxState, title_Position_, { 1280,720 });
	title_Sprite_->SetTexHandle(title_TexHD_);
	title_Sprite_->SetColor(title_TexColor_);

	// フェードの処理
	TransitionProcess::Initialize();
	// フェードに使う画像の設定
	TransitionProcess::GetInstance()->GetBG_Sprite()->SetTexHandle(useFade_BG);
	// 色を黒くしておく
	TransitionProcess::GetInstance()->GetBG_Sprite()->SetColor({ 0.0f, 0.0f, 0.0f, 1.0f });
	// フェードが明ける処理
	TransitionProcess::Fade_Out_Init();

	viewProjection_.Initialize({ 0.2f,-0.6f,0.0f }, { 11.0f,5.0f,-15 });
	
	shamWall_ = make_unique<ShamWall>();
	shamWall_->Initialize();

	// 天球
	skydome_ = make_unique<Skydome>();
	skydome_->Initialize();

	// 床
	mapGround_ = make_unique<MapGround>();
	mapGround_->Initialize();

}

// 更新処理
void TitleScene::Update(GameManager* scene) {

	shamWall_->Update();

	// 天球
	skydome_->Update();

	// 床
	mapGround_->Updatea();


	viewProjection_.UpdateMatrix();
	// シーン遷移
	if (Input::GetInstance()->PushKeyPressed(DIK_9))
	{
		scene->ChangeState(new GameScene);
		return;
	}

	// フェードが明ける処理
	TransitionProcess::Fade_Out();
	if (TransitionProcess::Fade_Out()) {

		// スペースでフェードスタート
		if (Input::GetInstance()->PushKeyPressed(DIK_SPACE)) {
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
	TransitionProcess::Draw();
}