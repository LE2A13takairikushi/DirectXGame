#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "PrimitiveDrawer.h"
#include <random>
#include "MyMath.h"

using namespace std;
//#include "AxisIndicator.h"

const float XM_PM = 3.14;

//winAppを使う際は、winApp.h内のwinAppコンストラクタがprivateになっているため注意

bool BoxColAABB(WorldTransform worldTransformA, WorldTransform worldTransformB)
{
	int DistanceX = worldTransformA.translation_.x - worldTransformB.translation_.x;
	int DistanceY = worldTransformA.translation_.y - worldTransformB.translation_.y;
	int DistanceZ = worldTransformA.translation_.z - worldTransformB.translation_.z;

	DistanceX = Abs(DistanceX);
	DistanceY = Abs(DistanceY);
	DistanceZ = Abs(DistanceZ);

	if (DistanceX <= worldTransformA.scale_.x + worldTransformB.scale_.x &&
		DistanceY <= worldTransformA.scale_.y + worldTransformB.scale_.y &&
		DistanceZ <= worldTransformA.scale_.z + worldTransformB.scale_.z)
	{
		return true;
	}
	return false;
}

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
	delete debugCamera_;
	delete skydome;
	delete sprite;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();

	groundTexture = TextureManager::Load("hogeta_white.png");
	model_ = Model::Create();

	textureHandle_ = TextureManager::Load("waito.jpg");
	player_.Initialize(model_,textureHandle_);

	enemyTexture = TextureManager::Load("enemy.png");
	enemy.Initialize(model_, enemyTexture);

	sprite = Sprite::Create(textureHandle_, { 0,0 });


	viewProjection_.Initialize();
	viewProjection_.eye = { 0,50,100 };
	viewProjection_.fovAngleY = FreqConversionRad(90.0f);

	//アスペクト比
	viewProjection_.aspectRatio = 1.0f;

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

	skydome = Model::CreateFromOBJ("skydome");

	skydomeTrans.Initialize();
	skydomeTrans.translation_ = { 0,0,0 };
	skydomeTrans.scale_ = { 1,1,1 };

	ground.Initialize(model_,groundTexture);

}

void GameScene::Update() {
	debugCamera_->Update();
	
	ground.Update();

	//地面との当たり判定
	player_.isGroundCol = BoxColAABB(player_.GetWorldTrans(), ground.worldTransform_);

	player_.Update();
	enemy.Update();

	CheckAllCollision();

	if (debugCameraMode == false)
	{

		//クォータニオンでは、注視点のオブジェクトの回転量がわかる
		//これをカメラに入れるには、注視点オブジェクトの正面ベクトルをカメラのベクトルに代入する

		viewProjection_.target = player_.GetWorldTrans().translation_;

		//マウスでカメラを動かす処理
		const float length = 10.0f;

		viewProjection_.eye = player_.GetWorldTrans().translation_ + (-player_.centerVec.normalize() * length);


		viewProjection_.UpdateMatrix();
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

	/*debugText_->SetPos(50, 50);
	debugText_->Printf(" worldTransform_[0].translation_.(x:%f),(y:%f),(z:%f)", 
		player_.worldTransform.translation_.x,
		player_.worldTransform.translation_.y,
		player_.worldTransform.translation_.z);*/
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

	skydome->Draw(skydomeTrans, viewProjection_);

	ground.Draw(viewProjection_);

	player_.Draw(viewProjection_);

	enemy.Draw(viewProjection_);

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

	/*if (BoxColAABB(player_.worldTransform,ground.worldTransform_))
	{
		sprite->Draw();
	}*/

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::CheckAllCollision()
{
	WorldTransform posA;
	WorldTransform posB;

	const list<unique_ptr<PlayerBullet>>& playerBullets = player_.GetBullets();

	posA = enemy.GetWorldTrans();

	for (const unique_ptr<PlayerBullet>& bullet : playerBullets)
	{
		posB = bullet->GetWorldTrans();

		if (BoxColAABB(posA, posB))
		{
			enemy.OnCollision();
			
			bullet->OnCollision();
		}
	}
}