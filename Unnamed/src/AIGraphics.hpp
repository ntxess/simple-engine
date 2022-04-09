#pragma once
#include <SFML/Graphics.hpp>
#include <Thor/Resources.hpp>
#include <Thor/Animations.hpp>

#include "GraphicsComponent.hpp"
#include "GameObject.hpp"

typedef std::unique_ptr<sf::RenderWindow> RenderWindowRef;

class AIGraphics : public GraphicsComponent
{
private:
	sf::Sprite _sprite;

public:
	AIGraphics();
	AIGraphics(thor::ResourceHolder<sf::Texture, std::string>& holder, const std::string& ID);
	~AIGraphics();

	sf::Sprite& GetSprite();
	void Animator(const GameObject& object);
	void Render(const RenderWindowRef& rw, const float& interpolation);
};

