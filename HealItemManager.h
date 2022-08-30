#pragma once
#include "EventManager.h"
class HealItemManager : public EventManager
{
public:
	void Initialize(Model* model);
	void Update();

	void CreateHealItem(Vector3 pos);

	void DeadInit();

private:
	void SetObjects();
};

