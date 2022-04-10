#pragma once
#include <iostream>
#include <vector>

#include "GameData.hpp"
#include "MainMenu.hpp"
#include "ResourceMonitor.hpp"
#include "GameObject.hpp"
#include "ShotParticle.hpp"
#include "ParticlePool.hpp"
#include "Particle.hpp"
#include "PlayerInput.hpp"
#include "PlayerPhysics.hpp"
#include "PlayerGraphics.hpp"
#include "AIInput.hpp"
#include "AIPhysics.hpp"
#include "AIGraphics.hpp"

class DebugScene : public State
{
private:
	std::shared_ptr<GameData> _data;

public:
	ResourceMonitor _fps;
	std::unique_ptr<GameObject> _player;
	std::unique_ptr<GameObject> _playerDup;
	std::unique_ptr<ParticlePool<Particle>> _particlePool;
	//GameObjectRef _background;
	//std::unique_ptr<GameObjectPool<Particle>> _particlePool;

	//PhysicsComponent* _physicsComponent = new PhysicsComponent[MAX_ENTITIES];
	//std::vector<PhysicsComponent> _physicsComponent;
	//std::vector<GraphicsComponent> _graphicsComponent;

	//std::vector<GameObjectRef> _assets;

	DebugScene(std::shared_ptr<GameData>& data);
	~DebugScene();
	void Init();
	void ProcessEvent(const sf::Event& event);
	void ProcessInput(const sf::Event& event);
	void Update(const float& deltaTime);
	void Render(const std::unique_ptr<sf::RenderWindow>& rw, const float& deltaTime, const float& interpolation);
	void CheckBoundary(const std::unique_ptr<GameObject>& object);
	bool CheckCollision(const std::unique_ptr<GameObject>& player, const std::unique_ptr<GameObject>& object);
	void SpawnShotParticle();
	void Pause();
	void Resume();
};