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

	switch (phase_)
	{
	case Phase::Approach:
		MoveCenter();
		break;
	case Phase::Leave:
		MoveOpp();
		break;
	}

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

void Enemy::MoveCenter()
{
	Vector3 centerVec;
	
	centerVec = shotVec * moveSpd;
	worldTransform_.translation_ += centerVec;
	centerVec = { 0,0,0 };
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

void Enemy::MoveOpp()
{
	Vector3 oppVec;

	oppVec = -shotVec * moveSpd;
	worldTransform_.translation_ += oppVec;
	oppVec = { 0,0,0 };
}

