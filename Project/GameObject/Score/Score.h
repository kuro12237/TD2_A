#pragma once
#include "Sprite/Sprite.h"
#include "WorldTransform.h"
#include "Graphics/TextureManager/TextureManager.h"
#include"Input.h"
#include "Audio.h"



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

	/// <summary>
	/// 描画処理
	/// </summary>
	static void Draw();

	/// <summary>
	/// スコアの加算処理
	/// </summary>
	static void AddScore(uint32_t addValue);


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

	// テクスチャ
	uint32_t scoreTexHD_;

	// テクスチャカラー
	Vector4 texColor_ = { 1.0f, 1.0f, 1.0f, 1.0f };

	// 座標
	SrcScore src_[10];
	Vector2 scorePosition_[4]{};
	WorldTransform scoreWorldTransform_[4]{};

	// 獲得スコア
	uint32_t acquisitionScore_;
	uint32_t eachTime_[4]{};
};