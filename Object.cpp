#include "Object.h"

//Object::Object()
//{
//	Initialize();
//}
//Object::~Object()
//{
//	delete model_;
//}
//
//void Object::Initialize()
//{
//	worldTransform_.Initialize();
//	this->model_ = Model::Create();;
//	this->textureHandle_ = TextureManager::Load("waito.jpg");
//}
//
//void Object::Initialize(Model* model_, TextureHandle textureHandle_)
//{
//	worldTransform_.Initialize();
//	this->model_ = model_;
//	this->textureHandle_ = textureHandle_;
//}
//
//void Object::Update()
//{
//	worldTransform_.UpdateMatrix();
//	worldTransform_.TransferMatrix();
//}
//
//void Object::Draw(ViewProjection viewProjection_)
//{
//	model_->Draw(worldTransform_, viewProjection_,textureHandle_);
//}
