#pragma once
#include "EventManager.h"

class enemyEventManager : public EventManager
{
public:
	void Initialize(Vector3 stagePos, Model* model_);
	std::list <std::unique_ptr<EventObject>>& GetBossObjects() {
		return BossObjects;
	};
	std::list <std::unique_ptr<EventObject>>& GetEnforceObjects() {
		return EnforceObjects;
	};
	void Update();
	void Draw(ViewProjection view);

	void DeadInit();
private:
	void SetObjects(Vector3 stagePos);

	std::list <std::unique_ptr<EventObject>> BossObjects;
	std::list <std::unique_ptr<EventObject>> EnforceObjects;

	Vector3 bossStagePos;

};

