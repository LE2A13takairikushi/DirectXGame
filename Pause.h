#pragma once
#include "Sprite.h"
#include "TextureManager.h"
#include "Utill.h"
#include "WinApp.h"
#include "Input.h"
#include "DebugText.h"

enum menu_Data
{
	PAUSE_TITLE,
	PAUSE_CONTINUE,
	PAUSE_END,
	MENU_NUM,
};

class Pause
{
public:
	Input* input = Input::GetInstance();
	DebugText* debugText = DebugText::GetInstance();

	void Initialize();
	void Update();
	void MenuDraw();

	void End();

	bool IsMenuOpen() { return openMenu; };

private:

	Sprite* menu[MENU_NUM] = { nullptr };
	Sprite* curser = nullptr;
	TextureHandle tex = 0;

	Vector2 mousePos;
	Vector2 mouseR = {1,1};

	bool openMenu = false;

	int menuData = PAUSE_CONTINUE;
};