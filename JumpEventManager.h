#pragma once
#include "EventManager.h"

class JumpEventManager : public EventManager
{
public:
	void Initialize(Model* model_);
private:
	void SetObjects();
};

