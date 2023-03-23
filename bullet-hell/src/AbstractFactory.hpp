#pragma once
#include "../GameData.hpp"
#include "../Entity.hpp"
#include "../Component.hpp"
#include <memory>

enum class TYPE
{
	PLAYER,
	ENEMY,
	FRIENDLY,
	BACKGROUND,
	OBJECT,
	ELEMENTS,
};

class AbstractFactory
{
public:
	virtual ~AbstractFactory() = default;
	virtual std::unique_ptr<Entity>	CreateEntity(TYPE type, sf::Texture& texture) const = 0;
};

