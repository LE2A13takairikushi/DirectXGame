#pragma once
#include "Boss.h"
#include <memory>
#include <list>

class BossManager
{
public:
	void Initialize(Model* model, TextureHandle tex);
	void Update(Vector3 pos, Vector3 scale, Vector3 targetPos, VanishParticleManager& vpManager);
	void Draw(ViewProjection view, float mouseVertRota);
	void BossUIDraw();

	void End();

	void SpawnBoss(Vector3 initpos);

	std::list<std::unique_ptr<Boss>>& GetBossList() {
		return bossList;
	};

	bool IsBossBattle() { return isBossBattle; };
	bool BossBattleStart() { return isBossBattle = true; };
	bool BossBattleEnd() { return isBossBattle = false; };

private:
	std::list<std::unique_ptr<Boss>> bossList;

	bool isBossBattle = false;

	Model* model = nullptr;
	TextureHandle tex = 0;

	TextureHandle weekTex = 0;
};

