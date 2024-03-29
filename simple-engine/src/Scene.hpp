#pragma once
#include "SFML/Graphics/RenderWindow.hpp"
#include "entt/entt.hpp"

class Scene
{
public:
	virtual void Init() = 0;
	virtual void ProcessEvent(const sf::Event& event) = 0;
	virtual void ProcessInput() = 0;
	virtual void Update(const float& deltaTime) = 0;
	virtual void Render(sf::RenderWindow& rw, const float& deltaTime, const float& interpolation) = 0;
	virtual void Pause() = 0;
	virtual void Resume() = 0;
	virtual entt::registry& GetRegistry() = 0;
};