#include "Skydome.h"



// ����������
void Skydome::Initialize() {

	skydome_.model = make_unique<Model>();
	skydome_.model->CreateFromObj("Skydome");
	skydome_.model->SetColor(modelColor_);
	skydome_.worldTansform.Initialize();
}