#pragma once
#include "VanishParticle.h"
#include <list>
#include <memory>

class VanishParticleManager
{
public:
	void Initialize(Model* model, TextureHandle tex);
	void Update();
	void Draw(ViewProjection view);
	void CreateParticle(Vector3 beginPos, Vector3 initScale, float scaleSpd);

	const std::list<std::unique_ptr<VanishParticle>>& GetParticle() {
		return particles;
	};

private:
	static const int Max = 10;

	std::list<std::unique_ptr<VanishParticle>> particles;
	Model* model_ = nullptr;
	TextureHandle tex = 0;

};

