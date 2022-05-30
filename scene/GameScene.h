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
	uint32_t textureHandle_ = 0;

	Model* model_ = nullptr;

	WorldTransform worldTransform_[20];
	ViewProjection viewProjection_;

	WinApp winApp_;
	DebugCamera* debugCamera_ = nullptr;

	Matrix4 matTrans;
	Matrix4 matRot;
	Matrix4 matRotX, matRotY, matRotZ;
	Matrix4 matScale;

	//カメラ上方向の角度
	float viewAngle = 0.0f;

	void CreateScale(Vector3& scaleMag, WorldTransform& worldTransform_);
	void CreateRot(Vector3& rotMag, WorldTransform& worldTransform_);
	void CreateTrans(Vector3& move, WorldTransform& worldTransform_);
	void MatrixCmp(WorldTransform& worldTransform_);

	bool debugCameraMode = false;

	enum PartId {
		kRoot,	//元座標
		kSpine,	//脊髄
		kChest,	//胸
		kHead,	//頭
		kArmL,	//左腕
		kArmR,	//右腕
		kHip,	//尻
		kLegL,	//左足
		kLegR,	//右足
		kNumPartId	//パーツの総数を表す数
	};

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
