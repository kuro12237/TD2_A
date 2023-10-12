#include"PhysicsFanc.h"

Vector3 PhysicsFanc::Repulsiveforce(float k, Vector3 v1, Vector3 v2) {

	float F; // ��
	Vector3 e; // �P�ʃx�N�g��
	Vector3 velo; // ��������������
	float d = sqrt((v1.x - v2.x)*(v1.x - v2.x)+(v1.y - v2.y)*(v1.y - v2.y)+(v1.z - v2.z)*(v1.z - v2.z)); // ���S�̋���
	float x = (1.0f - d);
	F = k * x;
	if (F >= 0) {
		e = VectorTransform::Multiply(VectorTransform::Subtruct(v1, v2), 1.0f / d);	// �P�ʃx�N�g�������߂�
		velo = VectorTransform::Multiply(e, F);  // �����ɗ͂���������
	}

	return velo;
}