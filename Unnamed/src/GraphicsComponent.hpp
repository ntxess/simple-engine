#pragma once
#include <string>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <Thor/Animations.hpp>

class GraphicsComponent
{
private:
	thor::Animator<sf::Sprite, std::string> _animator;

public:
	GraphicsComponent();
	~GraphicsComponent();
	void EventReceiver(sf::Vector2f direction);
	void Update(sf::Sprite& sprite, sf::Vector2f direction, float deltaTime);
};