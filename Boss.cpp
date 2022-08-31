#include "Boss.h"
#include "Collsion.h"
#include "WinApp.h"
#include "MyMath.h"
#include <math.h>

using namespace std;

void Boss::Initialize(Model* model,TextureHandle tex, TextureHandle weekTex)
{
	//本体
	for (int i = 0; i < bossPartsNum; i++)
	{
		bossParts[i].Initialize(model);
	}
	bossParts[0].LoadTexture(tex);
	bossParts[1].LoadTexture(weekTex);

	bulletModel = model;

	SetScale({ 1,1,1 });

	bodyShakeBox = bossParts[BossPartsName::body];

	weekShakeBox = bossParts[BossPartsName::weekPoint];

	exclamation = TextureManager::Load("exclamation.png");
	exclamationObj.Initialize(model);
	exclamationObj.LoadTexture(exclamation);

	exclamationObj.SetScale({
		bossParts[BossPartsName::body].GetScale().x,
		1,
		bossParts[BossPartsName::body].GetScale().z
		});

	TextureHandle redTex = weekTex;

	HPPosInit = { 300 ,50 };

	hitPointGauge = Sprite::Create(redTex, { 300 ,50 });
	oldHitPointGauge = Sprite::Create(redTex, { 300 ,50 },{0.5f,1,1,1});
	//xのサイズは640になるように
	hitGaugeOneSize = 640 / HPINIT;

	hitPointGauge->SetSize( { HPINIT * hitGaugeOneSize, 60 });

	HpbarGraph = Sprite::Create(TextureManager::Load("boss_hpbar.png"), {300 ,50});
	HpbarGraph->SetSize({ 670,80 });
	HpbarGraph->SetPosition({ hitPointGauge->GetPosition().x - 60, hitPointGauge->GetPosition().y - 10});
}

