#include "Skydome.h"



// ����������
void Skydome::Initialize() {

	skydome_.model = make_unique<Model>();
	skydome_.model->CreateFromObj("Skydome");
	skydome_.model->SetColor(modelColor_);
	skydome_.worldTansform.Initialize();
	skydome_.worldTansform.scale = { initScale_, initScale_, initScale_ };
}



// �X�V����
void Skydome::Update() {

	skydome_.worldTansform.UpdateMatrix();
	skydome_.worldTansform.scale = { initScale_,initScale_, initScale_ };

	skydome_.worldTansform.rotation.x -= 0.0005f;
	skydome_.worldTansform.rotation.y += 0.0005f;
	skydome_.worldTansform.rotation.z += 0.0005f;

	float time = float(clock() / 1000.0);
	skydome_.model->SetColor(CalculateColorGradient(time));
}



// �`�揈��
void Skydome::Draw(ViewProjection view) {

	skydome_.model->Draw(skydome_.worldTansform, view);
}




// �O���f�[�V�������鏈��
Vector4 Skydome::CalculateColorGradient(float time) {
	Vector4 color{};
	color.x = 0.5f + 0.5f * std::sin(0.7f * time);
	color.y = 0.5f + 0.5f * std::sin(0.7f * time + 2.0f);
	color.z = 0.5f + 0.5f * std::sin(0.7f * time + 4.0f);
	color.w = 1.0f;
	return color;
}