#include "GameObject/TransitionProcess/TransitionProcess.h"


// FadeProcessクラスのインスタンス取得
TransitionProcess* TransitionProcess::GetInstance() {
	static TransitionProcess instance;
	return &instance;
}


// 初期化処理
void TransitionProcess::Initialize() {

	// テクスチャの読み込み
	TransitionProcess::GetInstance()->BG_TexHD_ = TextureManager::LoadTexture("Resources/Texture/BackGround/BackGround.png");

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
	TransitionProcess::GetInstance()->frame_ = { 0, 0 };
	TransitionProcess::GetInstance()->value_ = { 0.0f, 0.0f };
	TransitionProcess::GetInstance()->isFadeIn_ = false;
	TransitionProcess::GetInstance()->isFadeOut_ = false;

}


// 更新処理
void TransitionProcess::Update() {

	/*if (Input::GetInstance()->PushKeyPressed(DIK_O))
	{
		Fade_Out_Init();
	}
	if (Input::GetInstance()->PushKeyPressed(DIK_I))
	{
		Fade_In_Init();
	}
	Fade_Out();
	Fade_In();*/

#ifdef _DEBUG

	ImGui::Begin("Transition");
	ImGui::Checkbox("BlackBG_isDraw", &TransitionProcess::GetInstance()->BG_isDraw_);
	ImGui::Text("tex_Color.alpha = %.5f", TransitionProcess::GetInstance()->BG_Sprite_->GetColor().w);
	ImGui::Text("nowFrame = %d", TransitionProcess::GetInstance()->frame_.Now);
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


// フェードインの初期化処理
void TransitionProcess::Fade_In_Init() {
	// イージングのスタートとゴールの値を設定する　黒 -> 透明
	TransitionProcess::GetInstance()->value_.Start = 0.0f;
	TransitionProcess::GetInstance()->value_.Goal = 1.0f;

	// フレームをセット
	TransitionProcess::GetInstance()->frame_ = { 0, 240 };

	// イージングの処理の実行フラグを立てる
	TransitionProcess::GetInstance()->isFadeIn_ = true;
}


// フェードイン処理
bool TransitionProcess::Fade_In() {

	Frame frame = TransitionProcess::GetInstance()->frame_;
	Value value = TransitionProcess::GetInstance()->value_;
	Vector4 color{};
	bool isFadeIn = TransitionProcess::GetInstance()->isFadeIn_;

	// 処理の実行フラグがtrueのとき
	if (isFadeIn) {

		// フレームを増やす
		frame.Now++;

		// フレームが目標値になったら実行フラグを折る
		if (frame.Now == frame.End) {
			isFadeIn = false;
			return true;
		}
	}

	// イージングに入れる値
	value.useVal = static_cast<float>(frame.Now) / static_cast<float>(frame.End);

	// イージング処理
	color.w = value.Start + (value.Goal - value.Start) * TransitionProcess::EaseOutQuint(value.useVal);

	TransitionProcess::GetInstance()->BG_Sprite_->SetColor(color);
	TransitionProcess::GetInstance()->isFadeIn_ = isFadeIn;
	TransitionProcess::GetInstance()->frame_ = frame;
	TransitionProcess::GetInstance()->value_ = value;

	return false;
}


// フェードアウトの初期化処理
void TransitionProcess::Fade_Out_Init() {

	// イージングのスタートとゴールの値を設定する　黒 -> 透明
	TransitionProcess::GetInstance()->value_.Start = 1.0f;
	TransitionProcess::GetInstance()->value_.Goal = 0.0f;

	// フレームをセット
	TransitionProcess::GetInstance()->frame_ = { 0, 400 };

	// イージングの処理の実行フラグを立てる
	TransitionProcess::GetInstance()->isFadeOut_ = true;
}


// フェードアウト処理
bool TransitionProcess::Fade_Out() {

	Frame frame = TransitionProcess::GetInstance()->frame_;
	Value value = TransitionProcess::GetInstance()->value_;
	Vector4 color{};
	bool isFadeOut = TransitionProcess::GetInstance()->isFadeOut_;

	// 処理の実行フラグがtrueのとき
	if (isFadeOut) {

		// フレームを増やす
		frame.Now++;

		// フレームが目標値になったら実行フラグを折る
		if (frame.Now == frame.End) {
			isFadeOut = false;
			return true;
		}
	}

	// イージングに入れる値
	value.useVal = static_cast<float>(frame.Now) / static_cast<float>(frame.End);

	// イージング処理
	color.w = value.Start + (value.Goal - value.Start) * TransitionProcess::EaseOutQuint(value.useVal);

	TransitionProcess::GetInstance()->BG_Sprite_->SetColor(color);
	TransitionProcess::GetInstance()->isFadeOut_ = isFadeOut;
	TransitionProcess::GetInstance()->frame_ = frame;
	TransitionProcess::GetInstance()->value_ = value;

	return false;
}


float TransitionProcess::EaseOutQuint(float& val) {
	return float(1 - pow(1 - val, 5));
}

