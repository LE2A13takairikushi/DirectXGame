#include "ItemManager.h"

using namespace std;

unique_ptr<Item> ItemCreate(Model* model_, Vector3 pos, Vector3 scale)
{
	unique_ptr<Item> newItem = make_unique<Item>();
	newItem->Initialize(model_,TextureManager::Load("waito.jpg"));
	newItem->SetPos({ pos.x, pos.y, pos.z });
	newItem->SetScale({ scale.x, scale.y, scale.z });
	return newItem;
}

void ItemManager::Initialize(Model* model_)
{
	Items.push_back(std::move(ItemCreate(model_, { -140,150,145 }, { 3,3,3 })));
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
