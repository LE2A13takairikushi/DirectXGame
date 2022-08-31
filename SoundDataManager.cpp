#include "SoundDataManager.h"

void SoundDataManager::Initialize()
{
	titleBGM = audio->LoadWave("title_bgm.wav");
	gamesceneBGM = audio->LoadWave("gamescene_bgm.wav");
	bossBGM = audio->LoadWave("boss_bgm.wav");
	bossBGM2 = audio->LoadWave("boss_bgm_2.wav");
	
	shotSE = audio->LoadWave("shot.wav");
	jumpSE = audio->LoadWave("jump.wav");
	dashSE = audio->LoadWave("dash.wav");
	healSE = audio->LoadWave("heal.wav");
	//jumpEndSE = audio->LoadWave("jump_end.wav");
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
}
