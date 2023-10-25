#pragma once
#include "WorldTransform.h"
#include "Graphics/TextureManager/TextureManager.h"
#include <Sprite/Sprite.h>


struct SrcStartCount {
	Vector2 RightTop;
	Vector2 RightBottom;
	Vector2 LeftTop;
	Vector2 LeftBottom;
};

struct StartCountElement {
	unique_ptr<Sprite> sprite;
	uint32_t TexHD;
	Vector2 position;
	WorldTransform worldTransform;
	SrcStartCount src[4];
};


class StartCount {

public:
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
	void Draw();

	/// <summary>
	/// タイマーを減らす
	/// </summary>
	void SubtructTimer();

	/// <summary>
	/// 各位に合ったテクスチャを設定する
	/// </summary>
	void SetSrc();



	bool GetIsStartCount() { return isStartCount_; }

private:

	StartCountElement startCount_;

	Vector4 texColor = { 1.0f, 1.0f, 1.0f, 1.0f };

	// スタートカウント
	uint32_t nowCounr_ = 0;
	uint32_t frame_;
	uint32_t eachCount_;
	uint32_t count_;
	bool isStartCount_;
};