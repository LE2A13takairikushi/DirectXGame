#include "JumpEventManager.h"

void JumpEventManager::Initialize(Model* model_)
{
	EventManager::Initialize(model_, TextureManager::Load("jumpBox.png"));
	SetObjects();
}

void JumpEventManager::SetObjects()
{
	//’n–Ê‚É’u‚­‚­‚ç‚¢‚Éİ’u‚·‚é‚Æ”²‚¯‚éŠëŒ¯«‚ª‚ ‚é
	CreateEventBox({20,20,80},{2,2,2});

	CreateEventBox({ 140,160,220 },{2,2,2});
	CreateEventBox({ 460,195,185 },{2,2,2});
	
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			CreateEventBox({ 252 + j * 4.0f,150,192 + i * 4.0f }, { 2,2,2 });
		}
	}
	
}