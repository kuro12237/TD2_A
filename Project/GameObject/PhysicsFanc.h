#pragma once
#include"Vector3.h"
#include"WorldTransform.h"
#include"VectorTransform.h"

class PhysicsFanc {
public:
	// �x�N�g������
	//void VelocityDecomposition(Vector3 velo, float angle); // velo = ���@�̑��x, angle = ���@�Ƒ���̊p�x

	static Vector3 VelocityDecomposition(float k, Vector3 v1, Vector3 v2);
};