﻿#include "GameObject/Score/Score.h"



// Scoereクラスのインスタンス取得
Score* Score::GetInstance() {
	static Score instance;
	return &instance;
}


// 初期化処理
void Score::Initialize() {

	// テクスチャの読み込み
	uint32_t scoreTexHD_ = TextureManager::LoadTexture("Resources/Texture/UI/Score.png");
	uint32_t scoreBgTexHD = TextureManager::LoadTexture("Resources/Texture/BackGround/Game/ScoreBg.png");

	// 画像の上下左右の座標を決める
	int column = 0;
	int line = 0;
	SrcScore src[10]{};
	for (int Index = 0; Index < 10; Index++) {

		// 上下左右の値を求める
		src[Index].RightTop = { 0.2f + (0.2f * column), 0.0f + (0.2f * line) };
		src[Index].RightBottom = { 0.2f + (0.2f * column), 0.2f + (0.2f * line) };
		src[Index].LeftTop = { 0.0f + (0.2f * column), 0.0f + (0.2f * line) };
		src[Index].LeftBottom = { 0.0f + (0.2f * column), 0.2f + (0.2f * line) };

		// 列を足す
		column = column + 1;

		// ５回ループしたら
		if (Index == 4) {
			// 列を０にして行に１足す
			column = 0;
			line++;
		}

		Score::GetInstance()->src_[Index] = src[Index];
	}

	// スプライトの初期化処理
	for (int Index = 0; Index < 4; Index++) {

		// 座標
		Score::GetInstance()->scoreWorldTransform_[Index].Initialize();
		Score::GetInstance()->scoreUseResultWorldTransform_[Index].Initialize();

		Score::GetInstance()->scorePosition_[Index] = { 20.0f + (85.0f * Index), 550.0f };
		Score::GetInstance()->scoreUseResultPosition_[Index] = { 760.0f + (85.0f * Index), 115.0f };

		// スプライト
		Score::GetInstance()->scoreSprite_[Index] = make_unique<Sprite>();
		Score::GetInstance()->scoreSprite_[Index]->SetSrc(src[0].RightTop, src[0].RightBottom, src[0].LeftTop, src[0].LeftBottom);
		Score::GetInstance()->scoreSprite_[Index]->Initialize(new SpriteBoxState, Score::GetInstance()->scorePosition_[Index], { 128.0f, 128.0f });
		Score::GetInstance()->scoreSprite_[Index]->SetTexHandle(scoreTexHD_);
		Score::GetInstance()->scoreSprite_[Index]->SetColor(Score::GetInstance()->texColor_);

		Score::GetInstance()->scoreUseResultSprite_[Index] = make_unique<Sprite>();
		Score::GetInstance()->scoreUseResultSprite_[Index]->SetSrc(src[0].RightTop, src[0].RightBottom, src[0].LeftTop, src[0].LeftBottom);
		Score::GetInstance()->scoreUseResultSprite_[Index]->Initialize(new SpriteBoxState, Score::GetInstance()->scoreUseResultPosition_[Index], { 128.0f, 128.0f });
		Score::GetInstance()->scoreUseResultSprite_[Index]->SetTexHandle(scoreTexHD_);
		Score::GetInstance()->scoreUseResultSprite_[Index]->SetColor(Score::GetInstance()->texColor_);
	}
	for (int Index = 0; Index < 4; Index++) {

		// 座標
		Score::GetInstance()->scoreWorldTransform_[Index].Initialize();
		Score::GetInstance()->scoreUseResultWorldTransform_[Index].Initialize();

		Score::GetInstance()->scorePosition_[Index] = { 20.0f + (85.0f * Index), 550.0f };
		Score::GetInstance()->scoreUseResultPosition_[Index] = { 760.0f + (85.0f * Index), 115.0f };

		// スプライト
		Score::GetInstance()->scoreSprite_[Index] = make_unique<Sprite>();
		Score::GetInstance()->scoreSprite_[Index]->SetSrc(src[0].RightTop, src[0].RightBottom, src[0].LeftTop, src[0].LeftBottom);
		Score::GetInstance()->scoreSprite_[Index]->Initialize(new SpriteBoxState, Score::GetInstance()->scorePosition_[Index], { 128.0f, 128.0f });
		Score::GetInstance()->scoreSprite_[Index]->SetTexHandle(scoreTexHD_);
		Score::GetInstance()->scoreSprite_[Index]->SetColor(Score::GetInstance()->texColor_);

		Score::GetInstance()->scoreUseResultSprite_[Index] = make_unique<Sprite>();
		Score::GetInstance()->scoreUseResultSprite_[Index]->SetSrc(src[0].RightTop, src[0].RightBottom, src[0].LeftTop, src[0].LeftBottom);
		Score::GetInstance()->scoreUseResultSprite_[Index]->Initialize(new SpriteBoxState, Score::GetInstance()->scoreUseResultPosition_[Index], { 128.0f, 128.0f });
		Score::GetInstance()->scoreUseResultSprite_[Index]->SetTexHandle(scoreTexHD_);
		Score::GetInstance()->scoreUseResultSprite_[Index]->SetColor(Score::GetInstance()->texColor_);
	}

	Score::GetInstance()->scoreBgWorldTransform_.Initialize();
	Score::GetInstance()->scoreBgPosition_ = { 0.0f, 0.0f };

	Score::GetInstance()->scoreBgSprite_ = make_unique<Sprite>();
	Score::GetInstance()->scoreBgSprite_->Initialize(new SpriteBoxState, Score::GetInstance()->scoreBgPosition_, { 1280.0f, 720.0f });
	Score::GetInstance()->scoreBgSprite_->SetTexHandle(scoreBgTexHD);
	Score::GetInstance()->scoreBgSprite_->SetColor(Score::GetInstance()->texColor_);

	Score::GetInstance()->acquisitionScore_ = 0;
}


