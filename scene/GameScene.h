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
#include <DirectXMath.h>

using namespace DirectX;

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

	Model* model_ = nullptr;
	Model* centerModel = nullptr;

	WorldTransform worldTransform_[2];
	ViewProjection viewProjection_;

	XMFLOAT3 centerVec = { 0,0,1 };
	XMFLOAT3 result[2] = { 
		{0,0,1},
		{0,0,1}
	};
	XMFLOAT3 keyInput = { 0,0,0 };

	XMFLOAT3 rota = { 0,0,0 };

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
