#include "GameObject/TransitionProcess/TransitionProcess.h"


// FadeProcess�N���X�̃C���X�^���X�擾
TransitionProcess* TransitionProcess::GetInstance() {
	static TransitionProcess instance;
	return &instance;
}


// ����������
void TransitionProcess::Initialize() {

}


// �X�V����
void TransitionProcess::Update() {


}


// �`�揈��
void TransitionProcess::Draw() {

}


// �t�F�[�h�C������
void TransitionProcess::Fade_In() {

}


// �t�F�[�h�A�E�g����
void TransitionProcess::Fade_Out() {

}
