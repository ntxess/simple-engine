#include "Sandbox.hpp"

Sandbox::Sandbox(std::shared_ptr<GameData>& data)
	:_data(data)
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
	_boundary = sf::FloatRect(0.f, 0.f, width, height);
	_quadTree = std::make_unique<QuadTree>(_boundary);
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
	_registry.emplace<SpriteComponent>(_player, _data->_holder["Ship"]);
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
	_registry.emplace<SpriteComponent>(_background, _data->_holder["Prototype"]);

	_fpsTracker = _registry.create();
	_registry.emplace<ClockComponent>(_fpsTracker);
	_registry.emplace<DataComponent<float>>(_fpsTracker);
}

void Sandbox::ProcessEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{

	}
}

void Sandbox::ProcessInput()
{
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
	PlayerUpdate(deltaTime);
	WayPointUpdate(deltaTime);
	TrackingUpdate(deltaTime);
	ProgressBarUpdate(deltaTime);
	QuadTreeUpdate();
	CollisionUpdate();
	CheckDestruction();
}

void Sandbox::Render(const std::unique_ptr<sf::RenderWindow>& rw, const float& deltaTime, const float& interpolation)
{
	RenderLayer(rw);
	FrameAnalyticsUpdate();
}

void Sandbox::Pause()
{}

void Sandbox::Resume()
{}

entt::registry& Sandbox::GetRegistry()
{
	return _registry;
}

void Sandbox::CheckBoundary(sf::Sprite& object)
{
	sf::Vector2f position = object.getPosition();
	sf::FloatRect rect = object.getGlobalBounds();
	sf::Vector2u bounds = _data->_window->getSize();

	if (position.x < 0)
		object.setPosition(sf::Vector2f(0.f, position.y));

	if (position.x + rect.width > bounds.x)
		object.setPosition(sf::Vector2f(bounds.x - rect.width, position.y));

	position = object.getPosition();

	if (position.y < 0)
		object.setPosition(sf::Vector2f(position.x, 0.f));

	if (position.y + rect.height > bounds.y)
		object.setPosition(sf::Vector2f(position.x, bounds.y - rect.height));
}

void Sandbox::PlayerUpdate(const float& deltaTime)
{
	auto controller = _registry.get<PlayerInputComponent>(_player);
	auto& player = _registry.get<SpriteComponent>(_player).sprite;
	auto speed = _registry.get<SpeedComponent>(_player).current;

	sf::Vector2f direction = controller.direction;

	float length = sqrt((direction.x * direction.x) + (direction.y * direction.y));

	if (length != 0.f)
	{
		direction.x = direction.x / length;
		direction.y = direction.y / length;
	}

	direction *= speed * deltaTime;

	player.move(direction);
	//CheckBoundary(player);
	_data->_focusedView.setCenter(player.getPosition());
}

void Sandbox::WayPointUpdate(const float& deltaTime)
{
	auto group = _registry.group<WayPointComponent, SpeedComponent>(entt::get<SpriteComponent>);
	for (auto entity : group)
	{
		auto [wpc, spd, sp] = group.get<WayPointComponent, SpeedComponent, SpriteComponent>(entity);

		WayPoint* headPtr = wpc.currentPath;
		WayPoint* nextPtr = headPtr->_nextWP.get();

		if (nextPtr == nullptr)
		{
			if (wpc.repeat)
			{
				wpc.currentPath = wpc.movePattern;
				wpc.distance = 0.f;
			}
			continue;
		}

		wpc.distance += spd.current * deltaTime;
		if (wpc.distance > nextPtr->_distanceTotal)
			wpc.currentPath = nextPtr;

		sf::Vector2f unitDist;
		unitDist.x = (nextPtr->_location.x - headPtr->_location.x) / headPtr->_distanceToNext;
		unitDist.y = (nextPtr->_location.y - headPtr->_location.y) / headPtr->_distanceToNext;

		sf::Vector2f velocity;
		velocity.x = unitDist.x * spd.current * deltaTime;
		velocity.y = unitDist.y * spd.current * deltaTime;

		sp.sprite.move(velocity);
	}
}

