#pragma once
#include"Vector3.h"
#include"WorldTransform.h"
#include"VectorTransform.h"

class PhysicsFunc {
public:
	 // ”½”­—ÍŒvŽZ
	static Vector3 Repulsiveforce(float k, Vector3 v1, Vector3 v2);

	static tuple<Vector3, Vector3> Decomposition(Vector3& v1, float angle1);

	static tuple<Vector3, Vector3> SpeedComposition(Vector3& v1,Vector3& v2, float angle1, float angle2);
};