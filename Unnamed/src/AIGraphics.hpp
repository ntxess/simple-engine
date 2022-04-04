#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <Thor/Animations.hpp>

#include "GraphicsComponent.hpp"
#include "GameObject.hpp"

class GameObject;

typedef std::unique_ptr<sf::RenderWindow> RenderWindowRef;

class AIGraphics : public GraphicsComponent
{
private:
	sf::Sprite _sprite;
	thor::Animator<sf::Sprite, std::string> _animator;

public:
	AIGraphics();
	AIGraphics(thor::ResourceHolder<sf::Texture, std::string>& holder, std::string ID);
	~AIGraphics();

	sf::Sprite& GetSprite();
	void Animator(const GameObject& object);
	void Render(const RenderWindowRef& rw, const float& deltaTime, const float& interpolation);
};

