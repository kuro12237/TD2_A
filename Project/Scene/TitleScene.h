#pragma once

#include"IScene.h"
#include"GameManager.h"

#include "Sprite/Sprite.h"
#include "WorldTransform.h"
#include "Graphics/TextureManager/TextureManager.h"
#include "GameObject/TransitionProcess/TransitionProcess.h"

#include"GameObject/ShamWall/ShamWall.h"
#include"GameObject/Skydome/Skydome.h"
#include"GameObject/MapGround/MapGround.h"




struct TitleBgElement {
	unique_ptr<Sprite>Sprite = nullptr;
	uint32_t TexHD;
	Vector2 Position;
	WorldTransform worldTransform{};
};


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


	unique_ptr<ShamWall>shamWall_ = nullptr;
	unique_ptr<Skydome>skydome_ = nullptr;
	unique_ptr<MapGround>mapGround_ = nullptr;


	TitleBgElement titleBg_;
	TitleBgElement pushBg_;
	Vector4 TexColor_ = { 1.0f, 1.0f, 1.0f, 1.0f };
};