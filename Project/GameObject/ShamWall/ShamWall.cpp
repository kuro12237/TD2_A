#include "ShamWall.h"



// èâä˙âªèàóù
void ShamWall::Initialize() {

	// è„ï”ÇÃï«
	Top_.model = make_unique<Model>();
	Top_.model->CreateFromObj("ShamWall");
	Top_.worldTansform.Initialize();
	Top_.worldTansform.scale.y = 5.0f;
	Top_.worldTansform.translate.x = 32;

	// â∫ï”ÇÃï«
	Bottom_.model = make_unique<Model>();
	Bottom_.model->CreateFromObj("ShamWall");
	Bottom_.worldTansform.Initialize();
	Bottom_.worldTansform.scale.y = 5.0f;
	Bottom_.worldTansform.translate.x = -32;

	// ç∂ï”ÇÃï«
	Left_.model = make_unique<Model>();
	Left_.model->CreateFromObj("ShamWall");
	Left_.worldTansform.Initialize();
	Left_.worldTansform.scale.y = 5.0f;
	Left_.worldTansform.translate.z = 32;

	// âEï”ÇÃï«
	Right_.model = make_unique<Model>();
	Right_.model->CreateFromObj("ShamWall");
	Right_.worldTansform.Initialize();
	Right_.worldTansform.scale.y = 5.0f;
	Right_.worldTansform.translate.z = -32;
}



// çXêVèàóù
void ShamWall::Update() {

	Top_.worldTansform.UpdateMatrix();
	Bottom_.worldTansform.UpdateMatrix();
	Left_.worldTansform.UpdateMatrix();
	Right_.worldTansform.UpdateMatrix();

}



// ï`âÊèàóù
void ShamWall::Draw(ViewProjection view) {

	Top_.model->Draw(Top_.worldTansform, view);
	Bottom_.model->Draw(Bottom_.worldTansform, view);
	Left_.model->Draw(Left_.worldTansform, view);
	Right_.model->Draw(Right_.worldTansform, view);
}