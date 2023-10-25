#include "HitParticle.h"

void HitParticle::Initialize()
{
	particle_ = make_unique<Particle>();
	texHandle = TextureManager::LoadTexture("Resources/circle.png");
	particle_->SetTexHandle(texHandle);
	particle_->SetName("HitParticles");
	particle_->Initialize(new ParticlePlaneState, 3500);
}

void HitParticle::Update()
{
	ListParticle_ = particle_->begin();

	for (Particle_param particle : ListParticle_)
	{
		particle.worldTransform_.translate = VectorTransform::Add(particle.worldTransform_.translate, particle.Velocity);
		particle.color_.w -= 0.01f;
		if (particle.color_.w<=0.0f)
		{
			continue;
		}

		particle_->PushList(particle);
	}

}

void HitParticle::Draw(ViewProjection view)
{
	particle_->Draw(view);
}

void HitParticle::Spown(Vector3 position)
{
	mt19937 randomEngine(randSeed());
	uniform_real_distribution<float>distributionVelocity(-1.0f, 1.0f);
	uniform_real_distribution<float>distributionColor(0.5f, 1.0f);
	for (int i = 0; i < 8; i++)
	{

		Vector3 VelocityRand = { 
			distributionVelocity(randomEngine),
			distributionVelocity(randomEngine),
			distributionVelocity(randomEngine) 
		};

		Vector4 colorRand = {
			distributionColor(randomEngine),
			distributionColor(randomEngine),
			distributionColor(randomEngine),
			1
		};

		Particle_param p1;
		p1.worldTransform_.Initialize();
		p1.worldTransform_.translate = position;
		p1.Velocity = VelocityRand;
		p1.worldTransform_.scale = { 0.8f,0.8f,0.8f };
		
		p1.color_ = colorRand;

		particle_->PushList(p1);

	}
}

void HitParticle::Move()
{
}
