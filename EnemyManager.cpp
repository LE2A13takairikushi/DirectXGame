#include "EnemyManager.h"
#include <cassert>
#include <random>

using namespace std;

EnemyManager::EnemyManager(Model* model_)
{
	Initialize(model_);
}

EnemyManager::~EnemyManager()
{
	
}

void EnemyManager::Initialize(Model* model_)
{
	assert(model_);
	this->model_ = model_;
}

void EnemyManager::EnemyPop()
{
	Vector3 tempPopPos = popPos;
	tempPopPos.x += RNG(-30, 30);
	tempPopPos.y += RNG(0,10);
	tempPopPos.z += RNG(-30, 30);

	unique_ptr<Enemy> newEnemy = make_unique<Enemy>();
	newEnemy->Initialize(model_, tempPopPos);

	//“G‚ð“o˜^‚·‚é
	enemys.push_back(std::move(newEnemy));
}

void EnemyManager::Update(Vector3 PPos)
{
	maxEnemyCount = enemys.size();
	popPos = PPos;

	popCount++;
	if (popCount > 120 && maxEnemyCount < MAX_ENEMY)
	{
		EnemyPop();
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
}

void EnemyManager::EventStart()
{
	for (int i = 0; i < 10; i++)
	{
		EnemyPop();
		eventSlayCount++;
	}
}
