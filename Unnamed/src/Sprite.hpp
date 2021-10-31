#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "GraphicsComponent.hpp"
#include "Animation.hpp"

typedef std::unique_ptr<sf::RenderWindow> RenderWindowRef;

class Sprite : public GraphicsComponent
{
public:
	sf::Texture _texture;
	sf::Sprite _sprite;
	std::unique_ptr<Animation> _animation;

	Sprite();
	Sprite(std::string location);
	~Sprite();
	sf::Sprite GetSprite() const;
	void SetScale(const sf::Vector2f scale);
	void SetPosition(const sf::Vector2f pos);
	void Update(float deltaTime);
	void Render(RenderWindowRef& rw, float interpolation);
};