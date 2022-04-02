#include "Player.hpp"

Player::Player()
	: _input(std::make_unique<PlayerInput>())
	, _physics(std::make_unique<PlayerPhysics>())
	, _graphics(std::make_unique<PlayerGraphics>())
{
	_defaultStats.HP = 100.f;
	_defaultStats.SPD = 200.f;
	_defaultStats.ATTACK_SPEED = 1.f;

	ResetStats();
}

Player::Player(thor::ResourceHolder<sf::Texture, std::string>& holder, std::string ID)
	: _input(std::make_unique<PlayerInput>())
	, _physics(std::make_unique<PlayerPhysics>())
	, _graphics(std::make_unique<PlayerGraphics>())
{
	_defaultStats.HP = 100.f;
	_defaultStats.SPD = 500.f;
	_defaultStats.ATTACK_SPEED = 1.f;

	ResetStats();

	sf::Texture& texture = holder[ID];
	_graphics->_sprite.setTexture(texture);
	_graphics->_sprite.setScale(sf::Vector2f(2, 2));
	_graphics->_sprite.setPosition(sf::Vector2f(360, 900));
	std::cout << "TEXTURE LOADED: " << ID << std::endl;
}

Player::~Player() 
{}

PlayerInputRef& Player::GetInput()
{
	return _input;
}

PlayerPhysicsRef& Player::GetPhysics()
{
	return _physics;
}

PlayerGraphicsRef& Player::GetGraphics()
{
	return _graphics;
}

void Player::Rebound()
{
	_graphics->_sprite.setPosition(_physics->_previousPos);
}

void Player::ResetStats()
{
	_currentStats.HP = _defaultStats.HP;
	_currentStats.SPD = _defaultStats.SPD;
	_currentStats.ATTACK_SPEED = _defaultStats.ATTACK_SPEED;
}

void Player::AugmentHealth(float newHealth)
{
	_defaultStats.HP = newHealth;
}

void Player::AugmentSpeed(float newSpeed)
{
	_defaultStats.SPD = newSpeed;
}

void Player::AugmentAttackSpeed(float newAttackSpeed)
{
	_defaultStats.ATTACK_SPEED = newAttackSpeed;
}

void Player::InputUpdate(sf::Event event)
{
	_input->Update(event);
}

void Player::PhysicsUpdate(float deltaTime)
{
	_physics->Update(*this, deltaTime);
}

void Player::GraphicsUpdate(RenderWindowRef& rw, float deltaTime, float interpolation)
{
	_graphics->Animator(*this);
	_graphics->Render(rw, deltaTime, interpolation);
}
