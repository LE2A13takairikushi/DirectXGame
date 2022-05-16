#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "AxisIndicator.h"
#include "PrimitiveDrawer.h"

const float XM_PM = 3.14;

//winAppを使う際は、winApp.h内のwinAppコンストラクタがprivateになっているため注意

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

	//スケール
	Vector3 scale = { 5.0f,2.0f,2.0f };

	CreateScale(scale, worldTransform_);

	//回転
	Vector3 rot = { XM_PM / 3.0f, XM_PM / 5.0f, XM_PM / 4.0f };

	CreateRot(rot,worldTransform_);

	//平行移動
	Vector3 Transform = { 10.0f,0.0f,0.0f };

	CreateTrans(Transform, worldTransform_);

	worldTransform_.TransferMatrix();

	winApp_;
	debugCamera_ = new DebugCamera(winApp_.kWindowWidth, winApp_.kWindowHeight);

	PrimitiveDrawer::GetInstance()->SetViewProjection(&debugCamera_->GetViewProjection());
	
	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());
}

void GameScene::Update() {
	debugCamera_->Update();
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

	PrimitiveDrawer::GetInstance()->DrawLine3d(Vector3(-100, 0, 0), Vector3(100, 0, 0), Vector4(255, 0, 0, 255));
	PrimitiveDrawer::GetInstance()->DrawLine3d(Vector3(0, -100, 0), Vector3(0, 100, 0), Vector4(0, 255, 0, 255));
	PrimitiveDrawer::GetInstance()->DrawLine3d(Vector3(0, 0, -100), Vector3(0, 0, 100), Vector4(0,0, 255, 255));

	
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

void GameScene::CreateScale(Vector3& scaleMag, WorldTransform& worldTransform_)
{
	//スケーリング行列
	Matrix4 matScale;

	//スケールを設定するやつら
	matScale.m[0][0] = scaleMag.x;
	matScale.m[1][1] = scaleMag.y;
	matScale.m[2][2] = scaleMag.z;
	matScale.m[3][3] = 1;

	worldTransform_.matWorld_.MatrixUint();
	worldTransform_.matWorld_ *= matScale;
}

void GameScene::CreateRot(Vector3& rotMag, WorldTransform& worldTransform_)
{
	Matrix4 matRot;
	Matrix4 matRotX, matRotY, matRotZ;

	matRot.MatrixUint();
	matRotX.MatrixUint();
	matRotY.MatrixUint();
	matRotZ.MatrixUint();

	matRotZ.m[0][0] = cos(rotMag.z);
	matRotZ.m[0][1] = sin(rotMag.z);
	matRotZ.m[1][0] = -sin(rotMag.z);
	matRotZ.m[1][1] = cos(rotMag.z);

	matRotX.m[1][1] = cos(rotMag.x);
	matRotX.m[1][2] = sin(rotMag.x);
	matRotX.m[2][1] = -sin(rotMag.x);
	matRotX.m[2][2] = cos(rotMag.x);

	matRotY.m[0][0] = cos(rotMag.y);
	matRotY.m[0][2] = -sin(rotMag.y);
	matRotY.m[2][0] = sin(rotMag.y);
	matRotY.m[2][2] = cos(rotMag.y);

	matRot *= matRotZ;
	matRot *= matRotX;
	matRot *= matRotY;

	worldTransform_.matWorld_.MatrixUint();
	worldTransform_.matWorld_ *= matRot;
}

void GameScene::CreateTrans(Vector3& move, WorldTransform& worldTransform_)
{
	Matrix4 matTrans = MathUtility::Matrix4Identity();

	matTrans.m[3][0] = move.x;
	matTrans.m[3][1] = move.y;
	matTrans.m[3][2] = move.z;

	worldTransform_.matWorld_.MatrixUint();
	worldTransform_.matWorld_ *= matTrans;
}