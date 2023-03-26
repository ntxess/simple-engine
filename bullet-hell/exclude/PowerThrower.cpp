#include "PowerThrower.hpp"

PowerThrower::PowerThrower(std::shared_ptr<GameData>& data)
	: _data(data)
{}

PowerThrower::~PowerThrower()
{}

void PowerThrower::Init()
{
	std::cout << "<<Power Thrower>>" << std::endl;

	float width = float(_data->window->getSize().x);
	float height = float(_data->window->getSize().y);
	_data->_defaultView.setSize(width, height);
	_data->_focusedView.setSize(width, height);
	_data->_defaultView.setCenter(width / 2, height / 2);
	_data->window->setView(_data->_defaultView);


	{ // tank initialization
		entt::entity tanktop = _registry.create();
		_registry.emplace<TopLayerTagComponent>(tanktop);
		_registry.emplace<SpriteComponent>(tanktop, _data->resourceManager["TankTop"]);
		_registry.get<SpriteComponent>(tanktop).sprite.setPosition(200 % int(width), 800 % int(height));

		entt::entity tankbot = _registry.create();
		_registry.emplace<TopLayerTagComponent>(tankbot);
		_registry.emplace<SpriteComponent>(tankbot, _data->resourceManager["TankBot"]);
		_registry.get<SpriteComponent>(tankbot).sprite.setPosition(195 % int(width), 840 % int(height));

		_cannon = _registry.create();
		_registry.emplace<TopLayerTagComponent>(_cannon);
		_registry.emplace<RotateTurretComponent>(_cannon, 100.f);
		_registry.emplace<SpriteComponent>(_cannon, _data->resourceManager["TankTurret"]);
		_registry.get<SpriteComponent>(_cannon).sprite.setPosition(220 % int(width), 770 % int(height));
		_registry.get<SpriteComponent>(_cannon).sprite.setOrigin(0, 0);
	}

	{ // background initialization
		_currentBg = _registry.create();
		_registry.emplace<BotLayerTagComponent>(_currentBg);
		_registry.emplace<SpriteComponent>(_currentBg);
		_registry.emplace<BackgroundComponent>(_currentBg, _data->resourceManager["Prototype"], sf::IntRect(0, 0, width, height));
		_registry.get<BackgroundComponent>(_currentBg).sprite.setPosition(0, 0);


		_nextBg = _registry.create();
		_registry.emplace<BotLayerTagComponent>(_nextBg);
		_registry.emplace<SpriteComponent>(_nextBg);
		_registry.emplace<BackgroundComponent>(_nextBg, _data->resourceManager["Prototype"], sf::IntRect(0, 0, width, height));
		_registry.get<BackgroundComponent>(_nextBg).sprite.setPosition(width, 0);
	}

	_performanceTracker = _registry.create();
	_registry.emplace<PerformanceMonitorComponent>(_performanceTracker);

	windowFlags = 0;
	windowFlags |= ImGuiWindowFlags_NoMove;
	windowFlags |= ImGuiWindowFlags_NoResize;
	windowFlags |= ImGuiWindowFlags_NoTitleBar;
	windowFlags |= ImGuiWindowFlags_NoBackground;

	ImGui::SFML::Init(*_data->window);
}

void PowerThrower::ProcessEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Escape)
			_data->sceneManager->AddScene(std::make_unique<MainMenu>(_data), true);

		if (event.key.code == sf::Keyboard::Space)
		{
			if (!_launch)
			{
				_projectile = _registry.create();
				_registry.emplace<PlayerTagComponent>(_projectile);
				_registry.emplace<MidLayerTagComponent>(_projectile);
				_registry.emplace<SpeedComponent>(_projectile, 500);
				_registry.emplace<AccelerationComponent>(_projectile);
				_registry.emplace<SpriteComponent>(_projectile, _data->resourceManager["TankBullet"]);
				_registry.get<SpriteComponent>(_projectile).sprite
					.setPosition(200 % int(_data->window->getSize().x), 840 % int(_data->window->getSize().x));
				_registry.get<SpriteComponent>(_projectile).sprite.setScale({ 0.5f, 0.5f });

				float rotation = _registry.get<SpriteComponent>(_cannon).sprite.getRotation();
				_registry.get<SpriteComponent>(_projectile).sprite.setRotation(rotation);
				_launch = true;
			}
		}
	}
}

void PowerThrower::ProcessInput()
{}

void PowerThrower::Update(const float& deltaTime)
{
	if (!_launch)
	{
		SystemHelper::RotateTurretUpdate(_registry, _cannon, deltaTime);
	}
	else
	{
		_pastPosition = _registry.get<SpriteComponent>(_projectile).sprite.getPosition().x;
		SystemHelper::FocusCameraOn(_data->_focusedView, _registry.get<SpriteComponent>(_projectile).sprite);
		SystemHelper::VelocityUpdate(_registry, _projectile, deltaTime);
		SystemHelper::GravityUpdate(_registry, _projectile, deltaTime);
		GetDistanceTraveled();

		auto accel = _registry.get<AccelerationComponent>(_projectile).current;
		if (accel <= 0.f)
			GameReset();
	}
}

void PowerThrower::Render(const std::unique_ptr<sf::RenderWindow>& rw, const float& deltaTime, const float& interpolation)
{
	if (_launch)
		_data->window->setView(_data->_focusedView);
	else
		_data->window->setView(_data->_defaultView);

	auto bgLayerSp = _registry.view<BackgroundComponent, BotLayerTagComponent>();
	for (auto entity : bgLayerSp)
		rw->draw(bgLayerSp.get<BackgroundComponent>(entity).sprite);

	auto midLayerSp = _registry.view<SpriteComponent, MidLayerTagComponent>();
	for (auto entity : midLayerSp)
		rw->draw(midLayerSp.get<SpriteComponent>(entity).sprite);

	auto topLayerSp = _registry.view<SpriteComponent, TopLayerTagComponent>();
	for (auto entity : topLayerSp)
		rw->draw(topLayerSp.get<SpriteComponent>(entity).sprite);

	ImGui::SFML::Update(*_data->window, sf::seconds(deltaTime));
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetWindowSize({ 10, 50 });
	ImGui::Begin("Demo", NULL, windowFlags);
	ImGui::SetWindowFontScale(4.f);
	ImGui::Text("DISTANCE: %f", _distanceTraveled);
	ImGui::End();
	ImGui::SFML::Render(*_data->window);

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
	_registry.destroy(_projectile);
	_launch = false;
	_distanceTraveled = 0;
}

void PowerThrower::GetDistanceTraveled()
{
	auto sprite = _registry.get<SpriteComponent>(_projectile).sprite;
	float currentPosition = sprite.getPosition().x;
	_distanceTraveled += currentPosition - _pastPosition;
	_pastPosition = currentPosition;
}
