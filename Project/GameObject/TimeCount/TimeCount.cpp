#include "TimeCount.h"



// 初期化処理
void TimeCount::Initialize() {

	// テクスチャの読み込み
	numTextureHD_[0] = TextureManager::LoadTexture("Resources/Number/0.png");
	numTextureHD_[1] = TextureManager::LoadTexture("Resources/Number/1.png");
	numTextureHD_[2] = TextureManager::LoadTexture("Resources/Number/2.png");
	numTextureHD_[3] = TextureManager::LoadTexture("Resources/Number/3.png");
	numTextureHD_[4] = TextureManager::LoadTexture("Resources/Number/4.png");
	numTextureHD_[5] = TextureManager::LoadTexture("Resources/Number/5.png");
	numTextureHD_[6] = TextureManager::LoadTexture("Resources/Number/6.png");
	numTextureHD_[7] = TextureManager::LoadTexture("Resources/Number/7.png");
	numTextureHD_[8] = TextureManager::LoadTexture("Resources/Number/8.png");
	numTextureHD_[9] = TextureManager::LoadTexture("Resources/Number/9.png");

	for (int index = 0; index < 3; index++) {
		sprite_[index] = make_unique<Sprite>();
		position_[index] = { 540.0f + (50.0f * index), 10.0f };
		sprite_[index]->Initialize(new SpriteBoxState, position_[index], { 100.0f, 100.0f });
		sprite_[index]->SetColor(textureColor_);
		sprite_[index]->SetTexHandle(numTextureHD_[0]);
	}

	// ワールドトランスフォーム
	for (int index = 0; index < 3; index++) {
		worldTransform_[index].Initialize();
		worldTransform_[index].translate = { position_[index].x, position_[index].y, 0.0f };
	}
	
	// 制限時間を設定する
	nowLimitTime_ = kSetLimitTime_;
	frame_ = 0;
}



// 更新処理
void TimeCount::Update() {

	// 制限時間の減算処理
	SubtructTimer();

	// 制限時間の加算処理
	AddTimeCount();

	// 制限時間の各位の値を求める
	CalcTimerPlace(nowLimitTime_);

	// 各位に合ったテクスチャを設定する
	SetNumberTexture();


#ifdef _DEBUG

	ImGui::Begin("TimeCount");
	ImGui::Text("frame_ = %d", frame_);
	ImGui::Text("nowTimer = %d", nowLimitTime_);
	ImGui::Text("onehundPlace = %d", eachTime_[0]);
	ImGui::Text("    tenPlace = %d", eachTime_[1]);
	ImGui::Text("    onePlace = %d", eachTime_[2]);
	ImGui::DragFloat3("trans[0]", &worldTransform_[0].translate.x, 1.0f);
	ImGui::DragFloat3("trans[1]", &worldTransform_[1].translate.x, 1.0f);
	ImGui::DragFloat3("trans[2]", &worldTransform_[2].translate.x, 1.0f);
	ImGui::End();

#endif // DEBUG
}



// タイマーを減らす
void TimeCount::SubtructTimer() {

	// フレームを増やす
	frame_++;

	// 60フレーム
	if (frame_ >= 60) {

		// タイマーに1秒減らす
		nowLimitTime_ = nowLimitTime_ - 1;
		// フレームを0に戻す
		frame_ = 0;
	}
}



// 時間の追加処理
void TimeCount::AddTimeCount() {

	// キーでタイム変化
	// 1キー = +10s
	// 2キー = +20s
	// 3キー = +30s
	// 上下キー = +1s
	if (Input::GetInstance()->PushKeyPressed(DIK_1)) {
		nowLimitTime_ = nowLimitTime_ + 10;
	}
	else if (Input::GetInstance()->PushKeyPressed(DIK_2)) {
		nowLimitTime_ = nowLimitTime_ + 20;
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
	sprite_[0]->SetTexHandle(numTextureHD_[eachTime_[0]]);
	sprite_[1]->SetTexHandle(numTextureHD_[eachTime_[1]]);
	sprite_[2]->SetTexHandle(numTextureHD_[eachTime_[2]]);
}



// 描画処理
void TimeCount::Draw() {

	for (int index = 0; index < 3; index++) {
		sprite_[index]->Draw(worldTransform_[index]);
	}
}


