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

//#include "ParticleManager.h"

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
	TextureHandle groundTexture = 0;

	//モデル
	ModelManager *modelManager;

	//カメラ
	ViewProjection viewProjection_;
	DebugCamera* debugCamera_ = nullptr;

	//キャラクター
	Player player_;
	EnemyManager* enemyManager;
	
	//オブジェクト
	Skydome skydome;

	//イベントを発生させるオブジェクト群
	GroundManager gManager;
	ItemManager iManager;
	enemyEventManager enemyEManager;
	JumpEventManager jEManager;
	VanishEventManager vEManager;

	EventObject Goal;

	//演出
	//ParticleManager particleManager;

	//描画系
	Sprite *sprite = nullptr;

	FPSfix fpsFix;

	bool debugCameraMode = false;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
	
	void CheckAllCollision();
	void CheckPlayerAllCollision();
	void CheckEnemyAllCollision();
};