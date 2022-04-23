#include "DebugScene.hpp"

DebugScene::DebugScene(std::shared_ptr<GameData>& data)
    :_data(data) 
{}

DebugScene::~DebugScene()
{}

void DebugScene::Init()
{
    //_background = std::make_unique<UIObject>(_data->_holder, "Background");

    _player = std::make_unique<PlayerObject>(_data->_holder["Ship"]);
    //_uEnemy = std::make_unique<UEnemyObject>(_data->_holder["Ship"]);
    //_uEnemy->GetPhysics()->SetMovePattern(_data->_pathMap.at("mCircle").get(), true);

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(100, 1800);
    
    for (int i = 0; i < enemyPool.POOL_SIZE; i++)
    {
        sf::Texture& ship = _data->_holder["Ship"];
        //WayPoint * pathPattern = _data->_pathMap.at("mRandom").get();
        sf::Vector2f randomPos = sf::Vector2f(float(dist6(rng)), float(dist6(rng) - 790));
        //enemyPool.Create(ship, pathPattern, randomPos);
        enemyPool.Create(ship, nullptr, randomPos);
        //enemyPool.GetObject(i).SetRepeatPath(true);
    }

    sf::FloatRect rect(0.f, 0.f, float(_data->_window->getSize().x), float(_data->_window->getSize().y));
    qTree = std::make_unique<QuadTree>(rect, 4);
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
            weaponPool.Create(basicAttack, pathPattern, playerPos);
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

    //_uEnemy->Update(deltaTime);
    //CheckBoundary(_uEnemy->GetGraphics()->GetSprite());

    enemyPool.Update(deltaTime);
    weaponPool.Update(deltaTime);

    qTree->Insert(&_player->GetGraphics()->GetSprite());
    for (unsigned int i = 0; i < enemyPool.POOL_SIZE; i++)
    {
        qTree->Insert(&enemyPool.GetObject(i).GetSprite());
        //CheckBoundary(enemyPool.GetObject(i).GetSprite());
    }
}

void DebugScene::Render(const std::unique_ptr<sf::RenderWindow>& rw, const float& deltaTime, const float& interpolation)
{
    qTree->DrawBox(rw);
    qTree->Clear();

    _player->Render(rw, interpolation);
    //_uEnemy->Render(rw, interpolation);

    enemyPool.Render(rw, deltaTime, interpolation);
    weaponPool.Render(rw, deltaTime, interpolation);

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

