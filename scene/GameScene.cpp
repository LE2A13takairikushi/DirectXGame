#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "PrimitiveDrawer.h"
#include <random>
#include "MyMath.h"
#include "Collsion.h"

using namespace std;
//#include "AxisIndicator.h"

const float XM_PM = 3.14;

//winAppを使う際は、winApp.h内のwinAppコンストラクタがprivateになっているため注意

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete modelManager;
	delete enemyManager;

	delete debugCamera_;
	delete sprite;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();

	//マウスを非表示に
	ShowCursor(false);

	groundTexture = TextureManager::Load("hogeta_white.png");

	modelManager = new ModelManager();

	textureHandle_ = TextureManager::Load("waito.jpg");
	player_.Initialize(modelManager->model_,textureHandle_);

	//enemyManager->Initialize(modelManager->model_);
	enemyManager = new EnemyManager(modelManager->model_);

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

	//skydome = Model::CreateFromOBJ("skydome");

	skydome.Initialize(modelManager->skydome);

	ground.Initialize(modelManager->model_,groundTexture);

	boxObject.Initialize(modelManager->model_, groundTexture);
	boxObject.SetPos({ 50.0f, 20.0f, 0.0f });

	boxObject2.Initialize(modelManager->model_, groundTexture);
	boxObject2.SetPos({ -50.0f, 00.0f, 0.0f });

	fpsFix.Initialize();

}

void GameScene::Update() {
	debugCamera_->Update();

	fpsFix.Update();
	
	ground.Update();

	boxObject.Update();
	boxObject2.Update();

	//地面との当たり判定
	
	//player_.isJumpCheck = BoxColAABB(player_.GetWorldTrans(), ground.GetWorldTrans());

	player_.Update();
	
	CheckPlayerAllCollision();

	player_.UpdateMatrixAndMove();

	enemyManager->Update(player_.GetWorldTrans().translation_);

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
	debugText_->Printf("fps:%f",fpsFix.fps);
	debugText_->SetPos(50, 70);
	debugText_->Printf("frameTime:%f",fpsFix.frameTime);*/
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
	
	skydome.Draw(viewProjection_);

	ground.Draw(viewProjection_);

	boxObject.Draw(viewProjection_);
	boxObject2.Draw(viewProjection_);

	player_.Draw(viewProjection_);

	enemyManager->Draw(viewProjection_);

	if (false)
	{
		PrimitiveDrawer::GetInstance()->DrawLine3d(Vector3(-100, 0, 0), Vector3(100, 0, 0), Vector4(255, 0, 0, 255));
		PrimitiveDrawer::GetInstance()->DrawLine3d(Vector3(0, -100, 0), Vector3(0, 100, 0), Vector4(0, 255, 0, 255));
		PrimitiveDrawer::GetInstance()->DrawLine3d(Vector3(0, 0, -100), Vector3(0, 0, 100), Vector4(0,0, 255, 255));
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

	const list<unique_ptr<Enemy>>& enemys = enemyManager->enemys;

	//敵と自分の弾の当たり判定
	for (const unique_ptr<PlayerBullet>& bullet : playerBullets)
	{
		for (const unique_ptr<Enemy>& enemy : enemys)
		{
			posA = enemy->GetWorldTrans();
			posB = bullet->GetWorldTrans();

			if (BoxColAABB(posA, posB))
			{
				enemy->OnCollision();

				bullet->OnCollision();
			}
		}
	}

	//自分と敵の弾の当たり判定
	for (const unique_ptr<Enemy>& enemy : enemys)
	{	
		posA = player_.GetWorldTrans();
		const list<unique_ptr<EnemyBullet>>& enemyBullet = enemy->GetBullets();
		for (const unique_ptr<EnemyBullet>& bullet : enemyBullet)
		{
			posB = bullet->GetWorldTrans();
			if (BoxColAABB(posA, posB))
			{
				bullet->OnCollision();
			}
		}
	}

	//地面と自分の弾の当たり判定
	posA = ground.GetWorldTrans();
	for (const unique_ptr<PlayerBullet>& bullet : playerBullets)
	{
		posB = bullet->GetWorldTrans();

		if (BoxColAABB(posA, posB))
		{
			bullet->OnCollision();
		}
		posA = boxObject.GetWorldTrans();
		if (BoxColAABB(posA, posB))
		{
			bullet->OnCollision();
		}
		posA = boxObject2.GetWorldTrans();
		if (BoxColAABB(posA, posB))
		{
			bullet->OnCollision();
		}
	}
	posA = ground.GetWorldTrans();
	//地面と敵の弾の当たり判定
	for (const unique_ptr<Enemy>& enemy : enemys)
	{
		const list<unique_ptr<EnemyBullet>>& enemyBullet = enemy->GetBullets();
		for (const unique_ptr<EnemyBullet>& bullet : enemyBullet)
		{
			if (BoxColAABB(posA, posB))
			{
				bullet->OnCollision();
			}
			posA = boxObject.GetWorldTrans();
			if (BoxColAABB(posA, posB))
			{
				bullet->OnCollision();
			}
			posA = boxObject2.GetWorldTrans();
			if (BoxColAABB(posA, posB))
			{
				bullet->OnCollision();
			}
		}
	}


	//敵の移動制御
	//プレイヤーの周りに透明な球を配置して、それに当たるまで
	//プレイヤーに前進し、そうでなければ後退する
	for (const unique_ptr<Enemy>& enemy : enemys)
	{
		posA = enemy->GetWorldTrans();
		posB = player_.GetWorldTrans();

		if (SphereCol(posA.translation_, posB.translation_, 30.0f, posB.scale_.x))
		{
			enemy->PhaseChange(Phase::Leave);
		}
		else
		{
			enemy->PhaseChange(Phase::Approach);
		}
	}
}

void GameScene::CheckPlayerAllCollision()
{
	WorldTransform posB;

	posB = boxObject.GetWorldTrans();
	player_.CheckHitBox(posB);

	posB = boxObject2.GetWorldTrans();
	player_.CheckHitBox(posB);

	posB = ground.GetWorldTrans();
	player_.CheckHitBox(posB);

}
