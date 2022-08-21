#include "Enemy.h"
#include "MyMath.h"
#include "Collsion.h"

using namespace std;

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
	
}

void Enemy::Initialize(Model* model_, Model* partModel,TextureHandle tex, Vector3 popPos)
{
	worldTransform_.Initialize();
	this->model_ = model_;
	//this->textureHandle_ = TextureManager::Load("enemy.png");;

	worldTransform_.translation_ = popPos;
	pManager.Initialize(partModel, tex);
	
}

void Enemy::Update(Vector3 pPos)
{
	bullets_.remove_if([](std::unique_ptr<EnemyBullet>& bullet) {
		return bullet->IsDead();
		});

	Attack();

	pManager.Update(worldTransform_.translation_);

	for (std::unique_ptr<EnemyBullet>& bullet : bullets_)
	{
		bullet->Update();
	}

	pCenterVec = pPos - worldTransform_.translation_;
	pCenterVec.normalize();

	moveVec = pCenterVec * moveSpd;

	sideVec = worldTransform_.matWorld_.ExtractAxisX();
	sideVec.normalize();

	sideVec *= moveSpd;

	pdegree = InterpointGetDegree(moveVec, sideVec);

	switch (phase_)
	{
	case Phase::Approach:
		MoveCenter();
		break;
	case Phase::Leave:
		MoveOpp();
		break;
	case Phase::OnWall:
		OnWallMove();
		break;
	}

	worldTransform_.translation_ += moveVec;

	worldTransform_.UpdateMatrix();
	worldTransform_.TransferMatrix();
}

void Enemy::Draw(ViewProjection viewProjection_)
{
	model_->Draw(worldTransform_, viewProjection_);


	for (std::unique_ptr<EnemyBullet>& bullet : bullets_)
	{
		bullet->Draw(viewProjection_);
	}

	pManager.Draw(viewProjection_);

	if (false)
	{
		debugText->SetPos(50, 200);
		debugText->Printf("kakudo %f", pdegree);
		debugText->SetPos(50, 230);
		debugText->Printf("moveVec %f %f %f", moveVec.x, moveVec.y, moveVec.z);
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
		tempVec = pCenterVec;
		
		unique_ptr<EnemyBullet> newBullet = make_unique<EnemyBullet>();
		newBullet->Initialize(Model::Create(), worldTransform_.translation_, tempVec);

		//’e‚ð“o˜^‚·‚é
		bullets_.push_back(std::move(newBullet));
		
		attackCount = 0;
	}
}

void Enemy::PhaseChange(Phase phase_)
{
	this->phase_ = phase_;
}

void Enemy::CheckHitBox(WorldTransform box)
{
	WorldTransform tempBox;
	tempBox = worldTransform_;
	tempBox.translation_ += moveVec;

	hitGround =
		tempBox.translation_.y - tempBox.scale_.y >
		box.translation_.y + box.scale_.y;

	hitCeiling =
		tempBox.translation_.y + tempBox.scale_.y <
		box.translation_.y - box.scale_.y;

	isBoxCol = BoxColAABB(tempBox, box);

	PhaseChange(Phase::OnWall);
}

void Enemy::OnWallMove()
{
	if (isBoxCol && (hitGround != 0 || hitCeiling != 0))
	{
		if (pdegree < -1)
		{
			moveVec.x = sideVec.x;
			moveVec.z = sideVec.z;
		}
		if (pdegree > 1)
		{
			moveVec.x = -sideVec.x;
			moveVec.z = -sideVec.z;
		}
		if (pdegree >= -1 && pdegree <= 1)
		{
			moveVec.x = 0;
			moveVec.z = 0;

			moveVec.y = moveSpd;
		}
	}
}

void Enemy::MoveCenter()
{
	moveVec *= 1;
}

void Enemy::MoveOpp()
{
	moveVec *= 0;
}

