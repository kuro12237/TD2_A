#include"PhysicsFunc.h"

Vector3 PhysicsFunc::Repulsiveforce(float k, Vector3 v1, Vector3 v2) {

	float F; // 力
	Vector3 e; // 単位ベクトル
	Vector3 velo{}; // 向きを持った力
	float d = sqrt((v1.x - v2.x)*(v1.x - v2.x)+(v1.y - v2.y)*(v1.y - v2.y)+(v1.z - v2.z)*(v1.z - v2.z)); // 中心の距離
	float x = (1.0f - d);
	F = k * x;
	e = VectorTransform::Multiply(VectorTransform::Subtruct(v1, v2), 1.0f / d);	// 単位ベクトルを求める
	velo = VectorTransform::Multiply(e, F);  // 向きに力を持たせる

	return velo;
}

tuple<Vector3, Vector3> PhysicsFunc::Decomposition(Vector3& v1, float angle) {

	float initialVelo = sqrt(VectorTransform::Dot(v1,v1)); // 速度の合成
	float angle2 = atan2(v1.z, v1.x); // 進行方向
	float angleSA = angle2 - angle;	// 角度の差

	float opponentVec = abs(initialVelo * std::cos(angleSA));
	float playerVec = abs(initialVelo * std::sin(angleSA));

    /*-----------------------------
		衝突後の相手球の速度計算
	------------------------------*/
	Vector3 opponentVelo;

	opponentVelo.x = opponentVec * std::cos(angle);
	opponentVelo.y = 0.0f;
	opponentVelo.z = opponentVec * std::sin(angle);

	/*-----------------------------
		衝突後の自球の速度計算
	------------------------------*/
	Vector3 playerVelo;

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


	return { opponentVelo, playerVelo };
}

tuple<Vector3, Vector3> PhysicsFunc::SpeedComposition(Vector3& v1,Vector3& v2, float angle1, float angle2) {

	tuple<Vector3, Vector3> Velo1 = PhysicsFunc::Decomposition(v1, angle1);
	tuple<Vector3, Vector3> Velo2 = PhysicsFunc::Decomposition(v2, angle2);

	Vector3 Velo3 = get<0>(Velo1);
	Vector3	Velo4 = get<1>(Velo1);
	Vector3 Velo5 = get<0>(Velo2);
	Vector3 Velo6 = get<1>(Velo2);

	Vector3 playerVelo = VectorTransform::Add(Velo3, Velo5);
	Vector3 opponentVelo = VectorTransform::Add(Velo4, Velo6);

	return	 { playerVelo, opponentVelo };
}