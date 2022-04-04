#pragma once
#include <SFML/Graphics.hpp>
#include <Thor/Animations.hpp>

#include "GraphicsComponent.hpp"
#include "GameObject.hpp"

typedef std::unique_ptr<sf::RenderWindow> RenderWindowRef;

class PlayerGraphics : public GraphicsComponent
{
private:
	sf::Sprite _sprite;
	thor::Animator<sf::Sprite, std::string> _animator;

public:
	PlayerGraphics();
	PlayerGraphics(thor::ResourceHolder<sf::Texture, std::string>& holder, std::string ID);
	~PlayerGraphics();

	sf::Sprite& GetSprite();
	void Animator(const GameObject& player);
	void Render(const RenderWindowRef& rw, const float& deltaTime, const float& interpolation);
};