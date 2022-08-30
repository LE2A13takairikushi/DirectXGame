#include "HealItemManager.h"
using namespace std;

void HealItemManager::Initialize(Model* model)
{
	EventManager::Initialize(model, TextureManager::Load("heal_item.png"));
	SetObjects();
}

void HealItemManager::Update()
{
	Objects.remove_if([](std::unique_ptr<EventObject>& object) {
		return object->IsDead();
		});

	for (unique_ptr<EventObject>& Object : Objects)
	{
		Object->worldTransform_.rotation_.y += 0.01f;
		Object->Update();
	}
}

void HealItemManager::CreateHealItem(Vector3 pos)
{
	CreateEventBox(pos, { 2,2,2 });
}

void HealItemManager::DeadInit()
{
	Objects.clear();
	SetObjects();
}

void HealItemManager::SetObjects()
{
	CreateEventBox({ 660, 370, 80 },{2,2,2});
	CreateEventBox({ 660, 380, 80 },{2,2,2});
	for (int i = 0; i < 3; i++)
	{
		CreateEventBox({ 490,355,300 + i * 20.0f }, { 2, 2, 2 });
	}
}


