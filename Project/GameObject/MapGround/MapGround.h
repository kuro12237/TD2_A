#pragma once

#include"Model.h"
#include"WorldTransform.h"


struct MapGroundElement {
	unique_ptr<Model>model = nullptr;
	WorldTransform worldTansform{};
};


/// <summary>
/// �}�b�v�̏��N���X
/// </summary>
class MapGround {

public:

	/// <summary>
	/// ����������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Updatea();

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw(ViewProjection view);

private:

	MapGroundElement ground_;

	Vector4 modelColor_ = { 1.0f, 1.0f, 1.0f, 1.0f };

};