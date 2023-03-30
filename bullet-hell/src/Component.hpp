#pragma once
#include "Waypoint.hpp"
#include "SFML/System/Clock.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "Thor/Animations/Animator.hpp"
#include "entt/entt.hpp"
#include <iostream>
//#include "CommandDodge.hpp"
//#include "CommandExSkill.hpp"
//#include "CommandBasic.hpp"

enum class TEAM
{
	PLAYER,
	ENEMY,
	NEUTRAL
};

struct Sprite
{
	sf::Sprite sprite;

	Sprite() = default;
	Sprite(sf::Texture& texture)
	{
		sprite.setTexture(texture);
	}
	Sprite(sf::Texture& texture, int width, int height, bool repeat)
	{
		texture.setRepeated(repeat);
		sprite.setTexture(texture);
		sprite.setTextureRect(sf::IntRect(0, 0, width, height));
	}
	Sprite(const Sprite&) = default;
};

struct Animator
{
	thor::Animator<sf::Sprite, std::string> animator;

	Animator() = default;
	Animator(thor::Animator<sf::Sprite, std::string> animations)
		: animator(animations) {}
	Animator(const Animator&) = default;
};

struct PlayerInput
{
	sf::Vector2f direction;
	//std::shared_ptr<Command> dodge;
	//std::shared_ptr<Command> exSkill;
	//std::shared_ptr<Command> attack;

	PlayerInput() = default;
	//PlayerInput(std::shared_ptr<Command> dodge, std::shared_ptr<Command> exSkill, std::shared_ptr<Command> attack)
	//	: dodge(dodge), exSkill(exSkill), attack(attack) {}
	PlayerInput(const PlayerInput&) = default;
};

struct MovementPattern
{
	Waypoint* movePattern;
	Waypoint* currentPath;
	float distance;
	bool repeat;

	MovementPattern() = default;
	MovementPattern(Waypoint* wp, const bool& repeat = false)
		: movePattern(&*wp), currentPath(&*wp), distance(0.0f), repeat(repeat) {}
	MovementPattern(const MovementPattern&) = default;
};

struct Health
{
	float max;
	float current;

	Health() = default;
	Health(const float& health)
		: max(health), current(health) {}
	Health(const Health&) = default;
	float IncreaseHealth(float increaseUnit)
	{
		current += increaseUnit;
		if (current > max)
			current = max;
		return current;
	}
	float DecreaseHealth(float decreaseUnit)
	{
		current -= decreaseUnit;
		if (current < 0.f)
			current = 0.f;
		return current;
	}
};

struct Speed
{
	float max;
	float current;

	Speed() = default;
	Speed(const float& speed)
		: max(speed), current(speed) {}
	Speed(const Speed&) = default;
};

struct Acceleration
{
	float current = 1.f;

	Acceleration() = default;
	Acceleration(const Acceleration&) = default;
	void Accelerate(float increaseUnit)
	{
		current += increaseUnit;
		if (current > 1.f)
			current = 1.f;
	}
	void Decelerate(float decreaseUnit)
	{
		current -= decreaseUnit;
		if (current < 0.f)
			current = 0.f;
	}
};

struct Attack
{
	float damage;

	Attack() = default;
	Attack(const float& damage)
		: damage(damage) {}
	Attack(const Attack&) = default;
};

struct Attraction
{
	union Power
	{
		bool fullStrength;
		float level;
	};

	Power power;

	Attraction() = default;
	Attraction(const float& strength)
	{
		power.level = strength;
	}
	Attraction(const bool& fullStrength)
	{
		power.fullStrength = fullStrength;
	}
	Attraction(const Attraction&) = default;
};

struct Text
{
	sf::Text text;
	sf::Font font;

	Text() = default;
	Text(const std::string& pathToFont)
	{
		if (!font.loadFromFile(pathToFont))
		{
			std::cout << "FAILURE TO LOAD FONT TYPE!" << std::endl;
			exit(-1);
		}
		text.setFont(font);
		text.setCharacterSize(20);
		text.setFillColor(sf::Color::White);
		text.setPosition(sf::Vector2f(10.f, 5.f));
	}
	Text(const Text&) = default;
};

struct Clock
{
	sf::Clock clock;

	Clock() = default;
	Clock(const Clock&) = default;
};

struct PerformanceMonitor
{
	sf::RenderWindow* rw;
	sf::Clock clock;
	float value;

	PerformanceMonitor() = default;
	PerformanceMonitor(sf::RenderWindow* renderWindow)
		: rw(renderWindow), value(0.f) {}
	PerformanceMonitor(const PerformanceMonitor&) = default;
};

struct TopLayerTag
{
	TopLayerTag() = default;
	TopLayerTag(const TopLayerTag&) = default;
};

struct MidLayerTag
{
	MidLayerTag() = default;
	MidLayerTag(const MidLayerTag&) = default;
};

struct BotLayerTag
{
	BotLayerTag() = default;
	BotLayerTag(const BotLayerTag&) = default;
};

struct Hitbox
{
	sf::FloatRect hitbox;
	Hitbox() = default;
	Hitbox(const sf::FloatRect& hitbox)
		: hitbox(hitbox) {}
	Hitbox(const Hitbox&) = default;
};

struct CollidedTag
{
	entt::entity collider;
	CollidedTag() = default;
	CollidedTag(const entt::entity& ent)
		: collider(ent) {}
	CollidedTag(const CollidedTag&) = default;
};

struct DestroyTag
{
	DestroyTag() = default;
	DestroyTag(const DestroyTag&) = default;
};

struct TeamTag
{
	TEAM tag;
	TeamTag() = default;
	TeamTag(TEAM teamtag)
		: tag(teamtag) {}
	TeamTag(const TeamTag&) = default;
};

