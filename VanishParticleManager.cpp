#include "VanishParticleManager.h"
using namespace std;

void VanishParticleManager::Initialize(Model* model, TextureHandle tex)
{
	model_ = model;
	this->tex = tex;
	/*for (unique_ptr<VanishParticle>& particle : particles)
	{
		particle->LoadModel(model_);
	}*/
}

void VanishParticleManager::Update()
{
	particles.remove_if([](std::unique_ptr<VanishParticle>& particle) {
		return particle->IsDead();
		});
	for (unique_ptr<VanishParticle>& particle : particles)
	{
		particle->Update();
	}
}

void VanishParticleManager::Draw(ViewProjection view)
{
	for (unique_ptr<VanishParticle>& particle : particles)
	{
		particle->Draw(view,tex);
	}
}

void VanishParticleManager::CreateParticle(Vector3 beginPos, Vector3 scale,float scaleSpd)
{
	for (int i = 0; i < Max; i++)
	{
		particles.emplace_back(new VanishParticle);
		particles.back()->Initialize(beginPos, scale, scaleSpd, model_);
	}
}