// 更新処理
void Score::Update() {

	for (int Index = 0; Index < 4; Index++) {
		Score::GetInstance()->scoreWorldTransform_[Index].UpdateMatrix();
		Score::GetInstance()->scoreUseResultWorldTransform_[Index].UpdateMatrix();
	}

	Score::CalcScorePlace(Score::GetInstance()->acquisitionScore_);
	Score::SetSrc();
	Score::GetInstance()->scoreBgWorldTransform_.UpdateMatrix();
}
void Score::UpdateResult(uint32_t score) {

	for (int Index = 0; Index < 4; Index++) {
		Score::GetInstance()->scoreUseResultWorldTransform_[Index].UpdateMatrix();
	}

	Score::CalcScorePlace(score);
	Score::SetSrc();
}


// 描画処理
void Score::Draw() {

	Score::GetInstance()->scoreBgSprite_->Draw(Score::GetInstance()->scoreBgWorldTransform_);
	for (int Index = 0; Index < 4; Index++) {
		Score::GetInstance()->scoreSprite_[Index]->Draw(Score::GetInstance()->scoreWorldTransform_[Index]);
	}
}
void Score::DrawResult() {



	for (int Index = 0; Index < 4; Index++) {
		Score::GetInstance()->scoreUseResultSprite_[Index]->Draw(Score::GetInstance()->scoreWorldTransform_[Index]);
	}
}


// スコアの加算処理
void Score::AddScore(uint32_t addVale) {

	uint32_t nowScore = Score::GetInstance()->acquisitionScore_;
	Score::GetInstance()->acquisitionScore_ = nowScore + addVale;

}


// スコアの各値を求める
void Score::CalcScorePlace(uint32_t nowScore) {

	// 1000の位
	Score::GetInstance()->eachTime_[0] = (nowScore % 10000) / 1000;
	// 100の位
	Score::GetInstance()->eachTime_[1] = (nowScore % 1000) / 100;
	// 10の位
	Score::GetInstance()->eachTime_[2] = (nowScore % 100) / 10;
	// 1の位
	Score::GetInstance()->eachTime_[3] = (nowScore % 10) / 1;
}


// 各値にあったSrcを設定する
void Score::SetSrc() {

	SrcScore src[10]{};
	uint32_t eachTime[4]{};

	for (int Index = 0; Index < 10; Index++) {
		src[Index] = Score::GetInstance()->src_[Index];
	}
	for (int Index = 0; Index < 4; Index++) {
		eachTime[Index] = Score::GetInstance()->eachTime_[Index];
	}

	// 各位の値にあったテクスチャを設定する
	Score::GetInstance()->scoreSprite_[0]->SetSrc(src[eachTime[0]].RightTop, src[eachTime[0]].RightBottom, src[eachTime[0]].LeftTop, src[eachTime[0]].LeftBottom);
	Score::GetInstance()->scoreSprite_[1]->SetSrc(src[eachTime[1]].RightTop, src[eachTime[1]].RightBottom, src[eachTime[1]].LeftTop, src[eachTime[1]].LeftBottom);
	Score::GetInstance()->scoreSprite_[2]->SetSrc(src[eachTime[2]].RightTop, src[eachTime[2]].RightBottom, src[eachTime[2]].LeftTop, src[eachTime[2]].LeftBottom);
	Score::GetInstance()->scoreSprite_[3]->SetSrc(src[eachTime[2]].RightTop, src[eachTime[2]].RightBottom, src[eachTime[2]].LeftTop, src[eachTime[2]].LeftBottom);
	Score::GetInstance()->scoreUseResultSprite_[0]->SetSrc(src[eachTime[0]].RightTop, src[eachTime[0]].RightBottom, src[eachTime[0]].LeftTop, src[eachTime[0]].LeftBottom);
	Score::GetInstance()->scoreUseResultSprite_[1]->SetSrc(src[eachTime[1]].RightTop, src[eachTime[1]].RightBottom, src[eachTime[1]].LeftTop, src[eachTime[1]].LeftBottom);
	Score::GetInstance()->scoreUseResultSprite_[2]->SetSrc(src[eachTime[2]].RightTop, src[eachTime[2]].RightBottom, src[eachTime[2]].LeftTop, src[eachTime[2]].LeftBottom);
	Score::GetInstance()->scoreUseResultSprite_[3]->SetSrc(src[eachTime[2]].RightTop, src[eachTime[2]].RightBottom, src[eachTime[2]].LeftTop, src[eachTime[2]].LeftBottom);
}

