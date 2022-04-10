#include "PlayerPhysics.hpp"

PlayerPhysics::PlayerPhysics()
{}

PlayerPhysics::~PlayerPhysics()
{}

sf::Vector2f PlayerPhysics::GetVelocity() const
{
	return _velocity;
}

void PlayerPhysics::Update(const GameObject& object, const float& deltaTime)
{
	// Execute any events triggered by the keys defined inside PlayerInput.Update()
	std::shared_ptr<Command> command = object.GetInput()->GetCommand();
	if (command)
		command->Execute(object);

	// Calculate distance to travel as offset
	sf::Vector2f direction = object.GetInput()->GetDirection();
	_velocity.x = direction.x * deltaTime * object.GetCurrentStats().SPD;
	_velocity.y = direction.y * deltaTime * object.GetCurrentStats().SPD;

	object.GetGraphics()->GetSprite().move(_velocity);
}
