#include "PartObjectManager.h"
using namespace std;

void PartObjectManager::Initialize(Model* model_, TextureHandle tex)
{
	this->model_ = model_;
	this->tex = tex;

	Vector3 bossStagePos = { 0,400,250 };
	Vector3 bossStageScale = { 100,10,100 };

	//“ü‚Á‚Ä‚«‚½•ûŒü‚©‚çŒ©‚Äã
	for (int i = 0; i < 2; i++)
	{
		CreateEventBox({
			bossStagePos.x - bossStageScale.x,
			bossStagePos.y + bossStageScale.y,
			bossStagePos.z - bossStageScale.z + i * 100
			},
			{ 1,1,1 });
	}

	//‰E
	for (int i = 0; i < 2; i++)
	{
		CreateEventBox({
			bossStagePos.x - bossStageScale.x + i * 100,
			bossStagePos.y + bossStageScale.y,
			bossStagePos.z + bossStageScale.z
			},
			{ 1,1,1 });
	}
	//‰º
	for (int i = 0; i < 2; i++)
	{
		CreateEventBox({
			bossStagePos.x + bossStageScale.x,
			bossStagePos.y + bossStageScale.y,
			bossStagePos.z - bossStageScale.z + i * 100
			},
			{ 1,1,1 });
	}
	//¶
	for (int i = 0; i < 2; i++)
	{
		CreateEventBox({
			bossStagePos.x - bossStageScale.x + i * 100,
			bossStagePos.y + bossStageScale.y,
			bossStagePos.z - bossStageScale.z
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
