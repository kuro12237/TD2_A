#include"PhysicsFanc.h"
// ベクトル分解
/*
void PhysicsFanc::VelocityDecomposition(Vector3 velo, float angle) {
	float v0; // 速度の合成
	float v1; // 衝突後の相手の速度
	float v2; // 衝突後の自機の速度
	float angle2; // 自機の進行方向
	float angleSA; // 角度の差
	Vector3 velocity;
    
	v0 = sqrt(velo.x * velo.x + velo.y * velo.y + velo.z * velo.z); // 中心の距離
	angle2 = atan2(velo.x, velo.z); // 自機の進行方向
	angleSA = angle2 - angle; // 角度の差
	v1 = std::abs(v0 * std::cos(angleSA)); // 衝突後の相手の速度
	v2 = std::abs(v0 * std::sin(angleSA)); // 衝突後の自機の速度
	velocity = {}

}*/

Vector3 PhysicsFanc::VelocityDecomposition(float k, Vector3 v1, Vector3 v2) {

	float F;
	Vector3 e;
	Vector3 V;
	float d = sqrt((v1.x - v2.x)*(v1.x - v2.x)+(v1.y - v2.y)*(v1.y - v2.y)+(v1.z - v2.z)*(v1.z - v2.z)); // 中心の距離
	F = k * (1.0f - d);
	e = VectorTransform::Multiply(VectorTransform::Subtruct(v1, v2),1.0f/d);
	V = VectorTransform::Multiply(e, F);

	return V;
}