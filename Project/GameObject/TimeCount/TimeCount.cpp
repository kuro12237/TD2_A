#include "TimeCount.h"



// 初期化処理
void TimeCount::Initialize() {

#pragma region TimeCount

	// テクスチャの読み込み
	numTextureHD_[0] = TextureManager::LoadTexture("Resources/TimeCount/0.png");
	numTextureHD_[1] = TextureManager::LoadTexture("Resources/TimeCount/1.png");
	numTextureHD_[2] = TextureManager::LoadTexture("Resources/TimeCount/2.png");
	numTextureHD_[3] = TextureManager::LoadTexture("Resources/TimeCount/3.png");
	numTextureHD_[4] = TextureManager::LoadTexture("Resources/TimeCount/4.png");
	numTextureHD_[5] = TextureManager::LoadTexture("Resources/TimeCount/5.png");
	numTextureHD_[6] = TextureManager::LoadTexture("Resources/TimeCount/6.png");
	numTextureHD_[7] = TextureManager::LoadTexture("Resources/TimeCount/7.png");
	numTextureHD_[8] = TextureManager::LoadTexture("Resources/TimeCount/8.png");
	numTextureHD_[9] = TextureManager::LoadTexture("Resources/TimeCount/9.png");

	// 初期化
	for (int index = 0; index < 3; index++) {
		// スプライト
		timerSprite_[index] = make_unique<Sprite>();
		timerPosition_[index] = { 540.0f + (50.0f * index), 10.0f };
		timerSprite_[index]->Initialize(new SpriteBoxState, timerPosition_[index], { 100.0f, 100.0f });
		timerSprite_[index]->SetColor(textureColor_);
		timerSprite_[index]->SetTexHandle(numTextureHD_[0]);
		// ワールドトランスフォーム
		timerWorldTransform_[index].Initialize();
		timerWorldTransform_[index].translate = { timerPosition_[index].x, timerPosition_[index].y, 0.0f };
	}
	// 制限時間を設定する
	nowLimitTime_ = kSetLimitTime_;
	frame_ = 0;

#pragma endregion


#pragma region TimeUp_Ui

	// テクスチャの読み込み
	timeUpUITextureHD_ = TextureManager::LoadTexture("Resources/TimeCount/TimeUp.png");

	// 初期化
	timeUpUISprite_ = make_unique<Sprite>();
	timeUpUIPosition_ = { 200.0f, 230.0f };
	timeUpUISprite_->Initialize(new SpriteBoxState, timeUpUIPosition_, { 900.0f, 300.0f });
	timeUpUISprite_->SetColor(textureColor_);
	timeUpUISprite_->SetTexHandle(timeUpUITextureHD_);
	// ワールドトランスフォーム
	timeUpUIWorldTransform_.Initialize();
	timeUpUIWorldTransform_.translate = { timeUpUIPosition_.x, timeUpUIPosition_.y, 0.0f };

#pragma endregion
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

	// 制限時間をリセットする
	ReSetTimer();


#ifdef _DEBUG

	ImGui::Begin("TimeCount");
	ImGui::Text("frame_ = %d", frame_);
	ImGui::Text("nowTimer = %d", nowLimitTime_);
	ImGui::Text("100 = %d", eachTime_[0]);
	ImGui::Text(" 10 = %d", eachTime_[1]);
	ImGui::Text("  1 = %d", eachTime_[2]);
	ImGui::Text("isTimeUp_ = %d", isTimeUp_);
	ImGui::Text("R-key : ResetTimer");
	ImGui::End();

#endif // DEBUG
}



// タイマーを減らす
void TimeCount::SubtructTimer() {

	// 制限時間が残っているとき
	if (isTimeUp_ == false) {

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

	// 制限時間が0になったら
	if (nowLimitTime_ <= 0) {

		// 0で固定
		frame_ = 0;
		nowLimitTime_ = 0;
		// 制限時間切れのフラグを立てる
		isTimeUp_ = true;
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



// 制限時間をリセットする
void TimeCount::ReSetTimer() {

	// 時間切れのフラグが立ったら
	if (isTimeUp_) {

		// Rキーでリセット
		if (Input::GetInstance()->PushKey(DIK_R)) {

			// 制限時間を再設定する
			nowLimitTime_ = kSetLimitTime_;
			frame_ = 0;

			// フラグを折る
			isTimeUp_ = false;
		}
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
	timerSprite_[0]->SetTexHandle(numTextureHD_[eachTime_[0]]);
	timerSprite_[1]->SetTexHandle(numTextureHD_[eachTime_[1]]);
	timerSprite_[2]->SetTexHandle(numTextureHD_[eachTime_[2]]);
}



// 描画処理
void TimeCount::Draw() {

	for (int index = 0; index < 3; index++) {
		timerSprite_[index]->Draw(timerWorldTransform_[index]);
	}
	if (isTimeUp_) {
		timeUpUISprite_->Draw(timeUpUIWorldTransform_);
	}
}


