#pragma once
#include <iostream>
#include <vector>

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
#include "AIInput.hpp"
#include "WayPoint.hpp"
#include "CircleMov.hpp"

class DebugScene : public State
{
private:
	std::shared_ptr<GameData> _data;

	ResourceMonitor _fps;
	std::unique_ptr<PlayerObject> _player;
	std::unique_ptr<EnemyObject> _enemy;
	//std::unique_ptr<ParticlePool<Particle>> _particlePool;

public:
	DebugScene(std::shared_ptr<GameData>& data);
	~DebugScene();

	void Init();
	void ProcessEvent(const sf::Event& event);
	void ProcessInput(const sf::Event& event);
	void Update(const float& deltaTime);
	void Render(const std::unique_ptr<sf::RenderWindow>& rw, const float& deltaTime, const float& interpolation);
	void CheckBoundary(const std::unique_ptr<PlayerObject>& object);
	bool CheckCollision(const std::unique_ptr<GameObject>& player, const std::unique_ptr<GameObject>& object);
	void SpawnShotParticle();
	void Pause();
	void Resume();
};