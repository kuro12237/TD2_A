#include "Skydome.h"



// ‰Šú‰»ˆ—
void Skydome::Initialize() {

	skydome_.model = make_unique<Model>();
	skydome_.model->CreateFromObj("Skydome");
	skydome_.model->SetColor(modelColor_);
	skydome_.worldTansform.Initialize();
	skydome_.worldTansform.scale = { initScale_, initScale_, initScale_ };
}



// XVˆ—
void Skydome::Update() {

	skydome_.worldTansform.UpdateMatrix();
	skydome_.worldTansform.scale = { initScale_,initScale_, initScale_ };
}



// •`‰æˆ—
void Skydome::Draw(ViewProjection view) {

	skydome_.model->Draw(skydome_.worldTansform, view);
}