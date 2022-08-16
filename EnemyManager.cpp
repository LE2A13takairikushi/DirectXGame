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
	//assert(model_);
	this->model_ = model_;
	EnemyPop();
}

void EnemyManager::EnemyPop()
{
	Vector3 popPos;
	popPos.x = RNG(-30, 30);
	popPos.y = 10;
	popPos.z = RNG(-30, 30);

	unique_ptr<Enemy> newEnemy = make_unique<Enemy>();
	newEnemy->Initialize(model_, popPos);

	//“G‚ð“o˜^‚·‚é
	enemys.push_back(std::move(newEnemy));
}

void EnemyManager::Update(Vector3 PPos)
{
	enemys.remove_if([](std::unique_ptr<Enemy>& enemy) {
		return enemy->IsDead();
		});

	maxEnemyCount = enemys.size();

	popCount++;
	if (popCount > 120 && maxEnemyCount < MAX_ENEMY)
	{
		EnemyPop();
		popCount = 0;
	}

	for (std::unique_ptr<Enemy>& enemy : enemys)
	{
		enemy->Update(PPos);
	}
}

void EnemyManager::Draw(ViewProjection viewProjection_)
{
	for (std::unique_ptr<Enemy>& enemy : enemys)
	{
		enemy->Draw(viewProjection_);
	}
}
