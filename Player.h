#pragma once
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "Model.h"
#include "Input.h"
#include "Utill.h"

class Player
{
public:
	Player();
	~Player();

	WorldTransform worldTransform;
	Model* model_ = nullptr;
	TextureHandle textureHandle_ = 0;

	Input* input_ = Input::GetInstance();

	//�c�����̉�]�p�x
	float verticalRotation = 0;
	float horizontalRotation = 0;

	//���x�N�g��
	Vector3 AxisXVec = {0,0,0};
	//���ʃx�N�g��
	Vector3 AxisZVec = {0,0,0};

	Vector3 AxisYVec = { 0,0,0 };

	Vector2 oldmouse;
	Vector2 mouse;

	Vector3 prevPos;

	float glavitySpd = 0.1f;

	float jumpSpd = 1.0f;

	void Initialize(Model* model_, TextureHandle textureHandle_);
	void Update();
	void Draw(ViewProjection viewProjection_);

	void PlayerUpdateMatrix();

private:
	void Move();
};

