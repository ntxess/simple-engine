#include "Sandbox.hpp"

Sandbox::Sandbox(std::shared_ptr<GameData>& data)
	: _data(data)
{}

Sandbox::~Sandbox()
{}

void Sandbox::Init()
{
	std::cout << "<<Sandbox>>" << std::endl;

	float width = float(_data->_window->getSize().x);
	float height = float(_data->_window->getSize().y);
	_data->_defaultView.setSize(width, height);
	_data->_focusedView.setSize(width, height);
	_data->_defaultView.setCenter(width / 2, height / 2);

	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 1920);

	for (size_t i = 0; i < MAX_SIZE; i++)
	{
		entt::entity entity = _registry.create();
		_registry.emplace<EnemyTagComponent>(entity);
		_registry.emplace<InteractableTagComponent>(entity);
		_registry.emplace<MidLayerTagComponent>(entity);
		_registry.emplace<HealthComponent>(entity, 100.f);
		_registry.emplace<SpeedComponent>(entity, float(dist6(rng) % 500));
		_registry.emplace<WayPointComponent>(entity, _data->_pathMap.at("mRandom").get(), true);
		_registry.emplace<SpriteComponent>(entity, _data->_holder["Ship"]);
		_registry.get<SpriteComponent>(entity).sprite.setPosition(float(dist6(rng)), float(dist6(rng) % 1080));
	}

	for (size_t i = 0; i < MAX_SIZE; i++)
	{
		entt::entity entity = _registry.create();
		_registry.emplace<EnemyTagComponent>(entity);
		_registry.emplace<InteractableTagComponent>(entity);
		_registry.emplace<MidLayerTagComponent>(entity);
		_registry.emplace<HealthComponent>(entity, 100.f);
		_registry.emplace<SpeedComponent>(entity, float(dist6(rng) % 400));
		_registry.emplace<AttractionComponent>(entity, true);
		_registry.emplace<SpriteComponent>(entity, _data->_holder["Ship"]);
		_registry.get<SpriteComponent>(entity).sprite.setPosition(float(dist6(rng)), float(dist6(rng) % 1080));
	}

	_player = _registry.create();
	_registry.emplace<PlayerTagComponent>(_player);
	_registry.emplace<InteractableTagComponent>(_player);
	_registry.emplace<MidLayerTagComponent>(_player);
	_registry.emplace<HealthComponent>(_player, 1000.f);
	_registry.emplace<SpeedComponent>(_player, 500.f);
	_registry.emplace<PlayerInputComponent>(_player, 
		std::make_shared<CommandDodge>(), 
		std::make_shared<CommandExSkill>(), 
		std::make_shared<CommandBasic>());
	_registry.emplace<SpriteComponent>(_player, _data->_holder["ShipAlt"]);
	_registry.get<SpriteComponent>(_player).sprite.setPosition(960, 1000);

	_dummy = _registry.create();
	_registry.emplace<EnemyTagComponent>(_dummy);
	_registry.emplace<InteractableTagComponent>(_dummy);
	_registry.emplace<MidLayerTagComponent>(_dummy);
	_registry.emplace<HealthComponent>(_dummy, 1000.f);
	_registry.emplace<SpeedComponent>(_dummy, 300.f);
	_registry.emplace<AttractionComponent>(_dummy, 500.f);
	_registry.emplace<SpriteComponent>(_dummy, _data->_holder["Ship"]);
	_registry.get<SpriteComponent>(_dummy).sprite.setPosition(960, 400);
	_registry.get<SpriteComponent>(_dummy).sprite.setScale(sf::Vector2f(5.f, 5.f));

	_progressionBorder = _registry.create();
	_registry.emplace<InterfaceTagComponent>(_progressionBorder);
	_registry.emplace<TopLayerTagComponent>(_progressionBorder);
	_registry.emplace<SpriteComponent>(_progressionBorder, _data->_holder["progressbarborder01"]);
	auto& pborder = _registry.get<SpriteComponent>(_progressionBorder).sprite;
	pborder.setOrigin(0, 0);
	pborder.setPosition(50, 1000);

	_progressionBar = _registry.create();
	_registry.emplace<InterfaceTagComponent>(_progressionBar);
	_registry.emplace<TopLayerTagComponent>(_progressionBar);
	_registry.emplace<SpriteComponent>(_progressionBar, _data->_holder["progressbar01"]);
	auto& pbar = _registry.get<SpriteComponent>(_progressionBar).sprite;
	pbar.setOrigin(0, 0);
	pbar.setPosition(52, 1002);

	_background = _registry.create();
	_registry.emplace<BotLayerTagComponent>(_background);
	_registry.emplace<BackgroundComponent>(_background, _data->_holder["Prototype"], sf::IntRect(0, 0, _data->_window->getSize().x, _data->_window->getSize().y));

	_performanceTracker = _registry.create();
	_registry.emplace<PerformanceMonitorComponent>(_performanceTracker);

	sf::FloatRect rect(0.f, 0.f, float(_data->_window->getSize().x), float(_data->_window->getSize().y));
	_quadTree = std::make_unique<QuadTree>(rect);


	_windowFlags = 0;
	_windowFlags |= ImGuiWindowFlags_NoMove;
	_windowFlags |= ImGuiWindowFlags_NoResize;
	_windowFlags |= ImGuiWindowFlags_NoTitleBar;
	_windowFlags |= ImGuiWindowFlags_NoBackground;

	ImGui::SFML::Init(*_data->_window);
}

void Sandbox::ProcessEvent(const sf::Event& event)
{
	// Useful for determining what keypresses will do when in different scenes
	ImGui::SFML::ProcessEvent(*_data->_window, event);
}

