#pragma once
#include "Enemy.h"
#include "Model.h"
#include <memory>
#include <list>
#include "VanishParticleManager.h"

class EnemyManager
{
public:
	std::list<std::unique_ptr<Enemy>> enemys;

	void Initialize(Model *model_, Model* partModel, TextureHandle tex);
	void EnemyPop(VanishParticleManager& vpmanager);
	void Update(Vector3 PPos, bool NotSpawnTerm,VanishParticleManager &vpmanager);
	void Draw(ViewProjection viewProjection_);

	void EventStart(VanishParticleManager& vpmanager);

	int GetEventCount() { return eventSlayCount; };

	EnemyManager(Model* model_, Model* partModel, TextureHandle tex);
	~EnemyManager();

private:
	int popCount = 0;

	int eventSlayCount = 0;

	Vector3 popPos = { 0,0,0 };

	//VanishParticleManager vpManager;

	//パソコンが壊れたら嫌なので一応エネミー発生数の上限をつけておく
	int maxEnemyCount = 0;
	static const int MAX_ENEMY = 0;

	Model* model_ = nullptr;
	Model* partModel_ = nullptr;
	TextureHandle tex = 0;
};

