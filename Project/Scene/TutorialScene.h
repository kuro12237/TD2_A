#pragma once

#include"IScene.h"
#include"GameManager.h"

#include "Sprite/Sprite.h"
#include "WorldTransform.h"
#include "Graphics/TextureManager/TextureManager.h"
#include "GameObject/TransitionProcess/TransitionProcess.h"



struct TutorialElement {
	unique_ptr<Sprite>sprite[2];
	uint32_t TexHD[2];
	Vector2 position;
	WorldTransform worldTansform[2];
};



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
	void Back2dSpriteDraw()override;
	void Object3dDraw()override;
	void Flont2dSpriteDraw()override;

private:

	TutorialElement tutorial_;
	Vector4 TexColor = { 1.0f, 1.0f, 1.0f, 1.0f };
	uint32_t timer_ = 0;
	bool fade_;
	uint32_t nowPage_;
};