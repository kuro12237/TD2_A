﻿#include "TimeCount.h"



// 初期化処理
void TimeCount::Initialize() {

#pragma region TimeCount

	// テクスチャの読み込み
	numberTexHD_ = TextureManager::LoadTexture("Resources/Texture/UI/Number.png");

	// 初期化処理
	// 画像の上下左右の座標を求める
	int column = 0;
	int line = 0;
	for (int Index = 0; Index < 10; Index++) {
		
		// 上下左右の値を求める
		src_[Index].RightTop    = { 0.2f + (0.2f * column), 0.0f + (0.2f *line) };
		src_[Index].RightBottom = { 0.2f + (0.2f * column), 0.2f + (0.2f *line) };
		src_[Index].LeftTop     = { 0.0f + (0.2f * column), 0.0f + (0.2f *line) };
		src_[Index].LeftBottom  = { 0.0f + (0.2f * column), 0.2f + (0.2f *line) };

		// 列を足す
		column = column + 1;

		// ５回ループしたら
		if (Index == 4) {
			// 列を０にして行に１足す
			column = 0;
			line++;
		}
	}

	for (int Index = 0; Index < 3; Index++) {

		// 座標
		timeCountWorldTransform_->Initialize();
		timeCountPosition_[Index] = { 480.0f + (95.0f * Index), 20.0f };
		// スプライト
		timeCountSprite_[Index] = make_unique<Sprite>();
		timeCountSprite_[Index]->SetSrc(src_[0].RightTop, src_[0].RightBottom, src_[0].LeftTop, src_[0].LeftBottom);
		timeCountSprite_[Index]->Initialize(new SpriteBoxState, timeCountPosition_[Index], { 128.0f, 128.0f });
		timeCountSprite_[Index]->SetTexHandle(numberTexHD_);
		timeCountSprite_[Index]->SetColor(textureColor_);
	}
	// 制限時間を設定する
	nowLimitTime_ = kSetLimitTime_;
	frame_ = 0;

#pragma endregion


#pragma region TimeUp_Ui

	// テクスチャの読み込み
	timeUpUITextureHD_ = TextureManager::LoadTexture("Resources/Texture/UI/TimeUp.png");

	// 初期化
	timeUpUISprite_ = make_unique<Sprite>();
	timeUpUIPosition_ = { 200.0f, 230.0f }; // <-あとで座標直す
	timeUpUISprite_->Initialize(new SpriteBoxState, timeUpUIPosition_, { 900.0f, 300.0f });
	timeUpUISprite_->SetColor(textureColor_);
	timeUpUISprite_->SetTexHandle(timeUpUITextureHD_);
	// ワールドトランスフォーム
	timeUpUIWorldTransform_.Initialize();
	timeUpUIWorldTransform_.scale = { 2.0f, 3.0f, 1.0f };

#pragma endregion
}



// 更新処理
void TimeCount::Update() {

	if (Input::GetInstance()->PushKeyPressed(DIK_0))
	{
		//Audio::AudioPlayWave(secondHandSound_);
	}


	if (isDebug_ == false) {

		// 制限時間の減算処理
		SubtructTimer();

		// 制限時間の加算処理
		AddTimeCount();

		// 制限時間の各位の値を求める
		CalcTimerPlace(nowLimitTime_);

		// 各位に合ったテクスチャを設定する
		SetSrc();

		// 制限時間をリセットする
		ReSetTimer();
	}

	for (int Index = 0; Index < 3; Index++) {
		timeCountWorldTransform_[Index].UpdateMatrix();
	}


#ifdef _DEBUG


	ImGui::Begin("TimeCount");
	ImGui::Text("frame_ = %d", frame_);
	ImGui::Text("nowTimer = %d", nowLimitTime_);
	ImGui::Text("100 = %d", eachTime_[0]);
	ImGui::Text(" 10 = %d", eachTime_[1]);
	ImGui::Text("  1 = %d", eachTime_[2]);
	ImGui::Text("isTimeUp_ = %d", isTimeUp_);
	ImGui::Text("R-key : ResetTimer");
	ImGui::Checkbox("isDebugMode", &isDebug_);
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
void TimeCount::SetSrc() {

	// 各位の値にあったテクスチャを設定する
	timeCountSprite_[0]->SetSrc(src_[eachTime_[0]].RightTop, src_[eachTime_[0]].RightBottom, src_[eachTime_[0]].LeftTop, src_[eachTime_[0]].LeftBottom);
	timeCountSprite_[1]->SetSrc(src_[eachTime_[1]].RightTop, src_[eachTime_[1]].RightBottom, src_[eachTime_[1]].LeftTop, src_[eachTime_[1]].LeftBottom);
	timeCountSprite_[2]->SetSrc(src_[eachTime_[2]].RightTop, src_[eachTime_[2]].RightBottom, src_[eachTime_[2]].LeftTop, src_[eachTime_[2]].LeftBottom);
}



// 描画処理
void TimeCount::Draw() {

	for (int Index = 0; Index < 3; Index++) {
		timeCountSprite_[Index]->Draw(timeCountWorldTransform_[Index]);
	}
	if (isTimeUp_) {
		timeUpUISprite_->Draw(timeUpUIWorldTransform_);
	}
}


