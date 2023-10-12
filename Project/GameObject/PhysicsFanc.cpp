#include"PhysicsFanc.h"

Vector3 PhysicsFanc::Repulsiveforce(float k, Vector3 v1, Vector3 v2) {

	float F; // 力
	Vector3 e; // 単位ベクトル
	Vector3 velo{}; // 向きを持った力
	float d = sqrt((v1.x - v2.x)*(v1.x - v2.x)+(v1.y - v2.y)*(v1.y - v2.y)+(v1.z - v2.z)*(v1.z - v2.z)); // 中心の距離
	float x = (1.0f - d);
	F = k * x;
	//if (F >= 0) {
		e = VectorTransform::Multiply(VectorTransform::Subtruct(v1, v2), 1.0f / d);	// 単位ベクトルを求める
		velo = VectorTransform::Multiply(e, F);  // 向きに力を持たせる
		return velo;
	//}

	//return velo;
}