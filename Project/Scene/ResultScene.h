#pragma once

#include"IScene.h"
#include"GameManager.h"

#include "Sprite/Sprite.h"
#include "WorldTransform.h"
#include "Graphics/TextureManager/TextureManager.h"
#include "GameObject/TransitionProcess/TransitionProcess.h"
#include "GameObject/Score/Score.h"
#include"GameObject/KillCounter/KillCounter.h"


struct ResultElement {
	unique_ptr<Sprite>sprite[3];
	uint32_t TexHD[3];
	Vector2 position;
	WorldTransform worldTransform[3];
};


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
	/// グラデーションする処理
	/// </summary>
	Vector4 CalculateColorGradient(float time);

	/// <summary>
	/// 描画処理
	/// </summary>
	void Back2dSpriteDraw()override;
	void Object3dDraw()override;
	void Flont2dSpriteDraw()override;


private:
	
	
	ResultElement result_;
	Vector4 result_TexColor_ = { 1.0f, 1.0f, 1.0f, 1.0f };
	uint32_t score_;

};