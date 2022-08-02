#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "PrimitiveDrawer.h"
#include <random>
#include "MyMath.h"

//#include "AxisIndicator.h"

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

	textureHandle_ = TextureManager::Load("waito.jpg");
	model_ = Model::Create();
	
	player_.Initialize(model_,textureHandle_);

	//大元
	//worldTransform_.Initialize();
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
		//AxisIndicator::GetInstance()->SetVisible(true);
		//AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());
	}
	else
	{
		PrimitiveDrawer::GetInstance()->SetViewProjection(&viewProjection_);
		//AxisIndicator::GetInstance()->SetVisible(true);
		//AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);
	}
}

void GameScene::Update() {
	debugCamera_->Update();

	Vector2 mouse = input_->GetMousePosition();

	if (false)
	{
		if (debugCameraMode == false)
		{
			Vector2 angle;
			angle.x -= mouse.x * 0.01f;
			angle.y += mouse.y * 0.01f;

			//クォータニオンでは、注視点のオブジェクトの回転量がわかる
			//これをカメラに入れるには、注視点オブジェクトの正面ベクトルをカメラのベクトルに代入する
			//

			viewProjection_.target = player_.worldTransform.translation_;

			//マウスでカメラを動かす処理
			float length = 10.0f;
			viewProjection_.eye.x = viewProjection_.target.x + cosf(FreqConversionRad(angle.x) * length);
			viewProjection_.eye.z = viewProjection_.target.z + sinf(FreqConversionRad(angle.x) * length);

			viewProjection_.UpdateMatrix();
		}
	}


	player_.Update();


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
		player_.worldTransform.translation_.x,
		player_.worldTransform.translation_.y,
		player_.worldTransform.translation_.z);

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
	
	//if (true)
	//{
	//	//デバッグカメラ
	//	if (debugCameraMode)
	//	{
	//		model_->Draw(player_.worldTransform, debugCamera_->GetViewProjection(), textureHandle_);
	//	}
	//	else
	//	{
	//		
	//	}
	//}
	player_.Draw(viewProjection_);

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