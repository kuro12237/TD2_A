﻿#pragma once

#include"IScene.h"
#include"GameManager.h"

#include "Sprite/Sprite.h"
#include "WorldTransform.h"
#include "Graphics/TextureManager/TextureManager.h"
#include "GameObject/TransitionProcess/TransitionProcess.h"

#include"GameObject/ShamWall/ShamWall.h"
#include"GameObject/Skydome/Skydome.h"
#include"GameObject/MapGround/MapGround.h"

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
	void Back2dSpriteDraw()override;
	void Object3dDraw()override;
	void Flont2dSpriteDraw()override;


private:

	ViewProjection viewProjection_{};
	
	WorldTransform CenterWorldTransform{};

	/* ----- テクスチャ ----- */
	unique_ptr<Sprite>title_Sprite_=nullptr;
	// ハンドル
	uint32_t title_TexHD_{};
	// ハンドル
	Vector4 title_TexColor_ = { 1.0f, 1.0f, 1.0f, 1.0f };

	/* ----- 座標系 ----- */
	// ２次元座標
	Vector2 title_Position_{};
	// ワールドトランスフォーム
	WorldTransform title_WorldTransform_{};

	unique_ptr<ShamWall>shamWall_ = nullptr;
	unique_ptr<Skydome>skydome_ = nullptr;
	unique_ptr<MapGround>mapGround_ = nullptr;
};