#pragma once
#include "object.h"
#include "ViewProjection.h"
#include "Input.h"
#include "Utill.h"
#include "PlayerBullet.h"
#include <memory>
#include <list>

class Player : public object
{
public:
	Player();
	~Player();

	Input* input_ = Input::GetInstance();

	//���x�N�g��
	Vector3 sideVec = {0,0,0};
	//���ʃx�N�g��
	Vector3 centerVec = {0,0,0};
	//������x�N�g��
	Vector3 upVec = { 0,0,0 };

	void Initialize(Model* model_, TextureHandle textureHandle_);
	void Update();
	void Draw(ViewProjection viewProjection_);

	void NotGravity();

	bool isGroundCol = false;

	const std::list<std::unique_ptr<PlayerBullet>>& GetBullets() { return bullets_; }

private:

	Vector3 prevPos;

	//�ړ������l
	Vector3 move = {0,0,0};

	//�c�����̉�]�p�x
	float verticalRotation = 0;
	float horizontalRotation = 0;

	//�}�E�X�̊��x
	float mouseSpd = 0.01f;

	//�W�����v�֌W
	float jumpSpd = 1.0f;
	float gravity = 0.1f;

	std::list<std::unique_ptr<PlayerBullet>> bullets_;

	void Move();
	void InputMove();
	void Attack();

	void PlayerUpdateMatrix();
};

