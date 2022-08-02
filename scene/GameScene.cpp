#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "AxisIndicator.h"
#include "PrimitiveDrawer.h"
#include <random>
#include "MyMath.h"

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

	//for (int i = 0; i < _countof(worldTransform_); i++)
	//{
	//	worldTransform_[i].Initialize();
	//}

	//大元
	worldTransform_.Initialize();
	viewProjection_.Initialize();

	viewProjection_.eye = { 0,50,100 };
	//viewProjection_.target = { 0,0,0 };
	//viewProjection_.up = { cosf(XM_PM / 4.0f),sinf(XM_PM / 4.0f),0.0f };
	//viewProjection_.up = {0.0f,0.0f,0.0f };

	viewProjection_.fovAngleY = FreqConversionRad(10.0f);

	//アスペクト比
	viewProjection_.aspectRatio = 1.0f;

	/*if (false)
	{
		//ニアクリップ距離を設定
		viewProjection_.nearZ = 52.0f;

		//ファークリップ距離を設定
		viewProjection_.farZ = 53.0f;

		//↑こいつらなーにー？
		// カメラに近い側(ニア)と遠い側	(ファー)の表示限界
		// これの間に挟まれた部分しか描画されなくなる
	}*/

	winApp_;
	debugCamera_ = new DebugCamera(winApp_.kWindowWidth, winApp_.kWindowHeight);

	if (debugCameraMode)
	{
		PrimitiveDrawer::GetInstance()->SetViewProjection(&debugCamera_->GetViewProjection());	
		AxisIndicator::GetInstance()->SetVisible(true);
		AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());
	}
	else
	{
		PrimitiveDrawer::GetInstance()->SetViewProjection(&viewProjection_);
		AxisIndicator::GetInstance()->SetVisible(true);
		AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);
	}
}

