#include "ItemManager.h"

using namespace std;

unique_ptr<Item> ItemCreate(Model* model_, Vector3 pos, Vector3 scale)
{
	unique_ptr<Item> newItem = make_unique<Item>();
	newItem->Initialize(model_,TextureManager::Load("life.png"));
	newItem->SetPos({ pos.x, pos.y, pos.z });
	newItem->SetScale({ scale.x, scale.y, scale.z });
	return newItem;
}

void ItemManager::SetObjects()
{
	//最初左ルートのやつ
	Items.push_back(std::move(ItemCreate(model_, { -140,132,145 }, { 3,3,3 })));

	//途中の空中のやつ
	Items.push_back(std::move(ItemCreate(model_, { 90,315,230 }, { 3,3,3 })));

	Items.push_back(std::move(ItemCreate(model_, { 440,220,200 }, { 3,3,3 })));
	Items.push_back(std::move(ItemCreate(model_, { 460,280,400 }, { 3,3,3 })));
	Items.push_back(std::move(ItemCreate(model_, { 440,360,200 }, { 3,3,3 })));
}

void ItemManager::DeadInit()
{
	Items.clear();
	SetObjects();
}

void ItemManager::Initialize(Model* model_)
{
	this->model_ = model_;
	SetObjects();
}

void ItemManager::Update()
{
	Items.remove_if([](std::unique_ptr<Item>& item) {
		return item->IsDead();
		});


	for (unique_ptr<Item>& Item : Items)
	{
		Item->Update();
	}
}

void ItemManager::Draw(ViewProjection viewProjection_)
{
	for (unique_ptr<Item>& Item : Items)
	{
		Item->Draw(viewProjection_);
	}
}
