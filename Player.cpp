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
	//弾の削除
	//弾の方でisDeadが呼ばれたらこっちのリストから消す設計
	//(ちょっと直感的じゃないけどまあ一番きれい)
	bullets_.remove_if([](std::unique_ptr<PlayerBullet>& bullet) {
		return bullet->IsDead();
		});

	//前回のフレームの座標を保存
	prevPos = worldTransform_;

	//移動とか攻撃とかの入力系
	Move();
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
	//移動した値を足す処理
	worldTransform_.translation_ += move;

	PlayerUpdateMatrix();
	worldTransform_.TransferMatrix();
}

void Player::InputMove()
{
	//正面に移動する処理
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
	//操作は混同すると大変そうなので、移動、ジャンプ、座標更新くらいで関数にしたい

	//移動値の初期化
	move = { 0,0,0 };

	InputMove();

	//ジャンプする処理
	//気に入ってないのでタスクが落ち着いたら変更したい
	if (input_->TriggerKey(DIK_SPACE) && isJumpCheck)
	{
		jumpSpd = 1.0f;
		gravity = 0.01f;
		isJumpCheck = false;
	}
	//重力をかける処理
	if (jumpSpd > -1.0f)
	{
		jumpSpd -= gravity;
	}
	move.y += jumpSpd;



	//マウスでカメラを動かす処理
	Vector2 temp = { 1920 / 2, 1080 / 2 };

	//マウスの現在位置を取得する処理
	POINT point;
	GetCursorPos(&point);
	//マウスを固定する処理
	SetCursorPos(temp.x, temp.y);

	//マウスの移動量に応じてカメラを動かす処理
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

	//弾を登録する
	bullets_.push_back(std::move(newBullet));
}

void Player::Draw(ViewProjection viewProjection_)
{
	debugText->SetPos(50, 50);
	debugText->Printf("isJumpCheck %d", isJumpCheck);
	debugText->SetPos(50, 70);
	debugText->Printf("gravity %f", gravity);
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
	//jumpSpd = 0;
	//gravity = 0;
	isJumpCheck = true;
}

void Player::CheckHitBox(WorldTransform box)
{

	//if文のボックスコリジョンの後ろにつけてる
	//y座標の比較がうまくいってない
	//明日ちゃんと考える
	if (input_->PushKey(DIK_W))
	{
		WorldTransform tempTrans = worldTransform_;
		tempTrans.translation_ += move;
		if (BoxColAABB(tempTrans, box) &&
			worldTransform_.translation_.y - worldTransform_.scale_.y * 2 >
			box.translation_.y + box.scale_.y * 2)
		{
			centerVec.normalize();
			move.x -= (centerVec.x * moveSpeed);
			move.z -= (centerVec.z * moveSpeed);
		}
	}

	if (input_->PushKey(DIK_S))
	{
		WorldTransform tempTrans = worldTransform_;
		tempTrans.translation_ += move;
		if (BoxColAABB(tempTrans, box) &&
			worldTransform_.translation_.y - worldTransform_.scale_.y * 2 >
			box.translation_.y + box.scale_.y * 2)
		{
			centerVec.normalize();
			move.x -= (centerVec.x * moveSpeed) * -1;
			move.z -= (centerVec.z * moveSpeed) * -1;
		}
	}
	if (input_->PushKey(DIK_D))
	{
		WorldTransform tempTrans = worldTransform_;
		tempTrans.translation_ += move;
		if (BoxColAABB(tempTrans, box) &&
			worldTransform_.translation_.y - worldTransform_.scale_.y * 2 >
			box.translation_.y + box.scale_.y * 2)
		{
			sideVec.normalize();
			move.x -= (sideVec.x * moveSpeed);
			move.z -= (sideVec.z * moveSpeed);
		}
	}
	if (input_->PushKey(DIK_A))
	{
		WorldTransform tempTrans = worldTransform_;
		tempTrans.translation_ += move;
		if (BoxColAABB(tempTrans, box) &&
			worldTransform_.translation_.y - worldTransform_.scale_.y * 2 >
			box.translation_.y + box.scale_.y * 2)
		{
			sideVec.normalize();
			move.x -= (sideVec.x * moveSpeed) * -1;
			move.z -= (sideVec.z * moveSpeed) * -1;
		}
	}

	if (true)
	{
		WorldTransform tempTrans = worldTransform_;
		tempTrans.translation_ += move;
		if (BoxColAABB(tempTrans, box) &&
			worldTransform_.translation_.y - worldTransform_.scale_.y * 2 <
			box.translation_.y + box.scale_.y * 2)
		{
			
			move.y -= jumpSpd;
			if (input_->TriggerKey(DIK_SPACE))
			{
				move.y += (jumpSpd + gravity);
			}

			JumpReady();
		}
	}
}