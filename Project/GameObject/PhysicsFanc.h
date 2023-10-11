#pragma once
#include"Vector3.h"
#include"WorldTransform.h"
#include"VectorTransform.h"

class PhysicsFanc {
public:
	 // ”½”­—ÍŒvŽZ
	static Vector3 Repulsiveforce(float k, Vector3 v1, Vector3 v2);
};