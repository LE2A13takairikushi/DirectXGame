#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

using namespace DirectX;

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();

	model_ = Model::Create();

	worldTransform_.scale_ = { 5.0f,5.0f,5.0f };

	worldTransform_.translation_ = { 0.0f,0.0f,0.0f };
	
	worldTransform_.rotation_ = { 0.0f,0.0f,0.0f };

	viewProjection_.eye = { -10,10,-100 };

	worldTransform_.Initialize();
	viewProjection_.Initialize();
}

void GameScene::Update() {
	XMFLOAT3 moveModel = { 0,0,0 };
	XMFLOAT3 moveView = { 0,0,0 };
	XMFLOAT3 moveRota = { 0,0,0 };

	const float kEyeSpeed = 0.5f;
	const float kRotaSpeed = 0.05f;

	//入力
	if (input_->PushKey(DIK_UP))
	{
		moveModel = { 
			kEyeSpeed,
			kEyeSpeed,
			kEyeSpeed
		};
	}
	if (input_->PushKey(DIK_DOWN))
	{
		moveModel = {
			-kEyeSpeed,
			-kEyeSpeed,
			-kEyeSpeed
		};
	}
	if (input_->PushKey(DIK_Q))
	{
		//ここでベクトルもrotaする？
		moveRota = {
			0,
			-XM_PI / 180.0f,
			0
		};
		//スピードが増えるけど方向も変わってる

	}
	if (input_->PushKey(DIK_E))
	{
		moveRota = {
			0,
			XM_PI / 180.0f,
			0
		};

	}

	center.x = cos(worldTransform_.translation_.y);
	center.z = -sin(worldTransform_.translation_.y);
	
	center.x = sin(worldTransform_.translation_.y);
	center.z = cos(worldTransform_.translation_.y);
	//moveView = { (input_->PushKey(DIK_RIGHT) - input_->PushKey(DIK_LEFT)) * kEyeSpeed ,0,0 };

	worldTransform_.translation_.x += moveModel.x;
	worldTransform_.translation_.y += moveModel.y;
	worldTransform_.translation_.z += moveModel.z;

	worldTransform_.rotation_.x += moveRota.x;
	worldTransform_.rotation_.y += moveRota.y;
	worldTransform_.rotation_.z += moveRota.z;

	viewProjection_.eye.x += moveView.x;
	viewProjection_.eye.y += moveView.y;
	viewProjection_.eye.z += moveView.z;

	worldTransform_.UpdateMatrix();

	viewProjection_.UpdateMatrix();
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	model_->Draw(worldTransform_, viewProjection_);

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
