#pragma once
#include "GraphicsComponent.hpp"

typedef std::unique_ptr<sf::RenderWindow> RenderWindowRef;

class Sprite : public GraphicsComponent
{
public:
	sf::Sprite _sprite;
	bool _isAnimated;
	thor::Animator<sf::Sprite, std::string> _animator;

	Sprite();
	Sprite(thor::ResourceHolder<sf::Texture, std::string>& holder, std::string ID, bool _isAnimated = false);
	~Sprite();
	sf::Sprite& GetSprite();
	thor::Animator<sf::Sprite, std::string>& GetAnimator();
	void Move(sf::Vector2f direction, float velocity, float deltaTime);
	void Update(float deltaTime);
	void Update(sf::Vector2f direction, float velocity, float deltaTime);
	void Render(RenderWindowRef& rw, float interpolation);
};