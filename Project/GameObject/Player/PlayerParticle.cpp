#include "PlayerParticle.h"

void PlayerParticle::Initialize()
{
	texHandle = TextureManager::LoadTexture("Resources/circle.png");
	particle_ = make_unique<Particle>();
	particle_->SetTexHandle(texHandle);
	particle_->Initialize(new ParticlePlaneState, 600);

}

void PlayerParticle::Update(Vector3 position)
{
	spownTime++;

	if (spownTime>20)
	{
		Particle_param p1{};
		p1.worldTransform_.Initialize();
		p1.worldTransform_.translate = position;
		p1.color_ = { 1,1,1,1 };
		particle_->SetList(p1);
		spownTime = 0;
	}

	particles_param_ = particle_->GetParticles();

	particle_->SetListParticles(particles_param_);


}

void PlayerParticle::Draw(ViewProjection view)
{
	particle_->Draw(view);

}
