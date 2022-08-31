#include "Title.h"

#include "WinApp.h"

void Title::Initialize(Model* model, Model* model2, Model* model3, ViewProjection view)
{
	playerModel = model;
	playerModel2 = model2;
	playerModel3 = model3;

	modelTrans.Initialize();
	modelTrans.translation_ = { view.eye.x + 5,view.eye.y - 2.5f,view.eye.z + 10 };
	modelTrans.rotation_ = { 0,4,0 };

	input = Input::GetInstance();
	mozi[0] = Sprite::Create(TextureManager::Load("T.png"),
		{ 200,50 });
	mozi[1] = Sprite::Create(TextureManager::Load("A.png"),
		{ 400,50 });
	mozi[2] = Sprite::Create(TextureManager::Load("N.png"),
		{ 600,50 });
	mozi[3] = Sprite::Create(TextureManager::Load("K.png"),
		{ 800,50 });
	curser = Sprite::Create(TextureManager::Load("curser.png"),
		{ 0,0 });

	for (int i = 0; i < 4; i++)
	{
		mozi[i]->SetSize({ 200, 200 });
	}

	UI[0] = Sprite::Create(TextureManager::Load("gameStart.png"),
		{ 100,WinApp::kWindowHeight - 300 });
	UI[1] = Sprite::Create(TextureManager::Load("option.png"),
		{ 100,WinApp::kWindowHeight - 200 });
	UI[2] = Sprite::Create(TextureManager::Load("end.png"),
		{ 100,WinApp::kWindowHeight - 100 });

	curser->SetSize({100, 100});

	/*for (int i = 0; i < 2; i++)
	{
		UI[i]->SetSize({ 100,100 });
	}*/
}

void Title::Update(Audio* audio, SoundDataManager sdmanager)
{
	if (input->PushKey(DIK_SPACE))
	{
		if (titleMenu == start)
		{
			isTitle = false;
			audio->StopWave(sdmanager.titleBGM);
			audio->PlayWave(sdmanager.gamesceneBGM, true, 0.1f);
		}
	}

	if (input->TriggerKey(DIK_W))
	{
		if (titleMenu != start) { 
			titleMenu--; 
			//audio->PlayWave(sdmanager.curserSE, false, 0.1f);
		}
		
	}
	if (input->TriggerKey(DIK_S))
	{
		if (titleMenu != end) { 
			titleMenu++; 
			//audio->PlayWave(sdmanager.curserSE, false, 0.1f);
		}
	}
	
	curser->SetPosition({ 
		UI[titleMenu]->GetPosition().x - 70,
		UI[titleMenu]->GetPosition().y });

	modelTrans.UpdateMatrix();
	modelTrans.TransferMatrix();
}

void Title::Draw()
{
	for (int i = 0; i < 4; i++)
	{
		mozi[i]->Draw();
	}

	for (int i = 0; i < 3; i++)
	{
		UI[i]->Draw();
	}

	curser->Draw();
}

void Title::ModelDraw(ViewProjection view)
{
	playerModel->Draw(modelTrans,view);
	playerModel2->Draw(modelTrans, view);
	playerModel3->Draw(modelTrans, view);
}
