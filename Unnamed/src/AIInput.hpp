#pragma once

#include "InputComponent.hpp"

typedef std::shared_ptr<Command> CommandRef;

class AIInput : public InputComponent
{
private:
	sf::Vector2f _direction;

	CommandRef _command;
	bool _moveLeft;
	bool _moveRight;

public:
	AIInput();
	~AIInput();

	// JSON file parser that read data and apply AI movement
	const CommandRef& GetCommand() const;
	sf::Vector2f GetDirection() const;
	void Update(const sf::Event& event);
};

