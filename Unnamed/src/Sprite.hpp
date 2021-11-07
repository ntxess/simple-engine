#pragma once
#include "GraphicsComponent.hpp"

typedef std::unique_ptr<sf::RenderWindow> RenderWindowRef;
typedef std::unique_ptr<thor::Animator<sf::Sprite, std::string>> AnimatorRef;

class Sprite : public GraphicsComponent
{
public:
	sf::Sprite _sprite;
	std::string _animationName;
	AnimatorRef _animator;

	Sprite();
	Sprite(thor::ResourceHolder<sf::Texture, std::string>& holder, std::string ID);
	~Sprite();
	sf::Sprite& GetSprite();
	AnimatorRef& GetAnimator();
	void SetScale(const sf::Vector2f scale);
	void SetPosition(const sf::Vector2f pos);
	void Move(sf::Vector2f direction, int velocity, float deltaTime);
	void Update(float deltaTime);
	void Update(sf::Vector2f direction, int velocity, float deltaTime);
	void Render(RenderWindowRef& rw, float interpolation);
};