#include "enemyEventManager.h"
using namespace std;

void enemyEventManager::Initialize(Model* model_)
{
	EventManager::Initialize(model_,TextureManager::Load("spawn.png"));
	SetObjects();

}

void enemyEventManager::Update()
{
	EventManager::Update();
	for (unique_ptr<EventObject>& Object : BossObjects)
	{
		Object->Update();
	}
}

void enemyEventManager::Draw(ViewProjection view)
{
	EventManager::Draw(view);
	for (unique_ptr<EventObject>& Object : BossObjects)
	{
		Object->Draw(view);
	}
}

void enemyEventManager::SetObjects()
{
	CreateEventBox({ 100,160,160 }, {2.0f,2.0f,2.0f});
	CreateEventBox({ -5,190,200 }, { 2.0f,2.0f,2.0f });

	unique_ptr<EventObject> newBox = make_unique<EventObject>();
	newBox->Initialize(model_, tex);
	newBox->SetPos({ 0, 420, 250 });
	newBox->SetScale({ 5, 5, 5 });
	BossObjects.push_back(std::move(newBox));

}