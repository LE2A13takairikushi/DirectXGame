#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "AxisIndicator.h"
#include "PrimitiveDrawer.h"

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
	delete debugCamera_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();

	textureHandle_ = TextureManager::Load("mario.jpg");
	model_ = Model::Create();

	worldTransform_.Initialize();
	viewProjection_.Initialize();
	debugCamera_ = new DebugCamera(1280, 720);

	PrimitiveDrawer::GetInstance()->SetViewProjection(&debugCamera_->GetViewProjection());

	worldTransform_.scale_ = { 5.0f,2.0f,2.0f };
	Matrix4 matScale;
	matScale.MatrixUint();

	Matrix4 uintMt;
	uintMt.MatrixUint();

	for (int i = 0; i < 4; i++)
	{
		matScale.m[0][i] *= worldTransform_.scale_.x;
		matScale.m[1][i] *= worldTransform_.scale_.y;
		matScale.m[2][i] *= worldTransform_.scale_.z;
	}

	worldTransform_.matWorld_ = uintMt;
	worldTransform_.matWorld_ *= matScale;

	//行列の転送
	worldTransform_.TransferMatrix();

	worldTransform_.rotation_ = { 1.0f,0.1f,0.1f };
	Matrix4 matRot;

	Matrix4 matRotZ
	{
		cos(worldTransform_.rotation_.x),sin(worldTransform_.rotation_.y),0,0,
		-sin(worldTransform_.rotation_.x),cos(worldTransform_.rotation_.y),0,0,
		0,0,1,0,
		0,0,0,1
	};

	Matrix4 matRotX
	{
		1,0,0,0,
		0,cos(worldTransform_.rotation_.y),sin(worldTransform_.rotation_.z),0,
		0,-sin(worldTransform_.rotation_.y),cos(worldTransform_.rotation_.z),0,
		0,0,0,1
	};

	Matrix4 matRotY
	{
		cos(worldTransform_.rotation_.x),0,-sin(worldTransform_.rotation_.z),0,
		0,1,0,0,
		sin(worldTransform_.rotation_.x),0,cos(worldTransform_.rotation_.z),0,
		0,0,0,1
	};

	matRot *= matRotZ;
	matRot *= matRotX;
	matRot *= matRotY;

	worldTransform_.matWorld_ = uintMt;
	worldTransform_.matWorld_ *= matRot;

	worldTransform_.TransferMatrix();

	//なんか消えた なんで？

	//worldTransform_.translation_ = { 10.0f,5.0f,1.0f };

	//Matrix4 matTrans = MathUtility::Matrix4Identity();


}

void GameScene::Update() {
	debugCamera_->Update();

	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());
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
	model_->Draw(worldTransform_, debugCamera_->GetViewProjection(), textureHandle_);

	//ライン描画
	/*Vector3 st = { 0,0,0 };
	Vector3 ed = { 640,640,640 };
	Vector4 color = {255, 255, 255, 255};*/

	//PrimitiveDrawer::GetInstance()->DrawLine3d(st, ed, color);

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
