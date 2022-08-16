#pragma once
#include "EventObject.h"
#include <memory>
#include <list>

class EventManager
{
public:
	void Initialize(Model* model_);
	void Update();
	void Draw(ViewProjection viewProjection_);

	const std::list <std::unique_ptr<EventObject>>& GetObjects() {
		return Objects; 
	};
private:
	std::list <std::unique_ptr<EventObject>> Objects;

};

