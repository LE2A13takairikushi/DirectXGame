#include "Result.h"
#include "WinApp.h"
#include "MyMath.h"

void Result::Initialize()
{
	NumInit();

	input = Input::GetInstance();

	back = Sprite::Create(TextureManager::Load("alpha.png"),
		{100,30},{1,1,1,0.5f});
	back->SetSize({ WinApp::kWindowWidth - 200,WinApp::kWindowHeight - 90 });

	resultString[0] =
		Sprite::Create(TextureManager::Load("result.png"),
			{ WinApp::kWindowWidth / 2 - 100,50 });
	resultString[1] =
		Sprite::Create(TextureManager::Load("clear.png"),
			{ WinApp::kWindowWidth / 2 - 400,150 });
	resultString[2] =
		Sprite::Create(TextureManager::Load("allheart.png"),
			{ WinApp::kWindowWidth / 2 - 200,150 });
	resultString[3] =
		Sprite::Create(TextureManager::Load("nodamage.png"),
			{ WinApp::kWindowWidth / 2 + 200,150 });
	resultString[4] =
		Sprite::Create(TextureManager::Load("collectheart.png"),
			{ WinApp::kWindowWidth / 2 - 450,420 });

	resultString[5] = 
		Sprite::Create(TextureManager::Load("start.png"),
			{ WinApp::kWindowWidth / 2 - 30,450 });
	resultString[6] =
		Sprite::Create(TextureManager::Load("checkPointMozi.png"),
			{ WinApp::kWindowWidth / 2 - 30,550 });

	for (int i = 0; i < num; i++)
	{
		SetBackWhite(i);
	}

	maxNum = Sprite::Create(TextureManager::Load("num\\5.png"),
		{
			resultString[4]->GetPosition().x + 300,
			resultString[4]->GetPosition().y + 100
		});

	numberGraph[10]->SetPosition({
			resultString[4]->GetPosition().x + 200,
			resultString[4]->GetPosition().y + 100
		});

	starGraph[0] = Sprite::Create(TextureManager::Load("star.png"),
		{
			resultString[1]->GetPosition().x + 80,
			resultString[1]->GetPosition().y + 120
		});
	starGraph[1] = Sprite::Create(TextureManager::Load("star.png"),
		{
			resultString[2]->GetPosition().x + 180,
			resultString[2]->GetPosition().y + 120
		});
	starGraph[2] = Sprite::Create(TextureManager::Load("star.png"),
		{
			resultString[3]->GetPosition().x + 80,
			resultString[3]->GetPosition().y + 120
		});

	starBlankGraph[0] = Sprite::Create(TextureManager::Load("star_blank.png"),
		{
			resultString[1]->GetPosition().x + 80,
			resultString[1]->GetPosition().y + 120
		});
	starBlankGraph[1] = Sprite::Create(TextureManager::Load("star_blank.png"),
		{
			resultString[2]->GetPosition().x + 180,
			resultString[2]->GetPosition().y + 120
		});
	starBlankGraph[2] = Sprite::Create(TextureManager::Load("star_blank.png"),
		{
			resultString[3]->GetPosition().x + 80,
			resultString[3]->GetPosition().y + 120
		});
	for (int i = 0; i < 3; i++)
	{
		starGraph[i]->SetSize({ 0,0 });
		starGraph[i]->SetAnchorPoint({ 0.5f,0.5f });
		starBlankGraph[i]->SetSize({ 0,0 });
		starBlankGraph[i]->SetAnchorPoint({ 0.5f,0.5f });
	}
	
	heartGraph = Sprite::Create(TextureManager::Load("life.png"),
		{
			resultString[4]->GetPosition().x - 50,
			resultString[4]->GetPosition().y + 80
		});
	heartGraph->SetSize({100, 100});

	curser = Sprite::Create(TextureManager::Load("curser.png"),
		{ 0,0 });
	curser->SetSize({ 100, 100 });

	uiPos[0] = resultString[5]->GetPosition();
	uiPos[1] = resultString[6]->GetPosition();
}

