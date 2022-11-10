#include "PowerThrower.hpp"

PowerThrower::PowerThrower(std::shared_ptr<GameData>& data)
	: _data(data)
{}

PowerThrower::~PowerThrower()
{}

void PowerThrower::Init()
{
	std::cout << "<<Power Thrower>>" << std::endl;
}

void PowerThrower::ProcessEvent(const sf::Event& event)
{}

void PowerThrower::ProcessInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		_data->_machine->AddState(std::make_unique<MainMenu>(_data));
}

void PowerThrower::Update(const float& deltaTime)
{
}

void PowerThrower::Render(const std::unique_ptr<sf::RenderWindow>& rw, const float& deltaTime, const float& interpolation)
{
}

void PowerThrower::Pause()
{
}

void PowerThrower::Resume()
{
}

entt::registry& PowerThrower::GetRegistry()
{
	return _registry;
}
