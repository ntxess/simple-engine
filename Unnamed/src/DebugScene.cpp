#include "DebugScene.hpp"

DebugScene::DebugScene(std::shared_ptr<GameData>& data)
    :_data(data) 
{}

DebugScene::~DebugScene()
{}

void DebugScene::Init()
{
    _player = std::make_unique<PlayerObject>(_data->_holder["Ship"]);
    _uEnemy = std::make_unique<UEnemyObject>(_data->_holder["Ship"]);
    _uEnemy->GetPhysics()->SetMovePattern(_data->_pathMap.at("mCircle").get(), true);

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 1920);
    
    for (int i = 0; i < _enemyPool.POOL_SIZE; i++)
    {
        sf::Texture& ship = _data->_holder["Ship"];
        WayPoint* pathPattern = _data->_pathMap.at("mRandom").get();
        sf::Vector2f randomPos = sf::Vector2f(float(dist6(rng)), float(dist6(rng) % 1080));
        _enemyPool.Create(ship, pathPattern, randomPos);
        _enemyPool.GetObject(i).SetRepeatPath(true);
        _enemyPool.GetObject(i).SetSpeed(float(dist6(rng) % 500));
        _enemyPool.GetObject(i).ResetStats();
    }

    _boundary = sf::FloatRect(0.f, 0.f, float(_data->_window->getSize().x), float(_data->_window->getSize().y));
    _range = sf::FloatRect(0.f, 0.f, 100.0f, 100.0f);
    _qTree = std::make_unique<QuadTree>(_boundary);
}

void DebugScene::ProcessEvent(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Escape)
            _data->_machine->AddState(std::make_unique<MainMenu>(_data));

        if (event.key.code == sf::Keyboard::L)
        {
            sf::Texture& basicAttack = _data->_holder["Shot"];
            WayPoint* pathPattern = _data->_pathMap.at("mStraight").get();
            sf::Vector2f playerPos = _player->GetGraphics()->GetSprite().getPosition();
            _weaponPool.Create(basicAttack, pathPattern, playerPos);
        }
    }
}

void DebugScene::ProcessInput(const sf::Event& event)
{ 
    _player->ProcessInput(event);
}

void DebugScene::Update(const float& deltaTime)
{
    _player->Update(deltaTime);
    CheckBoundary(_player->GetGraphics()->GetSprite());

    _uEnemy->Update(deltaTime);
    CheckBoundary(_uEnemy->GetGraphics()->GetSprite());

    _enemyPool.Update(deltaTime);
    _weaponPool.Update(deltaTime);

    _qTree = std::make_unique<QuadTree>(_boundary);
    _qTree->Insert(&_player.get()->GetGraphics().get()->GetSprite());
    for (unsigned int i = 0; i < _enemyPool.POOL_SIZE; i++)
    {
        CheckBoundary(_enemyPool.GetObject(i).GetSprite());
        _qTree->Insert(&_enemyPool.GetObject(i).GetSprite());
    }
}

void DebugScene::Render(const std::unique_ptr<sf::RenderWindow>& rw, const float& deltaTime, const float& interpolation)
{
    _player->Render(rw, interpolation);
    _uEnemy->Render(rw, interpolation);

    _enemyPool.Render(rw, deltaTime, interpolation);
    _weaponPool.Render(rw, deltaTime, interpolation);

    _fps.Update();
    _fps.Render(rw);
}

void DebugScene::CheckBoundary(sf::Sprite& object)
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

void DebugScene::CheckCollision(sf::Sprite& receiver, sf::Sprite& object)
{
    if (receiver.getGlobalBounds().intersects(object.getGlobalBounds()))
    {
        std::cout << "UGGHH I GOT HIT" << std::endl;
    }
}

void DebugScene::Pause()
{
}

void DebugScene::Resume()
{
}

