#include "checkPointManager.h"
using namespace std;

void checkPointManager::Initialize(Model* model)
{
	this->model_ = model;
	tex = TextureManager::Load("checkPoint.png");
	texTrue = TextureManager::Load("checkPoint_true.png");
	SetObjects();
}

void checkPointManager::Update()
{
	for (unique_ptr<EventObject>& Object : Objects)
	{
		Object->worldTransform_.rotation_.y += 0.01f;
		Object->Update();
	}
}

void checkPointManager::Draw(ViewProjection view)
{
	for (unique_ptr<EventObject>& Object : Objects)
	{
		if (Object->IsEvent())
		{
			Object->Draw(view,texTrue);
		}
		else
		{
			Object->Draw(view);
		}
	}
}

void checkPointManager::SetObjects()
{
	CreateEventBox({ 460,270,200 }, { 2,2,2 });

	CreateEventBox({ 490,355,360 }, { 2,2,2 });
}
