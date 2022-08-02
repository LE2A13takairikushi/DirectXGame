#include "Player.h"

Player::Player()
{
	worldTransform.Initialize();
}

Player::~Player()
{

}

void Player::Initialize(Model *model_, TextureHandle textureHandle_)
{
	worldTransform.Initialize();
	this->model_ = model_;
	this->textureHandle_ = textureHandle_;
}

void Player::Update()
{
	Move();

	worldTransform.UpdateMatrix();
	worldTransform.TransferMatrix();
}

void Player::Move()
{
	Vector3 move = { 0,0,0 };
	float moveSpeed = 0.1f;

	if (input_->PushKey(DIK_W))
	{
		move.z += moveSpeed;
	}
	if (input_->PushKey(DIK_S))
	{
		move.z -= moveSpeed;
	}
	if (input_->PushKey(DIK_D))
	{
		move.x += moveSpeed;
	}
	if (input_->PushKey(DIK_A))
	{
		move.x -= moveSpeed;
	}

	worldTransform.translation_ += move;

}

void Player::Draw(ViewProjection viewProjection_)
{
	model_->Draw(worldTransform, viewProjection_, textureHandle_);
}
