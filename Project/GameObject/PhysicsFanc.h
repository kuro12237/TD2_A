#pragma once
#include"Vector3.h"
#include"WorldTransform.h"
#include"VectorTransform.h"

class PhysicsFanc {
public:
	// ベクトル分解
	//void VelocityDecomposition(Vector3 velo, float angle); // velo = 自機の速度, angle = 自機と相手の角度

	static Vector3 VelocityDecomposition(float k, Vector3 v1, Vector3 v2);
};