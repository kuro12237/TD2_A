#pragma once
#include "Sprite/Sprite.h"
#include "WorldTransform.h"
#include "Graphics/TextureManager/TextureManager.h"
#include"Input.h"
#include "Audio.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <thread>



struct SrcScore {
	Vector2 RightTop;
	Vector2 RightBottom;
	Vector2 LeftTop;
	Vector2 LeftBottom;
};


/// <summary>
/// スコアクラス
/// </summary>
class Score {

public: // メンバ関数

	/// <summary>
	/// Scoreクラスのインスタンス取得
	/// </summary>
	static Score* GetInstance();

	/// <summary>
	/// 初期化処理
	/// </summary>
	static void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	static void Update();
	static void UpdateResult(uint32_t score);

	/// <summary>
	/// 描画処理
	/// </summary>
	static void Draw();
	static void DrawResult();

	/// <summary>
	/// スコアの加算処理
	/// </summary>
	static void AddScore(uint32_t addValue);



	Sprite* GetBG_Sprite0() { return Score::GetInstance()->scoreUseResultSprite_[0].get(); }
	Sprite* GetBG_Sprite1() { return Score::GetInstance()->scoreUseResultSprite_[1].get(); }
	Sprite* GetBG_Sprite2() { return Score::GetInstance()->scoreUseResultSprite_[2].get(); }
	Sprite* GetBG_Sprite3() { return Score::GetInstance()->scoreUseResultSprite_[3].get(); }
	uint32_t GetScore() { return Score::GetInstance()->acquisitionScore_; }

private: // メンバ関数

	/// <summary>
	/// スコアの各値を求める
	/// </summary>
	static void CalcScorePlace(uint32_t nowScore);

	/// <summary>
	/// 各値にあったSrcを設定する
	/// </summary>
	static void SetSrc();



private: // メンバ変数

	// スプライト
	unique_ptr<Sprite>scoreSprite_[4];
	unique_ptr<Sprite>scoreUseResultSprite_[4];
	unique_ptr<Sprite>scoreBgSprite_;

	// テクスチャ
	uint32_t scoreTexHD_;
	uint32_t scoreBgTexHd_;

	// テクスチャカラー
	Vector4 texColor_ = { 1.0f, 1.0f, 1.0f, 1.0f };

	// 座標
	SrcScore src_[10];
	Vector2 scorePosition_[4]{};
	Vector2 scoreUseResultPosition_[4]{};
	WorldTransform scoreWorldTransform_[4]{};
	WorldTransform scoreUseResultWorldTransform_[4]{};
	Vector2 scoreBgPosition_;
	WorldTransform scoreBgWorldTransform_;

	// 獲得スコア
	uint32_t acquisitionScore_;
	uint32_t useResultScore_;
	uint32_t eachTime_[4]{};
};