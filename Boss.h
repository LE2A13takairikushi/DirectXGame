#pragma once
#include "BoxObj.h"
#include "DebugText.h"
#include "VanishParticleManager.h"
#include "EnemyBullet.h"

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
	miniJump,
	superAttack,
	appearance,
	dead,
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
	void Viblation();
	void WeekViblation();
	void ShakeUpdate();
	void Attack(Vector3 velocity);

private:
	Vector3 initScale = { 10,10,10 };

	BoxObj bodyShakeBox;
	BoxObj weekShakeBox;

	Vector3 scalePlus = { 0,0,0 };
	float scaleSpd = 0.03f;
	int scalePTimer = 0;

	static const int HPINIT = 300;
	float hitGaugeOneSize = 0;
	int hitPoint = HPINIT;
	bool isFormChange = false;
	bool onGround = false;

	Vector3 move = {0,0,0};
	float jumpSpd = 0;
	bool isDead = false; 

	int fallTimer = 0;
	int miniJumpTimer = 0;
	int bulletTimer = 0;

	int stumpStock = 0;

	float moveSpd = 2.0f;
	float gravity = 0.01f;

	Vector3 targetDirectVec = {0,0,0};

	ActPhase phase = ActPhase::appearance;

	BoxObj bossParts[bossPartsNum];

	TextureHandle exclamation;
	Sprite* hitPointGauge = nullptr;

	BoxObj exclamationObj;

	Vector3 shake = { 0,0,0 };
	Vector3 weekShake = { 0,0,0 };

	bool isShake = false;
	int shakeTimer = 0;	
	bool isWeekShake = false;
	int weekShakeTimer = 0;

	Vector3 prevPos = { 0,0,0 };

	std::list<std::unique_ptr<EnemyBullet>> bullets_;
	Model* bulletModel = nullptr;
};