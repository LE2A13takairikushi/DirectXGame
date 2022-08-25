#include "Player.h"
#include "MyMath.h"
#include "Collsion.h"
#include <cassert>
#include "WinApp.h"

using namespace std;

static const float InitMoveSpd = 0.11f;

void Player::End()
{
	for (int i = 0; i < 99; i++)
	{
		delete newstocks[i];
	}
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

	skillIconSp = Sprite::Create(TextureManager::Load("dash_skill_icon.png"), { 0,0 });
	shotIconSp = Sprite::Create(TextureManager::Load("shot_skill_icon.png"), { 0,0 });
	skillCoolAlpha = Sprite::Create(TextureManager::Load("alpha.png"), { 0,0 },{1,1,1,0.9f});
	backWhite = Sprite::Create(TextureManager::Load("white.png"), { 0,0 }, { 1,1,1,1 });
	backWhite2 = Sprite::Create(TextureManager::Load("white.png"), { 0,0 }, { 1,1,1,1 });
	lShift = Sprite::Create(TextureManager::Load("Lshift.png"), { 0,0 });

	Vector2 dashSkillPos = {
		WinApp::kWindowWidth - 160,
		WinApp::kWindowHeight - 160
	};

	shotIconSp->SetSize({ 80,80 });
	shotIconSp->SetPosition({ dashSkillPos.x - 120 ,dashSkillPos.y});

	skillIconSp->SetSize({ 80,80 });
	skillIconSp->SetPosition(dashSkillPos);

	skillCoolAlpha->SetSize({ 80,80 });
	skillCoolAlpha->SetPosition(dashSkillPos);

	backWhite->SetSize({ 90,90 });
	backWhite->SetPosition({ dashSkillPos.x - 5,dashSkillPos.y - 5 });

	backWhite2->SetSize({ 90,90 });
	backWhite2->SetPosition({ dashSkillPos.x - 125,dashSkillPos.y - 5 });

	lShift->SetSize({ 120,30 });
	lShift->SetPosition({ dashSkillPos.x - 15,dashSkillPos.y + 75 });
}

void Player::SetSpawnPos(Vector3 pos)
{
	worldTransform_.translation_ = pos;
	respawnPos = pos;
}

void Player::Update(VanishParticleManager &vpmanager)
{
	if (oldIsJumpCheck == false && isJumpCheck)
	{
		vpmanager.CreateSplitParticle(worldTransform_.translation_,
			{ 0.5f,0.5f,0.5f }, 0.01f);
	}
	oldIsJumpCheck = isJumpCheck;

	//弾の削除
	//弾の方でisDeadが呼ばれたらこっちのリストから消す設計
	//(ちょっと直感的じゃないけどまあ一番きれい)
	bullets_.remove_if([](std::unique_ptr<PlayerBullet>& bullet) {
		return bullet->IsDead();
		});

	modelTransform = worldTransform_;


	//前回のフレームの座標を保存
	prevPos = worldTransform_;

	//移動とか攻撃とかの入力系
	Move(vpmanager);

	if (jumpSpd > 1.01f)
	{
		vpmanager.CreateParticle(worldTransform_.translation_,
			{ 0.5f,0.5f,0.5f }, 0.01f);
	}

	//視点を正面に向ける
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
	//正面に移動する処理
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
	//毎フレームダッシュ中か確認する
	isDash = false;
	if (input_->TriggerKey(DIK_LSHIFT) && dashCoolTime <= 0)
	{
		moveSpeed = 1.0f;
		tempMoveVec = moveVec;
		vpmanager.CreateParticle(worldTransform_.translation_,
			{1.5f,1.5f ,1.5f },0.01f);
		dashCoolTime = 180;
		isDash = true;
	}

	oldMoveSpd = moveSpeed;
	if (moveSpeed > InitMoveSpd)
	{
		moveSpeed -= 0.01f;
		isDash = true;

		//ダッシュ中にパーティクルを発生させる
		if (dashCoolTime % 6 == 0)
		{
			vpmanager.CreateParticle(worldTransform_.translation_,
				{ 1.5f,1.5f ,1.5f }, 0.02f);
		}
	}
	if (dashCoolTime > 0)
	{
		dashCoolTime--;
	}
}

void Player::Move(VanishParticleManager& vpmanager)
{
	//操作は混同すると大変そうなので、移動、ジャンプ、座標更新くらいで関数にしたい
	//移動値の初期化
	
	move = { 0,0,0 };

	if (isJumpCheck) isBossMove = false;

	if (isBossMove)
	{
		move += {-0.5f, 0, 0};
	}
	else
	{
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
	}

	//ダッシュ
	Dash(vpmanager);

	//ジャンプする処理
	if (input_->TriggerKey(DIK_SPACE) && isJumpCheck)
	{
		jumpSpd = 1.0f;
		isJumpCheck = false;
	}
	//重力をかける処理
	if (jumpSpd > -1.0f)
	{
		jumpSpd -= gravity;
		isJumpCheck = false;
	}
	move.y += jumpSpd;

	//マウスの現在位置を取得する処理
	POINT point;
	GetCursorPos(&point);

	//マウスでカメラを動かす処理
	Vector2 temp = { 1920 / 2, 1080 / 2 };
	////マウスを固定する処理
	//SetCursorPos(temp.x, temp.y);

	//マウスの移動量に応じてカメラを動かす処理
	horizontalRotation += (point.x - temp.x) * mouseSpd;
	verticalRotation += (point.y - temp.y) * mouseSpd;

	if (verticalRotation > PIf / 2 - DegreeConversionRad(1.0f)) verticalRotation = PIf / 2 - DegreeConversionRad(1.0f);
	if (verticalRotation < -PIf / 2 + DegreeConversionRad(1.0f)) verticalRotation = -PIf / 2 + DegreeConversionRad(1.0f);

	//落下した時に真ん中に戻る
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

	//弾を登録する
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

	backWhite->Draw();
	skillIconSp->Draw();
	lShift->Draw();

	backWhite2->Draw();
	shotIconSp->Draw();

	if (dashCoolTime > 0)
	{
		skillCoolAlpha->Draw();
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
	//スケーリング行列
	worldTransform_.matWorld_ *= worldTransform_.matScale;
	//回転行列
	//worldTransform.matWorld_ *= Matrix4::RotArbitrary(AxisYVec, horizontalRotation);
	worldTransform_.matWorld_ *= worldTransform_.matRot;
	worldTransform_.matWorld_ *= Matrix4::RotArbitrary(sideVec, verticalRotation);

	//平行移動行列
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
	//スケールが全て0なら判定をしない
	if (box.scale_.x == 0 && box.scale_.y == 0 && box.scale_.z == 0)
	{
		return false;
	}
	//天井と地面の当たり判定用
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

void Player::EnforceGoalOnCol()
{
	jumpSpd = 0;

	jumpSpd += 1.8f;
	isBossMove = true;
}
