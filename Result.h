#pragma once
#include "TextureManager.h"
#include "Sprite.h"
#include "Input.h"

enum startChoese
{
	initStart,
	checkpointStart,
	choeseNum,
};

class Result
{
public:
	void Initialize();
	void Update(int getHeart, bool noHitFlag, bool clearFlag);
	void Draw();

	void End();
	void SetBackWhite(int num);

	bool isResult = false;

	int curserNum = 0;

private:
	Input* input = nullptr;

	void NumInit();
	void NumPosInit();

	static const int num = 7;
	Sprite* resultString[num] = { nullptr };
	Sprite* backWhite[num] = { nullptr };

	Sprite* numberGraph[11] = { nullptr };
	Sprite* maxNum = nullptr;

	Sprite* starGraph[3] = { nullptr };
	Sprite* starBlankGraph[3] = { nullptr };

	Sprite* heartGraph = nullptr;
	Sprite* back = nullptr;

	Sprite* curser = nullptr;

	Vector2 uiPos[2];

	//ƒŠƒUƒ‹ƒg‚ÉŠÖŒW‚·‚é—v‘f
	int getHeart = 0;

	bool nohitFlag = false;
	bool clearFlag = false;
	bool allHeartFlag = false;

	bool isUpdateHeartNum = false;

	//bool resultFlag = false;
};

