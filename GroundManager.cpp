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
	SetBox({ 0,0,0 }, { 100,10,100 });
	//次の台地
	SetBox({ 0,50,200 }, { 100,100,100 });

	SetBox({ 0,180,250 }, { 10,10,10 });
	SetBox({ 0,200,280 }, { 10,10,10 });

	//階段
	SetBox( { 0,30,100 }, { 10,10,10 });
	SetBox( { 30,50,100 }, { 10,10,10 });
	SetBox( { 60,80,100 }, { 10,10,10 });
	SetBox( { 90,110,100 }, { 10,10,10 });

	//ちょっと危ない階段
	SetBox({ -120,30,80 }, { 10,10,10 });
	SetBox({ -140,60,110 }, { 10,10,10 });
	//SetBox({ -140,90,145 }, { 10,10,10 });
	SetBox({ -135,90,180 }, { 10,10,10 });
	SetBox({ -120,120,210 }, { 10,10,10 });

	SetSpawnPos({ 0,300,200 },10);
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
