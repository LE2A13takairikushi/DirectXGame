#include "Enemy.h"
using namespace std;

void Enemy::Initialize(Model* model_,Vector3 popPos)
{
	worldTransform_.Initialize();
	this->model_ = model_;
	this->textureHandle_ = TextureManager::Load("enemy.png");;

	worldTransform_.translation_ = popPos;
}

void Enemy::Update(Vector3 pPos)
{
	bullets_.remove_if([](std::unique_ptr<EnemyBullet>& bullet) {
		return bullet->IsDead();
		});

	shotVec = pPos - worldTransform_.translation_;
	shotVec.normalize();

	moveVec = shotVec * moveSpd;

	switch (phase_)
	{
	case Phase::Approach:
		MoveCenter();
		break;
	case Phase::Leave:
		MoveOpp();
		break;
	}

	worldTransform_.translation_ += moveVec;

	Attack();

	for (std::unique_ptr<EnemyBullet>& bullet : bullets_)
	{
		bullet->Update();
	}

	worldTransform_.UpdateMatrix();
	worldTransform_.TransferMatrix();
}

void Enemy::Draw(ViewProjection viewProjection_)
{
	model_->Draw(worldTransform_, viewProjection_, textureHandle_);

	for (std::unique_ptr<EnemyBullet>& bullet : bullets_)
	{
		bullet->Draw(viewProjection_);
	}
}

void Enemy::OnCollision()
{
	isDead = true;
}

void Enemy::Attack()
{
	//tempVec‚ª’e‚ÌƒxƒNƒgƒ‹‚É‚È‚é
	static Vector3 tempVec = {0,0,0};
	attackCount++;

	//’e‚ÌˆÊ’u‚ðŒˆ’è
	if (attackCount == MAX_ATTACK_COUNT)
	{
		tempVec = shotVec;
		
		unique_ptr<EnemyBullet> newBullet = make_unique<EnemyBullet>();
		newBullet->Initialize(model_, worldTransform_.translation_, tempVec);

		//’e‚ð“o˜^‚·‚é
		bullets_.push_back(std::move(newBullet));
		
		attackCount = 0;
	}
}

void Enemy::PhaseChange(Phase phase_)
{
	this->phase_ = phase_;
}

void Enemy::Back(WorldTransform box)
{
	bool hitGround =
		worldTransform_.translation_.y - worldTransform_.scale_.y >
		box.translation_.y + box.scale_.y;

	bool hitCeiling =
		worldTransform_.translation_.y + worldTransform_.scale_.y <
		box.translation_.y - box.scale_.y;

	if(hitGround||hitCeiling)
	{
		
	}

	moveVec.x = 0;
	moveVec.z = 0;

	worldTransform_.translation_ -= moveVec;
}

void Enemy::MoveCenter()
{
	moveVec *= 1;
}

void Enemy::MoveOpp()
{
	moveVec *= -1;
}

