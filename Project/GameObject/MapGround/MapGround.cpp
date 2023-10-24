#include "MapGround.h"



// 初期化処理
void MapGround::Initialize() {

	ground_.model = make_unique<Model>();
	ground_.model->CreateFromObj("MapGround");
	ground_.model->SetColor(modelColor_);
	ground_.worldTansform.Initialize();
}



// 更新処理
void MapGround::Updatea() {

	ground_.worldTansform.UpdateMatrix();
}



// 描画処理
void MapGround::Draw(ViewProjection view) {

	ground_.model->Draw(ground_.worldTansform, view);
}
