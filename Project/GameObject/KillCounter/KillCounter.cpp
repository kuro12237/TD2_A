#include "KillCounter.h"

KillCounter* KillCounter::GetInstance()
{
	static KillCounter instance;
	return &instance;
}

void KillCounter::Initialize()
{
	// テクスチャの読み込み
	uint32_t killCountTexHD = TextureManager::LoadTexture("Resources/Texture/UI/Score.png");

	// 画像の上下左右の座標を決める
	int column = 0;
	int line = 0;
	SrcKillCount src[10]{};
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

		KillCounter::GetInstance()->src_[Index] = src[Index];
	}


	// キルカウントの初期化処理
	for (int Index = 0; Index < 2; Index++) {

		// 座標
		KillCounter::GetInstance()->killCounter_.worldTrnsform[Index].Initialize();

		KillCounter::GetInstance()->killCounter_.position[Index] = { 730.0f + (85.0f * Index), 390.0f };

		// スプライト
		KillCounter::GetInstance()->killCounter_.sprite[Index] = make_unique<Sprite>();
		KillCounter::GetInstance()->killCounter_.sprite[Index]->SetSrc(src[0].RightTop, src[0].RightBottom, src[0].LeftTop, src[0].LeftBottom);
		KillCounter::GetInstance()->killCounter_.sprite[Index]->Initialize(new SpriteBoxState, KillCounter::GetInstance()->killCounter_.position[Index], { 128.0f, 128.0f });
		KillCounter::GetInstance()->killCounter_.sprite[Index]->SetTexHandle(killCountTexHD);
		KillCounter::GetInstance()->killCounter_.sprite[Index]->SetColor(KillCounter::GetInstance()->TexColor);
	}

	KillCounter::GetInstance()->count = 0;
}


void KillCounter::Update(uint32_t value) {

	for (int Index = 0; Index < 2; Index++) {
		KillCounter::GetInstance()->killCounter_.worldTrnsform[Index].UpdateMatrix();
	}

	KillCounter::CalcScorePlace(value);
	KillCounter::SetSrc();
}


void KillCounter::Draw() {

	for (int Index = 0; Index < 2; Index++) {
		KillCounter::GetInstance()->killCounter_.sprite[Index]->Draw(KillCounter::GetInstance()->killCounter_.worldTrnsform[Index]);
	}
}


void KillCounter::CalcScorePlace(uint32_t nowScore) {

	// 10の位
	KillCounter::GetInstance()->eachTime_[0] = (nowScore % 100) / 10;
	// 1の位
	KillCounter::GetInstance()->eachTime_[1] = (nowScore % 10) / 1;
}


void KillCounter::SetSrc() {

	SrcKillCount src[10]{};
	uint32_t eachTime[2]{};

	for (int Index = 0; Index < 10; Index++) {
		src[Index] = KillCounter::GetInstance()->src_[Index];
	}
	for (int Index = 0; Index < 2; Index++) {
		eachTime[Index] = KillCounter::GetInstance()->eachTime_[Index];
	}

	// 各位の値にあったテクスチャを設定する
	KillCounter::GetInstance()->killCounter_.sprite[0]->SetSrc(src[eachTime[0]].RightTop, src[eachTime[0]].RightBottom, src[eachTime[0]].LeftTop, src[eachTime[0]].LeftBottom);
	KillCounter::GetInstance()->killCounter_.sprite[1]->SetSrc(src[eachTime[1]].RightTop, src[eachTime[1]].RightBottom, src[eachTime[1]].LeftTop, src[eachTime[1]].LeftBottom);
}