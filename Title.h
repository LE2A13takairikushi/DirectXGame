#pragma once
#include "Input.h"
#include "Sprite.h"
#include "TextureManager.h"
#include "Utill.h"
#include "Model.h"
#include "SoundDataManager.h"

enum TitleMenu
{
	start,
	end,
};

class Title
{
public:
	void Initialize(Model* model, Model* model2, Model* model3, ViewProjection view);
	void Update(Audio* audio,SoundDataManager sdmanager);
	void Draw();

	void End();

	void BackDraw();

	void ModelDraw(ViewProjection view);

	bool IsTitle() { return isTitle; };

	//void NotTitle() { isTitle = false; };
	void TitleBack() { isTitle = true; };

	bool isTitle = true;

	bool endflag = false;

private:
	Input* input = nullptr;

private:

	Sprite* mozi[4] = { nullptr };

	Sprite* UI[2] = { nullptr };

	Sprite* curser = nullptr;

	Sprite* mouseImage[3] = {nullptr};
	Sprite* mouseMozi = nullptr;
	Sprite* spaceMozi = nullptr;
	Sprite* alpha = nullptr;
	Sprite* titleBack = nullptr;
	Sprite* titleImage = nullptr;
	Sprite* ten[3] = { nullptr };

	Model* playerModel = nullptr;
	Model* playerModel2 = nullptr;
	Model* playerModel3 = nullptr;
	WorldTransform modelTrans;

	Vector2 uiPos[2];

	float oldHori = 0;
	float horizontalRotation = 0;

	float oldVer = 0;
	float verticalRotation = 0;

	int titleMenu = TitleMenu::start;

	int mouseAnimeNum = 0;
	int mouseAnimeTime = 0;
};