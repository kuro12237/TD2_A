#include "TimeCount.h"



// 初期化処理
void TimeCount::Initialize() {

	// テクスチャの読み込み
	numTextureHD_[0]  = TextureManager::LoadTexture("Resources/uvChecker.png");
	numTextureHD_[1]  = 0; //TextureManager::LoadTexture("Resources/Number/1.png");
	numTextureHD_[2]  = 0; //TextureManager::LoadTexture("Resources/Number/2.png");
	numTextureHD_[3]  = 0; //TextureManager::LoadTexture("Resources/Number/3.png");
	numTextureHD_[4]  = 0; //TextureManager::LoadTexture("Resources/Number/4.png");
	numTextureHD_[5]  = 0; //TextureManager::LoadTexture("Resources/Number/5.png");
	numTextureHD_[6]  = 0; //TextureManager::LoadTexture("Resources/Number/6.png");
	numTextureHD_[7]  = 0; //TextureManager::LoadTexture("Resources/Number/7.png");
	numTextureHD_[8]  = 0; //TextureManager::LoadTexture("Resources/Number/8.png");
	numTextureHD_[9]  = 0; //TextureManager::LoadTexture("Resources/Number/9.png");


	// スプライト
	for (int index = 0; index < 3; index++) {
		sprite_[index] = make_unique<Sprite>();
		position_[index] = { 10.0f, 10.0f };
		sprite_[index]->Initialize(new SpriteBoxState, position_[index], { 1.0f, 1.0f });
		sprite_[index]->SetColor(textureColor_);
		//sprite_[index]->SetTexHandle(numTextureHD_[0]);
	}

	// ワールドトランスフォーム
	for (int index = 0; index < 3; index++) {
		worldTransform_[index].translate = { position_[index].x, position_[index].y , 0.0f };
		worldTransform_[index].Initialize();
	}
	
	// 制限時間を設定する
	nowLimitTime_ = kSetLimitTime_;
}



// 更新処理
void TimeCount::Update() {

	// 制限時間の各位の値を求める
	CalcTimerPlace(nowLimitTime_);

	// 各位に合ったテクスチャを設定する
	SetNumberTexture();

	// 制限時間の加減算処理
	AddTimeCount();


	/*ImGui::Begin("TimeCount");
	ImGui::Text("nowTimer = %d", nowLimitTime_);
	ImGui::Text("onehundPlace = %d", eachTime_[0]);
	ImGui::Text("    tenPlace = %d", eachTime_[1]);
	ImGui::Text("    oneplace = %d", eachTime_[2]);
	ImGui::Text("sprite_[0].texturehandle = %d", sprite_[0].get()->GetTexHandle());
	ImGui::Text("sprite_[1].texturehandle = %d", sprite_[1].get()->GetTexHandle());
	ImGui::Text("sprite_[2].texturehandle = %d", sprite_[2].get()->GetTexHandle());
	ImGui::End();*/
}



// 時間の追加処理
void TimeCount::AddTimeCount() {

	// キーでタイム変化
	if (Input::GetInstance()->PushKeyPressed(DIK_1)) {
		nowLimitTime_ = nowLimitTime_ + 10;
	}
	else if (Input::GetInstance()->PushKeyPressed(DIK_2)) {
		nowLimitTime_ = nowLimitTime_ + 10;
	}
	else if (Input::GetInstance()->PushKeyPressed(DIK_3)) {
		nowLimitTime_ = nowLimitTime_ + 30;
	}

	if (Input::GetInstance()->PushKey(DIK_UP)) {
		nowLimitTime_ += 1;
	}
	else if (Input::GetInstance()->PushKey(DIK_DOWN)) {
		nowLimitTime_ -= 1;
	}
}



// 制限時間の各位を求める
void TimeCount::CalcTimerPlace(uint32_t nowTimer) {

	// 100の位
	eachTime_[0] = (nowTimer % 1000) / 100;
	// 10の位
	eachTime_[1] = (nowTimer % 100) / 10;
	// 1の位
	eachTime_[2] = (nowTimer % 10) / 1;
}



// 各位に合ったテクスチャを設定する
void TimeCount::SetNumberTexture() {

	// 各位の値にあったテクスチャを設定する
	if (Input::GetInstance()->PushKeyPressed(DIK_SPACE)) {
		sprite_[0]->SetTexHandle(numTextureHD_[eachTime_[9]]);
	}

}



// 描画処理
void TimeCount::Draw() {

	for (int index = 0; index < 2; index ++) {
		sprite_[index]->Draw(worldTransform_[index]);
	}
}
