#include "EnemyManager.h"
#include <cassert>
#include <random>

using namespace std;

EnemyManager::EnemyManager(Model* model_, Model* partModel, TextureHandle tex)
{
	Initialize(model_, partModel, tex);
}

EnemyManager::~EnemyManager()
{
	
}

void EnemyManager::Initialize(Model* model_, Model* partModel, TextureHandle tex)
{
	assert(model_);
	this->model_ = model_;
	this->partModel_ = partModel;
	this->tex = tex;
}

void EnemyManager::EnemyPop(VanishParticleManager& vpmanager)
{
	Vector3 tempPopPos = popPos;
	tempPopPos.x += RNG(-30, 30);
	tempPopPos.y += RNG(0,10);
	tempPopPos.z += RNG(-30, 30);

	unique_ptr<Enemy> newEnemy = make_unique<Enemy>();
	newEnemy->Initialize(model_, partModel_,tex,tempPopPos);

	vpmanager.CreateParticle(newEnemy->GetWorldTrans().translation_, 
		{ 1.0f,1.0f ,1.0f }, 0.03f);

	//�G��o�^����
	enemys.push_back(std::move(newEnemy));
}

void EnemyManager::Update(Vector3 PPos, bool NotSpawnTerm, VanishParticleManager &vpmanager)
{
	maxEnemyCount = enemys.size();
	popPos = PPos;

	popCount++;
	if ((popCount > 120 && maxEnemyCount < MAX_ENEMY)&&
		NotSpawnTerm == false)
	{
		EnemyPop(vpmanager);
		popCount = 0;
	}

	for (std::unique_ptr<Enemy>& enemy : enemys)
	{
		enemy->Update(PPos);
		if (enemy->IsDead())
		{
			if (eventSlayCount > 0)
			{
				eventSlayCount--;
			}
		}
		if (enemy->IsDead())
		{
			vpmanager.CreateParticle(enemy->GetWorldTrans().translation_,{0.5f,0.5f ,0.5f },0.01f);
		}
		if (NotSpawnTerm)
		{
			enemy->OnCollision();
		}
	}

	enemys.remove_if([](std::unique_ptr<Enemy>& enemy) {
		return enemy->IsDead();
		});
}

void EnemyManager::Draw(ViewProjection viewProjection_)
{
	for (std::unique_ptr<Enemy>& enemy : enemys)
	{
		enemy->Draw(viewProjection_);
	}
	//vpManager.Draw(viewProjection_);
}

void EnemyManager::EventStart(VanishParticleManager& vpmanager)
{
	for (int i = 0; i < 10; i++)
	{
		EnemyPop(vpmanager);
		eventSlayCount++;
	}
}
