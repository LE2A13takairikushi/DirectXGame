#include "Player.h"
#include "MyMath.h"
#include <cassert>
using namespace std;

Player::Player()
{
	worldTransform.Initialize();
}

Player::~Player()
{

}

void Player::Initialize(Model *model_, TextureHandle textureHandle_)
{
	assert(model_);

	worldTransform.Initialize();
	this->model_ = model_;
	this->textureHandle_ = textureHandle_;
}

void Player::Update()
{
	//�e�̍폜
	bullets_.remove_if([](std::unique_ptr<PlayerBullet>& bullet) {
		return bullet->IsDead();
		});

	oldmouse = mouse;
	mouse = input_->GetMousePosition();

	prevPos = worldTransform.translation_;

	Move();

	if (input_->IsTriggerMouse(0))
	{
		Attack();
	}

	for (std::unique_ptr<PlayerBullet>& bullet : bullets_)
	{
		bullet->Update();
	}

	PlayerUpdateMatrix();
	worldTransform.TransferMatrix();
}

void Player::InputMove()
{
	float moveSpeed = 0.1f;

	//���ʂɈړ����鏈��
	centerVec.normalize();
	move.x += (centerVec.x * moveSpeed) * input_->PushKey(DIK_W);
	move.z += (centerVec.z * moveSpeed) * input_->PushKey(DIK_W);

	centerVec.normalize();
	move.x += (centerVec.x * moveSpeed) * -input_->PushKey(DIK_S);
	move.z += (centerVec.z * moveSpeed) * -input_->PushKey(DIK_S);

	sideVec.normalize();
	move.x += (sideVec.x * moveSpeed) * input_->PushKey(DIK_D);
	move.z += (sideVec.z * moveSpeed) * input_->PushKey(DIK_D);

	sideVec.normalize();
	move.x += (sideVec.x * moveSpeed) * -input_->PushKey(DIK_A);
	move.z += (sideVec.z * moveSpeed) * -input_->PushKey(DIK_A);
}

void Player::Move()
{
	//����͍�������Ƒ�ς����Ȃ̂ŁA�ړ��A�W�����v�A���W�X�V���炢�Ŋ֐��ɂ�����

	//�ړ��l�̏�����
	move = { 0,0,0 };

	InputMove();

	//�W�����v���鏈��
	//�C�ɓ����ĂȂ��̂Ń^�X�N��������������ύX������
	if (input_->TriggerKey(DIK_SPACE))
	{
		jumpSpd = 1.0f;
		gravity = 0.01f;
	}
	//�d�͂������鏈��
	if (jumpSpd > -1.0f)
	{
		jumpSpd -= gravity;
	}
	move.y += jumpSpd;

	//�}�E�X�ŃJ�����𓮂�������
	horizontalRotation += (mouse.x - oldmouse.x) * 0.01f;
	verticalRotation += (mouse.y - oldmouse.y) * 0.01f;

	if (verticalRotation > PIf / 2 - FreqConversionRad(1.0f)) verticalRotation = PIf / 2 - FreqConversionRad(1.0f);
	if (verticalRotation < -PIf / 2 + FreqConversionRad(1.0f)) verticalRotation = -PIf / 2 + FreqConversionRad(1.0f);
	
	//�ړ������l�𑫂�����
	worldTransform.translation_ += move;

}

void Player::Attack()
{
	const float bulletSpd = 0.5f;
	Vector3 velocity(0, 0, bulletSpd);

	velocity = centerVec;
	velocity.normalize();

	velocity *= bulletSpd;

	unique_ptr<PlayerBullet> newBullet = make_unique<PlayerBullet>();
	newBullet->Initialize(model_, worldTransform.translation_,velocity);

	//�e��o�^����
	bullets_.push_back(std::move(newBullet));
}

void Player::Draw(ViewProjection viewProjection_)
{
	model_->Draw(worldTransform, viewProjection_, textureHandle_);

	for (std::unique_ptr<PlayerBullet>& bullet : bullets_)
	{
		bullet->Draw(viewProjection_);
	}
}

void Player::PlayerUpdateMatrix()
{
	worldTransform.CreateScale();
	
	worldTransform.rotation_.y = horizontalRotation;
	worldTransform.CreateRot();

	sideVec = worldTransform.matRot.ExtractAxisX();

	worldTransform.CreateTrans();

	worldTransform.matWorld_.MatrixUint();
	//�X�P�[�����O�s��
	worldTransform.matWorld_ *= worldTransform.matScale;
	//��]�s��
	//worldTransform.matWorld_ *= Matrix4::RotArbitrary(AxisYVec, horizontalRotation);
	worldTransform.matWorld_ *= worldTransform.matRot;
	worldTransform.matWorld_ *= Matrix4::RotArbitrary(sideVec, verticalRotation);

	//���s�ړ��s��
	worldTransform.matWorld_ *= worldTransform.matTrans;

	centerVec = worldTransform.matWorld_.ExtractAxisZ();
}

void Player::Gravity()
{
	jumpSpd = 0;
	gravity = 0;
}
