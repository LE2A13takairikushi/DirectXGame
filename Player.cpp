#include "Player.h"
#include "MyMath.h"
#include "Collsion.h"
#include <cassert>

using namespace std;

Player::Player()
{
	worldTransform_.Initialize();
	//moveCollisionBox.Initialize();
}

Player::~Player()
{

}

void Player::Initialize(Model *model_, TextureHandle textureHandle_)
{
	assert(model_);

	worldTransform_.Initialize();
	this->model_ = model_;
	this->textureHandle_ = textureHandle_;
}

void Player::Update()
{
	//�e�̍폜
	//�e�̕���isDead���Ă΂ꂽ�炱�����̃��X�g��������݌v
	//(������ƒ����I����Ȃ����ǂ܂���Ԃ��ꂢ)
	bullets_.remove_if([](std::unique_ptr<PlayerBullet>& bullet) {
		return bullet->IsDead();
		});

	//�O��̃t���[���̍��W��ۑ�
	prevPos = worldTransform_;

	//�ړ��Ƃ��U���Ƃ��̓��͌n
	Move();
	if (input_->IsTriggerMouse(0))
	{
		Attack();
	}

	for (std::unique_ptr<PlayerBullet>& bullet : bullets_)
	{
		bullet->Update();
	}

	//�ړ������l�𑫂�����


}

void Player::UpdateMatrixAndMove()
{
	worldTransform_.translation_ += move;

	PlayerUpdateMatrix();
	worldTransform_.TransferMatrix();
}

void Player::InputMove()
{
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
	if (input_->TriggerKey(DIK_SPACE) && isJumpCheck)
	{
		jumpSpd = 1.0f;
		isJumpCheck = false;
	}
	//�d�͂������鏈��
	if (jumpSpd > -1.0f)
	{
		jumpSpd -= gravity;
		isJumpCheck = false;
	}
	move.y += jumpSpd;


	//�}�E�X�ŃJ�����𓮂�������
	Vector2 temp = { 1920 / 2, 1080 / 2 };

	//�}�E�X�̌��݈ʒu���擾���鏈��
	POINT point;
	GetCursorPos(&point);
	//�}�E�X���Œ肷�鏈��
	SetCursorPos(temp.x, temp.y);

	//�}�E�X�̈ړ��ʂɉ����ăJ�����𓮂�������
	horizontalRotation += (point.x - temp.x) * mouseSpd;
	verticalRotation += (point.y - temp.y) * mouseSpd;

	if (verticalRotation > PIf / 2 - FreqConversionRad(1.0f)) verticalRotation = PIf / 2 - FreqConversionRad(1.0f);
	if (verticalRotation < -PIf / 2 + FreqConversionRad(1.0f)) verticalRotation = -PIf / 2 + FreqConversionRad(1.0f);


}

void Player::Attack()
{
	const float bulletSpd = 0.5f;
	Vector3 velocity(0, 0, bulletSpd);

	velocity = centerVec;
	velocity.normalize();

	velocity *= bulletSpd;

	unique_ptr<PlayerBullet> newBullet = make_unique<PlayerBullet>();
	newBullet->Initialize(model_, worldTransform_.translation_,velocity);

	//�e��o�^����
	bullets_.push_back(std::move(newBullet));
}

void Player::Draw(ViewProjection viewProjection_)
{
	debugText->SetPos(50, 50);
	debugText->Printf("onGround %d", onGround);
	debugText->SetPos(50, 70);
	debugText->Printf("isJumpCheck %d", isJumpCheck);
	debugText->SetPos(50, 90);
	debugText->Printf("jumpSpd %f", jumpSpd);
	debugText->SetPos(50, 110);
	debugText->Printf("move %f %f %f", move.x,move.y,move.z);
	debugText->SetPos(50, 130);
	debugText->Printf("translation_ %f %f %f", 
		worldTransform_.translation_.x,
		worldTransform_.translation_.y,
		worldTransform_.translation_.z
	);

	model_->Draw(worldTransform_, viewProjection_, textureHandle_);

	for (std::unique_ptr<PlayerBullet>& bullet : bullets_)
	{
		bullet->Draw(viewProjection_);
	}
}

void Player::PlayerUpdateMatrix()
{
	worldTransform_.CreateScale();
	
	worldTransform_.rotation_.y = horizontalRotation;
	worldTransform_.CreateRot();

	sideVec = worldTransform_.matRot.ExtractAxisX();

	worldTransform_.CreateTrans();

	worldTransform_.matWorld_.MatrixUint();
	//�X�P�[�����O�s��
	worldTransform_.matWorld_ *= worldTransform_.matScale;
	//��]�s��
	//worldTransform.matWorld_ *= Matrix4::RotArbitrary(AxisYVec, horizontalRotation);
	worldTransform_.matWorld_ *= worldTransform_.matRot;
	worldTransform_.matWorld_ *= Matrix4::RotArbitrary(sideVec, verticalRotation);

	//���s�ړ��s��
	worldTransform_.matWorld_ *= worldTransform_.matTrans;

	centerVec = worldTransform_.matWorld_.ExtractAxisZ();
}

void Player::JumpReady()
{
	jumpSpd = 0;
	isJumpCheck = true;
}

void Player::CheckHitBox(WorldTransform box)
{

	//�����Ɏ��̃t���[���̈ړ��l��}���ꏊ
	WorldTransform tempBox;
	tempBox = worldTransform_;
	tempBox.translation_ += move;

	onGround = BoxColAABB(tempBox, box) && 
		tempBox.translation_.y - tempBox.scale_.y > 
		box.translation_.y + box.scale_.y;

	hitWall = BoxColAABB(tempBox, box) &&
		tempBox.translation_.y + tempBox.scale_.y >
		box.translation_.y - box.scale_.y;

	// && jumpSpd < 0

	if (LineFloarCol(upVec * -1, worldTransform_.translation_,
		{ box.translation_.x, box.translation_.y + box.scale_.y, box.translation_.z },
		{ 0,1,0 }))
	{
		worldTransform_.translation_.y -= move.y;
		JumpReady();
	}

	//if (onGround && hitWall)
	//{
	//	//worldTransform_.translation_.y -= move.y;
	//	//JumpReady();
	//}
	//else if(BoxColAABB(tempBox, box))
	//{
	//	if (hitWall)
	//	{
	//		if (tempBox.translation_.x + tempBox.scale_.x > box.translation_.x - box.scale_.x)
	//		{
	//			worldTransform_.translation_.x -= move.x;
	//		}
	//		if (tempBox.translation_.z + tempBox.scale_.z > box.translation_.z - box.scale_.z)
	//		{
	//			worldTransform_.translation_.z -= move.z;
	//		}
	//		//worldTransform_.translation_.y -= move.y;
	//		//JumpReady();
	//	}
	//}
	
}