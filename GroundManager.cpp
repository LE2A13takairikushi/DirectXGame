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
	//最初の台地
	SetBox({ 0,0,50 }, { 50,10,50 });
	//次の台地
	SetBox({ 100,100,160 }, { 50,50,50 });

	SetBox({ 0,130,200 }, { 50,50,10 });
	
	//3つ目の台地
	SetBox({ 200,200,200 }, { 50,50,50 });

	//階段
	SetBox( { 0,30,100 }, { 10,10,10 });
	SetBox( { 30,50,100 }, { 10,10,10 });
	SetBox( { 60,80,100 }, { 10,10,10 });
	SetBox( { 90,110,100 }, { 10,10,10 });

	//ちょっと危ない階段
	SetBox({ -80,10,70 }, { 10,10,10 });
	SetBox({ -120,30,80 }, { 10,10,10 });
	SetBox({ -140,60,110 }, { 10,10,10 });

	SetBox({ -135,90,180 }, { 10,10,10 });
	SetBox({ -120,120,200 }, { 10,10,10 });
	SetBox({ -90,140,210 }, { 10,10,10 });
	SetBox({ -70,160,200 }, { 10,10,10 });

	//上の方
	SetBox({ 0,160,235 }, { 10,10,10 });
	SetBox({ 0,180,220 }, { 10,10,10 });
	SetBox({ 0,180,250 }, { 10,10,10 });

	SetBox({ -20,200,250 }, { 10,10,10 });
	SetBox({ -20,220,230 }, { 10,10,10 });
	SetBox({ 0,240,230 }, { 10,10,10 });

	//上の方の安全なほう
	for (int i = 0; i < 5; i++)
	{
		SetBox({ 0,270,210 - (i * 10.0f) }, { 5,5,5 });
	}

	SetBox({ 4,270,150 }, { 8,8,8 });
	SetBox({ 20,270,150 }, { 8,8,8 });

	for (int i = 0; i < 8; i++)
	{
		SetBox({ 40 + (i * 20.0f),270,130 }, { 10,10,10 });
	}


	SetSpawnPos({ 0,0,50 },10);
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
