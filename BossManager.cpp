#include "BossManager.h"
using namespace std;

void BossManager::Initialize(Model* model, TextureHandle tex)
{
	this->model = model;
	this->tex = TextureManager::Load("skyBlue.png");

	weekTex = TextureManager::Load("red.png");
}

void BossManager::Update(Vector3 pos, Vector3 scale, Vector3 targetPos, VanishParticleManager& vpManager)
{
	bossList.remove_if([](std::unique_ptr<Boss>& boss) {
		return boss->IsDead();
		});

	for (std::unique_ptr<Boss>& boss : bossList)
	{
		boss->Update( pos, scale, targetPos, vpManager);
	}
}

void BossManager::Draw(ViewProjection view, float mouseVertRota)
{
	for (std::unique_ptr<Boss>& boss : bossList)
	{
		boss->Draw(view, mouseVertRota);
	}
}

void BossManager::BossUIDraw()
{
	for (std::unique_ptr<Boss>& boss : bossList)
	{
		boss->HPDraw();
	}
}

void BossManager::End()
{
	bossList.clear();
	//delete model;
}

void BossManager::SpawnBoss(Vector3 initpos)
{
	unique_ptr<Boss> newBoss = make_unique<Boss>();
	newBoss->Initialize(model, tex,weekTex);
	newBoss->SetPos(initpos);
	bossList.push_back(std::move(newBoss));
}

void BossManager::DeadInit()
{
	isBossBattle = false;
	bossList.clear();
}