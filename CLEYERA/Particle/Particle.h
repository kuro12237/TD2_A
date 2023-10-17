#pragma once
#include"WorldTransform.h"
#include"ViewProjection.h"
#include"state/ParticlePlaneState.h"
#include"SParticle.h"

class Particle
{
public:
	Particle() {};
	~Particle() { delete state_; }

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="new �`��I��"></param>
	/// <param name="�C���X�^���X�ő吔"></param>
	void Initialize(IParticleState *state ,const uint32_t NumInstance = 1);

	void Draw(ViewProjection viewProjection);

	/// <summary>
	/// particle�̍X�V�����̍ŏ��ɕK������
	/// </summary>
	list<Particle_param>begin();

#pragma region Set
	void SetTexHandle(uint32_t tex) { texhandle = tex; }
	
	void SetName(const string name) { name_ = name; }

	/// <summary>
	/// ���X�g�ɓo�^
	/// </summary>
	void PushList(Particle_param particle) { particles_.push_back(particle);}

#pragma endregion 

#pragma region get
	/// <summary>
	/// GetTex
	/// </summary>
	uint32_t GetTexhandle() { return texhandle; }
	
	/// <summary>
	/// �����ɕ\���ł���ő吔
	/// </summary>
	const uint32_t GetNumInstancing() const{ return NumInstance_; }
	
	/// <summary>
    /// ���X�g��Get
	/// </summary>
	list<Particle_param> GetParticles() { return particles_; }

#pragma endregion 
private:

	bool InitializeLock = false;
	string name_ = "/0";
	IParticleState* state_ = nullptr;
	
	uint32_t NumInstance_ = 20;

	uint32_t texhandle = 0;
	
	list<Particle_param> particles_{};
};




