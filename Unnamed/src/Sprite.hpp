#pragma once
#include <Thor/Resources.hpp>
#include "GraphicsComponent.hpp"
#include "Animation.hpp"

typedef std::unique_ptr<sf::RenderWindow> RenderWindowRef;

class Sprite : public GraphicsComponent
{
public:
	sf::Sprite _sprite;
	std::unique_ptr<Animation> _animation;
	
	Sprite();
	Sprite(thor::ResourceHolder<sf::Texture, std::string>& holder, std::string ID);
	~Sprite();
	sf::Sprite GetSprite() const;
	void SetScale(const sf::Vector2f scale);
	void SetPosition(const sf::Vector2f pos);
	void Move(sf::Vector2f direction, int velocity, float deltaTime);
	void Update(sf::Vector2f direction, int velocity, float deltaTime);
	void Render(RenderWindowRef& rw, float interpolation);
};