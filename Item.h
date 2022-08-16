#pragma once
#include "object.h"

class Item : public object
{
public:
	void Initialize(Model *model, TextureHandle tex);
	void Update();
	void Draw(ViewProjection view);
	
	bool IsDead() const { return isDead; };
	void Erase() { isDead = true; };
private:

	bool isDead = false;
};

