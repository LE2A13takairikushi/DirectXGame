#include "EventManager.h"
#include <cassert>
using namespace std;

void EventManager::CreateEventBox(Vector3 pos, Vector3 scale)
{
	unique_ptr<EventObject> newBox = make_unique<EventObject>();
	newBox->Initialize(model_, tex);
	newBox->SetPos({ pos.x, pos.y, pos.z });
	newBox->SetScale({ scale.x, scale.y, scale.z });
	Objects.push_back(std::move(newBox));
}

void EventManager::Initialize(Model* model_, TextureHandle tex)
{
	assert(model_);
	this->model_ = model_;
	this->tex = tex;
}

void EventManager::Update()
{
	Objects.remove_if([](std::unique_ptr<EventObject>& object) {
		return object->IsDead();
		});

	for (unique_ptr<EventObject>& Object : Objects)
	{
		Object->Update();
	}
}

void EventManager::Draw(ViewProjection viewProjection_)
{
	for (unique_ptr<EventObject>& Object : Objects)
	{
		Object->Draw(viewProjection_);
	}
}