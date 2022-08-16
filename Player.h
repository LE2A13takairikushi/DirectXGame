#pragma once
#include "object.h"
#include "ViewProjection.h"
#include "Input.h"
#include "Utill.h"
#include "PlayerBullet.h"
#include "DebugText.h"
#include <memory>
#include <list>

class Player : public object
{
public:
	Player();
	~Player();

	//なまぽでdeleteできないので危ない
	Input* input_ = Input::GetInstance();
	DebugText* debugText = DebugText::GetInstance();

	//横ベクトル
	Vector3 sideVec = {0,0,0};
	//正面ベクトル
	Vector3 centerVec = {0,0,0};
	//上方向ベクトル
	Vector3 upVec = { 0,1,0 };

	void Initialize(Model* model_);
	void SetSpawnPos(Vector3 pos);
	void Update();
	void UpdateMatrixAndMove();
	void Draw(ViewProjection viewProjection_);

	void JumpReady();

	void CheckHitBox(WorldTransform box);

	void StockPlus();

	bool isJumpCheck = false;
	bool hitGround = false;
	bool hitCeiling = false;

	const std::list<std::unique_ptr<PlayerBullet>>& GetBullets() { return bullets_; }

private:

	WorldTransform prevPos;

	WorldTransform modelTransform;

	//移動した値
	Vector3 move = {0,0,0};

	Vector3 moveVec;

	Vector3 respawnPos;

	//縦方向の回転角度
	float verticalRotation = 0;
	float horizontalRotation = 0;

	//マウスの感度
	float mouseSpd = 0.01f;

	//残基
	int stock = 3;

	//移動関係
	float moveSpeed = 0.1f;
	float jumpSpd = 0.0f;
	float gravity = 0.01f;

	std::list<std::unique_ptr<PlayerBullet>> bullets_;

	void Move();
	void InputMove();
	void Attack();

	void PlayerUpdateMatrix();
};

