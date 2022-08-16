#pragma once
#include "object.h"

class EventObject : public object
{
public:
	void Initialize(Model* model_);
	void Update();
	void Draw(ViewProjection view);

	bool IsDead() const { return isDead; };
	bool IsEvent() {return isEvent;	};

	void Erase() { isDead = true; };
	void Start() { isEvent = true; };

	int eventCount = 0;

private:
	bool isDead = false;

	bool isEvent = false;

};

