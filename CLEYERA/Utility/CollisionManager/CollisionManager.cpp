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
	Vector3 cAvelo = cA->GetVelocity();
	Vector3 cBvelo = cB->GetVelocity();

	float cAradious = cA->GetRadious();
	float cBradious = cB->GetRadious();

	if (CheckBallCollosion(cApos, cAradious,cAvelo, cBpos, cBradious,cBvelo,1.0f / 60.0f)) {
		cA->OnCollision();
		cB->OnCollision();
	}
}


bool CollisionManager::CheckBallCollosion(Vector3 v1, float v1Radius, Vector3 velo, Vector3 v2, float v2Radius, Vector3 velo2, float frameTime) {
	
	Vector3 newPos1 = VectorTransform::Add(v1, VectorTransform::Multiply(velo, frameTime));
	Vector3 newPos2 = VectorTransform::Add(v2, VectorTransform::Multiply(velo2, frameTime));


	Vector3 relativeVelocity = VectorTransform::Subtruct( velo , velo2);

	Vector3 relativePosition = VectorTransform::Subtruct(newPos1, newPos2);

	float a = VectorTransform::Dot(relativeVelocity, relativeVelocity);
	float b = 2.0f * VectorTransform::Dot(relativeVelocity ,relativePosition);
	float c = VectorTransform::Dot(relativePosition ,relativePosition) - (v1Radius + v2Radius) * (v1Radius + v2Radius);

	float discriminant = b * b - 4.0f * a * c;

	bool collision = false;

	if (discriminant > 0) {
		float t = (-b - sqrt(discriminant)) / (2.0f * a);

		if (t >= 0.0f && t <= 1.0f) {
			
			collision = true;
		}
	}

	return collision;
}


