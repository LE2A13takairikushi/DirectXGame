#include "ParticleObject.h"

void ParticleObject::Initialize(Model* model, Model* partModel, TextureHandle tex)
{
	//�I�u�W�F�N�g��(�`�悵�Ȃ�)
	object::LoadModel(model);
	object::LoadTexture(tex);
	worldTransform_.Initialize();
	
	pManager.Initialize(partModel, tex);
}

void ParticleObject::Update()
{
	pManager.Update(worldTransform_.translation_,{1.0f,1.0f,1.0f });
	MatUpdate();
}

void ParticleObject::Draw(ViewProjection view)
{
	pManager.Draw(view);
	//model_->Draw(worldTransform_,view,textureHandle_);
}