void GameScene::Update() {
	debugCamera_->Update();

	Vector2 mouse = input_->GetMousePosition();

	if (true)
	{
		if (debugCameraMode == false)
		{
			Vector2 angle;
			angle.x -= mouse.x * 0.01f;
			angle.y += mouse.y * 0.01f;

			//クォータニオンでは、注視点のオブジェクトの回転量がわかる
			//これをカメラに入れるには、注視点オブジェクトの正面ベクトルをカメラのベクトルに代入する
			//

			viewProjection_.target = worldTransform_.translation_;

			//マウスでカメラを動かす処理
			float length = 10.0f;
			viewProjection_.eye.x = viewProjection_.target.x + cosf(FreqConversionRad(angle.x) * length);
			viewProjection_.eye.z = viewProjection_.target.z + sinf(FreqConversionRad(angle.x) * length);

			viewProjection_.UpdateMatrix();
		}
	}

	//移動処理
	//キャラクターの移動ベクトル
	Vector3 move = { 0,0,0 };
	float moveSpeed = 0.1f;

	/*if (input_->PushKey(DIK_W))
	{
		move.z += moveSpeed;
	}
	if (input_->PushKey(DIK_S))
	{
		move.z -= moveSpeed;
	}
	if (input_->PushKey(DIK_D))
	{
		move.x += moveSpeed;
	}
	if (input_->PushKey(DIK_A))
	{
		move.x -= moveSpeed;
	}*/

	worldTransform_.translation_ += move;
	UpdateMatrix(worldTransform_);
	worldTransform_.TransferMatrix();

	//FOV変更処理
	if (input_->PushKey(DIK_UP)) {
		viewProjection_.fovAngleY += 0.01f;
		viewProjection_.fovAngleY = Max(viewProjection_.fovAngleY, XM_PM);
	}
	if (input_->PushKey(DIK_DOWN)) {
		viewProjection_.fovAngleY -= 0.01f;
		viewProjection_.fovAngleY = Min(viewProjection_.fovAngleY, 0.01f);
	}

	//ニアクリップ、ファークリップの更新の名残
	if (false)
	{
		if (input_->PushKey(DIK_UP)) {
			viewProjection_.nearZ += 0.1f;
		}
		if (input_->PushKey(DIK_DOWN)) {
			viewProjection_.nearZ -= 0.1f;
		}
	}

	viewProjection_.UpdateMatrix();

	debugText_->SetPos(50, 50);
	debugText_->Printf(" worldTransform_[0].translation_.(x:%f),(y:%f),(z:%f)", 
		worldTransform_.translation_.x,
		worldTransform_.translation_.y,
		worldTransform_.translation_.z);

	debugText_->SetPos(50, 70);
	debugText_->Printf(" mouse.translation_.(x:%f),(y:%f)",
		mouse.x,mouse.y);

	debugText_->SetPos(50, 90);
	debugText_->Printf(" viewProjection_.eye.(x:%f),(y:%f),(z:%f)",
		viewProjection_.eye.x, viewProjection_.eye.y, viewProjection_.eye.z);

	debugText_->SetPos(50, 110);
	debugText_->Printf(" viewProjection_.target.(x:%f),(y:%f),(z:%f)",
		viewProjection_.target.x, viewProjection_.target.y, viewProjection_.target.z);
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
	
	if (true)
	{
		//デバッグカメラ
		if (debugCameraMode)
		{
			model_->Draw(worldTransform_, debugCamera_->GetViewProjection(), textureHandle_);
		}
		else
		{
			model_->Draw(worldTransform_, viewProjection_, textureHandle_);
		}
	}

	//model_->Draw(worldTransform_, viewProjection_, textureHandle_);
	//model_->Draw(worldTransform_[1], viewProjection_, textureHandle_);

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

void GameScene::CreateScale(WorldTransform& worldTransform_)
{
	//スケーリング行列


	//スケールを設定するやつら
	matScale.m[0][0] = worldTransform_.scale_.x;
	matScale.m[1][1] = worldTransform_.scale_.y;
	matScale.m[2][2] = worldTransform_.scale_.z;
	matScale.m[3][3] = 1;

	worldTransform_.matWorld_.MatrixUint();
	worldTransform_.matWorld_ *= matScale;
}

void GameScene::CreateRot( WorldTransform& worldTransform_)
{

	matRot.MatrixUint();
	matRotX.MatrixUint();
	matRotY.MatrixUint();
	matRotZ.MatrixUint();

	matRotZ.m[0][0] = cos(worldTransform_.rotation_.z);
	matRotZ.m[0][1] = sin(worldTransform_.rotation_.z);
	matRotZ.m[1][0] = -sin(worldTransform_.rotation_.z);
	matRotZ.m[1][1] = cos(worldTransform_.rotation_.z);

	matRotX.m[1][1] = cos(worldTransform_.rotation_.x);
	matRotX.m[1][2] = sin(worldTransform_.rotation_.x);
	matRotX.m[2][1] = -sin(worldTransform_.rotation_.x);
	matRotX.m[2][2] = cos(worldTransform_.rotation_.x);

	matRotY.m[0][0] = cos(worldTransform_.rotation_.y);
	matRotY.m[0][2] = -sin(worldTransform_.rotation_.y);
	matRotY.m[2][0] = sin(worldTransform_.rotation_.y);
	matRotY.m[2][2] = cos(worldTransform_.rotation_.y);

	matRot *= matRotZ;
	matRot *= matRotX;
	matRot *= matRotY;

	worldTransform_.matWorld_.MatrixUint();
	worldTransform_.matWorld_ *= matRot;
}

void GameScene::CreateTrans(WorldTransform& worldTransform_)
{
	matTrans = MathUtility::Matrix4Identity();

	matTrans.m[3][0] = worldTransform_.translation_.x;
	matTrans.m[3][1] = worldTransform_.translation_.y;
	matTrans.m[3][2] = worldTransform_.translation_.z;

	worldTransform_.matWorld_.MatrixUint();
	worldTransform_.matWorld_ *= matTrans;
}

void GameScene::MatrixCmp(WorldTransform& worldTransform_)
{
	worldTransform_.matWorld_.MatrixUint();
	//スケーリング行列
	worldTransform_.matWorld_ *= matScale;
	//回転行列
	worldTransform_.matWorld_ *= matRot;
	//平行移動行列
	worldTransform_.matWorld_ *= matTrans;
}

void GameScene::UpdateMatrix(WorldTransform& worldTransform_)
{
	CreateScale(worldTransform_);
	CreateRot(worldTransform_);
	CreateTrans(worldTransform_);
	MatrixCmp(worldTransform_);
}