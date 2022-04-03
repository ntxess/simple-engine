#pragma once
#include <SFML/Graphics.hpp>

#include "CommandDodge.hpp"
#include "CommandEXSkill.hpp"

typedef std::shared_ptr<Command> CommandRef;

class PlayerInput
{
	friend class PlayerPhysics;
	friend class PlayerGraphics;

private:
	sf::Vector2f _direction;

	CommandRef _command;
	CommandRef _KeyLShift;
	CommandRef _KeyRShift;

public:
	PlayerInput();
	~PlayerInput();

	sf::Vector2f GetDirection() const;
	void ResetCommandBinds();
 	void Update(const sf::Event& event);
};

