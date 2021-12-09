#pragma once
#include <iostream>
#include <vector>
#include "GameData.hpp"

#include "DebugScene.hpp"
#include "ResourceMonitor.hpp"
#include "GameObject.hpp"

typedef std::unique_ptr<Identity> IdentityRef;

class MainMenu : public State
{
private:
    std::shared_ptr<GameData> _data;

public:
	ResourceMonitor _fps;
	std::vector<IdentityRef> _assets;
	
	IdentityRef _startButton;
	IdentityRef _quitButton;

	MainMenu(std::shared_ptr<GameData>& data);
	~MainMenu();
	void Init();
	void ProcessInput();
	void Update(float deltaTime);
	void Render(RenderWindowRef& rw, float interpolation);
	void Pause();
	void Resume();
};