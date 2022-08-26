#include "Boss.h"
#include "Collsion.h"
#include "WinApp.h"
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

	SetScale({ 10,10,10 });

	exclamation = TextureManager::Load("exclamation.png");
	exclamationObj.Initialize(model);
	exclamationObj.LoadTexture(exclamation);

	exclamationObj.SetScale({
		bossParts[BossPartsName::body].GetScale().x,
		1,
		bossParts[BossPartsName::body].GetScale().z
		});

	TextureHandle redTex = weekTex;

	hitPointGauge = Sprite::Create(redTex, {300 ,50 });
	//xのサイズは640になるように
	hitGaugeOneSize = 640 / HPINIT;
	
	hitPointGauge->SetSize( { HPINIT * hitGaugeOneSize, 50 });
}

void Boss::Update(Vector3 pos, Vector3 scale,Vector3 targetPos, VanishParticleManager& vpManager)
{
	float initJumpSpd = 1.2f;
	int initFallTime = 300;

	targetDirectVec = targetPos - bossParts[BossPartsName::body].GetPos();
	targetDirectVec.normalize();

	move = { 0,0,0 };

	if (Shake.x > 0) Shake.x -= 0.01f;
	if (Shake.y > 0) Shake.y -= 0.01f;
	if (Shake.z > 0) Shake.z -= 0.01f;

	if (Shake.x < 0) Shake.x += 0.01f;
	if (Shake.y < 0) Shake.y += 0.01f;
	if (Shake.z < 0) Shake.z += 0.01f;

	//hpが減ったらゲージにも反映
	if (hitPoint >= 0)
	{
		hitPointGauge->SetSize({ hitPoint * hitGaugeOneSize, 50 });
	}

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

	//移動を反映
	for (int i = 0; i < bossPartsNum; i++)
	{
		bossParts[i].worldTransform_.translation_ += move;
		bossParts[i].Update();
	}

	exclamationObj.worldTransform_.translation_ = bossParts[body].GetPos();
	exclamationObj.worldTransform_.translation_.y = pos.y + scale.y;

	exclamationObj.MatUpdate();
}

void Boss::Draw(ViewProjection view,float mouseVertRota)
{
	for (int i = 0; i < bossPartsNum; i++)
	{
		bossParts[i].Draw(view);
	}

	//カメラが見上げているときは邪魔なので描画しない
	if (mouseVertRota > -0.2f)
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
			Shake.x, Shake.y, Shake.z);
	}
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
	hitPointGauge->Draw();
}

BoxObj Boss::GetBossPart(int bossPartsNum)
{
	return bossParts[bossPartsNum];
}

void Boss::OnBodyColision()
{
	hitPoint--;
	////-0.1から0.1までの範囲
	//Shake = { 0,0,0 };

	//Shake.x = RNG(-10, 10) * 0.01f;
	//Shake.y = RNG(-10, 10) * 0.01f;
	//Shake.z = RNG(-10, 10) * 0.01f;
}

void Boss::OnWeekColision()
{
	hitPoint -= 2;
}