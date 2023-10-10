#pragma once
#include "Sprite/Sprite.h"
#include "WorldTransform.h"
#include "Graphics/TextureManager/TextureManager.h"
#include"Input.h"



/// <summary>
/// �^�C���J�E���g�N���X
/// </summary>
class TimeCount {

public:
	~TimeCount() {};
	/// <summary>
	/// ����������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw();

	/// <summary>
	/// �^�C�}�[�����炷
	/// </summary>
	void SubtructTimer();

	/// <summary>
	/// ���Ԃ̒ǉ�����
	/// </summary>
	void AddTimeCount();

	/// <summary>
	/// �������Ԃ̊e�ʂ����߂�
	/// </summary>
	void CalcTimerPlace(uint32_t nowTimer);

	/// <summary>
	/// �e�ʂɍ������e�N�X�`����ݒ肷��
	/// </summary>
	void SetNumberTexture();


private:

	// �X�v���C�g
	unique_ptr<Sprite>sprite_[3];

	// �e�N�X�`��
	uint32_t numTextureHD_[10]{};

	// �e�N�X�`���J���[
	Vector4 textureColor_ = { 1.0f, 1.0f, 1.0f, 1.0f };

	// �`����W
	Vector2 position_[3];
	WorldTransform worldTransform_[3];

	// ��������
	uint32_t nowLimitTime_;
	const uint32_t kSetLimitTime_ = 30;
	uint32_t eachTime_[3]{};
	uint32_t frame_;
};