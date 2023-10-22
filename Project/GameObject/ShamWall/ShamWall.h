#pragma once

#include"Model.h"
#include"WorldTransform.h"


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

	WallElemnt Top_{};
	WallElemnt Bottom_{};
	WallElemnt Left_{};
	WallElemnt Right_{};
};