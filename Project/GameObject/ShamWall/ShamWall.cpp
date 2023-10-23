#include "ShamWall.h"

// ‰Šú‰»ˆ—
void ShamWall::Initialize() {

	shamWall_.model = make_unique<Model>();
	shamWall_.model->CreateFromObj("ShamWall");
	shamWall_.model->SetColor(modelColor_);
	shamWall_.worldTansform.Initialize();
	shamWall_.worldTansform.scale = initScale_;
}

// XVˆ—
void ShamWall::Update() {

	shamWall_.worldTansform.UpdateMatrix();
	shamWall_.model->SetColor(modelColor_);
}

// •`‰æˆ—
void ShamWall::Draw(ViewProjection view) {

	shamWall_.model->Draw(shamWall_.worldTansform, view);
}

