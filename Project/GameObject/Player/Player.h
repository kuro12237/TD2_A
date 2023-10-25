#pragma once
#include"Model.h"
#include"WorldTransform.h"
#include"Input.h"
#include"VectorTransform.h"
#include"Collider.h"
#include"ColliderConfig.h"
#include"GameObject/MapWall/MapWall.h"
#include"GameObject/MapWall/IMapWall.h"
#include"PlayerParticle.h"
#include"GameObject/GameAudio/GameAudio.h"

#define MAX_MOVE_COOLTIME 300

class Enemy;

class Player: public Collider, public IMapWall
{
public:
	Player() {};
	~Player() {};

	void Initialize();

	void Update();

	void Draw(ViewProjection view);
	//void SetVelocity(){ SetVelosity(Velocity); }


	void OnCollision()override;

	void OnTopWall()override;
	void OnBottomWall()override;
	void OnLeftWall()override;
	void OnRightWall()override;

#pragma region get

	bool GetHitFlag() { return HitFlag; }

	Vector3 GetWorldPosition()override;

	Vector3 GetVelocity()override;

	const WorldTransform &GetWorldTransform()const { return worldTransform_; }

#pragma endregion

#pragma region set

	void SetEnemy(std::list<shared_ptr<Enemy>>enemys) { enemys_ = enemys; }

#pragma endregion

private:

	void Move();

    void Reticle();
	
	void FancFrictionCoefficient();
	
	Vector3 NoramalizeLerp(Vector3 v1, Vector3 v2);

	unique_ptr<Model>model_ = nullptr;
	unique_ptr<Model>PlaneModel_ = nullptr;
	unique_ptr<Model>reticleTestModel = nullptr;
	unique_ptr<Model>LineModel_ = nullptr;

	unique_ptr < PlayerParticle > MoveEffect= nullptr;

	WorldTransform worldTransform_ = {};
	WorldTransform reticleWorldTransform{};
	WorldTransform LineWorldTransform_ = {};

	Vector3 Velocity = { 0.0f,0.0f,0.0f};

	tuple<Vector3, Vector3> velocity_ = {};
	Vector3 HitVelo = {};
	bool isMove_ = false;
	Enemy* enemy_;
	std::list<shared_ptr<Enemy>>enemys_;
	Vector3 enemyVelo_ = {};
	Vector3 enemyPos_ = {};
	float angle = 0.0f;
	float angle2 = 0.0f;
	
	/// <summary>
	/// reticleƒgplayer‚ÌƒxƒNƒgƒ‹
	/// </summary>
	Vector3 RPNormalize = {};

	/// <summary>
	/// –€ŽC
	/// </summary>
	const float frictionCoefficient = 0.015f;

	uint32_t MoveCoolTime = 0;
	bool MoveFlag = false;

	const float speed = 2.0f;
	const float rotateSpeed = 0.1f;
	Vector3 Rvelocity{};

	bool HitFlag = false;

	uint32_t texHandle = 0;
};
