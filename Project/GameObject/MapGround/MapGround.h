#pragma once

#include "Sprite/Sprite.h"
#include "WorldTransform.h"
#include "Graphics/TextureManager/TextureManager.h"


struct MapGroundElement {

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
	void Draw();

private:


};