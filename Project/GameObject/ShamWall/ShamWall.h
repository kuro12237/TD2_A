#pragma once

#include"Model.h"
#include"WorldTransform.h"



struct WallElemnt {
	unique_ptr<Model>model = nullptr;
	WorldTransform worldTansform{};
};


enum ColorState {
	AddRed,
	SubRed,
	AddGreen,
	SubGreen,
	AddBlue,
	SubBlue,
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
	/// カラーの計算
	/// </summary>
	void CalcGradation(ColorState state);

	/// <summary>
	/// RGBを求める
	/// </summary>
	Vector3 CalcRGB(Vector4 color);
	
	/// <summary>
	/// RGBAを求める
	/// </summary>
	Vector4 CalcRGBA(Vector3 color);


#pragma region Get

	ColorState GetColorState() { return state_; }

#pragma endregion

private:

	WallElemnt shamWall_;


	// 初期スケール
	Vector3 initScale_ = { 1.07f, 2.0f, 1.07f };

	// カラー
	Vector4 modelColor_ = { 1.0f, 0.0f, 0.0f, 1.0f };

	Vector3 color_;

	ColorState state_ = AddGreen;
};