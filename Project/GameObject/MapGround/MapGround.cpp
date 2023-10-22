#include "MapGround.h"



// ����������
void MapGround::Initialize() {

	ground_.model = make_unique<Model>();
	ground_.model->CreateFromObj("MapGround");
	ground_.model->SetColor(modelColor_);
	ground_.worldTansform.Initialize();
}



// �X�V����
void MapGround::Updatea() {

	ground_.worldTansform.UpdateMatrix();
}



// �`�揈��
void MapGround::Draw(ViewProjection view) {

	ground_.model->Draw(ground_.worldTansform, view);
}
