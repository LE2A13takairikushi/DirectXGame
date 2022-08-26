#pragma once
#include "BoxObj.h"
#include "DebugText.h"
#include "VanishParticleManager.h"

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
	void Initialize(Model* model, TextureHandle tex,TextureHandle weekTex);
	void Update(Vector3 pos, Vector3 scale, Vector3 targetPos,VanishParticleManager& vpManager);
	void Draw(ViewProjection view, float mouseVertRota);

	void SetPos(Vector3 pos);
	void SetScale(Vector3 scale);

	DebugText* dT = DebugText::GetInstance();

	bool IsDead() { return isDead; };

	void HPDraw();

	/// <summary>
	/// ボスのボックスを返す
	/// 0なら体を、1なら弱点を返す
	/// </summary>
	BoxObj GetBossPart(int bossPartsNum);

	void OnBodyColision();
	void OnWeekColision();

private:

	static const int HPINIT = 300;
	float hitGaugeOneSize = 0;
	int hitPoint = HPINIT;

	Vector3 move = {0,0,0};
	float jumpSpd = 0;
	bool isDead = false; 

	int fallTimer = 0;

	float moveSpd = 2.0f;
	float gravity = 0.01f;

	Vector3 targetDirectVec = {0,0,0};

	ActPhase phase = ActPhase::jump;

	BoxObj bossParts[bossPartsNum];

	TextureHandle exclamation;
	Sprite* hitPointGauge = nullptr;

	BoxObj exclamationObj;

	Vector3 Shake = { 0,0,0 };
};