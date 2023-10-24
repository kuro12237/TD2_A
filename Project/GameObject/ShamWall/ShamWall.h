#pragma once

#include"Model.h"
#include"WorldTransform.h"
#include "GameObject/ShamWall/State/WallColorState.h"
#include "GameObject/ShamWall/State/CalcRed.h"
#include "GameObject/ShamWall/State/CalcGreen.h"
#include "GameObject/ShamWall/State/CalcBlue.h"



struct WallElemnt {
	unique_ptr<Model>model = nullptr;
	WorldTransform worldTansform{};
};


/// <summary>
/// ShamWallクラス
/// </summary>
class ShamWall {

public:

	ShamWall() {};
	~ShamWall() {};

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
	void Draw(ViewProjection view);

	/// <summary>
	/// RGBを求める
	/// </summary>
	Vector3 CalcRGB(Vector4 color);
	
	/// <summary>
	/// RGBAを求める
	/// </summary>
	Vector4 CalcRGBA(Vector3 color);

	/// <summary>
	/// カラーの計算を変更する
	/// </summary>
	void ChangeWallColorState(WallColorState* newState);


	/// <summary>
	/// グラデーションする処理
	/// </summary>
	Vector4 CalculateColorGradient(float time);


#pragma region Get

	Vector3 getRGBColor() { return color_; }
	ColorState GetColorState() { return colorState_; }

#pragma endregion

#pragma region Set

	void SetRGBColorR(float color) { color_.x = color; }
	void SetRGBColorG(float color) { color_.y = color; }
	void SetRGBColorB(float color) { color_.z = color; }
	void SetColorState(ColorState colorState) { colorState_ = colorState; }

#pragma endregion

private:

	WallElemnt shamWall_;


	// 初期スケール
	Vector3 initScale_ = { 1.07f, 1.0f, 1.07f };
	Vector3 initTranslate_ = { 1.0f, 1.0f, 1.0f };

	// RGBAカラー
	Vector4 modelColor_ = { 1.0f, 0.0f, 0.0f, 1.0f };

	// RGBカラー
	Vector3 color_;

	WallColorState* calcColorState_;


	ColorState colorState_ = AddGreen;
};