#pragma once
#include <iostream>
#include <vector>

#include "GameData.hpp"

class MainMenu : public Scene
{
	friend class Entity;

private:
	std::shared_ptr<GameData> _data;
	entt::registry _registry;

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
	entt::registry& GetRegistry();
};