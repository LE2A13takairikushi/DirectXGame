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

bool GameScene::SphereCollision(Sphere circle1, Sphere circle2)
{
	int a = circle1.position.x - circle2.position.x;
	int b = circle1.position.y - circle2.position.y;

	int c = circle1.r - circle2.r;

	int d = circle1.position.z - circle2.position.z;
	if (a * a + b * b + d * d <= c * c)
	{
		return true;
	}
	return false;
}

bool GameScene::SphereCollision(Sphere circle1, Ray circle2)
{
	int a = circle1.position.x - circle2.position.x;
	int b = circle1.position.y - circle2.position.y;

	int c = circle1.r - 0;

	int d = circle1.position.z - circle2.position.z;
	if (a * a + b * b + d * d <= c * c)
	{
		return true;
	}
	return false;
}

bool GameScene::RaySphereCol(const Ray ray,const Sphere sphere)
{
	//引数① レイ
	// -レイの方向
	// -レイの始点
	//引数② 球
	// -ポジション
	// -半径

	//レイの始点から球のポジションまでのびるベクトル = tempVec
	// start =　レイの始点 end = 球のポジション
	Vector3 tempVec;
	//終点-始点
	tempVec = sphere.position - ray.position;

	Vector3 tempRayDirection = ray.direction;
	tempRayDirection.normalize();

	//tempVec と レイの方向ベクトルをdotにぶち込んで tempLength(黒い球の長さが分かる)
	float tempLength = tempVec.dot(tempRayDirection);

	//tempLengthが0より小さかったら始点より後ろにあるはずなので当たってない
	if (tempLength < 0) return false;

	tempRayDirection *= tempLength;

	Vector3 tempRayPos = ray.position + tempRayDirection;

	//かるい！！！！！
	if (tempLength * tempLength > ray.direction.lengthSquared()) return false;

	// 球のポジション - tempRayPos = 球からレイまでの距離(aがわかる)
	Vector3 a = sphere.position - tempRayPos;

	//かるい!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	return a.lengthSquared() < sphere.r * sphere.r;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();

	textureHandle_ = TextureManager::Load("mario.jpg");
	model_ = Model::Create();

	worldTransform_.Initialize();
	worldTransform_.translation_ = { -10,0,0 };

	worldTransformSphere.position = worldTransform_.translation_;
	worldTransformSphere.r = worldTransform_.scale_.x;

	ray.direction = { 50,0,0 };
	ray.position = { 0,0,0 };

	sprite = Sprite::Create(textureHandle_, { 0,0 });

	//rayWorldTrans.scale_ = { 1.0f,1.0f,100.0f };
	
	//スケール
	Vector3 scale = { 1.0f,1.0f,1.0f };
	//回転
	Vector3 rot;
	//平行移動
	Vector3 Transform;

	viewProjection_.Initialize();
	viewProjection_.eye = { 0,200,-200 };

	viewProjection_.fovAngleY = FreqConversionRad(10.0f);

	//アスペクト比
	viewProjection_.aspectRatio = 1.0f;

	viewProjection_.UpdateMatrix();

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

float kakudo = 0;

void GameScene::Update() {
	debugCamera_->Update();

	//移動処理
	//キャラクターの移動ベクトル
	Vector3 move = { 0,0,0 };
	float moveSpeed = 0.1f;


	ray.direction = { 50,0, kakudo };

	if (input_->PushKey(DIK_Q))
	{
		kakudo += 1.0f;
	}

	if (input_->PushKey(DIK_E))
	{
		kakudo -= 1.0f;
	}

	if (input_->PushKey(DIK_D))
	{
		move.x += moveSpeed;
	}
	if (input_->PushKey(DIK_A))
	{
		move.x -= moveSpeed;
	}

	if (input_->PushKey(DIK_W))
	{
		move.z += moveSpeed;
	}
	if (input_->PushKey(DIK_S))
	{
		move.z -= moveSpeed;
	}

	if (input_->PushKey(DIK_RIGHT))
	{
		ray.position.x += moveSpeed;
	}
	if (input_->PushKey(DIK_LEFT))
	{
		ray.position.x -= moveSpeed;
	}

	/*if (input_->PushKey(DIK_UP))
	{
		ray.position.y += moveSpeed;
	}
	if (input_->PushKey(DIK_DOWN))
	{
		ray.position.y -= moveSpeed;
	}*/

	if (input_->PushKey(DIK_UP))
	{
		ray.position.z += moveSpeed;
	}
	if (input_->PushKey(DIK_DOWN))
	{
		ray.position.z -= moveSpeed;
	}

	worldTransform_.translation_ += move;
	UpdateMatrix(worldTransform_);
	worldTransform_.TransferMatrix();

	worldTransformSphere.position = worldTransform_.translation_;
	worldTransformSphere.r = worldTransform_.scale_.x;

	//FOV変更処理
	//if (input_->PushKey(DIK_UP)) {
	//	viewProjection_.fovAngleY += 0.01f;
	//	viewProjection_.fovAngleY = Max(viewProjection_.fovAngleY, XM_PM);
	//}
	//if (input_->PushKey(DIK_DOWN)) {
	//	viewProjection_.fovAngleY -= 0.01f;
	//	viewProjection_.fovAngleY = Min(viewProjection_.fovAngleY, 0.01f);
	//}

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
	debugText_->Printf(" ray(%d)",
		RaySphereCol(ray, worldTransformSphere));

	debugText_->SetPos(50, 90);
	debugText_->Printf(" ray(x:%f),(y:%f),(z:%f)",
		ray.position.x, ray.position.y, ray.position.z);

	debugText_->SetPos(50, 110);
	debugText_->Printf(" worldTransformSphere(x:%f),(y:%f),(z:%f)",
		worldTransformSphere.position.x, worldTransformSphere.position.y, worldTransformSphere.position.z);
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
	if (RaySphereCol(ray, worldTransformSphere))
	{
		sprite->Draw();
	}

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
	
	//デバッグカメラ
	if (debugCameraMode)
	{
		model_->Draw(worldTransform_, debugCamera_->GetViewProjection(), textureHandle_);

		Vector3 rayEnd;
		rayEnd = ray.position + ray.direction;

		PrimitiveDrawer::GetInstance()->DrawLine3d(ray.position, rayEnd, Vector4(255, 255, 255, 255));
	}
	else
	{
		model_->Draw(worldTransform_, viewProjection_, textureHandle_);

		Vector3 rayEnd;
		rayEnd = ray.position + ray.direction;

		PrimitiveDrawer::GetInstance()->DrawLine3d(ray.position, rayEnd, Vector4(255, 255, 255, 255));
	}

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

void GameScene::CreateRot(WorldTransform& worldTransform_)
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