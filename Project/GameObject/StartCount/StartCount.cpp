#include "StartCount.h"




void StartCount::Initialize() {

	// テクスチャの読み込み
	startCount_.TexHD = 0;


	startCount_.worldTransform.Initialize();
	startCount_.position = { 500.0f, 400.0f };

	startCount_.sprite = make_unique<Sprite>();
	startCount_.sprite->SetSrc(
		startCount_.src[0].RightTop,
		startCount_.src[0].RightBottom,
		startCount_.src[0].LeftTop,
		startCount_.src[0].LeftBottom);
	startCount_.sprite->Initialize(new SpriteBoxState, startCount_.position, { 640.0f, 640.0f });
	startCount_.sprite->SetTexHandle(startCount_.TexHD);
	startCount_.sprite->SetColor(texColor);


	eachCount_ = 0;
	frame_ = 0;

}



void StartCount::Update() {

	if (isStartCount_) {

		// 制限時間の減算処理
		SubtructTimer();

		// 制限時間の加算処理
		SubtructTimer();

		// 制限時間の各位の値を求める
		CalcTimerPlace(count_);

		// 各位に合ったテクスチャを設定する
		SetSrc();
	}

}



void StartCount::Draw() {

}



void StartCount::SubtructTimer() {

	if (isStartCount_) {

		frame_++;

		if (frame_ >= 60) {

			count_ = count_ - 1;
			frame_ = 0;
		}


		if (count_ <= 0) {

			frame_ = 0;
			count_ = 0;
			isStartCount_ = false;
		}
	}

}



void StartCount::CalcTimerPlace(uint32_t nowTimer) {

	eachCount_ = count_;
}



void StartCount::SetSrc() {

	startCount_.sprite->SetSrc(
		startCount_.src[count_].RightTop,
		startCount_.src[count_].RightBottom,
		startCount_.src[count_].LeftTop,
		startCount_.src[count_].LeftBottom);
}