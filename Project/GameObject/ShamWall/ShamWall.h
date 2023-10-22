#pragma once

#include"Model.h"
#include"WorldTransform.h"
#include <list>



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

	const static uint32_t MAX_WALL_OBJECT = 40;
	WallElemnt Top_[MAX_WALL_OBJECT]{};
	WallElemnt Bottom_[MAX_WALL_OBJECT]{};
	WallElemnt Left_[MAX_WALL_OBJECT]{};
	WallElemnt Right_[MAX_WALL_OBJECT]{};

	// 初期座標
	Vector3 initTopTranslate_ = { 33.0f, 0.0f, 40.7f };
	Vector3 initBottomTranslate_ = { -33.0f, 0.0f, 40.7f };
	Vector3 initLeftTranslate_ = { 40.7f, 0.0f, 33.0f };
	Vector3 initRightTranslate_ = { 40.7f, 0.0f, -33.0f };

	// 初期スケール
	Vector3 initScale_ = { 0.5f, 1.0f, 0.5f };

	Vector4 color = { 1.0f, 1.0f, 1.0f, 1.0f };
};