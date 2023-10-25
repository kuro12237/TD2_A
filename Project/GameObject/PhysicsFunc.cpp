#include"PhysicsFunc.h"

Vector3 PhysicsFunc::Repulsiveforce(float k, Vector3 v1, Vector3 v2) {

	float F; // ��
	Vector3 e; // �P�ʃx�N�g��
	Vector3 velo{}; // ��������������
	float d = sqrt((v1.x - v2.x)*(v1.x - v2.x)+(v1.y - v2.y)*(v1.y - v2.y)+(v1.z - v2.z)*(v1.z - v2.z)); // ���S�̋���
	float x = (1.0f - d);
	F = k * x;
	e = VectorTransform::Multiply(VectorTransform::Subtruct(v1, v2), 1.0f / d);	// �P�ʃx�N�g�������߂�
	velo = VectorTransform::Multiply(e, F);  // �����ɗ͂���������

	return velo;
}

tuple<Vector3, Vector3> PhysicsFunc::Decomposition(Vector3& v1, float angle) {

	float initialVelo = sqrt((v1.x * v1.x) + (v1.z * v1.z)); // ���x�̍���
	float angle2 = atan2(v1.z, v1.x); // �i�s����
	float angleSA = angle2 - angle;	// �p�x�̍�

	float opponentVec = abs(initialVelo * std::cos(angleSA));
	float playerVec = abs(initialVelo * std::sin(angleSA));

    /*-----------------------------
		�Փˌ�̑��苅�̑��x�v�Z
	------------------------------*/
	Vector3 opponentVelo;

	opponentVelo.x = opponentVec * std::cos(angle);
	opponentVelo.y = 0.0f;
	opponentVelo.z = opponentVec * std::sin(angle);

	/*-----------------------------
		�Փˌ�̎����̑��x�v�Z
	------------------------------*/
	Vector3 playerVelo;

	if (initialVelo == 0.0f) {
		// �[�������h��
		playerVelo = { 0.0f, 0.0f, 0.0f };
	}
	else {
		if (std::sin(angleSA) < 0) {
			playerVelo.x = playerVec * std::cos(angle - (float)M_PI / 2.0f);
			playerVelo.y = 0.0f;
			playerVelo.z = playerVec * std::sin(angle - (float)M_PI / 2.0f);
		}
		else {
			playerVelo.x = playerVec * std::cos(angle + (float)M_PI / 2.0f);
			playerVelo.y = 0.0f;
			playerVelo.z = playerVec * std::sin(angle + (float)M_PI / 2.0f);
		}
	}


	return { opponentVelo, playerVelo };
}

tuple<Vector3, Vector3> PhysicsFunc::SpeedComposition(Vector3& v1,Vector3& v2, float angle1, float angle2) {

	if (angle1 == 0.0f || angle2 == 0.0f) {
		// �[������G���[����������ꍇ�A�K�؂ȏ������s��
		return { Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f) };
	}

	tuple<Vector3, Vector3> Velo1 = PhysicsFunc::Decomposition(v1, angle1);
	tuple<Vector3, Vector3> Velo2 = PhysicsFunc::Decomposition(v2, angle2);


	Vector3 Velo3 = get<0>(Velo1);
	Vector3	Velo4 = get<1>(Velo1);
	Vector3 Velo5 = get<0>(Velo2);
	Vector3 Velo6 = get<1>(Velo2);

	Vector3 playerVelo = VectorTransform::Add(Velo3, Velo5);
	Vector3 opponentVelo = VectorTransform::Add(Velo4, Velo6);
	playerVelo = VectorTransform::Normalize(playerVelo);
	opponentVelo = VectorTransform::Normalize(opponentVelo);

	return	 { playerVelo, opponentVelo };
}