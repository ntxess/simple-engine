#pragma once
#include <iostream>
#include <vector>

#include "GameData.hpp"
#include "DebugScene.hpp"
#include "ResourceMonitor.hpp"
#include "GameObject.hpp"

typedef std::unique_ptr<GameObject> GameObjectRef;

class MainMenu : public State
{
private:
    std::shared_ptr<GameData> _data;

public:
	ResourceMonitor _fps;
	std::vector<GameObjectRef> _assets;
	
	GameObjectRef _startButton;
	GameObjectRef _quitButton;

	MainMenu(std::shared_ptr<GameData>& data);
	~MainMenu();
	void Init();
	void ProcessEvent(const sf::Event& event);
	void ProcessInput(const sf::Event& event);
	void Update(const float& deltaTime);
	void Render(const RenderWindowRef& rw, const float& deltaTime, const float& interpolation);
	void Pause();
	void Resume();
};