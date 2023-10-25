#include "TimeCount.h"



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

	for (int Index = 0; Index < 2; Index++) {

		// 座標
		timeCountWorldTransform_->Initialize();
		timeCountPosition_[Index] = { 545.0f + (85.0f * Index), 0.0f };
		// スプライト
		timeCountSprite_[Index] = make_unique<Sprite>();
		timeCountSprite_[Index]->SetSrc(src_[0].RightTop, src_[0].RightBottom, src_[0].LeftTop, src_[0].LeftBottom);
		timeCountSprite_[Index]->Initialize(new SpriteBoxState, timeCountPosition_[Index], { 104.0f, 104.0f });
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
	timeUpUIPosition_ = { 0.0f, 0.0f }; // <-あとで座標直す
	timeUpUISprite_->Initialize(new SpriteBoxState, timeUpUIPosition_, { 1280.0f, 720.0f });
	timeUpUISprite_->SetColor(textureColor_);
	timeUpUISprite_->SetTexHandle(timeUpUITextureHD_);
	// ワールドトランスフォーム
	timeUpUIWorldTransform_.Initialize();
	timeUpUIWorldTransform_.scale = { 1.0f, 1.0f, 1.0f };

#pragma endregion



#pragma region TimerUIBackGround

	// テクスチャの読み込み
	timerUIBGTexHD_ = TextureManager::LoadTexture("Resources/Texture/BackGround/TimerBg.png");

	// 初期化
	timerUIBGSprite_ = make_unique<Sprite>();
	timerUIBGPosition_ = { 0.0f, 0.0f };
	timerUIBGSprite_->Initialize(new SpriteBoxState, timerUIBGPosition_, { 1280.0f, 720.0f });
	timerUIBGSprite_->SetTexHandle(timerUIBGTexHD_);
	timerUIBGSprite_->SetColor(textureColor_);
	
	// ワールドトランスフォーム
	timerUIBGWorldTransform_.Initialize();

	isTimeUp_ = 0;

#pragma endregion

#pragma region A

	ATexHD_ = TextureManager::LoadTexture("Resources/Texture/UI/A.png");

	// 初期化
	ASprite_ = make_unique<Sprite>();
	APosition_ = { 430.0f, 350.0f };
	ASprite_->Initialize(new SpriteBoxState, APosition_, { 400.0f, 400.0f });
	ASprite_->SetTexHandle(ATexHD_);
	ASprite_->SetColor(textureColor_);

	// ワールドトランスフォーム
	ATransform_.Initialize();

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

	for (int Index = 0; Index < 2; Index++) {
		timeCountWorldTransform_[Index].UpdateMatrix();
	}
	timerUIBGWorldTransform_.UpdateMatrix();
	timeUpUIWorldTransform_.UpdateMatrix();
	ATransform_.UpdateMatrix();


#ifdef _DEBUG


	ImGui::Begin("TimeCount");
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
	eachTime_[0] = (nowTimer % 100) / 10;
	// 10の位
	eachTime_[1] = (nowTimer % 10) / 1;
}



// 各位に合ったテクスチャを設定する
void TimeCount::SetSrc() {

	// 各位の値にあったテクスチャを設定する
	timeCountSprite_[0]->SetSrc(src_[eachTime_[0]].RightTop, src_[eachTime_[0]].RightBottom, src_[eachTime_[0]].LeftTop, src_[eachTime_[0]].LeftBottom);
	timeCountSprite_[1]->SetSrc(src_[eachTime_[1]].RightTop, src_[eachTime_[1]].RightBottom, src_[eachTime_[1]].LeftTop, src_[eachTime_[1]].LeftBottom);
}



// 描画処理
void TimeCount::Draw() {

	timerUIBGSprite_->Draw(timerUIBGWorldTransform_);

	for (int Index = 0; Index < 2; Index++) {
		timeCountSprite_[Index]->Draw(timeCountWorldTransform_[Index]);
	}
	if (isTimeUp_) {
		timeUpUISprite_->Draw(timeUpUIWorldTransform_);
		ASprite_->Draw(timerUIBGWorldTransform_);
	}
}


