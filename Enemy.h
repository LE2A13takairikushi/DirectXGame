#pragma once
#include "object.h"
#include "ViewProjection.h"
#include "EnemyBullet.h"

enum class Phase {
	Approach,
	Leave,
};

class Enemy : public object
{
public:
	void Initialize(Model* model_, Vector3 popPos);
	void Update(Vector3 pPos);
	void Draw(ViewProjection viewProjection_);
	void OnCollision();

	void PhaseChange(Phase phase_);

	bool IsDead() { return isDead; }

	void Back(WorldTransform box);

	const std::list<std::unique_ptr<EnemyBullet>>& GetBullets() { return bullets_; }

private:
	bool isDead = false;
	float moveSpd = 0.3f;

	std::list<std::unique_ptr<EnemyBullet>> bullets_;

	Phase phase_ = Phase::Approach;

	int attackCount;
	static const int MAX_ATTACK_COUNT = 300;

	Vector3 shotVec = {0,0,0};

	Vector3 moveVec = { 0,0,0 };

	void MoveOpp();
	void MoveCenter();
	void Attack();

};