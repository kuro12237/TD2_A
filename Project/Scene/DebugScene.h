#pragma once
#include"IScene.h"
#include"GameManager.h"

#include"GameScene.h"
#include"Input.h"
#include"Audio.h"
#include"FileLoader.h"


#include"CollisionManager.h"

#include"Particle/Particle.h"
class DebugScene:public IScene
{
public:
	DebugScene() {};
	~DebugScene();


	void Initialize()override;

	void Update(GameManager* Scene)override;

	void Back2dSpriteDraw()override;
	void Object3dDraw()override;
	void Flont2dSpriteDraw()override;
	
private:
	void TestCsvFile();

	void CheckAllCollision();
	
	void Testparticle();

	ViewProjection viewProjection{};
	uint32_t soundHandle_  = 0;

	unique_ptr<Sprite>sprite_ = nullptr;
	WorldTransform spriteWorldTransform_{};
	
	unique_ptr<Sprite>sprite2_ = nullptr;
	WorldTransform sprite2WorldTransform_{};

	uint32_t SpriteTexHandle = 0;
	Vector4 color = { 1,1,1,1 };

	bool NoneFlag = true;
	bool AddFlag = false;
	bool MultiplyFlag = false;
	bool SubtractFlag = false;
	bool ScreenFlag = false;


	unique_ptr<Particle>particle_ = nullptr;
	
	Vector3 TestParticlesTranslate = {};
	Vector4 TestParticleColor = {1,1,1,1};
	
};
