#include "GroundManager.h"
using namespace std;

void GroundManager::SetBox(Vector3 pos, Vector3 scale)
{
	unique_ptr<BoxObj> newBox = make_unique<BoxObj>();
	newBox->Initialize(model_);
	newBox->SetPos({ pos.x, pos.y, pos.z });
	newBox->SetScale({ scale.x, scale.y, scale.z });
	Objects.push_back(std::move(newBox));
}

void GroundManager::EventSetBox(Vector3 pos, Vector3 scale)
{
	unique_ptr<BoxObj> newBox = make_unique<BoxObj>();
	newBox->Initialize(model_);
	newBox->SetPos({ pos.x, pos.y, pos.z });
	newBox->SetScale({ scale.x, scale.y, scale.z });
	eventObjects.push_back(std::move(newBox));
}

void GroundManager::Initialize(Model* model_)
{
	this->model_ = model_;
	//�ŏ��̑�n
	SetBox({ 0,0,50 }, { 50,10,50 });
	//���̑�n
	SetBox({ 100,100,160 }, { 50,50,50 });

	SetBox({ 0,130,200 }, { 50,50,10 });
	
	//3�ڂ̑�n
	SetBox({ 200,200,200 }, { 50,50,50 });

	//�K�i
	for (int i = 0; i < 6; i++)
	{
		SetBox({ 0 + i * 20.0f,20 + i * 20.0f,100 }, { 10,10,10 });
	}

	//������Ɗ�Ȃ��K�i
	SetBox({ -80,10,70 }, { 10,10,10 });
	SetBox({ -120,30,80 }, { 10,10,10 });
	SetBox({ -140,60,110 }, { 10,10,10 });

	SetBox({ -135,90,180 }, { 10,10,10 });
	SetBox({ -120,120,200 }, { 10,10,10 });
	SetBox({ -90,140,210 }, { 10,10,10 });
	SetBox({ -70,160,200 }, { 10,10,10 });

	//��̕�
	SetBox({ 0,160,235 }, { 10,10,10 });
	SetBox({ 0,180,220 }, { 10,10,10 });
	SetBox({ 0,180,250 }, { 10,10,10 });

	SetBox({ -20,200,250 }, { 10,10,10 });
	SetBox({ -20,220,230 }, { 10,10,10 });
	SetBox({ 0,240,230 }, { 10,10,10 });

	//��̕��̈��S�Ȃق�
	for (int i = 0; i < 5; i++)
	{
		SetBox({ 0,250 + i * 5.0f,215 - (i * 10.0f) }, { 5,5,5 });
		SetBox({ -10,250 + i * 5.0f,215 - (i * 10.0f) }, { 5,5,5 });
	}

	SetBox({ -20,270,160 }, { 10,10,10 });
	SetBox({ -20,270,140 }, { 10,10,10 });
	SetBox({ 0,270,160 }, { 10,10,10 });
	SetBox({ 0,270,140 }, { 10,10,10 });
	SetBox({ 20,270,160 }, { 10,10,10 });
	SetBox({ 20,270,140 }, { 10,10,10 });

	for (int i = 0; i < 6; i++)
	{
		SetBox({ 40 + (i * 20.0f),270 - (i * 5.0f),140}, {10,10,10});
		SetBox({ 40 + (i * 20.0f),270 - (i * 5.0f),160}, {10,10,10});
	}
	SetBox({ 160,240,140 }, { 10,10,10 });

	//���܂�Ă闎���鑫��]�[��
	for (int i = 0; i < 10; i++)
	{
		//��
		SetBox({ 260 + i * 20.0f,290,220 }, { 10,50,10 });
		SetBox({ 260 + i * 20.0f,290,180 }, { 10,50,10 });
	
		//�V��
		SetBox({ 260 + i * 20.0f,340,200 }, { 10,10,10 });

		//�������Ƃ����A���邽�߂̑���
		SetBox({ 260 + i * 20.0f,110,200 }, { 10,10,10 });

		//�������Ƃ��ȉ����̕�
		SetBox({ 260 + i * 20.0f,190,220 }, { 10,50,10 });
		SetBox({ 260 + i * 20.0f,90,220 }, { 10,50,10 });

		SetBox({ 260 + i * 20.0f,190,180 }, { 10,50,10 });
		SetBox({ 260 + i * 20.0f,90,180 }, { 10,50,10 });
	}

	//�V��̂ł��ς�
	SetBox({ 240,340,200 }, { 10,10,10 });

	//�������Ƃ��ȉ����̌��ɂ��邽�߂̕�
	SetBox({ 280,200,200 }, { 10,60,10 });
	SetBox({ 240,100,200 }, { 10,50,10 });

	//���܂�ė����鑫�ꂻ�̇A
	//�^�񒆂̊�̑���
	SetBox({ 460,250,400 }, { 10,10,10 });

	//�����[�g
	for (int i = 0; i < 2; i++)
	{
		SetBox({ 460,250,200 + i * 90.0f }, { 10,10,10 });
	}
	//�����[�g�̕�
	SetBox({ 460,250,420 }, { 10,50,10 });

	//�E���[�g
	for (int i = 0; i < 5; i++)
	{
		SetBox({ 460,250,200 - i * 30.0f }, { 10,10,10 });
	}
	//���̑���
	for (int i = 0; i < 8; i++)
	{
		SetBox({ 460,170,200 - i * 20.0f }, { 10,10,10 });
	}
	//���̕�
	for (int i = 0; i < 6; i++)
	{
		SetBox({ 460,230 - i * 20.0f,200 }, { 10,10,10 });
	}
	
	//
	for (int i = 0; i < 9; i++)
	{
		SetBox({ 480 + i * 20.0f  ,260 + i * 10.0f,80}, { 10,10,10 });
	}

	SetBox({560, 340, 190} ,{ 100, 10, 100 });
	SetBox({560, 460, 190} ,{ 100, 10, 100 });

	SetBox({ 660, 340, 80 },{ 10, 10, 10 });

	//��O�̕�
	for (int i = 0; i < 9; i++)
	{
		SetBox({ 630 - i * 20.0f ,400,100 }, { 10, 50, 10 });
	}
	//���̕�
	for (int i = 0; i < 8; i++)
	{
		SetBox({ 650 - i * 20.0f ,400,280 }, { 10, 50, 10 });
	}
	//���E�̕�
	for (int i = 0; i < 10; i++)
	{
		SetBox({ 670,400,100 + i * 20.0f }, { 10, 50, 10 });
		SetBox({ 470,400,100 + i * 20.0f }, { 10, 50, 10 });
	}

	for (int i = 0; i < 5; i++)
	{
		SetBox({ 490,340,300 + i * 20.0f }, { 10, 10, 10 });
	}
	SetBox({ 490,340,420}, { 30, 10, 30 });


	//�{�X�̑�n
	bossStagePos = { 300,450,400 };
	bossStageScale = { 100,10,100 };
	SetBox(bossStagePos, bossStageScale);

	//
	for (int i = 0; i < 5; i++)
	{
		unique_ptr<BoxObj> newBox = make_unique<BoxObj>();
		newBox->Initialize(model_);
		newBox->LoadTexture(TextureManager::Load("spawn.png"));
		newBox->SetPos({ 490,360 + i * 20.0f,280 });
		newBox->SetScale({ 10,10,10 });
		enforceObjects.push_back(std::move(newBox));
	}

	//SetSpawnPos({ 0,0,50 }, 10);
	SetSpawnPos(bossStagePos, 10);
}

