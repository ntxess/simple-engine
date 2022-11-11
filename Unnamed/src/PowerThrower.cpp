#include "PowerThrower.hpp"

PowerThrower::PowerThrower(std::shared_ptr<GameData>& data)
	: _data(data)
{}

PowerThrower::~PowerThrower()
{}

void PowerThrower::Init()
{
	std::cout << "<<Power Thrower>>" << std::endl;

	//float width = float(_data->_window->getSize().x);
	//float height = float(_data->_window->getSize().y);
	//_data->_defaultView.setSize(width, height);
	//_data->_focusedView.setSize(width, height);
	//_data->_defaultView.setCenter(width / 2, height / 2);

	_projectile = _registry.create();
	_registry.emplace<PlayerTagComponent>(_projectile);
	_registry.emplace<MidLayerTagComponent>(_projectile);
	_registry.emplace<SpeedComponent>(_projectile, 500);
	_registry.emplace<AccelerationComponent>(_projectile);
	_registry.emplace<SpriteComponent>(_projectile, _data->_holder["TankBullet"]);
	//_registry.get<SpriteComponent>(_projectile).sprite.setPosition(205, 840);
	_registry.get<SpriteComponent>(_projectile).sprite.setPosition(700, 840);
	_registry.get<SpriteComponent>(_projectile).sprite.setScale({0.5f, 0.5f});


	{
		entt::entity tanktop = _registry.create();
		_registry.emplace<TopLayerTagComponent>(tanktop);
		_registry.emplace<SpriteComponent>(tanktop, _data->_holder["TankTop"]);
		_registry.get<SpriteComponent>(tanktop).sprite.setPosition(200, 800);
	
		entt::entity tankbot = _registry.create();
		_registry.emplace<TopLayerTagComponent>(tankbot);
		_registry.emplace<SpriteComponent>(tankbot, _data->_holder["TankBot"]);
		_registry.get<SpriteComponent>(tankbot).sprite.setPosition(205, 840);

		_cannon = _registry.create();
		_registry.emplace<TopLayerTagComponent>(_cannon);
		_registry.emplace<RotateTurretComponent>(_cannon, 100.f);
		_registry.emplace<SpriteComponent>(_cannon, _data->_holder["TankTurret"]);
		_registry.get<SpriteComponent>(_cannon).sprite.setPosition(300, 815);
		_registry.get<SpriteComponent>(_cannon).sprite.setOrigin(0, 0);

	}

	_performanceTracker = _registry.create();
	_registry.emplace<PerformanceMonitorComponent>(_performanceTracker);
}

void PowerThrower::ProcessEvent(const sf::Event& event)
{}

void PowerThrower::ProcessInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		_data->_machine->AddState(std::make_unique<MainMenu>(_data));

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		float rotation = _registry.get<SpriteComponent>(_cannon).sprite.getRotation();
		_registry.get<SpriteComponent>(_projectile).sprite.setRotation(rotation);
		_launch = true;
	}
}

void PowerThrower::Update(const float& deltaTime)
{
	if(!_launch)
		SystemHelper::RotateTurretUpdate(_registry, _cannon, deltaTime);
}

void PowerThrower::Render(const std::unique_ptr<sf::RenderWindow>& rw, const float& deltaTime, const float& interpolation)
{
	//_data->_window->setView(_data->_focusedView);

	auto midLayerSp = _registry.view<SpriteComponent, MidLayerTagComponent>();
	for (auto entity : midLayerSp)
		rw->draw(midLayerSp.get<SpriteComponent>(entity).sprite);

	auto topLayerSp = _registry.view<SpriteComponent, TopLayerTagComponent>();
	for (auto entity : topLayerSp)
		rw->draw(topLayerSp.get<SpriteComponent>(entity).sprite);

	SystemHelper::PerformanceMetricUpdate(_registry, _performanceTracker, rw);
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

void PowerThrower::GameReset()
{
	_launch = false;
}