void Boss::Update(Vector3 pos, Vector3 scale,Vector3 targetPos, VanishParticleManager& vpManager, Audio* audio, SoundDataManager sdmanager)
{
	bullets_.remove_if([](std::unique_ptr<EnemyBullet>& bullet) {
		return bullet->IsDead();
		});

	for (std::unique_ptr<EnemyBullet>& bullet : bullets_)
	{
		bullet->Update();
	}

	float initJumpSpd = 1.2f;
	int initFallTime = 240;

	targetDirectVec = targetPos - bossParts[BossPartsName::body].GetPos();
	targetDirectVec.normalize();

	move = { 0,0,0 };

	if (shake.x > 0) shake.x -= 0.01f;
	if (shake.y > 0) shake.y -= 0.01f;
	if (shake.z > 0) shake.z -= 0.01f;

	if (shake.x < 0) shake.x += 0.01f;
	if (shake.y < 0) shake.y += 0.01f;
	if (shake.z < 0) shake.z += 0.01f;

	//static Vector2 tempHitGauge = { 0,0 };

	//hpが減ったらゲージにも反映
	if (hitPoint >= 0)
	{
		if (shakeTimer <= 0 && weekShakeTimer <= 0)
		{
			if (oldHitPoint >= hitPoint)
			{
				oldHitPoint -= 0.5f;
			}
			oldHitPointGauge->SetSize({ oldHitPoint * hitGaugeOneSize, 60 });
		}
		hitPointGauge->SetSize({ hitPoint * hitGaugeOneSize, 60 });
	}

	if (jumpSpd >= -1.0f)
	{
		jumpSpd -= gravity;
	}

	if (hitPoint <= HPINIT / 2 && isFormChange == false)
	{
		phase = ActPhase::superAttack;
	}
	if (hitPoint <= 0)
	{
		phase = ActPhase::dead;
	}

	static int superAttackCount = 0;
	Vector3 superAttackMoveVec = { 0,0,0 };

	superAttackMoveVec = pos - bossParts[body].GetPos();
	superAttackMoveVec.normalize();

	switch (phase)
	{
	case jump:
		if (jumpSpd <= 0 && fallTimer <= 0)
		{
			jumpSpd = initJumpSpd;
			fallTimer = initFallTime;

			//一旦ジャンプするときにパーティクル発生
			//本来は着地するタイミングで発生させたい
			vpManager.CreateSplitParticle(
				bossParts[BossPartsName::body].GetPos(),
				{ 5,5,5 }, 0.05f, 3.0f);
			
		}
		//プレイヤーを追いかける処理
		if (jumpSpd <= initJumpSpd * 0.5f)
		{
			targetDirectVec.y = 0;
			move += targetDirectVec * moveSpd;
		}
		//上昇しきったら次のフェーズに以降
		if (jumpSpd < 0)
		{
			phase = ActPhase::setTarget;
		}
		//大量発生すると重かったので発生数に制限
		if (vpManager.GetParticle().size() <= 300)
		{
			vpManager.CreateParticle(
				bossParts[BossPartsName::body].GetPos(),
				{ 3.0f,3.0f,3.0f }, 0.05f);
		}

		break;
	case setTarget:
		--fallTimer;
		if (fallTimer > 0)jumpSpd = 0;

		if (fallTimer >= initFallTime * 0.5f)
		{
			targetDirectVec.y = 0;
			move += targetDirectVec * moveSpd;
		}

		if (fallTimer <= 0)
		{
			phase = ActPhase::fall;
			fallTimer = 300;
		}
		break;
	case fall:
		fallTimer--;
		if (fallTimer <= 0)
		{
			phase = ActPhase::miniJump;
		}

		break;
	case miniJump:
		miniJumpTimer--;

		if (miniJumpTimer <= 0)
		{
			if (stumpStock >= 3)
			{
				phase = ActPhase::jump;
				stumpStock = 0;
				break;
			}
			jumpSpd = 0.5f;
			miniJumpTimer = 200;
			stumpStock++;
			vpManager.CreateSplitParticle(
				bossParts[BossPartsName::body].GetPos(),
				{ 5,5,5 }, 0.05f, 3.0f);
		}
		if (miniJumpTimer > 100)
		{
			targetDirectVec.y = 0;
			move += targetDirectVec * (0.4f);
		}

		break;
	case superAttack:

		if (isFormChange == false)
		{
			isFormChange = true;
			/*superAttackMoveVec.y = 0;
			move += superAttackMoveVec * moveSpd;
			if ((bossParts[body].GetPos().x >= pos.x - 10) &&
				(bossParts[body].GetPos().x <= pos.x + 10) &&
				(bossParts[body].GetPos().z >= pos.z - 10)&&
				(bossParts[body].GetPos().z <= pos.z + 10)
				)
			{
				isFormChange = true;
			}*/
		}
		
		if (onGround && isFormChange)
		{
			bulletTimer--;
			if (bulletTimer <= 0)
			{
				//攻撃するタイミングですでに五回攻撃していたら
				//次のフェーズに以降
				if (superAttackCount >= 5)
				{
					phase = ActPhase::miniJump;
					fallTimer = 0;
					miniJumpTimer = 0;
					isSuperAttack = true;
					break;
				}

				float minus = 0;
				while (minus < PIf * 2)
				{
					minus += 0.08f;
					Attack({ cosf(PIf - minus),0, sinf(PIf - minus)});
				}
				bulletTimer = 240;
				superAttackCount++;
			}
		}
		
		break;
	case appearance:
		//登場時にだんだん大きくなる演出

		scalePTimer--;
		if (bossParts[body].worldTransform_.scale_.x < initScale.x)
		{
			bossParts[body].worldTransform_.translation_.y += 1.1f;
			if (scalePTimer <= 0)
			{
				vpManager.CreateParticle(
					bossParts[BossPartsName::body].GetPos(),
					{ 5,5,5 }, 0.05f);
				scalePTimer = 20;
			}

			scalePlus.x += scaleSpd;
			scalePlus.y += scaleSpd;
			scalePlus.z += scaleSpd;
			SetScale(scalePlus);
			SetPos(bossParts[body].GetPos());
			exclamationObj.SetScale({
		bossParts[BossPartsName::body].GetScale().x,
		1,
		bossParts[BossPartsName::body].GetScale().z
				});
		}
		if (bossParts[body].worldTransform_.scale_.x >= initScale.x && onGround)
		{
			phase = ActPhase::miniJump;
			miniJumpTimer = 100;
		}
		break;
	case dead:
		bossDeadEffectFlag = true;
		jumpSpd = 0.01f;
		scalePTimer--;
		if (bossParts[body].worldTransform_.scale_.x > 0.1f)
		{
			if (scalePTimer <= 0)
			{
				vpManager.CreateParticle(
					bossParts[BossPartsName::body].GetPos(),
					{ 5,5,5 }, 0.05f);
				audio->PlayWave(sdmanager.bossboomSE, false, 0.1f);
				scalePTimer = 20;
			}

			scalePlus.x -= scaleSpd;
			scalePlus.y -= scaleSpd;
			scalePlus.z -= scaleSpd;
			SetScale(scalePlus);
			SetPos(bossParts[body].GetPos());
			exclamationObj.SetScale({
		bossParts[BossPartsName::body].GetScale().x,
		1,
		bossParts[BossPartsName::body].GetScale().z
				});
		}
		if (bossParts[body].worldTransform_.scale_.x <= 0.1f)
		{
			isDead = true;
			audio->PlayWave(sdmanager.bossendboomSE, false, 0.3f);
			vpManager.CreateSplitParticle(
				bossParts[BossPartsName::weekPoint].GetPos(),
				{ 10,10,10 }, 0.05f, 5.0f);
		}

		isShake = true;
		shakeTimer = 60;
		break;
	}

	move.y += jumpSpd;

	//落下処理(ホントはfallの中に書きたい)
	Vector3 tempPos;
	tempPos = bossParts[BossPartsName::body].GetPos();
	tempPos += move;

	if (prevPos.y > pos.y + scale.y * 2 + 3 &&
		tempPos.y <= pos.y + scale.y * 2 + 3)
	{
		vpManager.CreateSplitParticle(
			bossParts[BossPartsName::weekPoint].GetPos(),
			{ 5,5,5 }, 0.05f, 3.0f);
		if (isFormChange && isSuperAttack)
		{
			phase = ActPhase::superAttack;
			superAttackCount = 4;
		}
	}

	//地面判定
	if (tempPos.y <= pos.y + scale.y * 2)
	{
		move.y -= jumpSpd;
		onGround = true;
	}
	else
	{
		onGround = false;
	}

	//移動を反映
	for (int i = 0; i < bossPartsNum; i++)
	{
		bossParts[i].worldTransform_.translation_ += move;
		bossParts[i].Update();
	}

	prevPos = bossParts[0].worldTransform_.translation_;

	exclamationObj.worldTransform_.translation_ = bossParts[body].GetPos();
	exclamationObj.worldTransform_.translation_.y = pos.y + scale.y;

	exclamationObj.MatUpdate();

	ShakeUpdate();
}

