#pragma once


class FadeProcess {

public: // メンバ関数

	/// <summary>
	/// FadeProcessクラスのインスタンス取得
	/// </summary>
	static FadeProcess* GetInstance();

	/// <summary>
	/// 初期化処理」
	/// </summary>
	static void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	static void Update();

	/// <summary>
	/// フェードイン処理
	/// </summary>
	static void Fade_In();

	/// <summary>
	/// フェードアウト処理
	/// </summary>
	static void Fade_Out();

	/// <summary>
	/// 描画処理
	/// </summary>
	static void Draw();

private: // メンバ関数



private: // メンバ変数


};