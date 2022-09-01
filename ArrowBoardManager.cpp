#include "ArrowBoardManager.h"
#include "MathUtility.h"
using namespace std;

void ArrowBoardManager::Initialize(Model* model)
{
	this->model = model;
	tex = TextureManager::Load("arrow_nottrans.png");
	SetObjects();
}

void ArrowBoardManager::Update()
{
	for (unique_ptr<BoxObj>& object : objects)
	{
		object->Update();
	}
}

void ArrowBoardManager::Draw(ViewProjection view, float mouseVertRota)
{
	if (mouseVertRota > -0.2f)
	{
		for (unique_ptr<BoxObj>& object : objects)
		{
			object->Draw(view);
		}
	}
}

void ArrowBoardManager::SetObjects()
{
	CreateBoard({ 240,240,200 }, { 5,10,5 }, 1);
	CreateBoard({ 640, 340, 80 }, { 5,10,5 }, 0);
	CreateBoard({ 490,340,260 }, { 5,10,5 }, 0);

	CreateBoard({ 480,280,200 }, { 5,10,10 }, 3,1);
}

void ArrowBoardManager::CreateBoard(Vector3 pos, Vector3 scale, int velocity,int mode)
{
	unique_ptr<BoxObj> newBox = make_unique<BoxObj>();
	newBox->Initialize(model);
	newBox->LoadTexture(tex);
	switch (mode)
	{
	case 0:
		newBox->SetPos({ pos.x, pos.y + scale.y, pos.z });
		newBox->SetScale({ scale.x, 0.5f, scale.z });
		newBox->worldTransform_.rotation_.y += (MathUtility::PI / 2) * velocity;
		break;
	case 1:
		newBox->SetPos({ pos.x+ scale.x, pos.y , pos.z });
		newBox->SetScale({ 0.5f, scale.y, scale.z });
		newBox->worldTransform_.rotation_.x += (MathUtility::PI / 2) * velocity;
		break;
	case 2:
		newBox->SetPos({ pos.x, pos.y , pos.z + scale.z });
		newBox->SetScale({ scale.x, scale.y, 0.5f });
		newBox->worldTransform_.rotation_.z += (MathUtility::PI / 2) * velocity;
		break;
	default:
		newBox->SetPos({ pos.x, pos.y + scale.y, pos.z });
		newBox->SetScale({ scale.x, 1, scale.z });
		break;
	}

	objects.push_back(std::move(newBox));
}
