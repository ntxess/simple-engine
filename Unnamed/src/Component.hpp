#pragma once
#include <iostream>
#include <string>
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "Thor/Animations.hpp"
//#include "WayPoint.hpp"
//#include "CommandDodge.hpp"
//#include "CommandExSkill.hpp"
//#include "CommandBasic.hpp"

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

struct AnimatedSprite
{
	sf::Sprite sprite;
	thor::Animator<sf::Sprite, std::string> animator;

	AnimatedSprite() = default;
	AnimatedSprite(sf::Texture& texture)
	{
		sprite.setTexture(texture);
	}
	AnimatedSprite(const AnimatedSprite&) = default;
	void Update(sf::Time dt)
	{
		animator.update(dt);
	}
	void Animate()
	{
		animator.animate(sprite);
	}
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

struct Health
{
	float max;
	float current;

	Health() = default;
	Health(const float& health)
		: max(health), current(health) {}
	Health(const Health&) = default;
	void IncreaseHealth(float increaseUnit)
	{
		current += increaseUnit;
		if (current > max)
			current = max;
	}
	void DecreaseHealth(float decreaseUnit)
	{
		current -= decreaseUnit;
		if (current < 0.f)
			current = 0.f;
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

//struct WayPoint
//{
//	WayPoint* movePattern;
//	WayPoint* currentPath;
//	float distance;
//	bool repeat;
//
//	WayPoint() = default;
//	WayPoint(WayPoint* wp, const bool& repeat = false)
//		: movePattern(&*wp), currentPath(&*wp), distance(0.0f), repeat(repeat) {}
//	WayPoint(const WayPoint&) = default;
//};
//
//struct PlayerInput
//{
//	sf::Vector2f direction;
//	std::shared_ptr<Command> dodge;
//	std::shared_ptr<Command> exSkill;
//	std::shared_ptr<Command> attack;
//
//	PlayerInput() = default;
//	PlayerInput(std::shared_ptr<Command> dodge, std::shared_ptr<Command> exSkill, std::shared_ptr<Command> attack)
//		: dodge(dodge), exSkill(exSkill), attack(attack) {}
//	PlayerInput(const PlayerInput&) = default;
//};

struct Clock
{
	sf::Clock clock;

	Clock() = default;
	Clock(const Clock&) = default;
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

struct PlayerTag
{
	PlayerTag() = default;
	PlayerTag(const PlayerTag&) = default;
};

struct AllyTag
{
	AllyTag() = default;
	AllyTag(const AllyTag&) = default;
};

struct EnemyTag
{
	EnemyTag() = default;
	EnemyTag(const EnemyTag&) = default;
};

struct NeutralTag
{
	NeutralTag() = default;
	NeutralTag(const NeutralTag&) = default;
};

struct InteractableTag
{
	InteractableTag() = default;
	InteractableTag(const InteractableTag&) = default;
};

struct ParticleTag
{
	ParticleTag() = default;
	ParticleTag(const ParticleTag&) = default;
};

struct InterfaceTag
{
	InterfaceTag() = default;
	InterfaceTag(const InterfaceTag&) = default;
};

struct GravityTag
{
	bool gravityOn;

	GravityTag()
		: gravityOn(false) {}
	GravityTag(const GravityTag&) = default;
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

struct PerformanceMonitor
{
	sf::Clock clock;
	float value;

	PerformanceMonitor() = default;
	PerformanceMonitor(const PerformanceMonitor&) = default;
};

struct RotateTurret
{
	float degree;
	float speed;
	int flip;
	
	RotateTurret() : degree(275.f), speed(1.f), flip(true) {};
	RotateTurret(const float& speed) : degree(275.f), speed(speed), flip(true) {};
	RotateTurret(const RotateTurret&) = default;
};