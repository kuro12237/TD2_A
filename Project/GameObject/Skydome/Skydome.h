#pragma once

#include"Model.h"
#include"WorldTransform.h"


struct SkydomeElemnt {
	unique_ptr<Model>model = nullptr;
	WorldTransform worldTansform{};
};


/// <summary>
/// 天球
/// </summary>
class Skydome {
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
	void Draw(ViewProjection viewProjection);



	/// <summary>
	/// グラデーションする処理
	/// </summary>
	Vector4 CalculateColorGradient(float time);



private:

	SkydomeElemnt skydome_ = {};

	float initScale_ = 7000.0f;

	Vector4 modelColor_ = { 1.0f, 1.0f, 1.0f, 1.0f };


	// RGBカラー
	Vector3 color_ = {};
};