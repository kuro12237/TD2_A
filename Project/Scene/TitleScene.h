#pragma once

#include"IScene.h"
#include"GameManager.h"

#include "Sprite/Sprite.h"
#include "WorldTransform.h"
#include "Graphics/TextureManager/TextureManager.h"
#include "GameObject/TransitionProcess/TransitionProcess.h"


/// <summary>
/// タイトルシーンクラス
/// </summary>
class TitleScene : public IScene {

public:
	TitleScene() {};
	~TitleScene() {};
	
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
	void Draw() override;


private:

	/* ----- テクスチャ ----- */
	unique_ptr<Sprite>title_Sprite_;
	// ハンドル
	uint32_t title_TexHD_{};
	// ハンドル
	Vector4 title_TexColor_ = { 1.0f, 1.0f, 1.0f, 1.0f };

	/* ----- 座標系 ----- */
	// ２次元座標
	Vector2 title_Position_;
	// ワールドトランスフォーム
	WorldTransform title_WorldTransform_;
};