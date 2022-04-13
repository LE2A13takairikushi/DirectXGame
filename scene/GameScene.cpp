﻿#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include <random>

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

	textureHandle_ = TextureManager::Load("mario.jpg");
	model_ = Model::Create();

	//乱数シード生成器
	std::random_device seed_gen;

	//メルセンヌ・ツイスター
	std::mt19937_64 engine(seed_gen());

	//乱数範囲(回転角用)
	std::uniform_real_distribution<float> rotDist(0.0f, XM_2PI);

	//乱数範囲(座標用)
	std::uniform_real_distribution<float> posDist(-10.0f, 10.0f);

	for (int i = 0; i < _countof(worldTransform_); i++) {
		worldTransform_[i].scale_ = {1.0f, 1.0f, 1.0f};
		worldTransform_[i].rotation_ = {rotDist(engine), rotDist(engine), rotDist(engine)};
		worldTransform_[i].translation_ = {posDist(engine), posDist(engine), posDist(engine)};

		// 3dモデルの初期化
		worldTransform_[i].Initialize();
	}

	viewProjection_.eye = {0, 0, -10};

	//カメラの初期化
	viewProjection_.Initialize();
}

void GameScene::Update() { 

	if (input_->PushKey(DIK_W)) {
		viewProjection_.eye.z += 1;
	}
	if (input_->PushKey(DIK_S)) {
		viewProjection_.eye.z -= 1;
	}
	if (input_->PushKey(DIK_D)) {
		viewProjection_.eye.x += 1;
	}
	if (input_->PushKey(DIK_A)) {
		viewProjection_.eye.x -= 1;
	}

	for (int i = 0; i < _countof(worldTransform_); i++) {
		worldTransform_[i].rotation_.x += 0.1f;
	}

	viewProjection_.UpdateMatrix();

	for (int i = 0; i < _countof(worldTransform_); i++) {
		worldTransform_[i].UpdateMatrix();
	}
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
	for (int i = 0; i < _countof(worldTransform_); i++) {
		model_->Draw(worldTransform_[i], viewProjection_, textureHandle_);
	}


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