void GroundManager::EventStart(Vector3 playerPos)
{
	EventSetBox({ playerPos.x - 50,playerPos.y,playerPos.z }, { 10,100,50 });
	EventSetBox({ playerPos.x + 50,playerPos.y,playerPos.z }, { 10,100,50 });
	EventSetBox({ playerPos.x,playerPos.y,playerPos.z - 50 }, { 50,100,10 });
	EventSetBox({ playerPos.x,playerPos.y,playerPos.z + 50 }, { 50,100,10 });
}

void GroundManager::EventEnd()
{
	eventObjects.clear();
}

void GroundManager::BossBattleStart()
{
	BossBattleObject.emplace_back(new BoxObj);
	BossBattleObject.back()->Initialize(model_);
	BossBattleObject.back()->SetPos({
	bossStagePos.x - bossStageScale.x - 10,
	bossStagePos.y - bossStageScale.y,
	bossStagePos.z
		});
	BossBattleObject.back()->SetScale({ 10, 100, 100 });
	
	BossBattleObject.emplace_back(new BoxObj);
	BossBattleObject.back()->Initialize(model_);
	BossBattleObject.back()->SetPos({
	bossStagePos.x + bossStageScale.x + 10,
	bossStagePos.y - bossStageScale.y,
	bossStagePos.z
		});
	BossBattleObject.back()->SetScale({ 10, 100, 100 });

	BossBattleObject.emplace_back(new BoxObj);
	BossBattleObject.back()->Initialize(model_);
	BossBattleObject.back()->SetPos({
	bossStagePos.x,
	bossStagePos.y - bossStageScale.y,
	bossStagePos.z - bossStageScale.z - 10
		});
	BossBattleObject.back()->SetScale({ 100, 100, 10 });

	BossBattleObject.emplace_back(new BoxObj);
	BossBattleObject.back()->Initialize(model_);
	BossBattleObject.back()->SetPos({
	bossStagePos.x,
	bossStagePos.y - bossStageScale.y,
	bossStagePos.z + bossStageScale.z + 10
		});
	BossBattleObject.back()->SetScale({ 100, 100, 10 });
}

