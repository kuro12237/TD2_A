#pragma once

#include"Model.h"
#include"WorldTransform.h"


struct MapGroundElement {
	unique_ptr<Model>model = nullptr;
	WorldTransform worldTansform{};
};


/// <summary>
/// マップの床クラス
/// </summary>
class MapGround {

public:

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Updatea();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw(ViewProjection view);

private:

	MapGroundElement ground_;

	Vector4 modelColor_ = { 1.0f, 1.0f, 1.0f, 1.0f };

};