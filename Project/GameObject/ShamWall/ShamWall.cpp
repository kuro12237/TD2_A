#include "ShamWall.h"

// 初期化処理
void ShamWall::Initialize() {

	shamWall_.model = make_unique<Model>();
	shamWall_.model->CreateFromObj("ShamWall");
	shamWall_.model->SetColor(modelColor_);
	shamWall_.worldTansform.Initialize();
	shamWall_.worldTansform.scale = initScale_;
}

// 更新処理
void ShamWall::Update() {

	shamWall_.worldTansform.UpdateMatrix();
	shamWall_.model->SetColor(modelColor_);
}

// 描画処理
void ShamWall::Draw(ViewProjection view) {

	shamWall_.model->Draw(shamWall_.worldTansform, view);
}

