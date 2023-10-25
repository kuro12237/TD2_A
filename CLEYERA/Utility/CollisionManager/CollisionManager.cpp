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

	if (CheckBallCollision(cApos, cAradious,cAVelo, cBpos, cBradious, cBVelo)) {
		cA->OnCollision();
		cB->OnCollision();
	}
}


bool CollisionManager::CheckBallCollision(Vector3 v1, float radius1, Vector3 velocity1, Vector3 v2, float radius2, Vector3 velocity2) {
	// 時間刻みを設定
	float deltaTime = 0.01f;

	// 初期位置
	Vector3 currentPos1 = v1;
	Vector3 currentPos2 = v2;

	// 衝突判定フラグ
	bool collision = false;

	for (float t = 0; t <= 1.0f; t += deltaTime) {

		// オブジェクトの位置を時間刻み内で補間
		Vector3 newPos1 = VectorTransform::Add(currentPos1 , VectorTransform::Multiply(velocity1 , deltaTime));
		Vector3 newPos2 = VectorTransform::Add(currentPos2, VectorTransform::Multiply(velocity2, deltaTime));

		// 2つの球の中心間の距離を計算
		Vector3 centerDelta = VectorTransform::Subtruct( newPos2 , newPos1);
		float distanceSquared = VectorTransform::Dot(centerDelta, centerDelta);

		// 2つの球の半径の合計
		float combinedRadius = radius1 + radius2;

		if (distanceSquared <= combinedRadius * combinedRadius) {
			// 衝突が発生
			collision = true;
			break;
		}

		// 位置と速度を更新
		currentPos1 = newPos1;
		currentPos2 = newPos2;
	}

	return collision;
}



