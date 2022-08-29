#pragma once
#include "Input.h"
#include "Sprite.h"
#include "TextureManager.h"
#include "Utill.h"
#include "Model.h"

enum TitleMenu
{
	start,
	option,
	end,
};

class Title
{
public:
	void Initialize(Model* model, Model* model2, Model* model3, ViewProjection view);
	void Update();
	void Draw();

	void ModelDraw(ViewProjection view);

	bool IsTitle() { return isTitle; };

	void NotTitle() { isTitle = false; };

private:
	Input* input = nullptr;

private:
	bool isTitle = true;

	Sprite* mozi[4] = { nullptr };

	Sprite* UI[3] = { nullptr };

	Sprite* curser = nullptr;

	Model* playerModel = nullptr;
	Model* playerModel2 = nullptr;
	Model* playerModel3 = nullptr;
	WorldTransform modelTrans;

	int titleMenu = TitleMenu::start;
};