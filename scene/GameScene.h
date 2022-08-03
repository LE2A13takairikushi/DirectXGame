#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "DebugCamera.h"
#include "WinApp.h"
#include "Vector3.h"
#include "Player.h"
#include "Ground.h"
#include "Utill.h"

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

	TextureHandle textureHandle_ = 0;
	TextureHandle groundTexture = 0;

	Model* model_ = nullptr;

	Model* skydome = nullptr;

	//WorldTransform worldTransform_;
	ViewProjection viewProjection_;

	WinApp winApp_;
	DebugCamera* debugCamera_ = nullptr;

	Player player_;

	WorldTransform skydomeTrans;

	Ground ground;

	Sprite *sprite = nullptr;

	//カメラ上方向の角度
	float viewAngle = 0.0f;

	bool debugCameraMode = false;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};

bool BoxColAABB(WorldTransform worldTransformA, WorldTransform worldTransformB);