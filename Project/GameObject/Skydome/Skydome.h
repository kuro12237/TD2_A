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


private:

	SkydomeElemnt skydome_;

	Vector4 modelColor_ = { 1.0f, 1.0f, 1.0f, 1.0f };
};