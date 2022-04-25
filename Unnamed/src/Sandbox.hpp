#pragma once
#include <iostream>
#include <random>

#include "GameData.hpp"
#include "ResourceMonitor.hpp"
#include "QuadTree.hpp"
#include "ObjectPool.hpp"

#include "Entity.hpp"
#include "Component.hpp"
#include "ShotParticle.hpp"

class Sandbox : public Scene
{
	friend class Entity;
	static const unsigned int MAX_SIZE = 5000;

private:
	std::shared_ptr<GameData> _data;
	entt::registry _registry;

	ResourceMonitor _fps;

	sf::FloatRect _boundary;
	std::unique_ptr<QuadTree> _quadTree;

	Entity _player;

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
	entt::registry& GetRegistry();

	Entity CreateEntity(const std::string& name);
	void CheckBoundary(sf::Sprite& object);
	sf::Vector2f TraverseWayPoint(WayPointComponent& wpc, const float& speed, const float& deltaTime);
	void TransformEntity(const float& deltaTime);
};
