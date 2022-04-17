#pragma once
#include "Layer.h"
#include "Entities/Entity.h"
class EndLayer :  public Layer
{
public:
	EndLayer();
	~EndLayer();

	virtual void Init()            override;
	virtual void Draw()            override;
	virtual void Update()          override {};
	virtual void ProcessControls(SDL_Event event) override;

	bool controlContinue;

private:
	void keysToControls(SDL_Event event);
	void gamePadToControls(SDL_Event event);

	SDL_GameController* controller = nullptr;
	Entity background;
};

