#pragma once
#include <iostream>
#include <vector>

#include "GameData.hpp"
#include "DebugScene.hpp"
#include "ResourceMonitor.hpp"

class MainMenu : public State
{
private:
	std::shared_ptr<GameData> _data;

	ResourceMonitor _fps;
	//UIObjectRef _background;
	//UIObjectRef _startButton;
	//UIObjectRef _quitButton;

public:
	MainMenu(std::shared_ptr<GameData>& data);
	~MainMenu();

	void Init();
	void ProcessEvent(const sf::Event& event);
	void ProcessInput(const sf::Event& event);
	void Update(const float& deltaTime);
	void Render(const std::unique_ptr<sf::RenderWindow>& rw, const float& deltaTime, const float& interpolation);
	void Pause();
	void Resume();
};