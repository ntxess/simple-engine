#include "CommandExSkill.hpp"

CommandExSkill::CommandExSkill()
	: _cooldownTime(sf::seconds(5.f).asSeconds())
{}

CommandExSkill::~CommandExSkill()
{}

float CommandExSkill::GetTime() const
{
	return _timer.getElapsedTime().asSeconds();
}

float CommandExSkill::GetMaxTime() const
{
	return _cooldownTime;
}

void CommandExSkill::Execute(const PlayerObject& player)
{
	float currentTime = _timer.getElapsedTime().asSeconds();

	if (currentTime > _cooldownTime)
	{
		std::cout << "USING EX SKILL" << std::endl;
		_timer.restart();
	}
}

void CommandExSkill::Execute(entt::entity entity, entt::registry* registry)
{
	float currentTime = _timer.getElapsedTime().asSeconds();

	if (currentTime > _cooldownTime)
	{
		std::cout << "USING EX SKILL" << std::endl;
		_timer.restart();
	}
}