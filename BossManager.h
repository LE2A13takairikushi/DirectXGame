#pragma once
#include "Boss.h"
#include <memory>
#include <list>

class BossManager
{
public:
	void Initialize(Model* model, TextureHandle tex);
	void Update(Vector3 pos, Vector3 scale, Vector3 targetPos);
	void Draw(ViewProjection view);

	void End();

	void SpawnBoss(Vector3 initpos);

	std::list<std::unique_ptr<Boss>>& GetBossList() {
		return bossList;
	};

private:
	std::list<std::unique_ptr<Boss>> bossList;

	Model* model = nullptr;
	TextureHandle tex = 0;

};

