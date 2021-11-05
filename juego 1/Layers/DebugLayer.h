#pragma once

#include "Layer.h"

#include "Physics/Quadtree.h"
#include "Entities/Entity.h"
#include <vector>


// layer created to test the quadtree
class DebugLayer : public Layer
{
public:
	DebugLayer();
	~DebugLayer();

	virtual void Init()            override;
	virtual void Draw()            override;
	virtual void Update()          override;
	virtual void ProcessControls() override;
private:

	SDL_Rect r = { 100, 100, 500, 200 };


	std::list<Entity*> ents;
	std::list<Entity*> qEnts;
	QuadTree<Entity>* qt;

	int entsNum = 200;
};

