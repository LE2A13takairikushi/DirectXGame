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
	pause.End();
	player_.End();
	bossManager.End();
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();

	modelManager = new ModelManager();

	textureHandle_ = TextureManager::Load("waito.jpg");
	player_.Initialize(modelManager->player,modelManager->body,modelManager->taiya);

	TextureHandle white = TextureManager::Load("white.png");

	enemyManager = new EnemyManager(
		modelManager->firewisp,
		modelManager->model_,
		white
	);

	bossManager.Initialize(modelManager->model_,white);

	sprite = Sprite::Create(textureHandle_, { 0,0 });

	viewProjection_.Initialize();
	viewProjection_.eye = { 0,50,100 };
	viewProjection_.fovAngleY = DegreeConversionRad(90.0f);

	//アスペクト比
	viewProjection_.aspectRatio = 1.0f;

	winApp_;
	debugCamera_ = new DebugCamera(winApp_.kWindowWidth, winApp_.kWindowHeight);

	PrimitiveDrawer::GetInstance()->SetViewProjection(&viewProjection_);

	skydome.Initialize(modelManager->skydome);

	gManager.Initialize(modelManager->model_);
	iManager.Initialize(modelManager->model_);
	enemyEManager.Initialize(gManager.GetBossStagePos(), modelManager->model_);
	jEManager.Initialize(modelManager->model_);
	vEManager.Initialize(modelManager->model_);

	Goal.Initialize(modelManager->model_,TextureManager::Load("goal.png"));
	Goal.SetPos({ 490,370,420 });
	Goal.SetScale({ 8, 8, 8 });

	fpsFix.Initialize();

	vpManager.Initialize(modelManager->model_,white);
	pObjectManager.Initialize(gManager.GetBossStagePos(), 
		gManager.GetBossStageScale(),
		modelManager->model_,
		white);
	pause.Initialize();

	player_.SetSpawnPos(gManager.GetSpawnPos());


	title.Initialize(modelManager->player, modelManager->body, modelManager->taiya, titleView);
	titleView.Initialize();
	titleView.fovAngleY = DegreeConversionRad(90.0f);
	//アスペクト比
	titleView.aspectRatio = 1.0f;
}

void GameScene::Update() {
	fpsFix.Update();

	if (title.IsTitle())
	{
		title.Update();
	}
	else
	{
		if (pause.IsMenuOpen() == false)
		{
			debugCamera_->Update();

			gManager.Update();
			iManager.Update();
			enemyEManager.Update();
			jEManager.Update();
			vEManager.Update();

			Goal.Update();

			player_.Update(vpManager);

			CheckPlayerAllCollision();

			player_.UpdateMatrixAndMove();

			CheckEnemyAllCollision();

			vpManager.Update();
			pObjectManager.Update();

			enemyManager->Update(player_.GetPos(), bossManager.IsBossBattle(), vpManager);

			bossManager.Update(gManager.GetBossStagePos(),
				gManager.GetBossStageScale(), player_.GetPos(),
				vpManager);

			CheckBulletCollision();

			viewProjection_.target = player_.GetWorldTrans().translation_;

			//マウスでカメラを動かす処理
			const float length = 10.0f;
			viewProjection_.eye = player_.GetWorldTrans().translation_ + (-player_.centerVec.normalize() * length);

		}
		pause.Update();
	}
	viewProjection_.UpdateMatrix();

	if (true)
	{
		debugText_->SetPos(WinApp::kWindowWidth - 50, 50);
		debugText_->Printf("fps %f", fpsFix.fps);
	}

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

	if (title.IsTitle())
	{
		title.ModelDraw(titleView);
	}
	else
	{
		gManager.Draw(viewProjection_);
		iManager.Draw(viewProjection_);
		enemyEManager.Draw(viewProjection_);
		jEManager.Draw(viewProjection_);
		vEManager.Draw(viewProjection_);
		pObjectManager.Draw(viewProjection_);

		Goal.Draw(viewProjection_);

		player_.Draw(viewProjection_);

		bossManager.Draw(viewProjection_, player_.GetMouseVRota());
		enemyManager->Draw(viewProjection_);

		vpManager.Draw(viewProjection_);
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
	
	if (title.IsTitle() == false)
	{
		player_.SpriteDraw();
		bossManager.BossUIDraw();
		pause.MenuDraw();
	}

	if (title.IsTitle())
	{
		title.Draw();
	}

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::CheckBulletCollision()
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
				player_.OnDamage(1);
			}
		}
	}

	//地面と自分の弾の当たり判定
	for (const unique_ptr<BoxObj>& object : gManager.GetObjects())
	{
		posA = object->GetWorldTrans();
		for (const unique_ptr<PlayerBullet>& bullet : playerBullets)
		{
			posB = bullet->GetWorldTrans();

			if (BoxColAABB(posA, posB))
			{
				bullet->OnCollision();
			}
		}
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
			}
		}
	}

	//ボスと自分の弾の当たり判定
	for (const unique_ptr<PlayerBullet>& bullet : playerBullets)
	{
		posA = bullet->GetWorldTrans();
		for (const unique_ptr<Boss>& boss : bossManager.GetBossList())
		{
			posB = boss->GetBossPart(0).GetWorldTrans();
			if (BoxColAABB(posA, posB))
			{
				boss->OnBodyColision();
				bullet->OnCollision();
			}
			posB = boss->GetBossPart(1).GetWorldTrans();
			if (BoxColAABB(posA, posB))
			{
				boss->OnWeekColision();
				bullet->OnCollision();
			}
		}
	}
	//自分とボスの当たり判定
	for (const unique_ptr<Boss>& boss : bossManager.GetBossList())
	{
		posA = player_.GetWorldTrans();
		posB = boss->GetBossPart(0).GetWorldTrans();
		if (BoxColAABB(posA, posB))
		{
			player_.OnDamage(1);
		}
	}
}

