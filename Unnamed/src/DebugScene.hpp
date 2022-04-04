#pragma once
#include <iostream>
#include <vector>

#include "GameData.hpp"
#include "MainMenu.hpp"
#include "ResourceMonitor.hpp"
#include "GameObject.hpp"
#include "ShotParticle.hpp"
#include "GameObjectPool.hpp"
#include "Particle.hpp"
#include "PlayerInput.hpp"
#include "PlayerPhysics.hpp"
#include "PlayerGraphics.hpp"
#include "AIInput.hpp"
#include "AIPhysics.hpp"
#include "AIGraphics.hpp"

typedef std::unique_ptr<GameObject> GameObjectRef;
typedef std::shared_ptr<InputComponent> InputComponentRef;
typedef std::shared_ptr<PhysicsComponent> PhysicsComponentRef;
typedef std::shared_ptr<GraphicsComponent> GraphicsComponentRef;

class DebugScene : public State
{
private:
	//static const uint16_t MAX_ENTITIES = 100000;
	std::shared_ptr<GameData> _data;

public:
	ResourceMonitor _fps;
	GameObjectRef _player;
	GameObjectRef _playerDup;

	//GameObjectRef _background;
	//std::unique_ptr<GameObjectPool<Particle>> _particlePool;

	//PhysicsComponent* _physicsComponent = new PhysicsComponent[MAX_ENTITIES];
	//std::vector<PhysicsComponent> _physicsComponent;
	//std::vector<GraphicsComponent> _graphicsComponent;

	//std::vector<GameObjectRef> _assets;

	DebugScene(std::shared_ptr<GameData> &data);
	~DebugScene();
	void Init();
	void ProcessEvent(const sf::Event& event);
	void ProcessInput(const sf::Event& event);
	void Update(const float& deltaTime);
	void Render(const RenderWindowRef& rw, const float& deltaTime, const float& interpolation);
	void CheckBoundary(const GameObjectRef& object);
	bool CheckCollision(const GameObjectRef& player, const GameObjectRef& object);
	void SpawnShotParticle();
	void Pause();
	void Resume();
};