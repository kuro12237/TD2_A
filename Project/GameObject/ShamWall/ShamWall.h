#pragma once

#include"Model.h"
#include"WorldTransform.h"
#include <list>



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

private:

	const static uint32_t MAX_WALL_OBJECT = 40;
	WallElemnt Top_[MAX_WALL_OBJECT]{};
	WallElemnt Bottom_[MAX_WALL_OBJECT]{};
	WallElemnt Left_[MAX_WALL_OBJECT]{};
	WallElemnt Right_[MAX_WALL_OBJECT]{};

	// �������W
	Vector3 initTopTranslate_ = { 33.0f, 0.0f, 40.7f };
	Vector3 initBottomTranslate_ = { -33.0f, 0.0f, 40.7f };
	Vector3 initLeftTranslate_ = { 40.7f, 0.0f, 33.0f };
	Vector3 initRightTranslate_ = { 40.7f, 0.0f, -33.0f };

	// �����X�P�[��
	Vector3 initScale_ = { 0.5f, 1.0f, 0.5f };
};