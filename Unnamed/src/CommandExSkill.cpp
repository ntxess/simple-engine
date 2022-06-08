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

void CommandExSkill::Execute(entt::entity entity, entt::registry& registry)
{
	float currentTime = _timer.getElapsedTime().asSeconds();

	if (currentTime > _cooldownTime)
	{
		std::cout << "Using EX Skill\n";
		//auto view = registry->view<TagComponent>();
		//for (auto enemy : view)
		//{
		//	if (registry->get<TagComponent>(enemy).affiliation == TagComponent::AFFILIATION::Enemy)
		//	{
		//		registry->emplace<DestructionTagComponent>(enemy);
		//	}
		//}
		_timer.restart();
	}
}