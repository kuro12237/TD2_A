#pragma once

#include"Model.h"
#include"WorldTransform.h"



struct WallElemnt {
	unique_ptr<Model>model = nullptr;
	WorldTransform worldTansform{};
};


/// <summary>
/// ShamWallクラス
/// </summary>
class ShamWall {

public:

	ShamWall() {};
	~ShamWall() {};

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
	void Draw(ViewProjection view);

private:

	WallElemnt shamWall_;

	// 初期スケール
	Vector3 initScale_ = { 1.07f, 2.0f, 1.07f };

	// カラー
	Vector4 modelColor_ = { 1.0f, 1.0f, 1.0f, 1.0f };
};