void Sandbox::ProcessInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		_data->_machine->AddState(std::make_unique<MainMenu>(_data));

	auto& controller = _registry.get<PlayerInputComponent>(_player);

	const float input = 1.f;
	controller.direction = sf::Vector2f(0, 0);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		controller.direction.y -= input;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		controller.direction.x -= input;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		controller.direction.y += input;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		controller.direction.x += input;

	Command* command = NULL;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
		command = controller.attack.get();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		command = controller.dodge.get();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
		command = controller.exSkill.get();

	if (command)
		command->Execute(_registry, _player, _data);
}

void Sandbox::Update(const float& deltaTime)
{
	SystemHelper::InputMovementUpdate(_registry, _player, deltaTime);

	auto enemyView = _registry.view<EnemyTagComponent>();
	for (auto entity : enemyView)
		SystemHelper::CheckBoundary(_data->_window->getSize(), _registry.get<SpriteComponent>(entity).sprite);

	SystemHelper::CheckBoundary(_data->_window->getSize(), _registry.get<SpriteComponent>(_player).sprite);
	SystemHelper::FocusCameraOn(_data->_focusedView, _registry.get<SpriteComponent>(_player).sprite);
	SystemHelper::MobWaypointUpdate(_registry, deltaTime);
	SystemHelper::MobTrackingUpdate(_registry, _player, deltaTime);

	// Quadtree drawn with player focus
	//sf::Vector2f vwCenter = _data->_focusedView.getCenter();
	//sf::Vector2f rwSize = sf::Vector2f(_data->_window->getSize());
	//_quadTree = std::move(SystemHelper::QuadTreeUpdate(_registry, vwCenter, rwSize));

	// Quadtree draw with screen focus
	sf::Vector2f vwCenter = _data->_defaultView.getCenter();
	sf::Vector2f rwSize = sf::Vector2f(_data->_window->getSize());
	_quadTree = std::move(SystemHelper::QuadTreeUpdate(_registry, vwCenter, rwSize));

	SystemHelper::CollisionUpdate(_registry, _quadTree);
	SystemHelper::CheckDestruction(_registry);

	ProgressBarUpdate(deltaTime);
}

void Sandbox::Render(const std::unique_ptr<sf::RenderWindow>& rw, const float& deltaTime, const float& interpolation)
{
	RenderLayer(rw);

	{
		ImGui::SFML::Update(*_data->_window, sf::seconds(deltaTime));
		ImGui::SetNextWindowPos(ImVec2(0, 0));
		ImGui::SetWindowSize({ 10, 20 });
		ImGui::Begin("Demo", NULL, _windowFlags);
		ImGui::Checkbox("Toggle QuadTree Visualizer", &_quadTreeDemo);
		ImGui::Checkbox("Toggle HitBox Visualizer", &_hitBoxDemo);
		ImGui::End();
		ImGui::SFML::Render(*_data->_window);
		
		if (_quadTreeDemo)
			_quadTree->Render(_data->_window);

		if (_hitBoxDemo)
		{
			auto midLayerSp = _registry.view<SpriteComponent, MidLayerTagComponent>();
			for (auto entity : midLayerSp)
			{
				auto targetHitbox = midLayerSp.get<SpriteComponent>(entity).sprite.getGlobalBounds();
				sf::RectangleShape box;
				box.setPosition(midLayerSp.get<SpriteComponent>(entity).sprite.getPosition());
				box.setSize({ targetHitbox.width, targetHitbox.height });
				box.setOutlineThickness(1.0f);
				box.setFillColor(sf::Color::Transparent);
				box.setOutlineColor(sf::Color(0, 150, 100));
				rw->draw(box);
			}
		}
	}

	SystemHelper::PerformanceMetricUpdate(_registry, _performanceTracker, rw);
}

void Sandbox::Pause()
{}

void Sandbox::Resume()
{}

entt::registry& Sandbox::GetRegistry()
{
	return _registry;
}

void Sandbox::RenderLayer(const std::unique_ptr<sf::RenderWindow>& rw)
{
	rw->draw(_registry.get<BackgroundComponent>(_background).sprite);

	//_data->_window->setView(_data->_focusedView);

	auto botLayerSp = _registry.view<SpriteComponent, BotLayerTagComponent>();
	for (auto entity : botLayerSp)
		rw->draw(botLayerSp.get<SpriteComponent>(entity).sprite);

	auto botLayerTx = _registry.view<TextComponent, BotLayerTagComponent>();
	for (auto entity : botLayerTx)
		rw->draw(botLayerTx.get<TextComponent>(entity).text);

	auto midLayerSp = _registry.view<SpriteComponent, MidLayerTagComponent>();
	for (auto entity : midLayerSp)
		rw->draw(midLayerSp.get<SpriteComponent>(entity).sprite);

	auto midLayerTx = _registry.view<TextComponent, MidLayerTagComponent>();
	for (auto entity : midLayerTx)
		rw->draw(midLayerTx.get<TextComponent>(entity).text);

	_data->_window->setView(_data->_defaultView);

	auto topLayerSp = _registry.view<SpriteComponent, TopLayerTagComponent>();
	for (auto entity : topLayerSp)
		rw->draw(topLayerSp.get<SpriteComponent>(entity).sprite);

	auto topLayerTx = _registry.view<TextComponent, TopLayerTagComponent>();
	for (auto entity : topLayerTx)
		rw->draw(topLayerTx.get<TextComponent>(entity).text);
}

void Sandbox::ProgressBarUpdate(const float& deltaTime)
{
	auto skill = _registry.get<PlayerInputComponent>(_player).dodge;
	auto& progressBar = _registry.get<SpriteComponent>(_progressionBar);

	float progress = skill->GetTime() / skill->GetMaxTime();
	progressBar.sprite.setScale(std::clamp(progress, 0.f, 1.f), 1.f);
}