void Boss::Draw(ViewProjection view,float mouseVertRota)
{
	bossParts[0].Draw(view);
	bossParts[1].Draw(view);

	bodyShakeBox.Draw(view, shake);
	weekShakeBox.Draw(view, weekShake);

	for (std::unique_ptr<EnemyBullet>& bullet : bullets_)
	{
		bullet->Draw(view);
	}

	//カメラが見上げているときは邪魔なので描画しない
	if (mouseVertRota > -0.2f &&
		(phase == ActPhase::jump ||
		phase == ActPhase::setTarget ||
		phase == ActPhase::fall ||
		phase == ActPhase::appearance))
	{
		exclamationObj.Draw(view);
	}
	
	if (true)
	{
		dT->SetPos(50, 50);
		dT->Printf("bossPos %f %f %f",
			bossParts->GetWorldTrans().translation_.x,
			bossParts->GetWorldTrans().translation_.y,
			bossParts->GetWorldTrans().translation_.z);
		dT->SetPos(50, 70);
		dT->Printf("jumpSpd %f",
			jumpSpd);
		dT->SetPos(50, 90);
		dT->Printf("phase %d",
			phase);
		dT->SetPos(50, 110);
		dT->Printf("move %f %f %f",
			move.x, move.y, move.z);
		dT->SetPos(50, 130);
		dT->Printf("Shake %f %f %f",
			shake.x, shake.y, shake.z);
		dT->SetPos(50, 150);
		dT->Printf("targetDirectVec %f %f %f",
			targetDirectVec.x, targetDirectVec.y, targetDirectVec.z);dT->SetPos(50, 150);dT->SetPos(50, 150);
		dT->SetPos(50, 170);
		dT->Printf("oldHitPoint %f",
			oldHitPoint);
	}
}
void Boss::End()
{
	delete hitPointGauge;
	delete oldHitPointGauge;
	delete HpbarGraph;
}


