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

	for (int i = 0; i < _countof(worldTransform_); i++)
	{
		worldTransform_[i].Initialize();
		worldTransform_[i].translation_ = {-1000,-1000,-1000};
	}

	for (int i = 0; i < 9; i++)
	{
		worldTransform_[i].translation_ = { -8.0f + i * 2.0f,8,0 };
		worldTransform_[i + 9].translation_ = { -8.0f + i * 2.0f,-8,0 };
	}

	if (false)
	{
		std::random_device seed_gen;

		std::mt19937_64 engine(seed_gen());

		std::uniform_real_distribution<float> rotdist(0.0f, XM_PM);

		std::uniform_real_distribution<float> posdist(-10.0f, 10.0f);
	}

	//スケール
	Vector3 scale = { 1.0f,1.0f,1.0f };
	//回転
	Vector3 rot[100];
	//平行移動
	Vector3 Transform[100];


	viewProjection_.eye = { 0,0,-100 };

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

	viewProjection_.Initialize();

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

	//移動処理
	//キャラクターの移動ベクトル
	Vector3 move = { 0,0,0 };
	float moveSpeed = 0.1f;

	if (input_->PushKey(DIK_RIGHT))
	{
		move.x += moveSpeed;
	}
	if (input_->PushKey(DIK_LEFT))
	{
		move.x -= moveSpeed;
	}

	for (int i = 0; i < _countof(worldTransform_); i++)
	{
		worldTransform_[i].translation_ += move;
		CreateScale(worldTransform_[i].scale_, worldTransform_[i]);
		CreateRot(worldTransform_[i].rotation_, worldTransform_[i]);
		CreateTrans(worldTransform_[i].translation_, worldTransform_[i]);
		MatrixCmp(worldTransform_[i]);
		worldTransform_[i].TransferMatrix();
	}



	//ビュー処理
	//ビューいじった名残
	/*if (false)
	{
		Vector3 move = { 0,0,0 };

		const float kEyeSpeed = 0.2f;

		if (input_->PushKey(DIK_W)) {
			move.z -= kEyeSpeed;
		}
		if (input_->PushKey(DIK_S)) {
			move.z += kEyeSpeed;
		}

		viewProjection_.eye += move;

		Vector3 taMove = { 0,0,0 };

		const float kTargetSpeed = 0.2f;

		if (input_->PushKey(DIK_LEFT)) {
			taMove.x -= kTargetSpeed;
		}
		if (input_->PushKey(DIK_RIGHT)) {
			taMove.x += kTargetSpeed;
		}

		viewProjection_.target += taMove;

		const float kUpRotSpeed = 0.04f;

		if (input_->PushKey(DIK_SPACE)) {
			viewAngle += kUpRotSpeed;

			viewAngle = fmodf(viewAngle, XM_PM * 2.0f);
		}

		//上方向ベクトルを計算
		viewProjection_.up = { cosf(viewAngle),sinf(viewAngle),0.0f };

		//行列の再計算
		viewProjection_.UpdateMatrix();

		debugText_->SetPos(50, 50);
		debugText_->Printf(
			"eye:(%f,%f,%f)", viewProjection_.eye.x, viewProjection_.eye.y, viewProjection_.eye.z);
		debugText_->SetPos(50, 70);
		debugText_->Printf(
			"target:(%f,%f,%f)", viewProjection_.target.x, viewProjection_.target.y, viewProjection_.target.z);
		debugText_->SetPos(50, 90);
		debugText_->Printf(
			"up:(%f,%f,%f)", viewProjection_.up.x, viewProjection_.up.y, viewProjection_.up.z);
	}*/

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
	debugText_->Printf("%f", viewProjection_.fovAngleY);
	debugText_->SetPos(50, 70);
	debugText_->Printf("%f %f %f", worldTransform_[9].translation_.x, 
		worldTransform_[9].translation_.y, 
		worldTransform_[9].translation_.z);
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
	
	if (false)
	{
		for (size_t i = 0; i < _countof(worldTransform_); i++)
		{
			//デバッグカメラ
			if (debugCameraMode)
			{
				model_->Draw(worldTransform_[i], debugCamera_->GetViewProjection(), textureHandle_);
			}
			else
			{
				model_->Draw(worldTransform_[i], viewProjection_, textureHandle_);
			}
		}
	}

	for (int i = 0; i < _countof(worldTransform_); i++)
	{
		model_->Draw(worldTransform_[i], viewProjection_, textureHandle_);
		//model_->Draw(worldTransform_[i], debugCamera_->GetViewProjection(), textureHandle_);
	}
	
	//sennnobyouga
	//PrimitiveDrawer::GetInstance()->DrawLine3d(Vector3(-100, 0, 0), Vector3(100, 0, 0), Vector4(255, 0, 0, 255));
	//PrimitiveDrawer::GetInstance()->DrawLine3d(Vector3(0, -100, 0), Vector3(0, 100, 0), Vector4(0, 255, 0, 255));
	//PrimitiveDrawer::GetInstance()->DrawLine3d(Vector3(0, 0, -100), Vector3(0, 0, 100), Vector4(0,0, 255, 255));

	
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
	matTrans = MathUtility::Matrix4Identity();

	matTrans.m[3][0] = move.x;
	matTrans.m[3][1] = move.y;
	matTrans.m[3][2] = move.z;

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