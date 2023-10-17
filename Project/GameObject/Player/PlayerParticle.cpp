#include "PlayerParticle.h"

void PlayerParticle::Initialize()
{
	texHandle = TextureManager::LoadTexture("Resources/smoke.png");
	particle_ = make_unique<Particle>();
	particle_->SetTexHandle(texHandle);
	particle_->SetName("PlayerParticle");
	particle_->Initialize(new ParticlePlaneState, 600);

}

void PlayerParticle::Spown(Vector3 position)
{
	//��������
	spownTime++;
	if (spownTime > 1)
	{
		for (int i = 0; i < 7; i++)
		{
			Particle_param p1{};
			p1.worldTransform_.Initialize();
			mt19937 randomEngine(seedGenerator());
			uniform_real_distribution<float>distribution(-0.5f, 0.5f);

			Vector3 randpos = { distribution(randomEngine),distribution(randomEngine) ,distribution(randomEngine) };
			p1.worldTransform_.translate = VectorTransform::Add(position, randpos);

			uniform_real_distribution<float>distributionAlpha(0.2f, 1.0f);
			p1.color_ = { 1,1,1,distributionAlpha(randomEngine) };

			ParticleUV(p1.uvTransform_.scale, p1.uvTransform_.translate);

			particle_->PushList(p1);
		}
		spownTime = 0;
	}

}

void PlayerParticle::Update()
{
	//�X�V����
	particles_param_ = particle_->begin();
	ImGui::Begin("Particle_Param");
	ImGui::Text("size : %d", particles_param_.size());
	ImGui::End();
	for (Particle_param particle : particles_param_)
	{
		particle.color_.w -= 0.01f;
		if (particle.color_.w<=0.0f)
		{
			continue;
		}
		particle_->PushList(particle);
	}
}

void PlayerParticle::Draw(ViewProjection view)
{
	particle_->Draw(view);
}

void PlayerParticle::ParticleUV(Vector3& s, Vector3& t)
{
	mt19937 randomEngine(seedGenerator());
	uniform_int_distribution<int>distribution(0, 4);
	const int UVrand = distribution(randomEngine);
	s = { 0.5f,0.5f,0.5f };

	if (RT == UVrand)
	{
		t = { 0.5f,0,0 };
	}
	if (RB == UVrand)
	{
		t = { 0.5f,0.5f,0 };
	}
	if (LT == UVrand)
	{
		t = { 0.0f,0.0f,0 };
	}
	if (LB == UVrand)
	{
		t = { 0.0f,0.5f,0 };
	}

}
