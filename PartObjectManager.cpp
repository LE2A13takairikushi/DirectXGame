#include "PartObjectManager.h"
using namespace std;

void PartObjectManager::Initialize(Vector3 stagePos, Vector3 stageScale, Model* model_, TextureHandle tex)
{
	this->model_ = model_;
	this->tex = tex;

	//Vector3 bossStagePos = { 0,400,250 };
	//Vector3 stageScale = { 100,10,100 };

	//“ü‚Á‚Ä‚«‚½•ûŒü‚©‚çŒ©‚Äã
	for (int i = 0; i < 2; i++)
	{
		CreateEventBox({
			stagePos.x - stageScale.x,
			stagePos.y + stageScale.y,
			stagePos.z - stageScale.z + i * 100 + 100
			},
			{ 1,1,1 });
	}

	//‰E
	for (int i = 0; i < 2; i++)
	{
		CreateEventBox({
			stagePos.x - stageScale.x + i * 100 + 100 ,
			stagePos.y + stageScale.y,
			stagePos.z + stageScale.z
			},
			{ 1,1,1 });
	}
	//‰º
	for (int i = 0; i < 2; i++)
	{
		CreateEventBox({
			stagePos.x + stageScale.x,
			stagePos.y + stageScale.y,
			stagePos.z - stageScale.z + i * 100
			},
			{ 1,1,1 });
	}
	//¶
	for (int i = 0; i < 2; i++)
	{
		CreateEventBox({
			stagePos.x - stageScale.x + i * 100,
			stagePos.y + stageScale.y,
			stagePos.z - stageScale.z
			},
			{ 1,1,1 });
	}
}

void PartObjectManager::Update()
{
	for (unique_ptr<ParticleObject>& Object : Objects)
	{
		Object->Update();
	}
}

void PartObjectManager::Draw(ViewProjection viewProjection_)
{
	for (unique_ptr<ParticleObject>& Object : Objects)
	{
		Object->Draw(viewProjection_);
	}
}

void PartObjectManager::CreateEventBox(Vector3 pos, Vector3 scale)
{
	unique_ptr<ParticleObject> newBox = make_unique<ParticleObject>();
	newBox->Initialize(model_, model_,tex);
	newBox->SetPos({ pos.x, pos.y, pos.z });
	newBox->SetScale({ scale.x, scale.y, scale.z });
	Objects.push_back(std::move(newBox));
}
