#include "ShamWall.h"



// ‰Šú‰»ˆ—
void ShamWall::Initialize() {

	shamWall_.model = make_unique<Model>();
	shamWall_.model->CreateFromObj("ShamWall");
	shamWall_.model->SetColor(modelColor_);
	shamWall_.worldTansform.Initialize();
	shamWall_.worldTansform.scale = initScale_;

	state_ = AddGreen;
	color_ = CalcRGB(shamWall_.model->GetColor());
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
	ImGui::DragFloat3("RGB", &color_.x, 0.01f);
	ImGui::End();
}



// •`‰æˆ—
void ShamWall::Draw(ViewProjection view) {

	shamWall_.model->Draw(shamWall_.worldTansform, view);
}



// RGB‚ğ‹‚ß‚é
Vector3 ShamWall::CalcRGB(Vector4 color) {

	Vector3 result = {
		result.x = color.x / 256.0f,
		result.y = color.y / 256.0f,
		result.z = color.z / 256.0f,
	};

	return result;
}



// RGBA‚ğ‹‚ß‚é
Vector4 ShamWall::CalcRGBA(Vector3 color) {

	Vector4 result = {
		result.x = color.x * 256.0f,
		result.y = color.y * 256.0f,
		result.z = color.z * 256.0f,
		result.w = 1.0f,
	};

	return result;
}