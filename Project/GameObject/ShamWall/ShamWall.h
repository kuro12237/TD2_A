#pragma once

#include"Model.h"
#include"WorldTransform.h"



struct WallElemnt {
	unique_ptr<Model>model = nullptr;
	WorldTransform worldTansform{};
};


enum ColorState {
	AddRed,
	SubRed,
	AddGreen,
	SubGreen,
	AddBlue,
	SubBlue,
};



/// <summary>
/// ShamWall�N���X
/// </summary>
class ShamWall {

public:

	ShamWall() {};
	~ShamWall() {};

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
	void Draw(ViewProjection view);

	/// <summary>
	/// RGB�����߂�
	/// </summary>
	Vector3 CalcRGB(Vector4 color);
	
	/// <summary>
	/// RGBA�����߂�
	/// </summary>
	Vector4 CalcRGBA(Vector3 color);


#pragma region Get

	ColorState GetColorState() { return state_; }

#pragma endregion

private:

	WallElemnt shamWall_;


	// �����X�P�[��
	Vector3 initScale_ = { 1.07f, 2.0f, 1.07f };

	// �J���[
	Vector4 modelColor_ = { 1.0f, 0.0f, 0.0f, 1.0f };

	Vector3 color_;

	ColorState state_ = AddGreen;
};