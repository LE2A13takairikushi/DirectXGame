#include "Player.h"
#include "MyMath.h"
#include "Collsion.h"
#include <cassert>

using namespace std;

static const float InitMoveSpd = 0.11f;

Player::Player()
{
	worldTransform_.Initialize();
	//moveCollisionBox.Initialize();
}

Player::~Player()
{
	//delete stocks;
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

	for (int i = 0; i < 99; i++)
	{
		newstocks[i] = Sprite::Create(TextureManager::Load("life.png"), {0,0});
		newstocks[i]->SetSize({ 100,100 });
		newstocks[i]->SetPosition({ 0 + (i * 100.0f), 0 });
	}
}

void Player::SetSpawnPos(Vector3 pos)
{
	worldTransform_.translation_ = pos;
	respawnPos = pos;
}

void Player::Update(VanishParticleManager &vpmanager)
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
	Move(vpmanager);

	//���_�𐳖ʂɌ�����

	/*if (input_->PushKey(DIK_R))
	{
		verticalRotation = 0;
	}*/

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

	move.x += (moveVec.x * moveSpeed) * -input_->PushKey(DIK_S);
	move.z += (moveVec.z * moveSpeed) * -input_->PushKey(DIK_S);

	sideVec.normalize();
	move.x += (sideVec.x * moveSpeed) * input_->PushKey(DIK_D);
	move.z += (sideVec.z * moveSpeed) * input_->PushKey(DIK_D);

	move.x += (sideVec.x * moveSpeed) * -input_->PushKey(DIK_A);
	move.z += (sideVec.z * moveSpeed) * -input_->PushKey(DIK_A);
}

void Player::Dash(VanishParticleManager& vpmanager)
{
	if (input_->TriggerKey(DIK_LSHIFT) && dashCoolTime <= 0)
	{
		moveSpeed = 1.0f;
		tempMoveVec = moveVec;
		vpmanager.CreateParticle(worldTransform_.translation_,
			{1.5f,1.5f ,1.5f },0.01f);
		dashCoolTime = 180;
	}

	oldMoveSpd = moveSpeed;
	if (moveSpeed > InitMoveSpd)
	{
		moveSpeed -= 0.01f;
	}
	if (dashCoolTime > 0)
	{
		dashCoolTime--;
	}
}

void Player::Move(VanishParticleManager& vpmanager)
{
	//����͍�������Ƒ�ς����Ȃ̂ŁA�ړ��A�W�����v�A���W�X�V���炢�Ŋ֐��ɂ�����
	//�ړ��l�̏�����
	
	move = { 0,0,0 };

	if (moveSpeed <= InitMoveSpd)
	{
		InputMove();
		tempMoveVec = { 0,0,0 };
	}
	else
	{
		move.x += tempMoveVec.x * moveSpeed;
		move.z += tempMoveVec.z * moveSpeed;
	}

	//�_�b�V��
	Dash(vpmanager);

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

	//���ˍ��W�𓪂̈ʒu���炢�ɒ���
	//(�蓮�Ȃ̂Ń��f���ς�����獇��Ȃ��Ȃ�)
	Vector3 initPos = worldTransform_.translation_;
	initPos.y += 3;

	unique_ptr<PlayerBullet> newBullet = make_unique<PlayerBullet>();
	newBullet->Initialize(model_, initPos,velocity);

	//�e��o�^����
	bullets_.push_back(std::move(newBullet));
}

void Player::Draw(ViewProjection viewProjection_)
{
	if (false)
	{
		debugText->SetPos(50, 50);
		debugText->Printf("move %f %f %f", move.x, move.y, move.z);
		debugText->SetPos(50, 70);
		debugText->Printf("translation_ %f %f %f",
			worldTransform_.translation_.x,
			worldTransform_.translation_.y,
			worldTransform_.translation_.z
		);
		debugText->SetPos(50, 90);
		debugText->Printf("left %d", stock);

		debugText->SetPos(50, 110);
		debugText->Printf("movespd %f",
			moveSpeed);
		debugText->SetPos(50, 130);
		debugText->Printf("moveVec %f %f %f",
			moveVec.x, moveVec.y, moveVec.z
		);
		debugText->SetPos(50, 150);
		debugText->Printf("sideVec %f %f %f",
			sideVec.x, sideVec.y, sideVec.z
		);
		debugText->SetPos(50, 170);
		debugText->Printf("tempMoveVec %f %f %f",
			tempMoveVec.x, tempMoveVec.y, tempMoveVec.z
		);
		debugText->SetPos(50, 190);
		debugText->Printf("tempSideVec %f %f %f",
			tempSideVec.x, tempSideVec.y, tempSideVec.z
		);
		

	/*	debugText->SetPos(50, 130);
		debugText->Printf("tempmove %f %f %f",
			tempMove.x, tempMove.y, tempMove.z
		);*/

	}

	model_->Draw(modelTransform, viewProjection_);
	bodyModel->Draw(modelTransform, viewProjection_);
	taiyaModel->Draw(modelTransform, viewProjection_);

	for (std::unique_ptr<PlayerBullet>& bullet : bullets_)
	{
		bullet->Draw(viewProjection_);
	}
}

void Player::SpriteDraw()
{
	for (int i = 0; i < stock; i++)
	{
		//newstocks[i]->Draw();
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

bool Player::CheckHitBox(WorldTransform box)
{
	//�X�P�[�����S��0�Ȃ画������Ȃ�
	if (box.scale_.x == 0 && box.scale_.y == 0 && box.scale_.z == 0)
	{
		return false;
	}
	//�V��ƒn�ʂ̓����蔻��p
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

		if ((tempMoveVec.x != 0 && tempMoveVec.z != 0) && hitGround == 0)
		{
			move.x -= (tempMoveVec.x * oldMoveSpd);
			move.z -= (tempMoveVec.z * oldMoveSpd);
		}

		if (input_->PushKey(DIK_W))
		{
			WorldTransform moveBox;
			moveBox = worldTransform_;
			moveBox.translation_ += move;
			if (BoxColAABB(moveBox, box))
			{
				move.x -= (moveVec.x * oldMoveSpd);
				move.z -= (moveVec.z * oldMoveSpd);
			}
		}
		if (input_->PushKey(DIK_S))
		{
			WorldTransform moveBox;
			moveBox = worldTransform_;
			moveBox.translation_ += move;
			if (BoxColAABB(moveBox, box))
			{
				move.x -= (-moveVec.x * oldMoveSpd);
				move.z -= (-moveVec.z * oldMoveSpd);
			}
		}
		if (input_->PushKey(DIK_D))
		{
			WorldTransform moveBox;
			moveBox = worldTransform_;
			moveBox.translation_ += move;
			if (BoxColAABB(moveBox, box))
			{
				move.x -= (sideVec.x * oldMoveSpd);
				move.z -= (sideVec.z * oldMoveSpd);
			}
		}
		if (input_->PushKey(DIK_A))
		{
			WorldTransform moveBox;
			moveBox = worldTransform_;
			moveBox.translation_ += move;
			if (BoxColAABB(moveBox, box))
			{
				move.x -= (-sideVec.x * oldMoveSpd);
				move.z -= (-sideVec.z * oldMoveSpd);
			}
		}
	}

	if (BoxColAABB(tempBox, box))
	{
		return hitGround;
	}
	return false;

}

void Player::StockPlus()
{
	stock += 1;
}

void Player::EnforceJumpOnCol()
{
	jumpSpd = 0;
	jumpSpd += 2.0f;
}
