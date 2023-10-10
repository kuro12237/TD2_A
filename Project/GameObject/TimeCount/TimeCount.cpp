#include "TimeCount.h"



// ����������
void TimeCount::Initialize() {

	// �e�N�X�`���̓ǂݍ���
	numTextureHD_[0]  = TextureManager::LoadTexture("Resources/uvChecker.png");
	numTextureHD_[1]  = 0; //TextureManager::LoadTexture("Resources/Number/1.png");
	numTextureHD_[2]  = 0; //TextureManager::LoadTexture("Resources/Number/2.png");
	numTextureHD_[3]  = 0; //TextureManager::LoadTexture("Resources/Number/3.png");
	numTextureHD_[4]  = 0; //TextureManager::LoadTexture("Resources/Number/4.png");
	numTextureHD_[5]  = 0; //TextureManager::LoadTexture("Resources/Number/5.png");
	numTextureHD_[6]  = 0; //TextureManager::LoadTexture("Resources/Number/6.png");
	numTextureHD_[7]  = 0; //TextureManager::LoadTexture("Resources/Number/7.png");
	numTextureHD_[8]  = 0; //TextureManager::LoadTexture("Resources/Number/8.png");
	numTextureHD_[9]  = 0; //TextureManager::LoadTexture("Resources/Number/9.png");


	// �X�v���C�g
	for (int index = 0; index < 1; index++) {
		sprite_[index] = make_unique<Sprite>();
		position_[index] = { 10.0f, 10.0f };
		sprite_[index]->Initialize(new SpriteBoxState, position_[index], { 1.0f, 1.0f });
		sprite_[index]->SetColor(textureColor_);
		//sprite_[index]->SetTexHandle(numTextureHD_[0]);
	}

	// ���[���h�g�����X�t�H�[��
	for (int index = 0; index < 3; index++) {
		worldTransform_[index].translate = { position_[index].x, position_[index].y , 0.0f };
		worldTransform_[index].Initialize();
	}
	
	// �������Ԃ�ݒ肷��
	nowLimitTime_ = kSetLimitTime_;
}



// �X�V����
void TimeCount::Update() {

	// �������Ԃ̊e�ʂ̒l�����߂�
	CalcTimerPlace(nowLimitTime_);

	// �e�ʂɍ������e�N�X�`����ݒ肷��
	SetNumberTexture();

	// �������Ԃ̉����Z����
	AddTimeCount();



}



// ���Ԃ̒ǉ�����
void TimeCount::AddTimeCount() {

	// �L�[�Ń^�C���ω�
	if (Input::GetInstance()->PushKeyPressed(DIK_1)) {
		nowLimitTime_ = nowLimitTime_ + 10;
	}
	else if (Input::GetInstance()->PushKeyPressed(DIK_2)) {
		nowLimitTime_ = nowLimitTime_ + 10;
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
	if (Input::GetInstance()->PushKeyPressed(DIK_SPACE)) {
		sprite_[0]->SetTexHandle(numTextureHD_[eachTime_[9]]);
	}

}



// �`�揈��
void TimeCount::Draw() {

	for (int index = 0; index < 2; index ++) {
		sprite_[index]->Draw(worldTransform_[index]);
	}
}
