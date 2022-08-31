#include "Title.h"
#include <math.h>
#include "WinApp.h"
#include "MyMath.h"

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
	alpha = Sprite::Create(TextureManager::Load("alpha.png"),
		{ WinApp::kWindowWidth - 300,WinApp::kWindowHeight - 120 });
	alpha->SetSize({ 240,100 });

	mouseImage[0] = Sprite::Create(TextureManager::Load("mouseImage.png"),
		{ WinApp::kWindowWidth - 300,WinApp::kWindowHeight - 120 });
	mouseImage[0]->SetSize({ 100, 100 });
	mouseImage[1] = Sprite::Create(TextureManager::Load("mouseImage2.png"),
		{ WinApp::kWindowWidth - 300,WinApp::kWindowHeight - 120 });
	mouseImage[1]->SetSize({ 100, 100 });
	mouseImage[2] = Sprite::Create(TextureManager::Load("mouseImage3.png"),
		{ WinApp::kWindowWidth - 300,WinApp::kWindowHeight - 120 });
	mouseImage[2]->SetSize({ 100, 100 });
	
	mouseMozi = Sprite::Create(TextureManager::Load("MouseMove.png"),
		{ WinApp::kWindowWidth - 200,WinApp::kWindowHeight - 100 });
	mouseMozi->SetSize({ 120,60 });

	spaceMozi = Sprite::Create(TextureManager::Load("spaceMozi.png"),
		{ WinApp::kWindowWidth - 450,WinApp::kWindowHeight - 100 });
	spaceMozi->SetSize({ 120,60 });

	for (int i = 0; i < 4; i++)
	{
		mozi[i]->SetSize({ 200, 200 });
	}

	UI[0] = Sprite::Create(TextureManager::Load("gameStart.png"),
		{ 100,WinApp::kWindowHeight - 300 });
	UI[1] = Sprite::Create(TextureManager::Load("end.png"),
		{ 100,WinApp::kWindowHeight - 200 });

	uiPos[0] = UI[0]->GetPosition();
	uiPos[1] = UI[1]->GetPosition();

	curser->SetSize({100, 100});
}

void Title::Update(Audio* audio, SoundDataManager sdmanager)
{

	if (input->TriggerKey(DIK_SPACE))
	{
		if (titleMenu == start)
		{
			isTitle = false;
		}
		if (titleMenu == end)
		{
			endflag = true;
		}
		audio->PlayWave(sdmanager.pushSE, false, 0.1f);
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
	
	static int time[4] = {150,100,50,0};
	static int timespd[4] = {1,1,1,1};

	for (int i = 0; i < 4; i++)
	{
		time[i] += timespd[i];
		if (time[i] >= 360 || time[i] <= 0)
		{
			timespd[i] = -timespd[i];
		}
	}

	mouseAnimeTime++;
	if (mouseAnimeTime == 60){mouseAnimeNum = 1;}
	if (mouseAnimeTime == 120){mouseAnimeNum = 0;}
	if (mouseAnimeTime == 180){mouseAnimeNum = 2;}
	if (mouseAnimeTime == 240){
		mouseAnimeTime = 0;
		mouseAnimeNum = 0;
	}
	
	mozi[0]->SetPosition({ 200,50 + cosf(DegreeConversionRad(time[0])) * 30.0f});
	mozi[1]->SetPosition({ 400,50 + cosf(DegreeConversionRad(time[1])) * 30.0f });
	mozi[2]->SetPosition({ 600,50 + cosf(DegreeConversionRad(time[2])) * 30.0f });
	mozi[3]->SetPosition({ 800,50 + cosf(DegreeConversionRad(time[3])) * 30.0f });

	curser->SetPosition({ 
		UI[titleMenu]->GetPosition().x - 70,
		UI[titleMenu]->GetPosition().y - 20});


	for (int i = 0; i < 2; i++)
	{
		if (titleMenu == i)
		{
			UI[i]->SetPosition({ 
				uiPos [i].x + cosf(DegreeConversionRad(time[0])) * 10.0f,
				uiPos[i].y  
				});
		}
		else
		{
			UI[i]->SetPosition({ uiPos[i].x,uiPos[i].y });
		}
	}

	//マウスを非表示に
	ShowCursor(false);

	//マウスの現在位置を取得する処理
	POINT point;
	GetCursorPos(&point);

	//マウスでカメラを動かす処理
	Vector2 temp = { 1920 / 2, 1080 / 2 };

	//マウスを固定する処理
	SetCursorPos(temp.x, temp.y);

	//マウスの移動量に応じてカメラを動かす処理
	horizontalRotation += (point.x - temp.x) * 0.01f;
	verticalRotation += (point.y - temp.y) * -0.01f;

	modelTrans.rotation_.y = horizontalRotation;
	modelTrans.rotation_.x = verticalRotation;

	modelTrans.UpdateMatrix();
	modelTrans.TransferMatrix();

}

void Title::Draw()
{
	for (int i = 0; i < 4; i++)
	{
		mozi[i]->Draw();
	}

	for (int i = 0; i < 2; i++)
	{
		UI[i]->Draw();
	}

	curser->Draw();

	alpha->Draw();
	
	mouseImage[mouseAnimeNum]->Draw();
	mouseMozi->Draw();

	if (mouseAnimeTime % 120 >= 60)
	{
		spaceMozi->Draw();
	}
}

void Title::End()
{
	for (int i = 0; i < 4; i++)
	{
		delete mozi[i];
	}
	for (int i = 0; i < 2; i++)
	{
		delete UI[i];
	}
	delete curser;
	for (int i = 0; i < 3; i++)
	{
		delete mouseImage[i];
	}
	delete mouseMozi;
	delete spaceMozi;
	delete alpha;
}

void Title::ModelDraw(ViewProjection view)
{
	playerModel->Draw(modelTrans,view);
	playerModel2->Draw(modelTrans, view);
	playerModel3->Draw(modelTrans, view);
}
