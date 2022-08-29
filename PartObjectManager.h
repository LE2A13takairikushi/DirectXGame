#pragma once
#include "ParticleObject.h"

class PartObjectManager
{
public:
	void Initialize(Vector3 stagePos, Vector3 stageScale, Model* model_, TextureHandle tex = 0);
	void Update();
	void Draw(ViewProjection viewProjection_);

	void CreateEventBox(Vector3 pos, Vector3 scale);

	const std::list <std::unique_ptr<ParticleObject>>& GetObjects() {
		return Objects;
	};
private:
	std::list <std::unique_ptr<ParticleObject>> Objects;

	Model* model_ = nullptr;
	TextureHandle tex = 0;
};

