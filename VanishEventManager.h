#pragma once
#include "EventManager.h"

class VanishEventManager : public EventManager
{
public:
	void Initialize(Model* model_);
private:
	void SetObjects();
};

