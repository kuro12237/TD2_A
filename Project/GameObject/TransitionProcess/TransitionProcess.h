#pragma once
#include "WorldTransform.h"
#include "Graphics/TextureManager/TextureManager.h"
#include "Sprite/Sprite.h"
#include "Input.h"
#include "VectorTransform.h"



struct Frame {
	int Now;
	int End;
};

struct Value {
	float useVal;
	float Start;
	float Goal;
};


/// <summary>
/// TransitionProcessクラス
/// </summary>
class TransitionProcess {

public: // メンバ関数

	/// <summary>
	/// TransitionProcessクラスのインスタンス取得
	/// </summary>
	static TransitionProcess* GetInstance();

	/// <summary>
	/// 初期化処理」
	/// </summary>
	static void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	static void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	static void Draw();

	/// <summary>
	/// フェードインの初期化処理
	/// </summary>
	static void Fade_In_Init();

	/// <summary>
	/// フェードイン処理
	/// </summary>
	static void Fade_In();

	/// <summary>
	/// フェードアウトの初期化処理
	/// </summary>
	static void Fade_Out_Init();

	/// <summary>
	/// フェードアウト処理
	/// </summary>
	static void Fade_Out();

#pragma region Get 取得

	Sprite* GetBG_Sprite() { return TransitionProcess::GetInstance()->BG_Sprite_.get(); }
	uint32_t GetBG_TexHD() { return TransitionProcess::GetInstance()->BG_TexHD_; }
	Vector2 GetBG_Position() { return TransitionProcess::GetInstance()->BG_Position_; }
	WorldTransform GetBG_WorldTransform() { return TransitionProcess::GetInstance()->BG_WorldTransform_; }

#pragma endregion 


private: // メンバ関数

	/// <summary>
	/// イージングの処理
	/// 以下の処理をまとめた処理
	/// </summary>
	static void EaseProcess();


	static float EaseOutQuint(float& val);
	
private: // メンバ変数
	
	/* ----- スプライト ----- */
	unique_ptr<Sprite>BG_Sprite_;


	/* ----- テクスチャ ----- */
	// ハンドル
	uint32_t BG_TexHD_;
	// ハンドル
	Vector4 BG_TexColor_ = { 0.0f, 0.0f, 0.0f, 0.0f };


	/* ----- 座標系 ----- */
	// ２次元座標
	Vector2 BG_Position_;
	// ワールドトランスフォーム
	WorldTransform BG_WorldTransform_;


	/* ----- 描画フラグ ----- */
	bool BG_isDraw_ = true;


	/* ----- イージング ----- */
	// フレーム
	Frame frame_;
	// 終始の値
	Value value_;
	// イージングの実行フラグ
	bool ease_isStart_;

};