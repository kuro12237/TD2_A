#pragma once
#include"Pch.h"
#include "Sprite/Sprite.h"
#include "WorldTransform.h"


struct SrcKillCount {
	Vector2 RightTop;
	Vector2 RightBottom;
	Vector2 LeftTop;
	Vector2 LeftBottom;
};


struct KillCount {
	unique_ptr<Sprite>sprite[2];
	uint32_t TexHD[2];
	Vector2 position[2];
	WorldTransform worldTrnsform[2];
};



class KillCounter
{
public:
	
	static KillCounter* GetInstance();

	static void Initialize();

	static void Update(uint32_t value);

	static void Draw();

	static void ClearCount() { KillCounter::GetInstance()->count = 0; }
	static void AddCount(uint32_t t = 1) { KillCounter::GetInstance()->count+=t; }

	static uint32_t GetCount() { return KillCounter::GetInstance()->count; }

	/// <summary>
	/// スコアの各値を求める
	/// </summary>
	static void CalcScorePlace(uint32_t nowScore);

	/// <summary>
	/// 各値にあったSrcを設定する
	/// </summary>
	static void SetSrc();


	Sprite* GetBG_Sprite0() { return KillCounter::GetInstance()->killCounter_.sprite[0].get(); }
	Sprite* GetBG_Sprite1() { return KillCounter::GetInstance()->killCounter_.sprite[1].get(); }


private:

	KillCount killCounter_;
	SrcKillCount src_[10];

	Vector4 TexColor = { 1.0f, 1.0f, 1.0f,1.0f };

	uint32_t count = 0;
	uint32_t eachTime_[2]{};
};

