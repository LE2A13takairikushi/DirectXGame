#include "Pause.h"
#include "Collsion.h"

void Pause::End()
{
	for (int i = 0; i < MENU_NUM; i++)
	{
		delete menu[i];
	}
}

void Pause::Initialize()
{
	menu[PAUSE_TITLE] = Sprite::Create(TextureManager::Load("pause.png"),
		{ WinApp::kWindowWidth / 2 - 100 ,WinApp::kWindowHeight / 2 - 150 });
	menu[PAUSE_CONTINUE] = Sprite::Create(TextureManager::Load("continue.png"),
		{ WinApp::kWindowWidth / 2 - 150 ,WinApp::kWindowHeight / 2 });
	menu[PAUSE_END] = Sprite::Create(TextureManager::Load("end.png"),
		{ WinApp::kWindowWidth / 2 - 150,WinApp::kWindowHeight / 2 + 150});
	curser = Sprite::Create(TextureManager::Load("curser.png"),
		{ 0,0 });

	curser->SetSize({ 100, 100 });
}

void Pause::Update(Audio* audio, SoundDataManager sdmanager, bool pIsDead)
{

	if (input->TriggerKey(DIK_ESCAPE)) {
		openMenu = !openMenu;
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
				//audio->PlayWave(sdmanager.curserSE, false, 0.1f);
			}
		}

		if (input->TriggerKey(DIK_S))
		{
			if (menuData != PAUSE_END) {
				menuData++;
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
				//title.NotTitle();
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
	menu[menuData]->GetPosition().y });
}

void Pause::MenuDraw()
{
	if (openMenu)
	{
		//機能しないので一旦ゲーム終了ボタンを非表示に
		for (int i = 0; i < MENU_NUM - 1; i++)
		{
			menu[i]->Draw();
		}
		curser->Draw();
	}
}
