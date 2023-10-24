#pragma once

#include"Model.h"
#include"WorldTransform.h"
#include "GameObject/ShamWall/State/WallColorState.h"
#include "GameObject/ShamWall/State/CalcRed.h"
#include "GameObject/ShamWall/State/CalcGreen.h"
#include "GameObject/ShamWall/State/CalcBlue.h"



struct WallElemnt {
	unique_ptr<Model>model = nullptr;
	WorldTransform worldTansform{};
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

	/// <summary>
	/// �J���[�̌v�Z��ύX����
	/// </summary>
	void ChangeWallColorState(WallColorState* newState);


	/// <summary>
	/// �O���f�[�V�������鏈��
	/// </summary>
	Vector4 CalculateColorGradient(float time);


#pragma region Get

	Vector3 getRGBColor() { return color_; }
	ColorState GetColorState() { return colorState_; }

#pragma endregion

#pragma region Set

	void SetRGBColorR(float color) { color_.x = color; }
	void SetRGBColorG(float color) { color_.y = color; }
	void SetRGBColorB(float color) { color_.z = color; }
	void SetColorState(ColorState colorState) { colorState_ = colorState; }

#pragma endregion

private:

	WallElemnt shamWall_;


	// �����X�P�[��
	Vector3 initScale_ = { 1.0f, 1.0f, 1.0f };
	Vector3 initTranslate_ = { 0.015f, -0.5f, 0.015f };

	// RGBA�J���[
	Vector4 modelColor_ = { 1.0f, 0.0f, 0.0f, 1.0f };

	// RGB�J���[
	Vector3 color_;

	WallColorState* calcColorState_;


	ColorState colorState_ = AddGreen;
};