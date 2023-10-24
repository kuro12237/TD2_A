#include"CollisionManager.h"

void CollisionManager::CheckAllCollision()
{
	std::list<Collider*>::iterator itrA = colliders_.begin();

	for (; itrA != colliders_.end(); ++itrA) {

		Collider* colliderA = *itrA;

		std::list<Collider*>::iterator itrB = itrA;
		itrB++;
		for (; itrB != colliders_.end(); ++itrB) {
			Collider* colliderB = *itrB;
			//当たり判定処理
			CheckCollisionPair(colliderA, colliderB);
		}
	}
}

void CollisionManager::CheckCollisionPair(Collider* cA, Collider* cB) {

	//フィルタリング
	if ((cA->GetCollosionAttribute() & cB->GetCollisionMask()) == 0 ||
		(cA->GetCollisionMask() & cB->GetCollosionAttribute()) == 0) {
		return;
	}
	//当たり判定の計算開始
	Vector3 cApos = cA->GetWorldPosition();
	Vector3 cBpos = cB->GetWorldPosition();
	Vector3 cAVelo = cA->GetVelocity();
	Vector3 cBVelo = cB->GetVelocity();

	float cAradious = cA->GetRadious();
	float cBradious = cB->GetRadious();

	if (CheckBallCollosion(cApos, cAradious,cAVelo, cBpos, cBradious, cBVelo)) {
		cA->OnCollision();
		cB->OnCollision();
	}
}


bool CollisionManager::CheckBallCollosion(Vector3 v1, float v1Radious,Vector3 velo, Vector3 v2, float v2Radious, Vector3 velo2) {

	//当たってる時のフレームを求める
	float a = (velo.x * velo.x) - (2.0f * (velo.x * velo2.x)) + (velo2.x * velo2.x) +
		(velo.z * velo.z) - (2.0f * (velo.z * velo2.z)) + (velo2.z * velo2.z);

	float b = (2.0f * (v1.x * velo.x)) - (2.0f * (v1.x * velo2.x)) - (2.0f * (velo.x * v2.x)) +
		(2.0f * (v2.x * velo2.x)) + (2.0f * (v1.z * velo.z)) - (2.0f * (v1.z * velo2.z))
		- (2.0f * (velo.z * v2.z)) + (2.0f * (v2.z * velo2.z));

	float c = (v1.x * v1.x) - (2.0f * (v1.x * v2.x)) + (v2.x * v2.x) + (v1.z * v1.z) - (2.0f * (v1.z * v2.z)) +
		(v2.z * v2.z) - ((v1Radious + v2Radious) * (v1Radious + v2Radious));

	float d = (b * b) - 4.0f * a * c;

	bool Flag = false;

	if (d <= 0) {
	
	}
	else {

		d = sqrt(d);

		float f0 = (-b - d) / (2.0f * a); // 当たる瞬間のf
		//float f1 = (b + d) / (2.0f * a); // 離れる瞬間のf

		velo.x = velo.x * f0;
		velo.y = velo.y * f0;
		velo.z = velo.z * f0;

		velo2.x = velo2.x * f0;
		velo2.y = velo2.y * f0;
		velo2.z = velo2.z * f0;

		float x = (v2.x - v1.x);
		float y = (v2.y - v1.y);
		float z = (v2.z - v1.z);

		float resultPos = (x * x) + (y * y) + (z * z);

		float resultRadious = v1Radious + v2Radious;


		if (resultPos <= (resultRadious * resultRadious)) {

			Flag = true;

		}

	}

	return Flag;
}