void GroundManager::BossBattleEnd()
{
	BossBattleObject.clear();
}

void GroundManager::EnforceEventStart()
{
	for (int i = 0; i < 5; i++)
	{
		unique_ptr<BoxObj> newBox = make_unique<BoxObj>();
		newBox->Initialize(model_);
		newBox->LoadTexture(TextureManager::Load("spawn.png"));
		newBox->SetPos({ 650 ,360 + i * 20.0f,100 });
		newBox->SetScale({ 10,10,10 });
		enforceObjects.push_back(std::move(newBox));
	}
}

void GroundManager::EnforceEventEnd()
{
	enforceObjects.clear();
}

void GroundManager::DeadInit()
{
	eventObjects.clear();
	enforceObjects.clear();
	BossBattleObject.clear();

	for (int i = 0; i < 5; i++)
	{
		unique_ptr<BoxObj> newBox = make_unique<BoxObj>();
		newBox->Initialize(model_);
		newBox->LoadTexture(TextureManager::Load("spawn.png"));
		newBox->SetPos({ 490,360 + i * 20.0f,280 });
		newBox->SetScale({ 10,10,10 });
		enforceObjects.push_back(std::move(newBox));
	}

}

void GroundManager::Update()
{
	for (unique_ptr<BoxObj>& Object : Objects)
	{
		Object->Update();
	}
	for (unique_ptr<BoxObj>& Object : eventObjects)
	{
		Object->Update();
	}
	for (unique_ptr<BoxObj>& Object : BossBattleObject)
	{
		Object->Update();
	}
	for (unique_ptr<BoxObj>& Object : enforceObjects)
	{
		Object->Update();
	}
}

void GroundManager::Draw(ViewProjection viewProjection_)
{
	for (unique_ptr<BoxObj>& Object : Objects)
	{
		Object->Draw(viewProjection_);
	}
	for (unique_ptr<BoxObj>& Object : eventObjects)
	{
		Object->Draw(viewProjection_);
	}
	for (unique_ptr<BoxObj>& Object : enforceObjects)
	{
		Object->Draw(viewProjection_);
	}
	//�{�X��p�̌����Ȃ��ǂȂ̂ŕ`��͂��Ȃ�
	/*for (unique_ptr<BoxObj>& Object : BossBattleObject)
	{
		Object->Draw(viewProjection_);
	}*/
}

Vector3 GroundManager::GetSpawnPos()
{
	return spawnPos;
}

void GroundManager::SetSpawnPos(Vector3 pos, float yScale)
{
	spawnPos = pos;
	spawnPos.y += yScale * 2;
}
