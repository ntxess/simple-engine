#pragma once
#include <iostream>
#include <random>

#include "GameData.hpp"
#include "ResourceMonitor.hpp"
#include "QuadTree.hpp"
#include "ObjectPool.hpp"

#include "Component.hpp"
#include "ShotParticle.hpp"

class Sandbox : public Scene
{
	friend class Entity;
	static const unsigned int MAX_SIZE = 10;

private:
	std::shared_ptr<GameData> _data;
	entt::registry _registry;

	ResourceMonitor _fps;

	sf::FloatRect _boundary;
	std::unique_ptr<QuadTree> _quadTree;

	entt::entity _player;
	entt::entity _dummy;

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

	void CheckBoundary(sf::Sprite& object);
	void PlayerUpdate(const float& deltaTime);
	void WayPointUpdate(const float& deltaTime);
	void QuadTreeUpdate();
	void RenderEntities(const std::unique_ptr<sf::RenderWindow>& rw);
};
