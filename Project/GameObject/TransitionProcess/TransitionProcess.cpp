#include "GameObject/TransitionProcess/TransitionProcess.h"


// FadeProcessクラスのインスタンス取得
TransitionProcess* TransitionProcess::GetInstance() {
	static TransitionProcess instance;
	return &instance;
}


// 初期化処理
void TransitionProcess::Initialize() {

	// テクスチャの読み込み
	TransitionProcess::GetInstance()->BG_TexHD_ = TextureManager::LoadTexture("Resources/BackGround/BackGround.png");

	// 座標
	Vector2 pos = TransitionProcess::GetInstance()->BG_Position_;
	WorldTransform worldtransform = TransitionProcess::GetInstance()->BG_WorldTransform_;
	pos = { 0.0f, 0.0f };
	worldtransform.Initialize();
	worldtransform.translate = { pos.x, pos.y, 0.0f };
	TransitionProcess::GetInstance()->BG_Position_ = pos;
	TransitionProcess::GetInstance()->BG_WorldTransform_ = worldtransform;

	// スプライト
	TransitionProcess::GetInstance()->BG_Sprite_ = make_unique<Sprite>();
	TransitionProcess::GetInstance()->BG_Sprite_->Initialize(new SpriteBoxState, pos, { 1280, 720 });
	TransitionProcess::GetInstance()->BG_Sprite_->SetColor(TransitionProcess::GetInstance()->BG_TexColor_);
	TransitionProcess::GetInstance()->BG_Sprite_->SetTexHandle(TransitionProcess::GetInstance()->BG_TexHD_);

	/// イージングの各値の初期化
	// イージングタイプ
	TransitionProcess::GetInstance()->ease_Type_ = 1;
	// イージング開始フラグ
	TransitionProcess::GetInstance()->ease_isStart_ = false;
	// 現在のフレーム
	TransitionProcess::GetInstance()->ease_NowFrame_ = 0.0f;
	// 終了フレーム
	TransitionProcess::GetInstance()->ease_EndFrame_ = 0.0f;
	// イージング処理内で使う値
	TransitionProcess::GetInstance()->ease_val_ = 0.0f;
	// スタート地点
	TransitionProcess::GetInstance()->ease_StartVal_ = 0.0f;
	// ゴール地点
	TransitionProcess::GetInstance()->easse_EndVal_ = 0.0f;


	TransitionProcess::Fade_Out();
}


// 更新処理
void TransitionProcess::Update() {

#ifdef _DEBUG

	// Eキーをしながら上下キーでイージングのタイプを変える
	if (Input::GetInstance()->PushKey(DIK_E)) {

		if (Input::GetInstance()->PushKeyPressed(DIK_UP)) {
			TransitionProcess::GetInstance()->ease_Type_ = TransitionProcess::GetInstance()->ease_Type_ + 1;
		}
		else if (Input::GetInstance()->PushKeyPressed(DIK_DOWN)) {
			TransitionProcess::GetInstance()->ease_Type_ = TransitionProcess::GetInstance()->ease_Type_ - 1;
		}

		if (Input::GetInstance()->PushKeyPressed(DIK_O)) {
			TransitionProcess::Fade_Out();
		}
	}


	ImGui::Begin("Transition");
	ImGui::Checkbox("isDraw", &TransitionProcess::GetInstance()->BG_isDraw_);
	ImGui::Text("ease_Type = %d", TransitionProcess::GetInstance()->ease_Type_);
	ImGui::Text("ease_IsStart = %d", TransitionProcess::GetInstance()->ease_isStart_);
	ImGui::Text("ease_nowFrame = %.2f", TransitionProcess::GetInstance()->ease_NowFrame_);
	ImGui::Text("ease_endFrame = %.2f", TransitionProcess::GetInstance()->ease_EndFrame_);
	ImGui::Text("ease_val = %.2f", TransitionProcess::GetInstance()->ease_val_);
	ImGui::Text("ease_startVal = %.2f", TransitionProcess::GetInstance()->ease_StartVal_);
	ImGui::Text("ease_endVal = %.2f", TransitionProcess::GetInstance()->easse_EndVal_);

	ImGui::End();

#endif // DEBUG

}


// 描画処理
void TransitionProcess::Draw() {

	if (TransitionProcess::GetInstance()->BG_isDraw_) {
		TransitionProcess::GetInstance()->BG_Sprite_->Draw(
			TransitionProcess::GetInstance()->BG_WorldTransform_);
	}
}


// フェードイン処理
void TransitionProcess::Fade_In() {


}


// フェードアウト処理
void TransitionProcess::Fade_Out() {
	// スタート地点を設定
	TransitionProcess::GetInstance()->ease_StartVal_ = 1.0f;
	// ゴール地点を設定
	TransitionProcess::GetInstance()->easse_EndVal_ = 0.0f;

	// イージング開始
	TransitionProcess::EaseProcess();
}


