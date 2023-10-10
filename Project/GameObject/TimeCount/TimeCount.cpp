#include "TimeCount.h"



// ����������
void TimeCount::Initialize() {

	// �e�N�X�`���̓ǂݍ���
	numTextureHD_[0] = TextureManager::LoadTexture("Resources/Number/0.png");
	numTextureHD_[1] = TextureManager::LoadTexture("Resources/Number/1.png");
	numTextureHD_[2] = TextureManager::LoadTexture("Resources/Number/2.png");
	numTextureHD_[3] = TextureManager::LoadTexture("Resources/Number/3.png");
	numTextureHD_[4] = TextureManager::LoadTexture("Resources/Number/4.png");
	numTextureHD_[5] = TextureManager::LoadTexture("Resources/Number/5.png");
	numTextureHD_[6] = TextureManager::LoadTexture("Resources/Number/6.png");
	numTextureHD_[7] = TextureManager::LoadTexture("Resources/Number/7.png");
	numTextureHD_[8] = TextureManager::LoadTexture("Resources/Number/8.png");
	numTextureHD_[9] = TextureManager::LoadTexture("Resources/Number/9.png");

	for (int index = 0; index < 1; index++) {
		sprite_[index] = make_unique<Sprite>();
		position_[index] = { 540.0f + (50.0f * index), 10.0f };
		sprite_[index]->Initialize(new SpriteBoxState, position_[index], { 100.0f, 100.0f });
		sprite_[index]->SetColor(textureColor_);
		sprite_[index]->SetTexHandle(numTextureHD_[0]);
	}

	// ���[���h�g�����X�t�H�[��
	for (int index = 0; index < 3; index++) {
		worldTransform_[index].Initialize();
		worldTransform_[index].translate = { position_[index].x, position_[index].y, 0.0f };
	}
	
	// �������Ԃ�ݒ肷��
	nowLimitTime_ = kSetLimitTime_;
	frame_ = 0;
}



// �X�V����
void TimeCount::Update() {

	// �������Ԃ̌��Z����
	SubtructTimer();

	// �������Ԃ̉��Z����
	AddTimeCount();

	// �������Ԃ̊e�ʂ̒l�����߂�
	CalcTimerPlace(nowLimitTime_);

	// �e�ʂɍ������e�N�X�`����ݒ肷��
	SetNumberTexture();


#ifdef _DEBUG

	ImGui::Begin("TimeCount");
	ImGui::Text("frame_ = %d", frame_);
	ImGui::Text("nowTimer = %d", nowLimitTime_);
	ImGui::Text("onehundPlace = %d", eachTime_[0]);
	ImGui::Text("    tenPlace = %d", eachTime_[1]);
	ImGui::Text("    onePlace = %d", eachTime_[2]);
	ImGui::DragFloat3("trans[0]", &worldTransform_[0].translate.x, 1.0f);
	ImGui::DragFloat3("trans[1]", &worldTransform_[1].translate.x, 1.0f);
	ImGui::DragFloat3("trans[2]", &worldTransform_[2].translate.x, 1.0f);
	ImGui::End();

#endif // DEBUG
}



// �^�C�}�[�����炷
void TimeCount::SubtructTimer() {

	// �t���[���𑝂₷
	frame_++;

	// 60�t���[��
	if (frame_ >= 60) {

		// �^�C�}�[��1�b���炷
		nowLimitTime_ = nowLimitTime_ - 1;
		// �t���[����0�ɖ߂�
		frame_ = 0;
	}
}



// ���Ԃ̒ǉ�����
void TimeCount::AddTimeCount() {

	// �L�[�Ń^�C���ω�
	// 1�L�[ = +10s
	// 2�L�[ = +20s
	// 3�L�[ = +30s
	// �㉺�L�[ = +1s
	if (Input::GetInstance()->PushKeyPressed(DIK_1)) {
		nowLimitTime_ = nowLimitTime_ + 10;
	}
	else if (Input::GetInstance()->PushKeyPressed(DIK_2)) {
		nowLimitTime_ = nowLimitTime_ + 20;
	}
	else if (Input::GetInstance()->PushKeyPressed(DIK_3)) {
		nowLimitTime_ = nowLimitTime_ + 30;
	}
	if (Input::GetInstance()->PushKey(DIK_UP)) {
		nowLimitTime_ += 1;
	}
	else if (Input::GetInstance()->PushKey(DIK_DOWN)) {
		nowLimitTime_ -= 1;
	}
}



// �������Ԃ̊e�ʂ����߂�
void TimeCount::CalcTimerPlace(uint32_t nowTimer) {

	// 100�̈�
	eachTime_[0] = (nowTimer % 1000) / 100;
	// 10�̈�
	eachTime_[1] = (nowTimer % 100) / 10;
	// 1�̈�
	eachTime_[2] = (nowTimer % 10) / 1;
}



// �e�ʂɍ������e�N�X�`����ݒ肷��
void TimeCount::SetNumberTexture() {

	// �e�ʂ̒l�ɂ������e�N�X�`����ݒ肷��
	sprite_[0]->SetTexHandle(numTextureHD_[eachTime_[0]]);
	sprite_[1]->SetTexHandle(numTextureHD_[eachTime_[1]]);
	sprite_[2]->SetTexHandle(numTextureHD_[eachTime_[2]]);
}



// �`�揈��
void TimeCount::Draw() {

	for (int index = 0; index < 3; index++) {
		sprite_[index]->Draw(worldTransform_[index]);

	}
}


