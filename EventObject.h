#pragma once
#include "object.h"

class EventObject : public object
{
public:
	void Initialize(Model* model_,TextureHandle tex = 0);
	void Update();
	void Draw(ViewProjection view, TextureHandle tex = 0);

	void LoadTexture(TextureHandle tex);

	bool IsDead() const { return isDead; };
	bool IsEvent() { return isEvent;	};

	void Erase() { isDead = true; };
	void EventStart() { isEvent = true; };
	void EventEnd() { isEvent = false; };

	void CountUp();
	void CountDown();

	int GetEventCount() { return eventCount; };
	void SetEventCount(int count) { eventCount = count; };

	void NotCol();
	void InitScale();
	void InitPos();

	Vector3 GetInitScale() { return initScale; };
	void RemoveScale();

	void Vibration(float min, float max);

private:
	bool isDead = false;
	bool isEvent = false;

	int eventCount = 0;
};

