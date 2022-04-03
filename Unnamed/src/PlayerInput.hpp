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
	enum class COMMAND
	{
		NONE,
		DODGE,
		EX_SKILL
	};

	sf::Vector2f _direction;
	COMMAND _command;

	//CommandRef _command;
	//CommandRef _KeyLShift;
	//CommandRef _KeyRShift;

public:
	PlayerInput();
	~PlayerInput();

	void ResetCommandBinds();
 	void Update(sf::Event event);
};