void Boss::SetPos(Vector3 pos)
{
	bossParts[BossPartsName::body].SetPos(pos);
	Vector3 weekPos = pos;
	weekPos.y = pos.y - bossParts->GetScale().y;
	bossParts[BossPartsName::weekPoint].SetPos(weekPos);
}

void Boss::SetScale(Vector3 scale)
{
	bossParts[BossPartsName::body].SetScale(scale);
	Vector3 weekscale = scale * 0.2f;
	bossParts[BossPartsName::weekPoint].SetScale(weekscale);
}

void Boss::HPDraw()
{
	HpbarGraph->Draw();
	oldHitPointGauge->Draw();
	hitPointGauge->Draw();
}

BoxObj Boss::GetBossPart(int bossPartsNum)
{
	return bossParts[bossPartsNum];
}

void Boss::OnBodyColision()
{
	hitPoint -= 1;
	isShake = true;
	shakeTimer = 60;
}

void Boss::OnWeekColision()
{
	hitPoint -= 1 * 5;
	isWeekShake = true;
	weekShakeTimer = 60;
}

void Boss::ShakeUpdate()
{
	if (isShake)
	{
		--shakeTimer;
		Viblation();
	}
	else
	{
		shake = { 0,0,0 };
	}
	if (shakeTimer <= 0)
	{
		isShake = false;
	}

	if (isWeekShake)
	{
		--weekShakeTimer;
		WeekViblation();
	}
	else
	{
		weekShake = { 0,0,0 };
	}
	if (weekShakeTimer <= 0)
	{
		isWeekShake = false;
	}

	hitPointGauge->SetPosition({ HPPosInit.x + shake.x * 3.0f,HPPosInit.y + shake.y * 3.0f });
	if(weekShake.x != 0)hitPointGauge->SetPosition({ HPPosInit.x + weekShake.x * 3.0f,HPPosInit.y + weekShake.y * 3.0f });
	HpbarGraph->SetPosition({ hitPointGauge->GetPosition().x - 60, hitPointGauge->GetPosition().y - 10 });

	bodyShakeBox.worldTransform_ = bossParts[BossPartsName::body].GetWorldTrans();
	bodyShakeBox.worldTransform_.translation_ += shake;
	bodyShakeBox.Update();
	//元の位置に戻す
	bodyShakeBox.worldTransform_ = bossParts[BossPartsName::body].GetWorldTrans();

	weekShakeBox.worldTransform_ = bossParts[BossPartsName::weekPoint].GetWorldTrans();
	weekShakeBox.worldTransform_.translation_ += weekShake;
	weekShakeBox.Update();
	//元の位置に戻す
	weekShakeBox.worldTransform_ = bossParts[BossPartsName::weekPoint].GetWorldTrans();
}

void Boss::Attack(Vector3 velocity)
{
	unique_ptr<EnemyBullet> newBullet = make_unique<EnemyBullet>();
	newBullet->Initialize(bulletModel,
		{ 
			bossParts[BossPartsName::weekPoint].GetPos().x,
			bossParts[BossPartsName::weekPoint].GetPos().y + 3,
			bossParts[BossPartsName::weekPoint].GetPos().z
		},
		velocity);
	bullets_.push_back(std::move(newBullet));
}

void Boss::Viblation()
{
	shake.x = RNG(-10, 10) * 0.1f;
	shake.y = RNG(-10, 10) * 0.1f;
	shake.z = RNG(-10, 10) * 0.1f;
}

void Boss::WeekViblation()
{
	weekShake.x = RNG(-13, 13) * 0.1f;
	weekShake.y = RNG(-13, 13) * 0.1f;
	weekShake.z = RNG(-13, 13) * 0.1f;
}
