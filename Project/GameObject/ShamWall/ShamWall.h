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

	WallElemnt Top_{};
	WallElemnt Bottom_{};
	WallElemnt Left_{};
	WallElemnt Right_{};
};