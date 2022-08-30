#include "enemyEventManager.h"
using namespace std;

TextureHandle bossTex = 0;

void enemyEventManager::Initialize(Vector3 stagePos, Model* model_)
{
	EventManager::Initialize(model_,TextureManager::Load("hatena.png"));
	bossTex = TextureManager::Load("spawn.png");
	bossStagePos = stagePos;
	SetObjects(bossStagePos);
}

void enemyEventManager::Update()
{
	for (unique_ptr<EventObject>& Object : Objects)
	{
		Object->worldTransform_.rotation_.y += 0.01f;
	}
	EventManager::Update();
	BossObjects.remove_if([](std::unique_ptr<EventObject>& bossObj) {
		return bossObj->IsDead();
		});

	for (unique_ptr<EventObject>& Object : BossObjects)
	{
		Object->worldTransform_.rotation_.y += 0.01f;
		Object->Update();
	}
	
	EnforceObjects.remove_if([](std::unique_ptr<EventObject>& enforceObject) {
		return enforceObject->IsDead();
		});

	for (unique_ptr<EventObject>& Object : EnforceObjects)
	{
		Object->worldTransform_.rotation_.y += 0.01f;
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
	for (unique_ptr<EventObject>& Object : EnforceObjects)
	{
		Object->Draw(view);
	}
}

void enemyEventManager::DeadInit()
{
	Objects.clear();
	BossObjects.clear();
	EnforceObjects.clear();
	SetObjects(bossStagePos);
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

	unique_ptr<EventObject> newBox2 = make_unique<EventObject>();
	newBox2->Initialize(model_, bossTex);
	newBox2->SetPos({ 560, 370, 190 });
	newBox2->SetScale({ 2, 2, 2 });
	EnforceObjects.push_back(std::move(newBox2));

}