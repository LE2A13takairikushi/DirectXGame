#include "Player.h"
#include "MyMath.h"

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
	oldmouse = mouse;
	mouse = input_->GetMousePosition();

	prevPos = worldTransform.translation_;

	Move();

	PlayerUpdateMatrix();
	worldTransform.TransferMatrix();
}

void Player::Move()
{
	Vector3 move = { 0,0,0 };
	float moveSpeed = 0.1f;

	if (input_->PushKey(DIK_W))
	{
		AxisZVec.normalize();

		move.x += AxisZVec.x;
		move.x *= moveSpeed;

		//move.y += AxisZVec.y;
		//move.y *= moveSpeed;

		move.z += AxisZVec.z;
		move.z *= moveSpeed;
	}

	if (input_->TriggerKey(DIK_SPACE))
	{
		jumpSpd = 10;
	
		Vector3 tempPos;

		tempPos = worldTransform.translation_;
		move.y += (worldTransform.translation_.y - prevPos.y) + jumpSpd;
		prevPos.y = tempPos.y;

		jumpSpd = 1.0f;
	}

	//move.y += -glavitySpd;
	//if (input_->PushKey(DIK_S))
	//{
	//	move.z -= moveSpeed;
	//}
	//if (input_->PushKey(DIK_D))
	//{
	//	move.x += moveSpeed;
	//}
	//if (input_->PushKey(DIK_A))
	//{
	//	move.x -= moveSpeed;
	//}


	horizontalRotation += (mouse.x - oldmouse.x) * 0.01f;
	verticalRotation += (mouse.y - oldmouse.y) * 0.01f;

	//if (horizontalRotation > 90) horizontalRotation = 90;
	if (verticalRotation > PIf / 2 - FreqConversionRad(1.0f)) verticalRotation = PIf / 2 - FreqConversionRad(1.0f);
	if (verticalRotation < -PIf / 2 + FreqConversionRad(1.0f)) verticalRotation = -PIf / 2 + FreqConversionRad(1.0f);
	

	worldTransform.translation_ += move;

}

void Player::Draw(ViewProjection viewProjection_)
{
	model_->Draw(worldTransform, viewProjection_, textureHandle_);
}

void Player::PlayerUpdateMatrix()
{
	worldTransform.CreateScale();
	
	worldTransform.rotation_.y = horizontalRotation;
	worldTransform.CreateRot();

	AxisXVec = worldTransform.matRot.ExtractAxisX();

	//AxisYVec = worldTransform.matRot.ExtractAxisY();

	worldTransform.CreateTrans();

	worldTransform.matWorld_.MatrixUint();
	//スケーリング行列
	worldTransform.matWorld_ *= worldTransform.matScale;
	//回転行列
	//worldTransform.matWorld_ *= Matrix4::RotArbitrary(AxisYVec, horizontalRotation);
	worldTransform.matWorld_ *= worldTransform.matRot;
	worldTransform.matWorld_ *= Matrix4::RotArbitrary(AxisXVec, verticalRotation);

	//平行移動行列
	worldTransform.matWorld_ *= worldTransform.matTrans;

	AxisZVec = worldTransform.matWorld_.ExtractAxisZ();
}
