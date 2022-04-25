#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

//using namespace DirectX;

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

	float modelSpd = 0.5f;
	float modelRota = 0.02f;

	nyuryoku.x = input_->PushKey(DIK_UP) - input_->PushKey(DIK_DOWN);
	nyuryoku.z = input_->PushKey(DIK_UP) - input_->PushKey(DIK_DOWN);

	rota.y = input_->PushKey(DIK_RIGHT) - input_->PushKey(DIK_LEFT);

	//worldTransform_.rotation_.x += rota.x * modelRota;
	worldTransform_.rotation_.y += rota.y * modelRota;
	//worldTransform_.rotation_.z += rota.z * modelRota;

	

	//回転
	result.x = cos(worldTransform_.rotation_.y) * center.x + sin(worldTransform_.rotation_.y) * center.z;
	result.z = -sin(worldTransform_.rotation_.y) * center.x + cos(worldTransform_.rotation_.y) * center.z;
	
	worldTransform_.translation_.x += (nyuryoku.x * modelSpd) * result.x;
	worldTransform_.translation_.y += (nyuryoku.y * modelSpd) * result.y;
	worldTransform_.translation_.z += (nyuryoku.z * modelSpd) * result.z;

	worldTransform_.UpdateMatrix();
	viewProjection_.UpdateMatrix();

	debugText_->MyPrintf(50, 50, "worldTransform : %f,%f,%f",
		worldTransform_.translation_.x,
		worldTransform_.translation_.y,
		worldTransform_.translation_.z);
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
