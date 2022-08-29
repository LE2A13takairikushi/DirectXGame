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

void Pause::Update()
{

	if (input->TriggerKey(DIK_W))
	{
		if (menuData > PAUSE_CONTINUE)menuData--;
	}

	if (input->TriggerKey(DIK_S))
	{
		if (menuData < PAUSE_END)menuData++;
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

	curser->SetPosition({
	menu[menuData]->GetPosition().x - 70,
	menu[menuData]->GetPosition().y });

	if (input->TriggerKey(DIK_ESCAPE)) {
		openMenu = !openMenu;
	}

	switch (openMenu)
	{
	case true:
		//�}�E�X��\��
		ShowCursor(true);
		break;
	case false:
		//�}�E�X���\����
		ShowCursor(false);
		//�}�E�X�ŃJ�����𓮂�������
		Vector2 temp = { 1920 / 2, 1080 / 2 };
		//�}�E�X���Œ肷�鏈��
		SetCursorPos(temp.x, temp.y);
		break;
	}
}

void Pause::MenuDraw()
{
	if (openMenu)
	{
		//�@�\���Ȃ��̂ň�U�Q�[���I���{�^�����\����
		for (int i = 0; i < MENU_NUM - 1; i++)
		{
			menu[i]->Draw();
		}
		curser->Draw();
	}
}
