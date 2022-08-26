#include "VanishParticleManager.h"
using namespace std;

void VanishParticleManager::Initialize(Model* model, TextureHandle tex)
{
	model_ = model;
	this->tex = tex;
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
	splitParticles.remove_if([](std::unique_ptr<SplitParticle>& particle) {
		return particle->IsDead();
		});
	for (unique_ptr<SplitParticle>& particle : splitParticles)
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
	for (unique_ptr<SplitParticle>& particle : splitParticles)
	{
		particle->Draw(view,tex);
	}
}

void VanishParticleManager::CreateParticle(Vector3 beginPos, Vector3 initScale,float scaleSpd)
{
	for (int i = 0; i < Max; i++)
	{
		particles.emplace_back(new VanishParticle);
		particles.back()->Initialize(beginPos, initScale, scaleSpd, model_);
	}
}

void VanishParticleManager::CreateSplitParticle(Vector3 beginPos, Vector3 initScale, float scaleSpd,float moveSpd)
{
	splitParticles.emplace_back(new SplitParticle);
	splitParticles.back()->Initialize({ 0.1f * moveSpd,0 }, beginPos, initScale, scaleSpd, model_);
	splitParticles.emplace_back(new SplitParticle);
	splitParticles.back()->Initialize({ 0.1f * moveSpd,0.1f * moveSpd }, beginPos, initScale, scaleSpd, model_);
	splitParticles.emplace_back(new SplitParticle);
	splitParticles.back()->Initialize({ 0.1f * moveSpd,-0.1f * moveSpd }, beginPos, initScale, scaleSpd, model_);
	splitParticles.emplace_back(new SplitParticle);
	splitParticles.back()->Initialize({ -0.1f * moveSpd,0 }, beginPos, initScale, scaleSpd, model_);
	splitParticles.emplace_back(new SplitParticle);
	splitParticles.back()->Initialize({ -0.1f * moveSpd,0.1f * moveSpd }, beginPos, initScale, scaleSpd, model_);
	splitParticles.emplace_back(new SplitParticle);
	splitParticles.back()->Initialize({ -0.1f * moveSpd,-0.1f * moveSpd }, beginPos, initScale, scaleSpd, model_);
	splitParticles.emplace_back(new SplitParticle);
	splitParticles.back()->Initialize({ 0,0.1f * moveSpd }, beginPos, initScale, scaleSpd, model_);
	splitParticles.emplace_back(new SplitParticle);
	splitParticles.back()->Initialize({ 0,-0.1f * moveSpd }, beginPos, initScale, scaleSpd, model_);

}
