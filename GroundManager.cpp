#include "GroundManager.h"
using namespace std;

unique_ptr<BoxObj> BoxCreate(Model* model_,Vector3 pos, Vector3 scale)
{
	unique_ptr<BoxObj> newBox = make_unique<BoxObj>();
	newBox->Initialize(model_);
	newBox->SetPos({ pos.x, pos.y, pos.z });
	newBox->SetScale({ scale.x, scale.y, scale.z });
	return newBox;
}

void GroundManager::Initialize(Model* model_)
{
	//最初の台地
	Objects.push_back(std::move(BoxCreate(model_, { 0,0,0 }, { 100,10,100 })));
	//次の台地
	Objects.push_back(std::move(BoxCreate(model_, { 0,50,200 }, { 100,100,100 })));

	//階段
	Objects.push_back(std::move(BoxCreate(model_, { 0,30,100 }, { 10,10,10 })));
	Objects.push_back(std::move(BoxCreate(model_, { 30,50,100 }, { 10,10,10 })));
	Objects.push_back(std::move(BoxCreate(model_, { 60,80,100 }, { 10,10,10 })));
	Objects.push_back(std::move(BoxCreate(model_, { 90,110,100 }, { 10,10,10 })));

	//ちょっと危ない階段
	Objects.push_back(std::move(BoxCreate(model_, { -120,30,80 }, { 10,10,10 })));
	Objects.push_back(std::move(BoxCreate(model_, { -140,60,110 }, { 10,10,10 })));
	Objects.push_back(std::move(BoxCreate(model_, { -140,90,145 }, { 10,10,10 })));
	Objects.push_back(std::move(BoxCreate(model_, { -135,90,180 }, { 10,10,10 })));
	Objects.push_back(std::move(BoxCreate(model_, { -120,120,210 }, { 10,10,10 })));

	SetSpawnPos({ -120,30,80 },10);
}


void GroundManager::Update()
{
	for (unique_ptr<BoxObj>& Object : Objects)
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
