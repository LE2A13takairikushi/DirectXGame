#include "SoundDataManager.h"

void SoundDataManager::Initialize()
{
	gamesceneBGM = audio->LoadWave("gamescene_bgm.wav");
	
	shotSE = audio->LoadWave("shot.wav");
	jumpSE = audio->LoadWave("jump.wav");
	damageSE = audio->LoadWave("dash.wav");
	healSE = audio->LoadWave("heal.wav");
	jumpEndSE = audio->LoadWave("jump_end.wav");
	enemyPopSE = audio->LoadWave("enemypop.wav");
	hitSE = audio->LoadWave("hit.wav");
	deadEnemySE = audio->LoadWave("deadenemy.wav");
	jumpEventSE = audio->LoadWave("superjump.wav");
	curserSE = audio->LoadWave("curser.wav");
	eventclearSE = audio->LoadWave("eventclear.wav");
	vibrationSE = audio->LoadWave("vibration.wav");
	vibrationEndSE = audio->LoadWave("vibration_end.wav");
	bossboomSE = audio->LoadWave("boss_boom.wav");
	bossendboomSE = audio->LoadWave("boss_endboom.wav");
	checkpointSE = audio->LoadWave("checkpoint.wav");
	pushSE = audio->LoadWave("push.wav");
	dashSE = audio->LoadWave("dash_2.wav");
	bossJumpEndSE = audio->LoadWave("boss_jumpend.wav");
	criticalSE = audio->LoadWave("critical.wav");
}
