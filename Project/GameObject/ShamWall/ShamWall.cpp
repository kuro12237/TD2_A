#include "ShamWall.h"



// 初期化処理
void ShamWall::Initialize() {

	shamWall_.model = make_unique<Model>();
	shamWall_.model->CreateFromObj("ShamWall");
	shamWall_.model->SetColor(modelColor_);
	shamWall_.worldTansform.Initialize();
	shamWall_.worldTansform.scale = initScale_;

	state_ = AddGreen;
	color_ = CalcRGB(shamWall_.model->GetColor());
}



// 更新処理
void ShamWall::Update() {

	shamWall_.worldTansform.UpdateMatrix();
	CalcGradation(state_);
	
	ImGui::Begin("shamWall");
	ImGui::DragFloat3("scale", &shamWall_.worldTansform.scale.x, 0.005f);
	ImGui::DragFloat3("rotation", &shamWall_.worldTansform.rotation.x, 0.005f);
	ImGui::DragFloat3("translate", &shamWall_.worldTansform.translate.x, 0.005f);
	ImGui::ColorEdit4("color", &modelColor_.x);
	ImGui::DragFloat3("RGB", &color_.x, 0.01f);
	ImGui::End();
}



// 描画処理
void ShamWall::Draw(ViewProjection view) {

	shamWall_.model->Draw(shamWall_.worldTansform, view);
}



// ゲーミグのカラー計算
void ShamWall::CalcGradation(ColorState state) {

	if (state == AddRed) {
		color_.x++;

		if (color_.x >= 255) {
			state_ = SubRed;
		}
	}
	else if (state == SubRed) {
		color_.x--;
	}
	else if (state == AddGreen) {
		color_.y++;
	}
	else if (state == SubGreen) {
		color_.y--;
	}
	else if (state == AddBlue) {
		color_.z++;
	}
	else if (state == SubBlue) {
		color_.z--;
	}
}



// RGBを求める
Vector3 ShamWall::CalcRGB(Vector4 color) {

	Vector3 result = {
		result.x = color.x / 256.0f,
		result.y = color.y / 256.0f,
		result.z = color.z / 256.0f,
	};

	return result;
}



// RGBAを求める
Vector4 ShamWall::CalcRGBA(Vector3 color) {

	Vector4 result = {
		result.x = color.x * 256.0f,
		result.y = color.y * 256.0f,
		result.z = color.z * 256.0f,
		result.w = 1.0f,
	};

	return result;
}