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

	float cAradious = cA->GetRadious();
	float cBradious = cB->GetRadious();

	if (CheckBallCollosion(cApos, cAradious, cBpos, cBradious)) {
		CheckInterpolation(cApos, cBpos);
		cA->SetNamingLerp(cApos);
		cB->SetNamingLerp(cBpos);
		cA->OnCollision();
		cB->OnCollision();
	}
}


bool CollisionManager::CheckBallCollosion(Vector3 v1, float v1Radious, Vector3 v2, float v2Radious) {
	float x = (v2.x - v1.x);
	float y = (v2.y - v1.y);
	float z = (v2.z - v1.z);

	float resultPos = (x * x) + (y * y) + (z * z);

	float resultRadious = v1Radious + v2Radious;

	bool Flag = false;

	

	if (resultPos <= (resultRadious * resultRadious)) {
		
		Flag = true;
	}

	return Flag;
}

void CollisionManager::CheckInterpolation(Vector3& v1, Vector3& v2){
	float vx = (v1.x - v2.x);
	float vy = (v1.y - v2.y);
	float vz = (v1.z - v2.z);
	float len = sqrt(vx * vx + vy * vy + vz * vz);
	float radius = 1.0f;
	float dist = radius*2  - len;
	
	if (len > 0) {
		len = 1 / len;
		vx *= len;
		vy *= len;
		vz *= len;

		dist /= 2.0f;
		v1.x += vx * dist;
		v1.y += vy * dist;
		v1.z += vz * dist;
		v2.x -= vx * dist;
		v2.y -= vy * dist;
		v2.z -= vz * dist;

	}
}

