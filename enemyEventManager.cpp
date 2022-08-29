#include "enemyEventManager.h"
using namespace std;

TextureHandle bossTex = 0;

void enemyEventManager::Initialize(Vector3 stagePos, Model* model_)
{
	EventManager::Initialize(model_,TextureManager::Load("hatena.png"));
	bossTex = TextureManager::Load("spawn.png");
	SetObjects(stagePos);
}

void enemyEventManager::Update()
{
	EventManager::Update();
	BossObjects.remove_if([](std::unique_ptr<EventObject>& bossObj) {
		return bossObj->IsDead();
		});

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

void enemyEventManager::SetObjects(Vector3 stagePos)
{
	CreateEventBox({ 100,160,160 }, {2.0f,2.0f,2.0f});
	CreateEventBox({ -5,190,200 }, { 2.0f,2.0f,2.0f });

	unique_ptr<EventObject> newBox = make_unique<EventObject>();
	newBox->Initialize(model_, bossTex);
	newBox->SetPos({ stagePos.x, stagePos.y + 30, stagePos.z });
	newBox->SetScale({ 5, 5, 5 });
	BossObjects.push_back(std::move(newBox));

}