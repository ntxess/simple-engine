#pragma once
#include <iostream>
#include <random>

#include "GameData.hpp"
#include "QuadTree.hpp"
#include "Component.hpp"

class Sandbox : public Scene
{
	friend class Entity;
	static const size_t MAX_SIZE = 10000;

private:
	std::shared_ptr<GameData> _data;

	sf::FloatRect _boundary;
	std::unique_ptr<QuadTree> _quadTree;

	entt::registry _registry;
	entt::entity _background;
	entt::entity _player;
	entt::entity _dummy;
	entt::entity _progressionBorder;
	entt::entity _progressionBar;
	entt::entity _fpsTracker;

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

	void CheckBoundary(sf::Sprite& object);
	void PlayerUpdate(const float& deltaTime);
	void WayPointUpdate(const float& deltaTime);
	void QuadTreeUpdate();
	void CollisionUpdate();
	void DamageUpdate(entt::entity inflictor, entt::entity afflicted);
	void CheckDestruction();
	void RenderLayer(const std::unique_ptr<sf::RenderWindow>& rw);
	void ProgressBarUpdate(const float& deltaTime);
	void TrackingUpdate(const float& deltaTime);
	void FrameAnalyticsUpdate();
};
