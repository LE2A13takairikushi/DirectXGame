#include "Boss.h"
#include "Collsion.h"
using namespace std;

void Boss::Initialize(Model* model,TextureHandle tex)
{
	//本体
	for (int i = 0; i < bossPartsNum; i++)
	{
		bossParts[i].Initialize(model);
		bossParts[i].LoadTexture(tex);
	}

	SetScale({ 10,10,10 });
}

void Boss::Update(Vector3 pos, Vector3 scale,Vector3 targetPos)
{
	float initJumpSpd = 1.5f;
	int initFallTime = 300;

	targetDirectVec = targetPos - bossParts[BossPartsName::body].GetPos();
	targetDirectVec.normalize();

	move = { 0,0,0 };

	if (jumpSpd >= -1.0f)
	{
		jumpSpd -= gravity;
	}

	switch (phase)
	{
	case jump:
		if (jumpSpd <= 0 && fallTimer <= 0)
		{
			jumpSpd = initJumpSpd;
			fallTimer = initFallTime;
		}
		if (jumpSpd <= initJumpSpd * 0.5f)
		{
			targetDirectVec.y = 0;
			move += targetDirectVec * moveSpd;
		}

		if (jumpSpd < 0)
		{
			phase = ActPhase::setTarget;
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

		if(fallTimer <= 0)phase = ActPhase::fall;
		break;
	case fall:
		break;
	}

	move.y += jumpSpd;

	//落下処理(ホントはfallの中に書きたい)
	Vector3 tempPos;
	tempPos = bossParts[BossPartsName::body].GetPos();
	tempPos += move;
	if (tempPos.y < pos.y + scale.y * 2)
	{
		move.y -= jumpSpd;
	}

	//地面についたらもう一度ジャンプさせる処理
	if (tempPos.y <= pos.y + scale.y * 2)
	{
		phase = ActPhase::jump;
	}


	for (int i = 0; i < bossPartsNum; i++)
	{
		bossParts[i].worldTransform_.translation_ += move;
		bossParts[i].Update();
	}
}

void Boss::Draw(ViewProjection view)
{
	for (int i = 0; i < bossPartsNum; i++)
	{
		bossParts[i].Draw(view);
	}
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
	dT->Printf("targetDirectVec %f %f %f",
		targetDirectVec.x, targetDirectVec.y, targetDirectVec.z);
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
	Vector3 weekscale = scale * 0.1f;
	bossParts[BossPartsName::weekPoint].SetScale(weekscale);
}