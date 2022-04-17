#include "DebugScene.hpp"

DebugScene::DebugScene(std::shared_ptr<GameData>& data)
    :_data(data) 
{}

DebugScene::~DebugScene()
{}

void DebugScene::Init()
{
    //_background = std::make_unique<UIObject>(_data->_holder, "Background");
    //_particlePool = std::make_unique<ParticlePool<Particle>>();
    //pathRandom = std::make_unique<MRandom>();
    //pathCircle = std::make_unique<MCircle>();

    _player = std::make_unique<PlayerObject>(_data->_holder, "Ship");
    _enemy = std::make_unique<EnemyObject>(_data->_holder, "Ship");
    _enemy2 = std::make_unique<EnemyObject>(_data->_holder, "Ship");

    _enemy->GetPhysics()->SetMovePattern(_data->_pathMap.at("mCircle").get(), true);
    _enemy2->GetPhysics()->SetMovePattern(_data->_pathMap.at("mCircle").get(), false);
    _enemy2->GetGraphics()->GetSprite().setPosition(1000.f, 800.f);

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(100, 1800);
    
    for (int i = 0; i < SIZE; i++)
    {
        std::unique_ptr<EnemyPhysics> physics = std::make_unique<EnemyPhysics>();
        std::unique_ptr<EnemyGraphics> graphics = std::make_unique<EnemyGraphics>(_data->_holder, "Ship");
        enemies[i].AugmentHealth(100.f);
        enemies[i].AugmentSpeed(500.f);
        enemies[i].AugmentAttackSpeed(1.f);
        enemies[i].ResetStats();
        enemies[i].SetPhysics(physics);
        enemies[i].GetPhysics()->SetMovePattern(_data->_pathMap.at("mRandom").get(), true);
        enemies[i].SetGraphics(graphics);
        enemies[i].GetGraphics()->GetSprite().setScale(sf::Vector2f(1.f, 1.f));
        enemies[i].GetGraphics()->GetSprite().setPosition(float(dist6(rng)), float(dist6(rng) - 790));
    }

    for (int i = 0; i < SIZE; i++)
    {
        std::unique_ptr<EnemyObject> object = std::make_unique<EnemyObject>(_data->_holder, "Ship");
        object->GetPhysics()->SetMovePattern(_data->_pathMap.at("mCircle").get(), true);
        object->GetGraphics()->GetSprite().setScale(sf::Vector2f(1.f, 1.f));
        object->GetGraphics()->GetSprite().setPosition(float(dist6(rng)), float(dist6(rng) - 790));
        enemiesPtr[i] = std::move(object);
    }
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

    for (int i = 0; i < SIZE; i++)
    {
        enemies[i].PhysicsUpdate(deltaTime);
        CheckBoundary(enemies[i].GetGraphics()->GetSprite());
        //CheckCollision(_player->GetGraphics()->GetSprite(), enemies[i].GetGraphics()->GetSprite());
        
        enemiesPtr[i]->PhysicsUpdate(deltaTime);
        CheckBoundary(enemiesPtr[i]->GetGraphics()->GetSprite());
        //CheckCollision(_player->GetGraphics()->GetSprite(), enemiesPtr[i]->GetGraphics()->GetSprite());
    }
}

void DebugScene::Render(const std::unique_ptr<sf::RenderWindow>& rw, const float& deltaTime, const float& interpolation)
{
    _player->GraphicsUpdate(rw, interpolation);
    _enemy->GraphicsUpdate(rw, interpolation);
    _enemy2->GraphicsUpdate(rw, interpolation);

    //auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < SIZE; i++)
    {
        enemies[i].GraphicsUpdate(rw, interpolation);
        enemiesPtr[i]->GraphicsUpdate(rw, interpolation);
    }
    //auto stop = std::chrono::high_resolution_clock::now();
    //auto duration = duration_cast<std::chrono::nanoseconds>(stop - start);
    //std::cout << duration.count() << std::endl;

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

