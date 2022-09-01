#pragma once
#include "Boss.h"
#include <memory>
#include <list>
#include "SoundDataManager.h"

class BossManager
{
public:
	void Initialize(Model* model);
	void Update(Vector3 pos, Vector3 scale, Vector3 targetPos, VanishParticleManager& vpManager,Audio* audio,SoundDataManager sdmanager);
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

	void DeadInit();

private:
	std::list<std::unique_ptr<Boss>> bossList;

	bool isBossBattle = false;

	Model* model = nullptr;
	TextureHandle tex = 0;
	TextureHandle weekTex = 0;
	TextureHandle changeTex = 0;
	TextureHandle bTex = 0;
};

