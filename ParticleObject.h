#pragma once
#include "EventObject.h"
#include "ParticleManager.h"

class ParticleObject : public EventObject
{
public:
	void Initialize(Model* model, Model* partModel, TextureHandle tex);
	void Update();
	void Draw(ViewProjection view);
private:
	ParticleManager pManager;
};