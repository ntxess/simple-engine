#pragma once
#include <iostream>
#include <random>

#include "SFML-imgui/imgui.h"
#include "SFML-imgui/imgui-SFML.h"
#include "MainMenu.hpp"
#include "GameData.hpp"
#include "Component.hpp"
#include "SystemHelper.hpp"

class PowerThrower : public Scene
{
private:
	std::shared_ptr<GameData> _data;

	entt::registry _registry;
	entt::entity _projectile;
	entt::entity _cannon;
	entt::entity _performanceTracker;

	bool _launch;

public:
	PowerThrower(std::shared_ptr<GameData>& data);
	~PowerThrower();

	void Init();
	void ProcessEvent(const sf::Event& event);
	void ProcessInput();
	void Update(const float& deltaTime);
	void Render(const std::unique_ptr<sf::RenderWindow>& rw, const float& deltaTime, const float& interpolation);
	void Pause();
	void Resume();
	entt::registry& GetRegistry();

	void GameReset();
};

