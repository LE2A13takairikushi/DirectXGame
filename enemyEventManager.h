#pragma once
#include "EventManager.h"

class enemyEventManager : public EventManager
{
public:
	void Initialize(Model* model_);
private:
	void SetObjects();
};

