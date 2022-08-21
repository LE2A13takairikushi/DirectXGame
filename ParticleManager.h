#pragma once
#include "Particle.h"
#include <list>
#include <memory>

class ParticleManager
{
public:
	ParticleManager();
	~ParticleManager();

	void Initialize(Model* model, TextureHandle tex);
	void Update(Vector3 beginPos);
	void Draw(ViewProjection view);

	void CreateParticle(Vector3 beginPos);

	const std::list<std::unique_ptr<Particle>>& GetParticle() {
		return particles; 
	};

	static const int LIMIT = 3;

private:
	std::list<std::unique_ptr<Particle>> particles;
	Model* model_ = nullptr;
	TextureHandle tex=0;
};