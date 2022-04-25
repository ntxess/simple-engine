#pragma once
#include <iostream>
#include <random>
#include <entt/entt.hpp>

#include "GameData.hpp"
#include "ResourceMonitor.hpp"
#include "QuadTree.hpp"

#include "Component.hpp"

class Sandbox : public Scene
{
	static const unsigned int MAX_SIZE = 1000;

private:
	std::shared_ptr<GameData> _data;
	ResourceMonitor _fps;
	entt::registry _registry;

	sf::FloatRect _boundary;
	std::unique_ptr<QuadTree> _quadTree;

public:
	Sandbox(std::shared_ptr<GameData>& data);
	~Sandbox();

	void Init();
	void ProcessEvent(const sf::Event& event);
	void ProcessInput(const sf::Event& event);
	void Update(const float& deltaTime);
	void Render(const std::unique_ptr<sf::RenderWindow>& rw, const float& deltaTime, const float& interpolation);
	void Pause();
	void Resume();

	void CheckBoundary(sf::Sprite& object);
	sf::Vector2f TraverseWayPoint(WayPointComponent& wpc, const float& speed, const float& deltaTime);
};
