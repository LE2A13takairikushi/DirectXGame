#pragma once
#include "object.h"
#include "ViewProjection.h"
#include "Input.h"
#include "Utill.h"
#include "PlayerBullet.h"
#include "DebugText.h"
#include <memory>
#include <list>

#include "VanishParticleManager.h"

class Player : public object
{
public:

	//なまぽでdeleteできないので危ない
	Input* input_ = Input::GetInstance();
	DebugText* debugText = DebugText::GetInstance();

	//横ベクトル
	Vector3 sideVec = {0,0,0};
	//正面ベクトル
	Vector3 centerVec = {0,0,0};
	//上方向ベクトル
	Vector3 upVec = { 0,1,0 };

	void End();

	void Initialize(Model* model_,Model* bodyModel, Model* taiyaModel);
	void SetSpawnPos(Vector3 pos);
	void Update(VanishParticleManager& vpmanager);
	void UpdateMatrixAndMove();
	void Draw(ViewProjection viewProjection_);
	void SpriteDraw();

	bool CheckHitBox(WorldTransform box);

	void JumpReady();
	void StockPlus();
	void OnDamage(int damage);

	//無敵時間さん！？
	int mutekiTimer = 0;

	float GetJumpSpd() { return jumpSpd; };

	//強制ジャンプイベント用
	void EnforceJumpOnCol();

	//ゴール用
	void EnforceGoalOnCol();

	bool isJumpCheck = false;
	
	bool IsDash() { return isDash; };
	void SetMuteki() { mutekiTimer = MUTEKI_TIME; };

	const std::list<std::unique_ptr<PlayerBullet>>& GetBullets() { return bullets_; }

	float GetMouseVRota() { return verticalRotation; };

	float enforceJumpSpd = 2.0f;

private:

	WorldTransform prevPos;


	bool hitGround = false;
	bool hitCeiling = false;

	bool oldIsJumpCheck = false;

	bool isBossMove = false;

	bool isDamageHit = false;

	//ステータス関係
	int bulletCool = 0;
	static const int MAX_BULLET_COOL = 30;

	//移動した値
	Vector3 move = {0,0,0};

	//移動方向のベクトル
	Vector3 moveVec;

	Vector3 tempMoveVec;
	Vector3 tempSideVec;

	Vector3 respawnPos;

	//縦方向の回転角度
	float verticalRotation = 0;
	float horizontalRotation = 0;

	//マウスの感度
	float mouseSpd = 0.01f;

	//hp
	int stock = 3;
	int hp = 30;
	static const int MUTEKI_TIME = 120;

	//移動関係

	float InitMoveSpd = 0.21f;
	float moveSpeed = InitMoveSpd;
	float jumpSpd = 0.0f;
	float gravity = 0.01f;

	//スキル関係
	float oldMoveSpd = 0;
	int dashCoolTime = 0;
	bool isDash = false;

	//描画関係
	std::list<std::unique_ptr<PlayerBullet>> bullets_;

	Model* bodyModel = nullptr;
	Model* taiyaModel = nullptr;

	static const int MAX_STACK = 10;
	Sprite* newstocks[MAX_STACK] = { nullptr };

	Vector2 HPPOS_INIT[MAX_STACK];

	Sprite* skillIconSp = nullptr;
	Sprite* skillCoolAlpha = nullptr;
	Sprite* backWhite = nullptr;
	Sprite* backWhite2 = nullptr;
	Sprite* lShift = nullptr;
	Sprite* shotIconSp = nullptr;

	Sprite* hpRed = nullptr;

	void Move(VanishParticleManager& vpmanager);
	void Dash(VanishParticleManager& vpmanager);
	void InputMove();
	void Attack();
	void DamageHitEffect();

	void PlayerUpdateMatrix();
};

