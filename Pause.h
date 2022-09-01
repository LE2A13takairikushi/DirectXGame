#pragma once
#include "Sprite.h"
#include "TextureManager.h"
#include "Utill.h"
#include "WinApp.h"
#include "Input.h"
#include "DebugText.h"
#include "SoundDataManager.h"

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
	void Update(Audio* audio,SoundDataManager sdmanager,bool pIsDead, bool notOpenResult);
	void MenuDraw();

	void End();

	bool IsMenuOpen() { return openMenu; };

	bool titleBack = false;

	void Reset();

private:
	void SetBackWhite(int num);
	Sprite* backWhite[MENU_NUM] = { nullptr };

	Sprite* menu[MENU_NUM] = { nullptr };
	Sprite* curser = nullptr;
	Sprite* alpha = nullptr;

	TextureHandle tex = 0;

	Vector2 mousePos;
	Vector2 mouseR = {1,1};

	Vector2 uiPos[MENU_NUM];

	bool openMenu = false;

	int menuData = PAUSE_CONTINUE;
};