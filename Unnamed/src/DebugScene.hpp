#pragma once
#include <iostream>
#include <vector>
#include <chrono>
#include <random>

#include "GameData.hpp"
#include "ResourceMonitor.hpp"
#include "MainMenu.hpp"
#include "PlayerObject.hpp"
#include "UEnemyObject.hpp"
#include "EnemyObject.hpp"
#include "ObjectPool.hpp"
#include "ShotParticle.hpp"

class DebugScene : public State
{
private:
	std::shared_ptr<GameData> _data;

	ResourceMonitor _fps;
	std::unique_ptr<PlayerObject> _player;
	std::unique_ptr<UEnemyObject> _uEnemy;

	ObjectPool<ShotParticle> weaponPool;
	ObjectPool<EnemyObject> enemyPool;

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