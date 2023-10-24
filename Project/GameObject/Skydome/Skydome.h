#pragma once

#include"Model.h"
#include"WorldTransform.h"


struct SkydomeElemnt {
	unique_ptr<Model>model = nullptr;
	WorldTransform worldTansform{};
};


/// <summary>
/// �V��
/// </summary>
class Skydome {
public:

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
	void Draw(ViewProjection viewProjection);



	/// <summary>
	/// �O���f�[�V�������鏈��
	/// </summary>
	Vector4 CalculateColorGradient(float time);



	/// <summary>
	/// RGB�����߂�
	/// </summary>
	Vector3 CalcRGB(Vector4 color);

	/// <summary>
	/// RGBA�����߂�
	/// </summary>
	Vector4 CalcRGBA(Vector3 color);


private:

	SkydomeElemnt skydome_;

	float initScale_ = 7000.0f;

	Vector4 modelColor_ = { 1.0f, 1.0f, 1.0f, 1.0f };


	// RGB�J���[
	Vector3 color_;
};