void Sandbox::QuadTreeUpdate()
{	
	float left = _data->_focusedView.getCenter().x - (float(_data->_window->getSize().x) / 2);
	float top = _data->_focusedView.getCenter().y - (float(_data->_window->getSize().y) / 2);
	float width = float(_data->_window->getSize().x);
	float height = float(_data->_window->getSize().y);

	_boundary = sf::FloatRect(left, top, width, height);
	_quadTree = std::make_unique<QuadTree>(_boundary);

	auto view = _registry.view<HealthComponent>();

	for (auto entity : view)
	{
		if (_registry.all_of<EnemyTagComponent>(entity))
			_quadTree->Insert(entity, _registry);
	}
}

void Sandbox::CollisionUpdate()
{
	auto view = _registry.view<DamageComponent>();
	for (auto inflictor : view)
	{
		auto& inflictorSp = _registry.get<SpriteComponent>(inflictor);
		sf::FloatRect range = inflictorSp.sprite.getGlobalBounds();
		std::vector<entt::entity> found = _quadTree->QueryRange(range, _registry);

		for (auto inflicted : found)
		{
			auto& inflictedSp = _registry.get<SpriteComponent>(inflicted);
			if(inflictorSp.sprite.getGlobalBounds().intersects(inflictedSp.sprite.getGlobalBounds()))
			{
				DamageUpdate(inflictor, inflicted);
			}
		}
	}
}

void Sandbox::DamageUpdate(entt::entity inflictor, entt::entity inflicted)
{
	if (!_registry.valid(inflictor) || !_registry.valid(inflicted)) 
		return;

	auto dmg = _registry.get<DamageComponent>(inflictor);
	auto& hp = _registry.get<HealthComponent>(inflicted);
	hp.current -= dmg.damage;
	_registry.destroy(inflictor);
}

void Sandbox::CheckDestruction()
{
	auto viewHp = _registry.view<HealthComponent>();
	for (auto entity : viewHp)
	{
		auto health = _registry.get<HealthComponent>(entity);
		if (health.current <= 0.f)
		{
			_registry.destroy(entity);
		}
	}

	auto viewWp = _registry.view<WayPointComponent>();
	for (auto entity : viewWp)
	{
		auto wp = _registry.get<WayPointComponent>(entity);

		if (_registry.all_of<ParticleTagComponent, WayPointComponent>(entity) && 
			wp.currentPath->_distanceToNext == 0.f && !wp.repeat)
		{
			_registry.destroy(entity);
		}
	}
}

void Sandbox::RenderLayer(const std::unique_ptr<sf::RenderWindow>& rw)
{
	_data->_window->setView(_data->_focusedView);

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

void Sandbox::TrackingUpdate(const float& deltaTime)
{
	auto view = _registry.view<AttractionComponent>();

	for (auto entity : view)
	{
		auto& traveler = _registry.get<SpriteComponent>(entity).sprite;
		auto target = _registry.get<SpriteComponent>(_player).sprite;

		auto attraction = _registry.get<AttractionComponent>(entity);
		auto speed = _registry.get<SpeedComponent>(entity).current;

		float targetX = target.getPosition().x;
		float targetY = target.getPosition().y;
		float travelerX = traveler.getPosition().x;
		float travelerY = traveler.getPosition().y;

		float distance = sqrt((targetX - travelerX) * (targetX - travelerX) + 
			(targetY - travelerY) * (targetY - travelerY));

		if (distance <= attraction.power.level || attraction.power.fullStrength)
		{
			sf::Vector2f unitDist;
			unitDist.x = (targetX - travelerX) / distance;
			unitDist.y = (targetY - travelerY) / distance;

			sf::Vector2f velocity;
			velocity.x = unitDist.x * speed * deltaTime;
			velocity.y = unitDist.y * speed * deltaTime;

			traveler.move(velocity);		
		}
	}
}

void Sandbox::FrameAnalyticsUpdate()
{
	auto [tracker, fps] = _registry.get<ClockComponent, DataComponent<float>>(_fpsTracker);
	if (tracker.clock.getElapsedTime().asSeconds() >= 1.f)
	{
		std::string title = "Engine 9 | Ver 0.30.2 | FPS: ";
		title += std::to_string(int(fps.value));
		title += " | ";
		title += std::to_string(1000 / fps.value);
		title += "m/s";
		_data->_window->setTitle(title);

		fps.value = 0.f;
		tracker.clock.restart();
	}
	++fps.value;
}
