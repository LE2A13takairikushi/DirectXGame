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
	/*delete debugText;
	delete input_;*/
}

void Player::Initialize(Model *model_,Model* bodyModel, Model* taiyaModel)
{
	assert(model_);
	assert(bodyModel);

	worldTransform_.Initialize();
	this->model_ = model_;
	this->bodyModel = bodyModel;
	this->taiyaModel = taiyaModel;
}

void Player::SetSpawnPos(Vector3 pos)
{
	worldTransform_.translation_ = pos;
	respawnPos = pos;
}

void Player::Update()
{
	//�e�̍폜
	//�e�̕���isDead���Ă΂ꂽ�炱�����̃��X�g��������݌v
	//(������ƒ����I����Ȃ����ǂ܂���Ԃ��ꂢ)
	bullets_.remove_if([](std::unique_ptr<PlayerBullet>& bullet) {
		return bullet->IsDead();
		});

	modelTransform = worldTransform_;
	

	//�O��̃t���[���̍��W��ۑ�
	prevPos = worldTransform_;

	//�ړ��Ƃ��U���Ƃ��̓��͌n
	Move();

	//���_�𐳖ʂɌ�����
	if (input_->PushKey(DIK_R))
	{
		verticalRotation = 0;
	}

	if (input_->IsTriggerMouse(0))
	{
		Attack();
	}

	for (std::unique_ptr<PlayerBullet>& bullet : bullets_)
	{
		bullet->Update();
	}
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
	moveVec.normalize();
	move.x += (moveVec.x * moveSpeed) * input_->PushKey(DIK_W);
	move.z += (moveVec.z * moveSpeed) * input_->PushKey(DIK_W);

	moveVec.normalize();
	move.x += (moveVec.x * moveSpeed) * -input_->PushKey(DIK_S);
	move.z += (moveVec.z * moveSpeed) * -input_->PushKey(DIK_S);

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

	if (verticalRotation > PIf / 2 - DegreeConversionRad(1.0f)) verticalRotation = PIf / 2 - DegreeConversionRad(1.0f);
	if (verticalRotation < -PIf / 2 + DegreeConversionRad(1.0f)) verticalRotation = -PIf / 2 + DegreeConversionRad(1.0f);

	//�����������ɐ^�񒆂ɖ߂�
	if (worldTransform_.translation_.y <= -100)
	{
		worldTransform_.translation_ = respawnPos;
		stock -= 1;
	}
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
	debugText->Printf("move %f %f %f", move.x,move.y,move.z);
	debugText->SetPos(50, 70);
	debugText->Printf("translation_ %f %f %f", 
		worldTransform_.translation_.x,
		worldTransform_.translation_.y,
		worldTransform_.translation_.z
	);
	debugText->SetPos(50, 90);
	debugText->Printf("left %d",stock);

	debugText->SetPos(50, 110);
	debugText->Printf("rotation_ %f %f %f",
		worldTransform_.rotation_.x,
		worldTransform_.rotation_.y,
		worldTransform_.rotation_.z
	);

	debugText->SetPos(50, 130);
	debugText->Printf("jumpSpd %f",
		jumpSpd
	);

	model_->Draw(modelTransform, viewProjection_);
	bodyModel->Draw(modelTransform, viewProjection_);
	taiyaModel->Draw(modelTransform, viewProjection_);

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

	moveVec = worldTransform_.matRot.ExtractAxisZ();
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

	//yhan
	WorldTransform tempBox;
	tempBox = worldTransform_;
	tempBox.translation_ += move;

	hitGround = 
		tempBox.translation_.y - tempBox.scale_.y > 
		box.translation_.y + box.scale_.y;

	hitCeiling = 
		tempBox.translation_.y + tempBox.scale_.y <
		box.translation_.y - box.scale_.y;
	
	if (BoxColAABB(tempBox, box))
	{
		if ((hitGround && jumpSpd < 0)|| (hitCeiling && jumpSpd > 0))
		{
			move.y -= jumpSpd;
			JumpReady();
		}
		if (input_->PushKey(DIK_W))
		{
			WorldTransform moveBox;
			moveBox = worldTransform_;
			moveBox.translation_ += move;
			if (BoxColAABB(moveBox, box))
			{
				move.x -= (moveVec.x * moveSpeed);
				move.z -= (moveVec.z * moveSpeed);
			}
		}
		if (input_->PushKey(DIK_S))
		{
			WorldTransform moveBox;
			moveBox = worldTransform_;
			moveBox.translation_ += move;
			if (BoxColAABB(moveBox, box))
			{
				move.x -= (-moveVec.x * moveSpeed);
				move.z -= (-moveVec.z * moveSpeed);
			}
		}
		if (input_->PushKey(DIK_D))
		{
			WorldTransform moveBox;
			moveBox = worldTransform_;
			moveBox.translation_ += move;
			if (BoxColAABB(moveBox, box))
			{
				move.x -= (sideVec.x * moveSpeed);
				move.z -= (sideVec.z * moveSpeed);
			}
		}
		if (input_->PushKey(DIK_A))
		{
			WorldTransform moveBox;
			moveBox = worldTransform_;
			moveBox.translation_ += move;
			if (BoxColAABB(moveBox, box))
			{
				move.x -= (-sideVec.x * moveSpeed);
				move.z -= (-sideVec.z * moveSpeed);
			}
		}
	}
}

void Player::StockPlus()
{
	stock += 1;
}

void Player::EnforceJumpOnCol()
{
	jumpSpd += 2.0f;
}
