#include "Pause.h"
#include "Collsion.h"
#include "MyMath.h"

void Pause::End()
{
	for (int i = 0; i < MENU_NUM; i++)
	{
		delete menu[i];
		delete backWhite[i];
	}
	delete curser;
	delete alpha;
}

void Pause::Initialize()
{
	menu[PAUSE_TITLE] = Sprite::Create(TextureManager::Load("pause.png"),
		{ WinApp::kWindowWidth / 2 - 100 ,WinApp::kWindowHeight / 2 - 150 });
	menu[PAUSE_CONTINUE] = Sprite::Create(TextureManager::Load("remove.png"),
		{ WinApp::kWindowWidth / 2 - 150 ,WinApp::kWindowHeight / 2 });
	menu[PAUSE_END] = Sprite::Create(TextureManager::Load("titleback.png"),
		{ WinApp::kWindowWidth / 2 - 150,WinApp::kWindowHeight / 2 + 150});
	curser = Sprite::Create(TextureManager::Load("curser.png"),
		{ 0,0 });
	alpha = Sprite::Create(TextureManager::Load("alpha.png"),
		{ 200,100 },{1,1,1,0.5f});
	alpha->SetSize({ 900,600 });

	for (int i = 0; i < MENU_NUM; i++)
	{
		SetBackWhite(i);
	}

	curser->SetSize({ 100, 100 });
	for (int i = 0; i < MENU_NUM; i++)
	{
		uiPos[i] = menu[i]->GetPosition();
	}
}

void Pause::Update(Audio* audio, SoundDataManager sdmanager, bool pIsDead)
{

	if (input->TriggerKey(DIK_ESCAPE)) {
		openMenu = !openMenu;
	}

	static int time = 0;
	static int timespd = 1;

	time += timespd;
	if (time >= 360 || time <= 0)
	{
		timespd = -timespd;
	}

	for (int i = 0; i < MENU_NUM; i++)
	{
		if (menuData == i)
		{
			menu[i]->SetPosition({
				uiPos[i].x + cosf(DegreeConversionRad(time)) * 10.0f,
				uiPos[i].y
				});
			backWhite[i]->SetPosition({
				uiPos[i].x + cosf(DegreeConversionRad(time)) * 10.0f - 10,
				uiPos[i].y - 10
				});
		}
		else
		{
			menu[i]->SetPosition({ uiPos[i].x,uiPos[i].y });
			backWhite[i]->SetPosition({
					uiPos[i].x - 10,
					uiPos[i].y - 10
				});
		}
	}

	switch (openMenu)
	{
	case true:
		//マウスを表示
		ShowCursor(true);

		if (input->TriggerKey(DIK_W))
		{
			if (menuData != PAUSE_CONTINUE) {
				menuData--;
				time = 0;
				//audio->PlayWave(sdmanager.curserSE, false, 0.1f);
			}
		}

		if (input->TriggerKey(DIK_S))
		{
			if (menuData != PAUSE_END) {
				menuData++;
				time = 0;
				//audio->PlayWave(sdmanager.curserSE, false, 0.1f);
			}
		}

		if (input->TriggerKey(DIK_SPACE))
		{
			if (menuData == PAUSE_CONTINUE)
			{
				openMenu = false;
			}
			if (menuData == PAUSE_END)
			{
				titleBack = true;
			}
		}

		break;
	case false:
		if (pIsDead == false)
		{
			//マウスを非表示に
			ShowCursor(false);
			//マウスでカメラを動かす処理
			Vector2 temp = { 1920 / 2, 1080 / 2 };
			//マウスを固定する処理
			SetCursorPos(temp.x, temp.y);
		}
		break;
	}

	curser->SetPosition({
	menu[menuData]->GetPosition().x - 70,
	menu[menuData]->GetPosition().y - 20});
}

void Pause::MenuDraw()
{
	if (openMenu)
	{
		alpha->Draw();

		for (int i = 0; i < MENU_NUM; i++)
		{
			backWhite[i]->Draw();
			menu[i]->Draw();
		}
		curser->Draw();
	}
}

void Pause::Reset()
{
	openMenu = false;
	menuData = PAUSE_CONTINUE;
}

void Pause::SetBackWhite(int num)
{
	backWhite[num] =
		Sprite::Create(TextureManager::Load("white.png"),
			{ WinApp::kWindowWidth / 2,50 });
	backWhite[num]->SetSize({
		menu[num]->GetSize().x + 20,
		menu[num]->GetSize().y + 20
		}
	);
	backWhite[num]->SetPosition({
		menu[num]->GetPosition().x - 10,
		menu[num]->GetPosition().y - 10
		});
}