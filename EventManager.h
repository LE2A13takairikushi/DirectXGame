#pragma once
#include "EventObject.h"
#include <memory>
#include <list>

class EventManager
{
public:
	void Initialize(Model* model_, TextureHandle tex = 0);
	void Update();
	void Draw(ViewProjection viewProjection_);

	void CreateEventBox(Vector3 pos, Vector3 scale);

	const std::list <std::unique_ptr<EventObject>>& GetObjects() {
		return Objects; 
	};
protected:
	std::list <std::unique_ptr<EventObject>> Objects;

	Model* model_ = nullptr;
	TextureHandle tex = 0;
};

