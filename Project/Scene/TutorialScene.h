#pragma once

#include"IScene.h"
#include"GameManager.h"

#include "Sprite/Sprite.h"
#include "WorldTransform.h"
#include "Graphics/TextureManager/TextureManager.h"


/// <summary>
/// チュートリアルシーンクラス
/// </summary>
class TutorialScene : public IScene {

public:
	TutorialScene() {};
	~TutorialScene() {};

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
	unique_ptr<Sprite>tutorial_Sprite_;
	// ハンドル
	uint32_t tutorial_TexHD_{};
	// ハンドル
	Vector4 tutorial_TexColor_ = { 1.0f, 1.0f, 1.0f, 1.0f };

	/* ----- 座標系 ----- */
	// ２次元座標
	Vector2 tutorial_Position_;
	// ワールドトランスフォーム
	WorldTransform tutorial_WorldTransform_;
};