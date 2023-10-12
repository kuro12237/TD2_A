#include "PlayerParticle.h"

void PlayerParticle::Initialize()
{
	texHandle = TextureManager::LoadTexture("Resources/uvChecker.png");
	particle_ = make_unique<Particle>();
	particle_->SetTexHandle(texHandle);
	particle_->Initialize(new ParticlePlaneState, 60);
}

void PlayerParticle::Update(Vector3 position)
{
	//•¦‚«ˆ—
	spownTime++;
	if (spownTime>2)
	{
		Particle_param p1{};
		p1.worldTransform_.Initialize();
		mt19937 randomEngine(seedGenerator());
		uniform_real_distribution<float>distribution(-1.0f, 1.0f);

		Vector3 randpos = { distribution(randomEngine),distribution(randomEngine) ,distribution(randomEngine) };
		p1.worldTransform_.translate = VectorTransform::Add(position, randpos);
		p1.color_ = { distribution(randomEngine),distribution(randomEngine) ,distribution(randomEngine) ,1 };
		p1.uvTransform_.scale = { 0.5f,0.5f,0.5f };
		
		particle_->PushList(p1);
		spownTime = 0;
	}

	//XVˆ—
	particles_param_ = particle_->begin();
	ImGui::Begin("Particle_Param");
	ImGui::Text("size : %d", particles_param_.size());
	ImGui::End();
	for (Particle_param particle : particles_param_)
	{
		particle.worldTransform_.translate.y += 0.1f;
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
