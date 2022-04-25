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
	centerModel = Model::Create();

	worldTransform_[0].scale_ = {5.0f,5.0f,5.0f};
	worldTransform_[0].translation_ = { 0.0f,0.0f,0.0f };
	worldTransform_[0].rotation_ = { 0.0f,0.0f,0.0f };

	viewProjection_.eye = { -10,10,-100 };

	//親
	worldTransform_[0].Initialize();

	//子
	worldTransform_[1].scale_ = { 0.5f ,0.5f ,0.5f };
	worldTransform_[1].translation_ = { 0,0,5 };
	worldTransform_[1].parent_ = &worldTransform_[0];
	worldTransform_[1].Initialize();

	viewProjection_.Initialize();

}

void GameScene::Update() {

	float modelSpd = 0.5f;
	float modelRota = 0.02f;

	keyInput.x = input_->PushKey(DIK_UP) - input_->PushKey(DIK_DOWN);
	keyInput.z = input_->PushKey(DIK_UP) - input_->PushKey(DIK_DOWN);

	rota.y = input_->PushKey(DIK_RIGHT) - input_->PushKey(DIK_LEFT);

	worldTransform_[0].rotation_.x += rota.x * modelRota;
	worldTransform_[0].rotation_.y += rota.y * modelRota;
	worldTransform_[0].rotation_.z += rota.z * modelRota;


	//回転
	result[0].x = cos(worldTransform_[0].rotation_.y) * centerVec.x + sin(worldTransform_[0].rotation_.y) * centerVec.z;
	result[0].z = -sin(worldTransform_[0].rotation_.y) * centerVec.x + cos(worldTransform_[0].rotation_.y) * centerVec.z;
	
	worldTransform_[0].translation_.x += (keyInput.x * modelSpd) * result[0].x;
	worldTransform_[0].translation_.y += (keyInput.y * modelSpd) * result[0].y;
	worldTransform_[0].translation_.z += (keyInput.z * modelSpd) * result[0].z;

	for (int i = 0; i < 2; i++)
	{
		worldTransform_[i].UpdateMatrix();
	}
	viewProjection_.UpdateMatrix();

	debugText_->MyPrintf(50, 50, "worldTransform : %f,%f,%f",
		worldTransform_[0].translation_.x,
		worldTransform_[0].translation_.y,
		worldTransform_[0].translation_.z);
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
	model_->Draw(worldTransform_[0], viewProjection_);
	centerModel->Draw(worldTransform_[1], viewProjection_);

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
