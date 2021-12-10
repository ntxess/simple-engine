#pragma once
#include <iostream>
#include <vector>
#include "GameData.hpp"

#include "DebugScene.hpp"
#include "ResourceMonitor.hpp"
#include "Component.hpp"

typedef std::unique_ptr<Component> ComponentRef;

class MainMenu : public State
{
private:
    std::shared_ptr<GameData> _data;

public:
	ResourceMonitor _fps;
	std::vector<ComponentRef> _assets;
	
	ComponentRef _startButton;
	ComponentRef _quitButton;

	MainMenu(std::shared_ptr<GameData>& data);
	~MainMenu();
	void Init();
	void ProcessInput(sf::Event event);
	void Update(float deltaTime);
	void Render(RenderWindowRef& rw, float interpolation);
	void Pause();
	void Resume();
};