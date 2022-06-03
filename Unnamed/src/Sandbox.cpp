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
	_boundary = sf::FloatRect(0.f, 0.f, width, height);
	_quadTree = std::make_unique<QuadTree>(_boundary);
	_data->_mainView.setSize(width, height);

	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 1920);

	for (size_t i = 0; i < MAX_SIZE; i++)
	{
		entt::entity entity = _registry.create();
		_registry.emplace<TagComponent>(entity, "generic_enemy", TagComponent::AFFILIATION::Enemy, TagComponent::TYPE::Interactable);
		_registry.emplace<MidLayerTagComponent>(entity);
		_registry.emplace<HealthComponent>(entity, 100.f);
		_registry.emplace<SpeedComponent>(entity, float(dist6(rng) % 500));
		_registry.emplace<WayPointComponent>(entity, _data->_pathMap.at("mRandom").get(), true);
		_registry.emplace<SpriteComponent>(entity, _data->_holder["Ship"]);
		_registry.get<SpriteComponent>(entity).sprite.setPosition(float(dist6(rng)), float(dist6(rng) % 1080));
	}

	_player = _registry.create();
	_registry.emplace<TagComponent>(_player, "player", TagComponent::AFFILIATION::Ally, TagComponent::TYPE::Interactable);
	_registry.emplace<MidLayerTagComponent>(_player);
	_registry.emplace<HealthComponent>(_player, 1000.f);
	_registry.emplace<SpeedComponent>(_player, 500.f);
	_registry.emplace<PlayerInputComponent>(_player, std::make_shared<CommandDodge>(), std::make_shared<CommandExSkill>());
	_registry.emplace<SpriteComponent>(_player, _data->_holder["Ship"]);
	_registry.get<SpriteComponent>(_player).sprite.setPosition(960, 1000);

	_dummy = _registry.create();
	_registry.emplace<TagComponent>(_dummy, "dummy", TagComponent::AFFILIATION::Enemy, TagComponent::TYPE::Interactable);
	_registry.emplace<MidLayerTagComponent>(_dummy);
	_registry.emplace<HealthComponent>(_dummy, 1000.f);
	_registry.emplace<SpeedComponent>(_dummy, 500.f);
	_registry.emplace<SpriteComponent>(_dummy, _data->_holder["Ship"]);
	_registry.get<SpriteComponent>(_dummy).sprite.setPosition(960, 400);
	_registry.get<SpriteComponent>(_dummy).sprite.setScale(sf::Vector2f(5.f, 5.f));

	_progressionBorder = _registry.create();
	_registry.emplace<TagComponent>(_progressionBorder, "dodge_border", TagComponent::AFFILIATION::None, TagComponent::TYPE::UI);
	_registry.emplace<TopLayerTagComponent>(_progressionBorder);
	_registry.emplace<SpriteComponent>(_progressionBorder, _data->_holder["progressbarborder01"]);
	_registry.get<SpriteComponent>(_progressionBorder).sprite.setOrigin(0, 0);
	_registry.get<SpriteComponent>(_progressionBorder).sprite.setPosition(50, 1000);

	_progressionBar = _registry.create();
	_registry.emplace<TagComponent>(_progressionBar, "dodge_bar", TagComponent::AFFILIATION::None, TagComponent::TYPE::UI);
	_registry.emplace<TopLayerTagComponent>(_progressionBar);
	_registry.emplace<SpriteComponent>(_progressionBar, _data->_holder["progressbar01"]);
	_registry.get<SpriteComponent>(_progressionBar).sprite.setOrigin(0, 0);
	_registry.get<SpriteComponent>(_progressionBar).sprite.setPosition(52, 1002);

	_background = _registry.create();
	_registry.emplace<TagComponent>(_background, "prototype_bg", TagComponent::AFFILIATION::None, TagComponent::TYPE::None);
	_registry.emplace<BotLayerTagComponent>(_background);
	_registry.emplace<SpriteComponent>(_background, _data->_holder["Prototype"]);

	_fpsTracker = _registry.create();
	_registry.emplace<TagComponent>(_fpsTracker, "fps_tracker", TagComponent::AFFILIATION::None, TagComponent::TYPE::UI);
	_registry.emplace<TopLayerTagComponent>(_fpsTracker);
	_registry.emplace<ClockComponent>(_fpsTracker);
	_registry.emplace<DataComponent<float>>(_fpsTracker);
	_registry.emplace<TextComponent>(_fpsTracker, "resources/font/VCR_OSD_MONO_1.001.ttf");
}

