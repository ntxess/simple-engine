#pragma once

#include <SFML/Graphics.hpp>
#include "GraphicsComponent.hpp"
#include "Animation.hpp"

class Sprite : public GraphicsComponent
{
private:
	sf::Texture  _texture;
	std::string  _type;

public:
	sf::Sprite   _sprite;
	sf::Vector2f _posC;
	sf::Vector2f _posN;
	Animation* _animation;

	Sprite();
	~Sprite();
	virtual void Init() = 0;
	void SetScale(const sf::Vector2f scale);
	void SetPosition(const sf::Vector2f pos);
	void Update();
	void Render(sf::RenderTarget* rt, double interpolation);
};