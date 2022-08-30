#pragma once
#include "EventObject.h"
#include "EventManager.h"
#include <memory>
#include <list>

class checkPointManager : public EventManager
{
public:
	void Initialize(Model* model);
	void Update();
	void Draw(ViewProjection view);

	//std::list<std::unique_ptr<EventObject>>& GetObjects() { return checkPoints; };

private:

	void SetObjects();

	TextureHandle texTrue = 0;
};

