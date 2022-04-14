#include "DebugScene.hpp"

DebugScene::DebugScene(std::shared_ptr<GameData>& data)
    :_data(data) 
{}

DebugScene::~DebugScene()
{
    for (int i = 0; i < SIZE; i++)
    {
        delete enemiesPtr[i];
        std::cout << enemiesPtr[i]->GetCurrentStats().SPD << std::endl;
    }
}

void DebugScene::Init()
{
    //_background = std::make_unique<UIObject>(_data->_holder, "Background");
    //_particlePool = std::make_unique<ParticlePool<Particle>>();

    _player = std::make_unique<PlayerObject>(_data->_holder, "Ship");
    _enemy = std::make_unique<EnemyObject>(_data->_holder, "Ship");
    _enemy2 = std::make_unique<EnemyObject>(_data->_holder, "Ship");

    MCircle* path = new MCircle();
    _enemy->GetPhysics()->SetMovePattern(path->wps, true);
    _enemy2->GetPhysics()->SetMovePattern(path->wps);
    _enemy2->GetGraphics()->GetSprite().setPosition(1000.f, 800.f);

    for (int i = 0; i < SIZE; i++)
    {
        std::unique_ptr<EnemyPhysics> physics = std::make_unique<EnemyPhysics>();
        std::unique_ptr<EnemyGraphics> graphics = std::make_unique<EnemyGraphics>(_data->_holder, "Ship");
        enemies[i].SetPhysics(physics);
        enemies[i].SetGraphics(graphics);
        enemies[i].GetGraphics()->GetSprite().setPosition((i * 40.0f), 50.0f);
    }

    for (int i = 0; i < SIZE; i++)
    {
        EnemyObject* object = new EnemyObject(_data->_holder, "Ship");
        object->GetGraphics()->GetSprite().setPosition((i * 40.0f), 100.0f);
        enemiesPtr[i] = object;
    }

    //thor::FrameAnimation idle;
    //for (int i = 0; i < 4; i++)
    //    idle.addFrame(1.f, sf::IntRect(16 * i, 0, 16, 24));
    //_data->_animator.addAnimation("idle", idle, sf::seconds(8.f));
    //_data->_animator.playAnimation("idle", true);

    //_playerDup->GetGraphics()->GetSprite().setPosition(sf::Vector2f(700, 900));
    //_particlePool->Create(_data->_holder, "Ship", _player->GetGraphics()->GetSprite().getPosition());
    //_particlePool->Create(_data->_holder, "Ship", sf::Vector2f(300, 500));
    //_particlePool->Create(_data->_holder, "Ship", sf::Vector2f(300, 600));
    //_particlePool->Create(_data->_holder, "Ship", sf::Vector2f(200, 500));
    //_particlePool->Create(_data->_holder, "Ship", sf::Vector2f(100, 500));
    //_particlePool->Create(_data->_holder, "Ship", sf::Vector2f(600, 700));
}

void DebugScene::ProcessEvent(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Escape)
            _data->_machine->AddState(std::make_unique<MainMenu>(_data));
    }
}

void DebugScene::ProcessInput(const sf::Event& event)
{ 
    _player->InputUpdate(event);
}

void DebugScene::Update(const float& deltaTime)
{
    _player->PhysicsUpdate(deltaTime);
    CheckBoundary(_player->GetGraphics()->GetSprite());

    _enemy->PhysicsUpdate(deltaTime);
    CheckBoundary(_enemy->GetGraphics()->GetSprite());

    _enemy2->PhysicsUpdate(deltaTime);
    CheckBoundary(_enemy2->GetGraphics()->GetSprite());

    CheckCollision(_player->GetGraphics()->GetSprite(), _enemy->GetGraphics()->GetSprite());
}

void DebugScene::Render(const std::unique_ptr<sf::RenderWindow>& rw, const float& deltaTime, const float& interpolation)
{
    _fps.Update();
    _fps.Render(rw);

    _player->GraphicsUpdate(rw, interpolation);
    _enemy->GraphicsUpdate(rw, interpolation);
    _enemy2->GraphicsUpdate(rw, interpolation);

    //auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < SIZE; i++)
    {
        enemies[i].GraphicsUpdate(rw, interpolation);
    }
    //auto stop = std::chrono::high_resolution_clock::now();
    //auto duration = duration_cast<std::chrono::nanoseconds>(stop - start);
    //std::cout << duration.count() << std::endl;

    //auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < SIZE; i++)
    {
        enemiesPtr[i]->GraphicsUpdate(rw, interpolation);
    }
    //auto stop = std::chrono::high_resolution_clock::now();
    //auto duration = duration_cast<std::chrono::nanoseconds>(stop - start);
    //std::cout << duration.count() << std::endl;
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

void DebugScene::CheckCollision(sf::Sprite& player, sf::Sprite& object)
{
    if (player.getGlobalBounds().intersects(object.getGlobalBounds()))
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

