#pragma once
#include <string>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <Thor/Animations.hpp>
#include "InputComponent.hpp"

class GraphicsComponent
{
private:
	InputComponent _input;
	sf::Sprite _sprite;
	thor::Animator<sf::Sprite, std::string> _animator;

public:
	GraphicsComponent();
	~GraphicsComponent();
	void EventReceiver(sf::Vector2f direction);
	void Update(sf::Sprite& sprite, sf::Vector2f direction, float deltaTime);
};