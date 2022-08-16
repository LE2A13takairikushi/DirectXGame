#include "EventManager.h"
using namespace std;

unique_ptr<EventObject> BoxCreate(Model* model_, Vector3 pos, Vector3 scale)
{
	unique_ptr<EventObject> newBox = make_unique<EventObject>();
	newBox->Initialize(model_);
	newBox->SetPos({ pos.x, pos.y, pos.z });
	newBox->SetScale({ scale.x, scale.y, scale.z });
	return newBox;
}

void EventManager::Initialize(Model* model_)
{
	Objects.push_back(BoxCreate(model_, { 0,15,60 }, { 2.0f,2.0f,2.0f }));
	Objects.push_back(BoxCreate(model_, { 0,150,200 }, { 2.0f,2.0f,2.0f }));
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
