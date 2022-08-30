#pragma once
#include "BoxObj.h"
#include <memory>
#include <list>

class ArrowBoardManager
{
public:
	void Initialize(Model* model);
	void Update();
	void Draw(ViewProjection view, float mouseVertRota);

	std::list<std::unique_ptr<BoxObj>>& GetObjects() {
		return objects;
	};

private:
	void SetObjects();
	void CreateBoard(Vector3 pos,Vector3 scale,int velocity = 0, int mode = 0);

	std::list<std::unique_ptr<BoxObj>> objects;
	Model* model = nullptr;
	TextureHandle tex = 0;
};

