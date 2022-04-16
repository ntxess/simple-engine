#pragma once
#include <iostream>
#include <vector>
#include <chrono>
#include <random>

#include "GameData.hpp"
#include "MainMenu.hpp"
#include "ResourceMonitor.hpp"
#include "EnemyObject.hpp"
#include "PlayerObject.hpp"
#include "ShotParticle.hpp"
#include "ParticlePool.hpp"
#include "Particle.hpp"
#include "PlayerInput.hpp"
#include "PlayerPhysics.hpp"
#include "PlayerGraphics.hpp"
#include "WayPoint.hpp"
#include "MCircle.hpp"
#include "MRandom.hpp"

class DebugScene : public State
{
private:
	static const int SIZE = 50; // Upper limit - 15000@60fps
	std::shared_ptr<GameData> _data;

	ResourceMonitor _fps;
	std::unique_ptr<PlayerObject> _player;
	std::unique_ptr<EnemyObject> _enemy;
	std::unique_ptr<EnemyObject> _enemy2;

	EnemyObject enemies[SIZE];
	std::unique_ptr<EnemyObject> enemiesPtr[SIZE];
	//std::unique_ptr<ParticlePool<Particle>> _particlePool;

public:
	DebugScene(std::shared_ptr<GameData>& data);
	~DebugScene();

	void Init();
	void ProcessEvent(const sf::Event& event);
	void ProcessInput(const sf::Event& event);
	void Update(const float& deltaTime);
	void Render(const std::unique_ptr<sf::RenderWindow>& rw, const float& deltaTime, const float& interpolation);
	void CheckBoundary(sf::Sprite& object);
	void CheckCollision(sf::Sprite& player, sf::Sprite& object);
	void Pause();
	void Resume();
};