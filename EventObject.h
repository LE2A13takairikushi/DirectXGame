#pragma once
#include "object.h"

class EventObject : public object
{
public:
	void Initialize(Model* model_);
	void Update();
	void Draw(ViewProjection view);

	bool IsDead() const { return isDead; };
	bool IsEvent() { return isEvent;	};

	void Erase() { isDead = true; };
	void EventStart() { isEvent = true; };
	void EventEnd() { isEvent = false; };

	int eventCount = 0;

private:
	bool isDead = false;
	bool isEvent = false;

};