void Result::Update(int getHeart,bool nohitFlag,bool clearFlag)
{
	static int time = 0;
	static int timespd = 1;

	time += timespd;
	if (time >= 360 || time <= 0)
	{
		timespd = -timespd;
	}

	if (input->TriggerKey(DIK_S))
	{
		if (curserNum != checkpointStart)
		{
			curserNum++;
			time = 0;
		}
	}
	if (input->TriggerKey(DIK_W))
	{
		if (curserNum != initStart)
		{
			curserNum--;
			time = 0;
		}
	}

	for (int i = 0; i < 2; i++)
	{
		if (curserNum == i)
		{
			resultString[i + 5]->SetPosition({
				uiPos[i].x + cosf(DegreeConversionRad(time)) * 10.0f,
				uiPos[i].y
				});
			backWhite[i + 5]->SetPosition({
				uiPos[i].x + cosf(DegreeConversionRad(time)) * 10.0f - 10,
				uiPos[i].y - 10
				});
		}
		else
		{
			resultString[i + 5]->SetPosition({ uiPos[i].x,uiPos[i].y });
			backWhite[i + 5]->SetPosition({
					uiPos[i].x - 10,
					uiPos[i].y - 10
				});
		}
	}

	curser->SetPosition({
	resultString[curserNum + 5]->GetPosition().x - 70,
	resultString[curserNum + 5]->GetPosition().y - 20 });

	this->nohitFlag = nohitFlag;
	this->clearFlag = clearFlag;

	allHeartFlag = getHeart >= 5;

	static float a[3] = {0};
	if (isResult == false)
	{
		a[0] = 0;
		a[1] = 0;
		a[2] = 0;
	}

	for (int i = 0; i < 3; i++)
	{
		starGraph[i]->SetSize({ a[i],a[i] });
		starBlankGraph[i]->SetSize({ a[i],a[i] });
	}

	if (starGraph[0]->GetSize().x <= 100)
	{
		a[0] += 5;
	}
	if (starGraph[0]->GetSize().x >= 100 && 
		starGraph[1]->GetSize().x < 100)
	{
		a[1] += 5;
	}
	if (starGraph[1]->GetSize().x >= 100 && 
		starGraph[2]->GetSize().x < 100)
	{
		a[2] += 5;
	}

	if (starGraph[2]->GetSize().x >= 100)
	{
		static float scaleTimer = 0;
		static float scaleSpd = 1;

		if (scaleTimer > 60.0f || scaleTimer < -60.0f)scaleSpd = -scaleSpd;
		scaleTimer += scaleSpd;

		if (clearFlag)
		{
			a[0] += scaleTimer * 0.01f;
		}
		if (allHeartFlag)
		{
			a[1] += scaleTimer * 0.01f;
		}
		if (nohitFlag)
		{
			a[2] += scaleTimer * 0.01f;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		starGraph[i]->SetSize({ a[i],a[i] });
		starBlankGraph[i]->SetSize({ a[i],a[i] });
	}

	if (isResult)
	{
		for (int i = 0; i < 5 + 1; i++)
		{
			if (i == getHeart)
			{
				numberGraph[getHeart]->SetPosition(
					{
						resultString[4]->GetPosition().x + 100,
						resultString[4]->GetPosition().y + 100
					}
				);
			}
		}
	}
}

void Result::Draw()
{
	back->Draw();
	for (int i = 0; i < num; i++)
	{
		backWhite[i]->Draw();
		resultString[i]->Draw();
	}
	for (int i = 0; i < 11; i++)
	{
		numberGraph[i]->Draw();
	}
	if (clearFlag)
	{
		starGraph[0]->Draw();
	}
	else
	{
		starBlankGraph[0]->Draw();
	}
	if (allHeartFlag)
	{
		starGraph[1]->Draw();
	}
	else
	{
		starBlankGraph[1]->Draw();
	}
	if (nohitFlag)
	{
		starGraph[2]->Draw();
	}
	else
	{
		starBlankGraph[2]->Draw();
	}

	heartGraph->Draw();
	maxNum->Draw();
	curser->Draw();
}

void Result::End()
{
	for (int i = 0; i < num; i++)
	{
		delete resultString[i];
		delete backWhite[i];
	}
	for (int i = 0; i < 11; i++)
	{
		delete numberGraph[i];
	}
	delete heartGraph;
	delete maxNum;
}

void Result::SetBackWhite(int num)
{
	backWhite[num] =
		Sprite::Create(TextureManager::Load("white.png"),
			{ WinApp::kWindowWidth / 2,50 });
	backWhite[num]->SetSize({
		resultString[num]->GetSize().x + 10,
		resultString[num]->GetSize().y + 10
		}
	);
	backWhite[num]->SetPosition({
		resultString[num]->GetPosition().x - 10,
		resultString[num]->GetPosition().y - 10
		});
}

void Result::NumInit()
{
	numberGraph[0] = Sprite::Create(TextureManager::Load("num\\0.png"),
		{ -100,0 });
	numberGraph[1] = Sprite::Create(TextureManager::Load("num\\1.png"),
		{ -100,0 });
	numberGraph[2] = Sprite::Create(TextureManager::Load("num\\2.png"),
		{ -100,0 });
	numberGraph[3] = Sprite::Create(TextureManager::Load("num\\3.png"),
		{ -100,0 });
	numberGraph[4] = Sprite::Create(TextureManager::Load("num\\4.png"),
		{ -100,0 });
	numberGraph[5] = Sprite::Create(TextureManager::Load("num\\5.png"),
		{ -100,0 });
	numberGraph[6] = Sprite::Create(TextureManager::Load("num\\6.png"),
		{ -100,0 });
	numberGraph[7] = Sprite::Create(TextureManager::Load("num\\7.png"),
		{ -100,0 });
	numberGraph[8] = Sprite::Create(TextureManager::Load("num\\8.png"),
		{ -100,0 });
	numberGraph[9] = Sprite::Create(TextureManager::Load("num\\9.png"),
		{ -100,0 });
	numberGraph[10] = Sprite::Create(TextureManager::Load("num\\slash.png"),
		{ -100,0 });
}

void Result::NumPosInit()
{
	for (int i = 0; i < 10; i++)
	{
		numberGraph[i]->SetPosition({ -100,0 });
	}
}
