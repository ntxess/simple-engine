#include "AIPhysics.hpp"

AIPhysics::AIPhysics()
	: _velocity(sf::Vector2f(0, 0))
{}

AIPhysics::~AIPhysics()
{}

void AIPhysics::Update(const GameObject& object, const float& deltaTime)
{
	sf::Vector2f direction = object.GetInput()->GetDirection();
	_velocity.x = direction.x * deltaTime * object.GetCurrentStats().SPD;
	_velocity.y = direction.y * deltaTime * object.GetCurrentStats().SPD;

	object.GetGraphics()->GetSprite().move(_velocity);
}
