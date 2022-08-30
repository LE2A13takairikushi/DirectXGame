#include "VanishEventManager.h"

void VanishEventManager::Initialize(Model* model_)
{
	EventManager::Initialize(model_,TextureManager::Load("tikuwa.png"));
	SetObjects();
}

void VanishEventManager::SetObjects()
{

	//ê^ÇÒíÜ
	CreateEventBox({ -140,90,145 }, { 10,10,10 });

	//
	CreateEventBox({ 35,260,230 }, { 10,10,10 });
	CreateEventBox({ 75,270,230 }, { 10,10,10 });
	CreateEventBox({ 115,280,230 }, { 10,10,10 });

	for (int i = 0; i < 8; i++)
	{
		CreateEventBox({ 300 + i * 20.0f,250,200 }, { 10,10,10 });
	}

	for (int i = 0; i < 2; i++)
	{
		CreateEventBox({ 460,250,200 + i * 90.0f + 45.0f }, { 10,10,10 });
	}
}
