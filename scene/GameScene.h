#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "DebugText.h"
#include "Input.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "DebugCamera.h"
#include "WinApp.h"
#include "Vector3.h"
#include "Player.h"
#include "Utill.h"

#include "EnemyManager.h"

#include "ModelManager.h"
#include "Skydome.h"
#include "FPSfix.h"

#include "GroundManager.h"
#include "ItemManager.h"

#include "enemyEventManager.h"
#include "JumpEventManager.h"
#include "VanishEventManager.h"

#include "VanishParticleManager.h"

#include "Pause.h"

#include "BossManager.h"

#include "PartObjectManager.h"
#include "checkPointManager.h"
#include "HealItemManager.h"

#include "Title.h"
#include "ArrowBoardManager.h"
#include "SoundDataManager.h"

#include "Result.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
  /// <summary>
  /// コンストクラタ
  /// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;
	WinApp winApp_;

	//テクスチャハンドル
	TextureHandle textureHandle_ = 0;

	//モデル
	ModelManager *modelManager;

	//カメラ
	ViewProjection viewProjection_;
	DebugCamera* debugCamera_ = nullptr;

	//キャラクター
	Player player_;
	EnemyManager* enemyManager;
	BossManager bossManager;

	//オブジェクト
	Skydome skydome;
	ArrowBoardManager aBoardManager;

	//イベントを発生させるオブジェクト群
	GroundManager gManager;
	ItemManager iManager;
	enemyEventManager enemyEManager;
	JumpEventManager jEManager;
	VanishEventManager vEManager;
	checkPointManager cManager;
	HealItemManager hIManager;

	EventObject Goal;

	//演出
	VanishParticleManager vpManager;
	PartObjectManager pObjectManager;

	//描画系
	Sprite *sprite = nullptr;
	Pause pause;
	Result result;

	//サウンド
	//BGM
	SoundDataManager SDManager;

	FPSfix fpsFix;

	Title title;
	ViewProjection titleView;

	bool clearFlag = false;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
	
	void CheckBulletCollision();
	void CheckPlayerAllCollision();
	void CheckEnemyAllCollision();
};