#pragma once

#include "InputComponent.hpp"

class AIInput : public InputComponent
{
private:
	sf::Vector2f _direction;

	std::shared_ptr<Command> _command;
	bool _moveLeft;
	bool _moveRight;

public:
	AIInput();
	~AIInput();

	// JSON file parser that read data and apply AI movement
	const std::shared_ptr<Command>& GetCommand() const;
	sf::Vector2f GetDirection() const;
	void Update(const sf::Event& event);
};