void GameScene::CheckPlayerAllCollision()
{
	WorldTransform posA;
	WorldTransform posB;
	
	posA = player_.GetWorldTrans();
	
	for (const unique_ptr<BoxObj>& object : gManager.GetObjects())
	{
		posB = object->GetWorldTrans();
		player_.CheckHitBox(posB);
	}
	for (const unique_ptr<BoxObj>& object : gManager.GetEventObjects())
	{
		posB = object->GetWorldTrans();
		player_.CheckHitBox(posB);
	}
	for (const unique_ptr<BoxObj>& object : gManager.GetBossObjects())
	{
		posB = object->GetWorldTrans();
		player_.CheckHitBox(posB);
	}
	for (const unique_ptr<Item>& item : iManager.GetObjects())
	{
		posB = item->GetWorldTrans();
		if (BoxColAABB(posA, posB))
		{
			vpManager.CreateParticle(item->GetWorldTrans().translation_, { 2.0f ,2.0f ,2.0f }, 0.03f);
			player_.StockPlus();
			item->Erase();
		}
	}
	for (const unique_ptr<EventObject>& eventObj : enemyEManager.GetObjects())
	{
		posB = eventObj->GetWorldTrans();
		//ボックスに当たったらイベントを開始する
		if (BoxColAABB(posA, posB) && eventObj->IsEvent() == false)
		{
			enemyManager->EventStart(vpManager);
			gManager.EventStart(posA.translation_);
			eventObj->EventStart();
		}
		//イベント中なら敵が倒したかをカウントする
		if (eventObj->IsEvent())
		{
			eventObj->SetEventCount(enemyManager->GetEventCount());
		}
		//イベントが終了したら
		if (eventObj->GetEventCount() <= 0 && eventObj->IsEvent())
		{
			//パーティクルを発生
			vpManager.CreateParticle(eventObj->GetWorldTrans().translation_, { 3.0f ,3.0f ,3.0f }, 0.03f);
			for (const unique_ptr<BoxObj>& object : gManager.GetEventObjects())
			{
				vpManager.CreateParticle(object->GetWorldTrans().translation_, { 3.0f ,3.0f ,3.0f }, 0.03f);
			}

			//周りの壁を消す
			gManager.EventEnd();
			eventObj->Erase();
		}
	}

	for (const unique_ptr<EventObject>& eventObj : jEManager.GetObjects())
	{
		posB = eventObj->GetWorldTrans();
		if (BoxColAABB(posA, posB))
		{
			if (eventObj->IsEvent() == false)
			{
				player_.EnforceJumpOnCol();
				eventObj->EventStart();
			}
		}
		else
		{
			eventObj->EventEnd();
		}
	}
	for (const unique_ptr<EventObject>& eventObj : vEManager.GetObjects())
	{
		posB = eventObj->GetWorldTrans();

		if (player_.CheckHitBox(posB))
		{
			eventObj->EventStart();
		}

		if (eventObj->IsEvent())
		{
			eventObj->CountUp();
			//二秒たったら消す
			if (eventObj->GetEventCount() >= 120)
			{
				eventObj->NotCol();
				eventObj->EventEnd();
				vpManager.CreateParticle(eventObj->GetWorldTrans().translation_, { 3.0f ,3.0f ,3.0f }, 0.03f);
			}

			if (eventObj->GetEventCount() <= 60)
			{
				eventObj->Vibration(-0.1f, 0.1f);
			}
			else
			{
				eventObj->Vibration(-0.5f, 0.5f);
			}
		}
		else
		{
			eventObj->InitPos();
			if (eventObj->GetEventCount() > 0)
			{
				eventObj->CountDown();
			}
			if (eventObj->GetEventCount() <= 0)
			{
				eventObj->RemoveScale();
				
			}
		}

	}

	//ゴール時の処理
	//ゴールしたらボスエリアに移動
	posB = Goal.GetWorldTrans();
	if (BoxColAABB(posA, posB))
	{
		player_.EnforceGoalOnCol();
	}

	for (const unique_ptr<EventObject>& eventObj : enemyEManager.GetBossObjects())
	{
		posB = eventObj->GetWorldTrans();
		//ボス発生オブジェクトに衝突したら
		if (BoxColAABB(posA, posB))
		{
			Vector3 spawnPos = eventObj->GetWorldTrans().translation_;
			spawnPos.y += 10;
			bossManager.BossBattleStart();
			bossManager.SpawnBoss(spawnPos);
			eventObj->Erase();
			gManager.BossBattleStart();
		}
	}
}

void GameScene::CheckEnemyAllCollision()
{
	WorldTransform posA;
	WorldTransform posB;

	const list<unique_ptr<Enemy>>& enemys = enemyManager->enemys;

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
		if (BoxColAABB(posA, posB) && player_.IsDash())
		{
			enemy->OnCollision();
		}
	}

	for (const unique_ptr<Enemy>& enemy : enemys)
	{
		posA = enemy->GetWorldTrans();
		for (const unique_ptr<BoxObj>& object : gManager.GetObjects())
		{
			if (BoxColAABB(posA, posB))
			{
				enemy->CheckHitBox(posB);
			}
		}
	}
}
