#include "ShamWall.h"

// 初期化処理
void ShamWall::Initialize() {

	shamWall_.model = make_unique<Model>();
	shamWall_.model->CreateFromObj("ShamWall");
	shamWall_.model->SetColor(modelColor_);
	shamWall_.worldTansform.Initialize();
	shamWall_.worldTansform.scale = initScale_;
	shamWall_.worldTansform.translate = initTranslate_;

	color_ = CalcRGB(shamWall_.model->GetColor());

	calcColorState_ = new CalcGreen();
}

// 更新処理
void ShamWall::Update() {

	shamWall_.worldTansform.UpdateMatrix();
	

	calcColorState_->CalcColor(this);

	shamWall_.model->SetColor(CalcRGBA(color_));

	
#ifdef _DEBUG

	/*ImGui::Begin("shamWall");
	ImGui::DragFloat3("scale", &shamWall_.worldTansform.scale.x, 0.005f);
	ImGui::DragFloat3("rotation", &shamWall_.worldTansform.rotation.x, 0.005f);
	ImGui::DragFloat3("translate", &shamWall_.worldTansform.translate.x, 0.005f);
	ImGui::ColorEdit4("color", &modelColor_.x);
	ImGui::DragFloat3("RGB", &color_.x, 0.01f);
	ImGui::End();*/

#endif // _DEBUG

}

// 描画処理
void ShamWall::Draw(ViewProjection view) {

	shamWall_.model->Draw(shamWall_.worldTansform, view);
}



/// <summary>
/// カラーの計算を変更する
/// </summary>
void ShamWall::ChangeWallColorState(WallColorState* newState) {
	delete calcColorState_;
	calcColorState_ = newState;
}



// RGBを求める
Vector3 ShamWall::CalcRGB(Vector4 color) {

	Vector3 result = {
		result.x = color.x * 255.0f,
		result.y = color.y * 255.0f,
		result.z = color.z * 255.0f,
	};

	return result;
}



// RGBAを求める
Vector4 ShamWall::CalcRGBA(Vector3 color) {

	Vector4 result = {
		result.x = color.x / 255.0f,
		result.y = color.y / 255.0f,
		result.z = color.z / 255.0f,
		result.w = 1.0f,
	};

	return result;
}


// グラデーションする処理
Vector4 ShamWall::CalculateColorGradient(float time) {
	Vector4 color{};
	color.x = 0.5f + 0.5f * std::sin(0.7f * time);
	color.y = 0.5f + 0.5f * std::sin(0.7f * time + 2.0f);
	color.z = 0.5f + 0.5f * std::sin(0.7f * time + 4.0f);
	color.w = 1.0f;
	return color;
}