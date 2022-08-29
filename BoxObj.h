#pragma once
#include "object.h"

class BoxObj : public object
{
public:
	void Initialize(Model* model_);
	void Update();
	void Draw(ViewProjection viewProjection,Vector3 shake = {0,0,0});

	bool GetCheckUpdate();

	void LoadTexture(TextureHandle tex);

private:
	bool isCheckPointUpdate = false;
	
};

