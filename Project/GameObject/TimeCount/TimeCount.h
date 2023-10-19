﻿#pragma once
#include "Sprite/Sprite.h"
#include "WorldTransform.h"
#include "Graphics/TextureManager/TextureManager.h"
#include"Input.h"
#include "Audio.h"



struct Src {
	Vector2 RightTop;
	Vector2 RightBottom;
	Vector2 LeftTop;
	Vector2 LeftBottom;
};


/// <summary>
/// タイムカウントクラス
/// </summary>
class TimeCount {

public:
	~TimeCount() {};
	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

	/// <summary>
	/// タイマーを減らす
	/// </summary>
	void SubtructTimer();

	/// <summary>
	/// 時間の追加処理
	/// </summary>
	void AddTimeCount();

	/// <summary>
	/// 制限時間をリセットする
	/// </summary>
	void ReSetTimer();

	/// <summary>
	/// 制限時間の各位を求める
	/// </summary>
	void CalcTimerPlace(uint32_t nowTimer);

	/// <summary>
	/// 各位に合ったテクスチャを設定する
	/// </summary>
	void SetNumberTexture();


#pragma region get

	/// <summary>
	/// 時間切れのフラグの取得
	/// </summary>
	bool GetIsTimeUp() { return isTimeUp_; }

#pragma endregion


private:

	// スプライト
	unique_ptr<Sprite>timeCountSprite_[3];
	unique_ptr<Sprite>timeUpUISprite_;

	// テクスチャ
	uint32_t numberTexHD_;
	uint32_t timeUpUITextureHD_{};
	
	// テクスチャカラー
	Vector4 textureColor_ = { 1.0f, 1.0f, 1.0f, 1.0f };

	// 座標
	Src src_[10];
	Vector2 timeCountPosition_[3]{};
	WorldTransform timeCountWorldTransform_[3]{};
	Vector2 timeUpUIPosition_;
	WorldTransform timeUpUIWorldTransform_{};

	// 制限時間
	uint32_t nowLimitTime_ = 0;
	const uint32_t kSetLimitTime_ = 30;
	uint32_t eachTime_[3]{};
	uint32_t frame_ = 0;
	bool isTimeUp_ = false;

	// デバッグフラグ　
	bool isDebug_ = true;
};