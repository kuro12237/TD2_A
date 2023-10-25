#pragma once

#include"IScene.h"
#include"GameManager.h"

#include "Sprite/Sprite.h"
#include "WorldTransform.h"
#include "Graphics/TextureManager/TextureManager.h"
#include "GameObject/TransitionProcess/TransitionProcess.h"


/// <summary>
/// リザルトシーンクラス
/// </summary>
class ResultScene : public IScene {

public:
	ResultScene() {};
	~ResultScene() {};

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update(GameManager* scene) override;

	/// <summary>
	/// 描画処理
	/// </summary>
	void Back2dSpriteDraw()override;
	void Object3dDraw()override;
	void Flont2dSpriteDraw()override;


private:

	/* ----- テクスチャ ----- */
	unique_ptr<Sprite>result_Sprite_=nullptr;
	// ハンドル
	uint32_t result_TexHD_{};
	// ハンドル
	Vector4 result_TexColor_ = { 1.0f, 1.0f, 1.0f, 1.0f };

	/* ----- 座標系 ----- */
	// ２次元座標
	Vector2 result_Position_ = {};
	// ワールドトランスフォーム
	WorldTransform result_WorldTransform_ = {};
};