#pragma once
#include "Item.h"
#include <memory>
#include <list>

class ItemManager
{
public:
	void Initialize(Model* model_);
	void Update();
	void Draw(ViewProjection viewProjection_);

	const std::list <std::unique_ptr<Item>>& GetObjects() {
		return Items;
	};

	void DeadInit();

private:
	void SetObjects();

	std::list <std::unique_ptr<Item>> Items;
	Model* model_ = nullptr;
};

