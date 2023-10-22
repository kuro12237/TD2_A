#include "ShamWall.h"



// èâä˙âªèàóù
void ShamWall::Initialize() {

	// è„ï”ÇÃï«
	for (int Index = 0; Index < MAX_WALL_OBJECT; Index++) {

		// è„ï”ÇÃï«
		/*Top_[Index].model = make_unique<Model>();
		Top_[Index].model->CreateFromObj("ShamWall");
		Top_[Index].model->SetColor({ 1.0f, 0.0f, 0.0f, 1.0f });
		Top_[Index].worldTansform.scale = initScale_;
		Top_[Index].worldTansform.translate = initTopTranslate_;
		initTopTranslate_.z -= 2.2f;*/


		// â∫ï”ÇÃï«
		/*Bottom_[Index].model = make_unique<Model>();
		Bottom_[Index].model->CreateFromObj("ShamWall");
		Bottom_[Index].model->SetColor({ 0.0f, 1.0f, 0.0f, 1.0f });
		Bottom_[Index].worldTansform.scale = initScale_;
		Bottom_[Index].worldTansform.translate = initBottomTranslate_;
		initBottomTranslate_.z -= 2.2f;*/


		// ç∂ï”ÇÃï«
		/*Left_[Index].model = make_unique<Model>();
		Left_[Index].model->CreateFromObj("ShamWall");
		Left_[Index].model->SetColor({ 0.0f, 0.0f, 1.0f, 1.0f });
		Left_[Index].worldTansform.scale = initScale_;
		Left_[Index].worldTansform.translate = initLeftTranslate_;
		initLeftTranslate_.x -= 2.2f;*/


		// âEï”ÇÃï«
		Right_[Index].model = make_unique<Model>();
		Right_[Index].model->CreateFromObj("ShamWall");
		Right_[Index].model->SetColor({ 1.0f, 1.0f, 0.0f, 1.0f });
		Right_[Index].worldTansform.scale = initScale_;
		Right_[Index].worldTansform.translate = initRightTranslate_;
		initRightTranslate_.x -= 2.2f;
	}
}



// çXêVèàóù
void ShamWall::Update() {

	for (int Index = 0; Index < MAX_WALL_OBJECT; Index++) {
		//Top_[Index].worldTansform.UpdateMatrix();
		//Bottom_[Index].worldTansform.UpdateMatrix();
		//Left_[Index].worldTansform.UpdateMatrix();
		Right_[Index].worldTansform.UpdateMatrix();
		Right_[Index].model->SetColor(color);
	}
	ImGui::Begin("color");
	ImGui::DragFloat4("color", &color.x, 0.05f);
	ImGui::End();
}



// ï`âÊèàóù
void ShamWall::Draw(ViewProjection view) {

	for (int Index = 0; Index < MAX_WALL_OBJECT; Index++) {
		//Top_[Index].model->Draw(Top_[Index].worldTansform, view);
		//Bottom_[Index].model->Draw(Bottom_[Index].worldTansform, view);
		//Left_[Index].model->Draw(Left_[Index].worldTansform, view);
		Right_[Index].model->Draw(Right_[Index].worldTansform, view);
	}
}