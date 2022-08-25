#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include "Utill.h"
#include "ViewProjection.h"

class object
{
public:
	object();
	~object();

	WorldTransform GetWorldTrans();
	void LoadModel(Model* model_);
	void LoadTexture(TextureHandle textureHandle_);

	void SetPos(Vector3 pos);
	void SetScale(Vector3 scale);

	Vector3 GetPos() { return worldTransform_.translation_; };
	Vector3 GetScale() { return worldTransform_.scale_; };

	void MatUpdate();

	WorldTransform worldTransform_;

protected:

	Model* model_ = nullptr;
	TextureHandle textureHandle_;

	Vector3 initScale = { 0,0,0 };
	Vector3 initPos = { 0,0,0 };
};

