#include "VanishEventManager.h"

void VanishEventManager::Initialize(Model* model_)
{
	EventManager::Initialize(model_,TextureManager::Load("tikuwa.png"));
	SetObjects();
}

void VanishEventManager::SetObjects()
{
	CreateEventBox({60,30,0},{5,5,5});
	CreateEventBox({60,30,10},{5,5,5});
	CreateEventBox({60,30,20},{5,5,5});
	CreateEventBox({60,30,30},{5,5,5});

	//ê^ÇÒíÜ
	CreateEventBox({ -140,90,145 }, { 10,10,10 });

	//
	CreateEventBox({ 35,280,230 }, { 10,10,10 });
	CreateEventBox({ 75,280,230 }, { 10,10,10 });
	CreateEventBox({ 115,280,230 }, { 10,10,10 });
}
