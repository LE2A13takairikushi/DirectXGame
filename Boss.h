#pragma once
#include "BoxObj.h"
#include "DebugText.h"

enum BossPartsName
{
	body,
	weekPoint,
	bossPartsNum,
};

enum ActPhase
{
	jump,
	setTarget,
	fall,
	none,
	PhaseNum,
};

class Boss
{
public:
	void Initialize(Model* model, TextureHandle tex);
	void Update(Vector3 pos, Vector3 scale, Vector3 targetPos);
	void Draw(ViewProjection view);

	void SetPos(Vector3 pos);
	void SetScale(Vector3 scale);

	DebugText* dT = DebugText::GetInstance();

	bool IsDead() { return isDead; };

private:

	Vector3 move = {0,0,0};
	float jumpSpd = 0;
	bool isDead = false; 

	int fallTimer = 0;

	float moveSpd = 2.0f;
	float gravity = 0.01f;

	Vector3 targetDirectVec = {0,0,0};

	ActPhase phase = ActPhase::jump;

	BoxObj bossParts[bossPartsNum];
};