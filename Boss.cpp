#include "Boss.h"
#include "Collsion.h"
#include "WinApp.h"
using namespace std;

void Boss::Initialize(Model* model,TextureHandle tex, TextureHandle weekTex)
{
	//�{��
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
	//x�̃T�C�Y��640�ɂȂ�悤��
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

	//hp����������Q�[�W�ɂ����f
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

			//��U�W�����v����Ƃ��Ƀp�[�e�B�N������
			//�{���͒��n����^�C�~���O�Ŕ�����������
			vpManager.CreateSplitParticle(
				bossParts[BossPartsName::body].GetPos(),
				{ 5,5,5 }, 0.05f, 3.0f);
		}
		//�v���C���[��ǂ������鏈��
		if (jumpSpd <= initJumpSpd * 0.5f)
		{
			targetDirectVec.y = 0;
			move += targetDirectVec * moveSpd;
		}
		//�㏸���������玟�̃t�F�[�Y�Ɉȍ~
		if (jumpSpd < 0)
		{
			phase = ActPhase::setTarget;
		}
		//��ʔ�������Əd�������̂Ŕ������ɐ���
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

	//��������(�z���g��fall�̒��ɏ�������)
	Vector3 tempPos;
	tempPos = bossParts[BossPartsName::body].GetPos();
	tempPos += move;
	if (tempPos.y < pos.y + scale.y * 2)
	{
		move.y -= jumpSpd;
	}

	//�n�ʂɂ����������x�W�����v�����鏈��
	if (tempPos.y <= pos.y + scale.y * 2)
	{
		phase = ActPhase::jump;
	}

	//�ړ��𔽉f
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

	//�J���������グ�Ă���Ƃ��͎ז��Ȃ̂ŕ`�悵�Ȃ�
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
	////-0.1����0.1�܂ł͈̔�
	//Shake = { 0,0,0 };

	//Shake.x = RNG(-10, 10) * 0.01f;
	//Shake.y = RNG(-10, 10) * 0.01f;
	//Shake.z = RNG(-10, 10) * 0.01f;
}

void Boss::OnWeekColision()
{
	hitPoint -= 2;
}