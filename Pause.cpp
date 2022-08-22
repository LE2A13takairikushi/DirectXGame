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

}

void Pause::Update()
{
	POINT point;
	GetCursorPos(&point);

	mousePos = { (float)point.x,(float)point.y };

	for (int i = 0; i < MENU_NUM; i++)
	{
		if (BoxCollsion(
			menu[i]->GetPosition(), mousePos,
			menu[i]->GetSize(), mouseR)&&
			input->IsTriggerMouse(0))
		{
			if (menu[PAUSE_CONTINUE]) {
				openMenu = false; 
			}
			if (menu[PAUSE_END]){
				
			}
		}
	}

	debugText->SetPos(50, 70);
	debugText->Printf("menupos %f %f",
		menu[PAUSE_CONTINUE]->GetPosition().x,menu[PAUSE_CONTINUE]->GetPosition().y);
	debugText->SetPos(50, 90);
	debugText->Printf("menupos2 %f %f",
		menu[PAUSE_END]->GetPosition().x, menu[PAUSE_END]->GetPosition().y);
	debugText->SetPos(50, 110);
	debugText->Printf("mousePos %f %f",
		mousePos.x, mousePos.y);



	if (input->TriggerKey(DIK_ESCAPE)) {
		openMenu = !openMenu;
	}

	switch (openMenu)
	{
	case true:
		//マウスを表示
		ShowCursor(true);
		break;
	case false:
		//マウスを非表示に
		ShowCursor(false);
		//マウスでカメラを動かす処理
		Vector2 temp = { 1920 / 2, 1080 / 2 };
		//マウスを固定する処理
		SetCursorPos(temp.x, temp.y);
		break;
	}
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
	}
}
