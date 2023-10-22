#include "ShamWall.h"



// ‰Šú‰»ˆ—
void ShamWall::Initialize() {

	shamWall_.model = make_unique<Model>();
	shamWall_.model->CreateFromObj("ShamWall");
	shamWall_.model->SetColor(modelColor_);
	shamWall_.worldTansform.scale = initScale_;
}



// XVˆ—
void ShamWall::Update() {

	shamWall_.worldTansform.UpdateMatrix();
	shamWall_.model->SetColor(modelColor_);

	
	ImGui::Begin("shamWall");
	ImGui::DragFloat3("scale", &shamWall_.worldTansform.scale.x, 0.005f);
	ImGui::DragFloat3("rotation", &shamWall_.worldTansform.rotation.x, 0.005f);
	ImGui::DragFloat3("translate", &shamWall_.worldTansform.translate.x, 0.005f);
	ImGui::ColorEdit4("color", &modelColor_.x);
	ImGui::End();
}



// •`‰æˆ—
void ShamWall::Draw(ViewProjection view) {

	shamWall_.model->Draw(shamWall_.worldTansform, view);
}

