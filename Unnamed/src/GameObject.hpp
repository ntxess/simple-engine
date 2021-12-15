#pragma once
#include <SFML/Graphics.hpp>
#include <Thor/Resources.hpp>
#include "InputComponent.hpp"
#include "PhysicsComponent.hpp"
#include "GraphicsComponent.hpp"

typedef std::unique_ptr<sf::RenderWindow> RenderWindowRef;
typedef std::unique_ptr<InputComponent> InputComponentRef;
typedef std::unique_ptr<PhysicsComponent> PhysicsComponentRef;
typedef std::unique_ptr<GraphicsComponent> GraphicsComponentRef;

class GameObject
{
public:
	InputComponentRef _input;
	PhysicsComponentRef _physics;
	GraphicsComponentRef _graphics;
	sf::Sprite _sprite;
	float _velocity;
	bool _isTouched;

	GameObject();
	GameObject(thor::ResourceHolder<sf::Texture, std::string>& holder, std::string ID);
	~GameObject();
	InputComponentRef& GetInput();
	PhysicsComponentRef& GetPhysics();
	GraphicsComponentRef& GetGraphics();
	bool IsTouched();
	const sf::Sprite& GetSprite();
	const sf::Vector2f& GetPosition();
	void SetInput(InputComponentRef& input);
	void SetPhysics(PhysicsComponentRef& physics);
	void SetGraphics(GraphicsComponentRef& graphics);
	void SetVelocity(float velocity);
	void SetTouchTag(bool isTouched);
	void SetScale(sf::Vector2f scale);
	void SetPosition(sf::Vector2f position);
	void SetOrigin(sf::Vector2f position);
	void Update(float deltaTime);
	void Render(RenderWindowRef& rw, float interpolation);
}; 