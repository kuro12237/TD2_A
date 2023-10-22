#include "Skydome.h"



// 初期化処理
void Skydome::Initialize() {

	skydome_.model = make_unique<Model>();
	skydome_.model->CreateFromObj("Skydome");
	skydome_.model->SetColor(modelColor_);
	skydome_.worldTansform.Initialize();
	skydome_.worldTansform.scale = { initScale_, initScale_, initScale_ };
}



// 更新処理
void Skydome::Update() {

	skydome_.worldTansform.UpdateMatrix();
	skydome_.worldTansform.scale = { initScale_,initScale_, initScale_ };


	ImGui::Begin("Skydome");

	ImGui::DragFloat("scale", &initScale_, 0.05f);
	ImGui::DragFloat3("rotate", &skydome_.worldTansform.rotation.x, 0.05f);
	ImGui::DragFloat3("translate", &skydome_.worldTansform.translate.x, 0.05f);
	ImGui::End();
}



// 描画処理
void Skydome::Draw(ViewProjection view) {

	skydome_.model->Draw(skydome_.worldTansform, view);
}