// イージング処理をまとめたもの
void TransitionProcess::EaseProcess() {

	/* --- 開始時処理 --- */
	if (TransitionProcess::GetInstance()->ease_isStart_ == false) {

		// イージング開始のフラグを立てる
		TransitionProcess::GetInstance()->ease_isStart_ = true;
		// 進行度０でスタート
		TransitionProcess::GetInstance()->ease_NowFrame_ = 0;
		// 終了フレームを設定
		TransitionProcess::GetInstance()->ease_EndFrame_ = 60;
	}


	/* --- 実行時処理 --- */
	Vector4 newColor{};
	float startVal = TransitionProcess::GetInstance()->ease_StartVal_;
	float endVal = TransitionProcess::GetInstance()->easse_EndVal_;
	float val = TransitionProcess::GetInstance()->ease_val_;

	// 終了フレームに追いつくまでwhile文で回す
		// イージングの開始フラグが立っていたら
	if (TransitionProcess::GetInstance()->ease_isStart_) {

		while (TransitionProcess::GetInstance()->ease_NowFrame_ == TransitionProcess::GetInstance()->ease_EndFrame_) {

			// 進行度を増やす
			TransitionProcess::GetInstance()->ease_NowFrame_++;

			// フレーム進行 : 0->開始 1->終了
			val = TransitionProcess::GetInstance()->ease_NowFrame_ / TransitionProcess::GetInstance()->ease_EndFrame_;

			if (TransitionProcess::GetInstance()->ease_Type_ == 1) {
				// イージング実行

				newColor.w = startVal + (endVal - startVal) * TransitionProcess::EaseOutQuint(val);
				// イージングで求めたカラーをセットする
				TransitionProcess::GetInstance()->BG_Sprite_->SetColor(newColor);
			}
		}
	}

	TransitionProcess::GetInstance()->ease_StartVal_ = startVal;
	TransitionProcess::GetInstance()->easse_EndVal_ = endVal;
	TransitionProcess::GetInstance()->ease_val_ = val;


	/* --- 終了時処理 --- */
	if (TransitionProcess::GetInstance()->ease_NowFrame_ == TransitionProcess::GetInstance()->ease_EndFrame_) {

		// イージング開始のフラグを折る
		TransitionProcess::GetInstance()->ease_isStart_ = false;
	}
}


// イージング開始時処理
void TransitionProcess::EaseStartPreparation() {

	if (TransitionProcess::GetInstance()->ease_isStart_ == false) {

		// イージング開始のフラグを立てる
		TransitionProcess::GetInstance()->ease_isStart_ = true;
		// 進行度０でスタート
		TransitionProcess::GetInstance()->ease_NowFrame_ = 0;
		// 終了フレームを設定
		TransitionProcess::GetInstance()->ease_EndFrame_ = 60;
	}
}


// イージング実行処理
void TransitionProcess::EaseContentProcess() {

	Vector4 newColor{};
	float startVal = TransitionProcess::GetInstance()->ease_StartVal_;
	float endVal = TransitionProcess::GetInstance()->easse_EndVal_;
	float val = TransitionProcess::GetInstance()->ease_val_;


	// イージングの開始フラグが立っていたら
	if (TransitionProcess::GetInstance()->ease_isStart_) {

		// 進行度を増やす
		TransitionProcess::GetInstance()->ease_NowFrame_++;

		// フレーム進行 : 0->開始 1->終了
		val = TransitionProcess::GetInstance()->ease_NowFrame_ / TransitionProcess::GetInstance()->ease_EndFrame_;

		if (TransitionProcess::GetInstance()->ease_Type_ == 1) {
			// イージング実行

			newColor.w = startVal + (endVal - startVal) * TransitionProcess::EaseOutQuint(val);
			// イージングで求めたカラーをセットする
			TransitionProcess::GetInstance()->BG_Sprite_->SetColor(newColor);
		}
	}

	TransitionProcess::GetInstance()->ease_StartVal_ = startVal;
	TransitionProcess::GetInstance()->easse_EndVal_ = endVal;
	TransitionProcess::GetInstance()->ease_val_ = val;
}


// イージング終了時処理
void TransitionProcess::EaseEndPreparation() {

	// 終了フレームに追いついたら、終了時処理に入る
	if (TransitionProcess::GetInstance()->ease_NowFrame_ == TransitionProcess::GetInstance()->ease_EndFrame_) {

		// イージング開始のフラグを折る
		TransitionProcess::GetInstance()->ease_isStart_ = false;
	}
	else {
		// 終了しなかったら再帰
		TransitionProcess::EaseContentProcess();
	}
}



float TransitionProcess::EaseOutQuint(float& val) {
	return float(1 - pow(1 - val, 5));
}

