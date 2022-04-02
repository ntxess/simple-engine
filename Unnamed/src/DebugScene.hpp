#pragma once
#include <iostream>
#include <vector>

#include "GameData.hpp"
#include "MainMenu.hpp"
#include "ResourceMonitor.hpp"
#include "GameObject.hpp"
#include "Player.hpp"
#include "ShotParticle.hpp"
#include "GameObjectPool.hpp"
#include "Particle.hpp"

typedef std::unique_ptr<GameObject> GameObjectRef;
typedef std::unique_ptr<Player> PlayerRef;


class DebugScene : public State
{
private:
	//static const uint16_t MAX_ENTITIES = 100000;
	std::shared_ptr<GameData> _data;

public:
	ResourceMonitor _fps;
	PlayerRef _player;
	GameObjectRef _background;
	std::unique_ptr<GameObjectPool<Particle>> _particlePool;

	//PhysicsComponent* _physicsComponent = new PhysicsComponent[MAX_ENTITIES];
	//std::vector<PhysicsComponent> _physicsComponent;
	//std::vector<GraphicsComponent> _graphicsComponent;

	std::vector<GameObjectRef> _assets;

	DebugScene(std::shared_ptr<GameData> &data);
	~DebugScene();
	void Init();
	void ProcessEvent(sf::Event event);
	void ProcessInput(sf::Event event);
	void Update(float deltaTime);
	void Render(RenderWindowRef& rw, float deltaTime, float interpolation);
	void CheckBoundary(PlayerRef& object);
	bool CheckCollision(GameObjectRef& player, GameObjectRef& object);
	void SpawnShotParticle();
	void Pause();
	void Resume();
};