#pragma once
#include "EventManager.h"

class enemyEventManager : public EventManager
{
public:
	void Initialize(Model* model_);
	std::list <std::unique_ptr<EventObject>>& GetBossObjects() {
		return BossObjects;
	};
	void Update();
	void Draw(ViewProjection view);
private:
	void SetObjects();

	std::list <std::unique_ptr<EventObject>> BossObjects;

};

