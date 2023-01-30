#pragma once
#include <iostream>
#include <random>
#include <fstream>
#include <algorithm>
#include <sstream>

#include "SFML-imgui/imgui.h"
#include "SFML-imgui/imgui-SFML.h"
#include "MainMenu.hpp"
#include "GameData.hpp"
#include "Component.hpp"
#include "SystemHelper.hpp"

class GameOfLifeSim : public Scene
{
private:
	std::shared_ptr<GameData> _data;
	entt::registry _registry;

	std::vector<std::vector<int>> gridWorld;
	std::vector<std::vector<int>> buffer;
	bool drawMode = false;
	bool mouseHold = false;

	ImGuiWindowFlags _windowFlags;

public:
	GameOfLifeSim(std::shared_ptr<GameData>& data);
	~GameOfLifeSim();

	void Init();
	void ProcessEvent(const sf::Event& event);
	void ProcessInput();
	void Update(const float& deltaTime);
	void Render(const std::unique_ptr<sf::RenderWindow>& rw, const float& deltaTime, const float& interpolation);
	void Pause();
	void Resume();
	entt::registry& GetRegistry();

	void DrawOptions(const std::unique_ptr<sf::RenderWindow>& rw, const float& deltaTime);
	int GetNeighbors(std::vector<std::vector<int>>& board, int i, int j);
	void ReadFile(const std::string& fileName);

};
