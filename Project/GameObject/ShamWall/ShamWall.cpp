#include "ShamWall.h"

// ����������
void ShamWall::Initialize() {

	shamWall_.model = make_unique<Model>();
	shamWall_.model->CreateFromObj("ShamWall");
	shamWall_.model->SetColor(modelColor_);
	shamWall_.worldTansform.Initialize();
	shamWall_.worldTansform.scale = initScale_;
}

// �X�V����
void ShamWall::Update() {

	shamWall_.worldTansform.UpdateMatrix();
	shamWall_.model->SetColor(modelColor_);
}

// �`�揈��
void ShamWall::Draw(ViewProjection view) {

	shamWall_.model->Draw(shamWall_.worldTansform, view);
}

