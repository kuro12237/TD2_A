#pragma once
#include"./Collider/Collider.h"
#include"Pch.h"
#include "VectorTransform.h"

class CollisionManager {
public:


	void CheckAllCollision();

	void ClliderPush(Collider* collider) { colliders_.push_back(collider); }
	void ClliderClear() { colliders_.clear(); }

private:
	void CheckCollisionPair(Collider* cA, Collider* cB);
	bool CheckBallCollision(Vector3 v1, float radius1, Vector3 velocity1, Vector3 v2, float radius2, Vector3 velocity2);

	std::list<Collider*> colliders_;
};
