#include "StartCount.h"




void StartCount::Initialize() {

	// テクスチャの読み込み
	startCount_.TexHD = TextureManager::LoadTexture("Resources/Texture/UI/Number.png");


	// 画像の上下左右の座標を求める
	int column = 0;
	int line = 0;
	for (int Index = 0; Index < 3; Index++) {

		// 上下左右の値を求める
		startCount_.src[Index].RightTop = { 0.2f + (0.2f * column), 0.0f + (0.2f * line) };
		startCount_.src[Index].RightBottom = { 0.2f + (0.2f * column), 0.2f + (0.2f * line) };
		startCount_.src[Index].LeftTop = { 0.0f + (0.2f * column), 0.0f + (0.2f * line) };
		startCount_.src[Index].LeftBottom = { 0.0f + (0.2f * column), 0.2f + (0.2f * line) };

		// 列を足す
		column = column + 1;
	}



	startCount_.worldTransform.Initialize();
	startCount_.position = { 0.0f, 0.0f };

	startCount_.sprite = make_unique<Sprite>();
	startCount_.sprite->SetSrc(
		startCount_.src[0].RightTop,
		startCount_.src[0].RightBottom,
		startCount_.src[0].LeftTop,
		startCount_.src[0].LeftBottom);
	startCount_.sprite->Initialize(new SpriteBoxState, startCount_.position, { 640.0f, 640.0f });
	startCount_.sprite->SetTexHandle(startCount_.TexHD);
	startCount_.sprite->SetColor(texColor);


	eachCount_ = 3;
	frame_ = 60;
	isStartCount_ = true;
}



void StartCount::Update() {

	if (isStartCount_) {

		// 制限時間の減算処理
		SubtructTimer();

		// 制限時間の加算処理
		SubtructTimer();

		// 各位に合ったテクスチャを設定する
		SetSrc();
	}

	startCount_.worldTransform.UpdateMatrix();


#ifdef _DEBUG

	ImGui::Begin("StartCount");
	ImGui::Text("Count = %d", count_);
	ImGui::DragFloat3("transform", &startCount_.worldTransform.translate.x, 0.01f);
	ImGui::End();

#endif // _DEBUG

}



void StartCount::Draw() {

	if (isStartCount_) {

		startCount_.sprite->Draw(startCount_.worldTransform);
	}
}



void StartCount::SubtructTimer() {

	if (isStartCount_) {

		frame_--;

		if (frame_ <= 0) {

			count_ = count_ - 1;
			frame_ = 60;
		}


		if (count_ <= 0) {

			frame_ = 0;
			count_ = 0;
			isStartCount_ = false;
		}
	}

}



void StartCount::SetSrc() {

	startCount_.sprite->SetSrc(
		startCount_.src[count_].RightTop,
		startCount_.src[count_].RightBottom,
		startCount_.src[count_].LeftTop,
		startCount_.src[count_].LeftBottom);
}