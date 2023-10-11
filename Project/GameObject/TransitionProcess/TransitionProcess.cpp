#include "GameObject/TransitionProcess/TransitionProcess.h"


// FadeProcessクラスのインスタンス取得
TransitionProcess* TransitionProcess::GetInstance() {
	static TransitionProcess instance;
	return &instance;
}


// 初期化処理
void TransitionProcess::Initialize() {

}


// 更新処理
void TransitionProcess::Update() {


}


// 描画処理
void TransitionProcess::Draw() {

}


// フェードイン処理
void TransitionProcess::Fade_In() {

}


// フェードアウト処理
void TransitionProcess::Fade_Out() {

}
