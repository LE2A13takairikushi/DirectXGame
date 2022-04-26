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

	viewProjection_.eye = { -10,30,-100 };

	//親
	worldTransform_[0].Initialize();

	//子
	worldTransform_[1].scale_ = { 0.5f ,0.5f ,0.5f };
	worldTransform_[1].translation_ = { 0,0,5 };
	worldTransform_[1].parent_ = &worldTransform_[0];
	worldTransform_[1].Initialize();

	for (int i = 2; i < 12; i++)
	{
		worldTransform_[i].scale_ = { 5.0f,5.0f,5.0f };
		worldTransform_[i].translation_ = { 0.0f,-35.0f,i * 30.0f - 50.0f };
		worldTransform_[i].rotation_ = { 0.0f,0.0f,0.0f };

		worldTransform_[i].Initialize();
	}

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
	result.x = cos(worldTransform_[0].rotation_.y) * centerVec.x + sin(worldTransform_[0].rotation_.y) * centerVec.z;
	result.z = -sin(worldTransform_[0].rotation_.y) * centerVec.x + cos(worldTransform_[0].rotation_.y) * centerVec.z;

	worldTransform_[0].translation_.x += (keyInput.x * modelSpd) * result.x;
	worldTransform_[0].translation_.y += (keyInput.y * modelSpd) * result.y;
	worldTransform_[0].translation_.z += (keyInput.z * modelSpd) * result.z;

	//カメラ回転
	viewProjection_.eye.x = worldTransform_[0].translation_.x + ( -result.x * 100);
	viewProjection_.eye.y = worldTransform_[0].translation_.y + ( -result.y * 10) + 50;
	viewProjection_.eye.z = worldTransform_[0].translation_.z + ( -result.z * 100);

	viewProjection_.target.x = worldTransform_[0].translation_.x;
	viewProjection_.target.y = worldTransform_[0].translation_.y;
	viewProjection_.target.z = worldTransform_[0].translation_.z;

	for (int i = 0; i < 2; i++)
	{
		worldTransform_[i].UpdateMatrix();
	}
	viewProjection_.UpdateMatrix();

	debugText_->MyPrintf(50, 50, "worldTransform : %f,%f,%f",
		worldTransform_[0].translation_.x,
		worldTransform_[0].translation_.y,
		worldTransform_[0].translation_.z);

	debugText_->MyPrintf(50, 70, "centerVector : %f,%f,%f",
		result.x,
		result.y,
		result.z);

	debugText_->MyPrintf(50, 90, "viewProjection_.eye : %f,%f,%f",
		viewProjection_.eye.x,
		viewProjection_.eye.y,
		viewProjection_.eye.z);
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

	for (int i = 2; i < 12; i++)
	{
		model_->Draw(worldTransform_[i], viewProjection_);
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