void Sandbox::ProcessEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::L)
		{
			auto position = _registry.get<SpriteComponent>(_player).sprite.getPosition();
			entt::entity entity = _registry.create();
			_registry.emplace<TagComponent>(entity, "shot_particle", TagComponent::AFFILIATION::Ally, TagComponent::TYPE::Particle);
			_registry.emplace<MidLayerTagComponent>(entity);
			_registry.emplace<SpeedComponent>(entity, 2000.f);
			_registry.emplace<WayPointComponent>(entity, _data->_pathMap.at("mStraight").get(), false);
			_registry.emplace<DamageComponent>(entity, 100.f);
			_registry.emplace<SpriteComponent>(entity, _data->_holder["Shot"]);
			_registry.get<SpriteComponent>(entity).sprite.setPosition(position);
			_registry.get<SpriteComponent>(entity).sprite.setScale(2.f, 2.f);
		}

		auto controller = _registry.get<PlayerInputComponent>(_player);
		Command* command = NULL;

		if (event.key.code == sf::Keyboard::LShift)
			command = controller.dash.get();

		if (event.key.code == sf::Keyboard::RShift)
			command = controller.exSkill.get();

		if (command)
			command->Execute(_player, &_registry);
	}
}

void Sandbox::ProcessInput(const sf::Event& event)
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
}

void Sandbox::Update(const float& deltaTime)
{
	PlayerUpdate(deltaTime);
	WayPointUpdate(deltaTime);
	ProgressBarUpdate(deltaTime);
	QuadTreeUpdate();
	CheckCollision();
	CheckDestruction();
}

void Sandbox::Render(const std::unique_ptr<sf::RenderWindow>& rw, const float& deltaTime, const float& interpolation)
{
	RenderLayers(rw);
	FramesAnalyticUpdate();
}

void Sandbox::Pause()
{


}

void Sandbox::Resume()
{


}

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
	auto& sp = _registry.get<SpriteComponent>(_player);
	auto speed = _registry.get<SpeedComponent>(_player);

	sf::Vector2f direction = controller.direction;
	direction *= deltaTime * speed.current;

	sp.sprite.move(direction);
	_data->_mainView.setCenter(sp.sprite.getPosition());
	//CheckBoundary(sp.sprite);
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
	_quadTree = std::make_unique<QuadTree>(_boundary);
	auto view = _registry.view<HealthComponent>();
	for (auto entity : view)
	{
		if(_registry.get<TagComponent>(entity).affiliation != TagComponent::AFFILIATION::Ally)
			_quadTree->Insert(entity, &_registry);
	}
}

void Sandbox::CheckCollision()
{
	auto view = _registry.view<DamageComponent>();
	for (auto inflictor : view)
	{
		auto& inflictorSp = _registry.get<SpriteComponent>(inflictor);
		sf::FloatRect range = inflictorSp.sprite.getGlobalBounds();
		std::vector<entt::entity> found = _quadTree->QueryRange(range, &_registry);

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

void Sandbox::DamageUpdate(const entt::entity& inflictor, const entt::entity& inflicted)
{
	if (!_registry.valid(inflictor) || !_registry.valid(inflicted)) return;

	auto dmg = _registry.get<DamageComponent>(inflictor);
	auto& hp = _registry.get<HealthComponent>(inflicted);
	hp.current -= dmg.damage;
	_registry.destroy(inflictor);
	//_registry.emplace<DestructionTagComponent>(inflictor);
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
		auto tag = _registry.get<TagComponent>(entity);

		if (tag.type == TagComponent::TYPE::Particle && wp.currentPath->_distanceToNext == 0.f && !wp.repeat)
		{
			_registry.destroy(entity);
		}
	}

	//auto viewDest = _registry.view<DestructionTagComponent>();
	//for (auto entity : viewDest)
	//{
	//	_registry.destroy(entity);
	//}
}

void Sandbox::RenderLayers(const std::unique_ptr<sf::RenderWindow>& rw)
{
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

	auto topLayerSp = _registry.view<SpriteComponent, TopLayerTagComponent>();
	for (auto entity : topLayerSp)
		rw->draw(topLayerSp.get<SpriteComponent>(entity).sprite);

	auto topLayerTx = _registry.view<TextComponent, TopLayerTagComponent>();
	for (auto entity : topLayerTx)
		rw->draw(topLayerTx.get<TextComponent>(entity).text);
}

void Sandbox::ProgressBarUpdate(const float& deltaTime)
{
	auto skill = _registry.get<PlayerInputComponent>(_player).dash;
	auto& progressBar = _registry.get<SpriteComponent>(_progressionBar);

	float progress = skill->GetTime() / skill->GetMaxTime();
	progressBar.sprite.setScale(std::clamp(progress, 0.f, 1.f), 1.f);
}

void Sandbox::PlayerTrackUpdate(const float& deltaTime)
{
	
}

void Sandbox::FramesAnalyticUpdate()
{
	//auto& tracker = _registry.get<ClockComponent>(_fpsTracker);
	//auto& data = _registry.get<DataComponent<float>>(_fpsTracker);
	//auto& str = _registry.get<TextComponent>(_fpsTracker);


	auto [tracker, data, str] = _registry.get<ClockComponent, DataComponent<float>, TextComponent>(_fpsTracker);
	if (tracker.clock.getElapsedTime().asSeconds() >= 1.f)
	{
		str.text.setString("FPS: " + FloatToString(data.value) + "\n" + FloatToString(1000 / data.value) + "m/s");
		data.value = 0;
		tracker.clock.restart();
	}
	++data.value;
}
std::string Sandbox::FloatToString(const float& d)
{
	std::stringstream ss;
	ss << d;
	return ss.str();
}