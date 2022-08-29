#pragma once
#include "EventManager.h"

class enemyEventManager : public EventManager
{
public:
	void Initialize(Vector3 stagePos, Model* model_);
	std::list <std::unique_ptr<EventObject>>& GetBossObjects() {
		return BossObjects;
	};
	void Update();
	void Draw(ViewProjection view);
private:
	void SetObjects(Vector3 stagePos);

	std::list <std::unique_ptr<EventObject>> BossObjects;

};

