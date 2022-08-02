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

	//ècï˚å¸ÇÃâÒì]äpìx
	float verticalRotation = 0;
	float horizontalRotation = 0;

	void Initialize(Model* model_, TextureHandle textureHandle_);
	void Update();
	void Draw(ViewProjection viewProjection_);

private:
	void Move();
};

