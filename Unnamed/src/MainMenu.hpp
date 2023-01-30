#pragma once
#include <iostream>
#include <vector>

#include "SFML-imgui/imgui.h"
#include "SFML-imgui/imgui-SFML.h"
#include "Sandbox.hpp"
#include "PowerThrower.hpp"
#include "Sudoku.hpp"
#include "GameOfLifeSim.hpp"
#include "GameData.hpp"
#include "SystemHelper.hpp"


class MainMenu : public Scene
{
private:
	std::shared_ptr<GameData> _data;
	entt::registry _registry;

	ImGuiWindowFlags _windowFlags;
	entt::entity _performanceTracker;

public:
	MainMenu(std::shared_ptr<GameData>& data);
	~MainMenu();

	void Init();
	void ProcessEvent(const sf::Event& event);
	void ProcessInput();
	void Update(const float& deltaTime);
	void Render(const std::unique_ptr<sf::RenderWindow>& rw, const float& deltaTime, const float& interpolation);
	void Pause();
	void Resume();
	entt::registry& GetRegistry();
};