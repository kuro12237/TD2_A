#pragma once

class TransitionProcess {

public: // �����o�֐�

	/// <summary>
	/// TransitionProcess�N���X�̃C���X�^���X�擾
	/// </summary>
	static TransitionProcess* GetInstance();

	/// <summary>
	/// �����������v
	/// </summary>
	static void Initialize();

	/// <summary>
	/// �X�V����
	/// </summary>
	static void Update();

	/// <summary>
	/// �t�F�[�h�C������
	/// </summary>
	static void Fade_In();

	/// <summary>
	/// �t�F�[�h�A�E�g����
	/// </summary>
	static void Fade_Out();

	/// <summary>
	/// �`�揈��
	/// </summary>
	static void Draw();


private: // �����o�֐�



private: // �����o�ϐ�


};