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
	Sprite* sprite = nullptr;

	WorldTransform worldTransform_;
	ViewProjection viewProjection_;

	WinApp winApp_;
	DebugCamera* debugCamera_ = nullptr;

	Matrix4 matTrans;
	Matrix4 matRot;
	Matrix4 matRotX, matRotY, matRotZ;
	Matrix4 matScale;

	//カメラ上方向の角度
	float viewAngle = 0.0f;

	void CreateScale(WorldTransform& worldTransform_);
	void CreateRot( WorldTransform& worldTransform_);
	void CreateTrans(WorldTransform& worldTransform_);
	void MatrixCmp(WorldTransform& worldTransform_);
	void UpdateMatrix(WorldTransform& worldTransform_);

	bool debugCameraMode = true;

	struct Ray
	{
		Vector3 direction;
		Vector3 position;
	};

	struct Sphere
	{
		Vector3 position;
		float r;
	};

	Sphere worldTransformSphere;
	Ray ray;

	bool RaySphereCol(const Ray ray, const Sphere sphere);

	bool SphereCollision(Sphere circle1, Sphere circle2);
	bool SphereCollision(Sphere circle1, Ray circle2);
	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
