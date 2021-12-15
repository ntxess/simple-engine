#include "Player.hpp"

Player::Player(thor::ResourceHolder<sf::Texture, std::string>& holder, std::string ID)
	: _MAX_HEALTH(1000)
	, _attackDamage(10)
	, _health(_MAX_HEALTH)
	, _isShooting(false)
{
	_component = std::make_unique<GameObject>(holder, "Ship");
	InputComponentRef controller = std::make_unique<InputComponent>();
	PhysicsComponentRef rb = std::make_unique<PhysicsComponent>();
	GraphicsComponentRef animation = std::make_unique<ShipAnimation>();
	_component->SetInput(controller);
	_component->SetPhysics(rb);
	_component->SetGraphics(animation);
	_component->SetVelocity(600.f);
	_component->SetScale(sf::Vector2f(2, 2));
	_component->SetPosition(sf::Vector2f(360, 900));
}

GameObjectRef& Player::GetComponent()
{
	return _component;
}

bool Player::IsAlive() const
{
	return _health > 0 ? true : false;
}

float Player::GetAttackDamage() const
{
	return _attackDamage;
}

void Player::TakeDamage(float damage)
{
	if (_health > 0.f)
		_health -= damage;
}

void Player::Heal(float healAmount)
{
	_health += healAmount;
	if (_MAX_HEALTH > _health)
		_health = _MAX_HEALTH;
}

void Player::Shoot(bool isShooting)
{
	_isShooting = isShooting;
}

void Player::Update(float deltaTime)
{
	_component->Update(deltaTime);
}

void Player::Render(RenderWindowRef& rw, float interpolation)
{
	_component->Render(rw, interpolation);
}
