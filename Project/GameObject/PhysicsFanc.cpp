#include"PhysicsFanc.h"
// �x�N�g������
/*
void PhysicsFanc::VelocityDecomposition(Vector3 velo, float angle) {
	float v0; // ���x�̍���
	float v1; // �Փˌ�̑���̑��x
	float v2; // �Փˌ�̎��@�̑��x
	float angle2; // ���@�̐i�s����
	float angleSA; // �p�x�̍�
	Vector3 velocity;
    
	v0 = sqrt(velo.x * velo.x + velo.y * velo.y + velo.z * velo.z); // ���S�̋���
	angle2 = atan2(velo.x, velo.z); // ���@�̐i�s����
	angleSA = angle2 - angle; // �p�x�̍�
	v1 = std::abs(v0 * std::cos(angleSA)); // �Փˌ�̑���̑��x
	v2 = std::abs(v0 * std::sin(angleSA)); // �Փˌ�̎��@�̑��x
	velocity = {}

}*/

Vector3 PhysicsFanc::VelocityDecomposition(float k, Vector3 v1, Vector3 v2) {

	float F;
	Vector3 e;
	Vector3 V;
	float d = sqrt((v1.x - v2.x)*(v1.x - v2.x)+(v1.y - v2.y)*(v1.y - v2.y)+(v1.z - v2.z)*(v1.z - v2.z)); // ���S�̋���
	F = k * (1.0f - d);
	e = VectorTransform::Multiply(VectorTransform::Subtruct(v1, v2),1.0f/d);
	V = VectorTransform::Multiply(e, F);

	return V;
}