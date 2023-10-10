#pragma once
#include "Sprite/Sprite.h"
#include "WorldTransform.h"
#include "Graphics/TextureManager/TextureManager.h"
#include"Input.h"



/// <summary>
/// タイムカウントクラス
/// </summary>
class TimeCount {

public:
	TimeCount() {};
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
	/// 時間の追加処理
	/// </summary>
	void AddTimeCount();

	/// <summary>
	/// 制限時間の各位を求める
	/// </summary>
	void CalcTimerPlace(uint32_t nowTimer);

	/// <summary>
	/// 各位に合ったテクスチャを設定する
	/// </summary>
	void SetNumberTexture();

private:

	// スプライト
	unique_ptr<Sprite>sprite_[3];

	// テクスチャ
	uint32_t numTextureHD_[10]{};

	// テクスチャカラー
	Vector4 textureColor_ = { 1.0f, 1.0f, 1.0f, 1.0f };

	// 描画座標
	Vector2 position_[2];
	WorldTransform worldTransform_[2];

	// 制限時間
	uint32_t nowLimitTime_;
	const uint32_t kSetLimitTime_ = 30;
	uint32_t eachTime_[3]{};
};