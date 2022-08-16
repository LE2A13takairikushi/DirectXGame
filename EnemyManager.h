#pragma once
#include "Enemy.h"
#include "Model.h"
#include <memory>
#include <list>

class EnemyManager
{
public:
	std::list<std::unique_ptr<Enemy>> enemys;

	void Initialize(Model *model_);
	void EnemyPop();
	void Update(Vector3 PPos);
	void Draw(ViewProjection viewProjection_);

	void EventStart();

	int GetEventCount() { return eventSlayCount; };

	EnemyManager(Model* model_);
	~EnemyManager();

private:
	int popCount = 0;

	int eventSlayCount = 0;

	Vector3 popPos = { 0,0,0 };

	//パソコンが壊れたら嫌なので一応エネミー発生数の上限をつけておく
	int maxEnemyCount = 0;
	static const int MAX_ENEMY = 1;

	Model* model_ = nullptr;

};

