#pragma once
#include <iostream>
#include <random>

#include "SFML-imgui/imgui.h"
#include "SFML-imgui/imgui-SFML.h"
#include "GameData.hpp"
#include "QuadTree.hpp"
#include "Component.hpp"
#include "Event.hpp"
#include "EventDispatcher.hpp"
#include "EventHandler.hpp"
#include "SystemHelper.hpp"

class Sandbox : public Scene
{
	friend class Entity;
	static const size_t MAX_SIZE = 10;

private:
	std::shared_ptr<GameData> _data;

	std::unique_ptr<QuadTree> _quadTree;

	entt::registry _registry;
	entt::entity _background;
	entt::entity _player;
	entt::entity _dummy;
	entt::entity _progressionBorder;
	entt::entity _progressionBar;
	entt::entity _performanceTracker;

	std::unique_ptr<EventDispatcher> _dispatcher;

public:
	Sandbox(std::shared_ptr<GameData>& data);
	~Sandbox();

	void Init();
	void ProcessEvent(const sf::Event& event);
	void ProcessInput();
	void Update(const float& deltaTime);
	void Render(const std::unique_ptr<sf::RenderWindow>& rw, const float& deltaTime, const float& interpolation);
	void Pause();
	void Resume();
	entt::registry& GetRegistry();

	void RenderLayer(const std::unique_ptr<sf::RenderWindow>& rw);
	void ProgressBarUpdate(const float& deltaTime);
};
