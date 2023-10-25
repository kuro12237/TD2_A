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
	//•¦‚«ˆ—
	spownTime++;
	if (spownTime > 1)
	{
		for (int i = 0; i < 3; i++)
		{
			Particle_param p1{};
			p1.worldTransform_.Initialize();
			mt19937 randomEngine(seedGenerator());
			uniform_real_distribution<float>distribution(-0.5f, 0.5f);

			Vector3 randpos = { distribution(randomEngine),distribution(randomEngine) ,distribution(randomEngine) };
			p1.worldTransform_.translate = VectorTransform::Add(position, randpos);

			uniform_real_distribution<float>distributionAlpha(0.2f, 1.0f);
			Vector4 color = Model::ColorConversion(0x616161ff);
			p1.color_ = { color.x,color.y,color.z,distributionAlpha(randomEngine) };

			ParticleUV(p1.uvTransform_.scale, p1.uvTransform_.translate);
			
			particle_->PushList(p1);
		}
		spownTime = 0;
	}

}

void PlayerParticle::Update()
{
	//XVˆ—
	particles_param_ = particle_->begin();
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
