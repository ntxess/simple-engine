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

    _player = std::make_unique<PlayerObject>(_data->_holder, "Ship");
    _enemy = std::make_unique<EnemyObject>(_data->_holder, "Ship");
    _enemy->GetPhysics()->SetMovePattern(std::make_unique<CircleMov>());
    //std::unique_ptr<WayPoint> pointA = std::make_unique<WayPoint>(sf::Vector2f(100.0f, 100.0f));
    //std::unique_ptr<WayPoint> pointB = std::make_unique<WayPoint>(sf::Vector2f(200.0f, 600.0f));
    //std::unique_ptr<WayPoint> pointC = std::make_unique<WayPoint>(sf::Vector2f(-100.0f, -100.0f));

    //WayPoint* pointA = new WayPoint(sf::Vector2f(10.0f, 10.0f));
    //WayPoint* pointB = new WayPoint(sf::Vector2f(10.0f, 40.0f));
    //WayPoint* pointC = new WayPoint(sf::Vector2f(-100.0f, -100.0f));

    //pointB->AddNext(std::move(pointC));
    //pointA->AddNext(std::move(pointB));
    //_enemy->GetPhysics()->SetPath(std::move(pointA));

    //thor::FrameAnimation idle;
    //for (int i = 0; i < 4; i++)
    //    idle.addFrame(1.f, sf::IntRect(16 * i, 0, 16, 24));
    //_data->_animator.addAnimation("idle", idle, sf::seconds(8.f));
    //_data->_animator.playAnimation("idle", true);

    //_playerDup = std::make_unique<GameObject>();
    //std::shared_ptr<InputComponent> aiInput = std::make_shared<AIInput>();
    //std::shared_ptr<PhysicsComponent> aiPhysics = std::make_shared<AIPhysics>();
    //std::shared_ptr<GraphicsComponent> aiGraphics = std::make_shared<AIGraphics>(_data->_holder, "Ship");
    //_playerDup->SetInput(aiInput);
    //_playerDup->SetPhysics(aiPhysics);
    //_playerDup->SetGraphics(aiGraphics);

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
    //_playerDup->InputUpdate(event);
}

void DebugScene::Update(const float& deltaTime)
{
    _player->PhysicsUpdate(deltaTime);
    CheckBoundary(_player);

    _enemy->PhysicsUpdate(deltaTime);
    //_playerDup->PhysicsUpdate(deltaTime);
    //CheckBoundary(_playerDup);

    //_particlePool->Create(_data->_holder, "Shot", _player->GetGraphics()->GetSprite().getPosition());
    //_particlePool->Update(deltaTime);

    //_player->Update(deltaTime);
    //if (_player->_isShooting)
    //    SpawnShotParticle();

    //CheckBoundary(_player->GetComponent());

    //auto assetStart = _assets.begin();
    //for (int i = 0; i < _assets.size(); i++)
    //{
    //    _assets[i]->Update(deltaTime);
    //    _assets[i]->GetInput()->Update(sf::Vector2f(0, -1));
    //    CheckBoundary(_assets[i]);
    //}

    //if (!_player->IsAlive())
    //{
    //    _data->_machine->AddState(std::make_unique<MainMenu>(_data));
    //}
}

void DebugScene::Render(const std::unique_ptr<sf::RenderWindow>& rw, const float& deltaTime, const float& interpolation)
{
    //_background->Render(rw, deltaTime, interpolation);
    _fps.Update();
    _fps.Render(rw);

    //_data->_animator.animate(_player->GetGraphics()->GetSprite());
    _player->GraphicsUpdate(rw, interpolation);
    _enemy->GraphicsUpdate(rw, interpolation);
    //_playerDup->GraphicsUpdate(rw, interpolation);
    //_particlePool->Render(rw, deltaTime, interpolation);
    //for (int i = 0; i < _assets.size(); i++)
    //    _assets[i]->Render(rw, interpolation);
}

void DebugScene::CheckBoundary(const std::unique_ptr<PlayerObject>& object)
{
    sf::Vector2f position = object->GetGraphics()->GetSprite().getPosition();
    sf::FloatRect rect = object->GetGraphics()->GetSprite().getGlobalBounds();
    sf::Vector2u bounds = _data->_window->getSize();

    if (position.x < 0)
        object->GetGraphics()->GetSprite().setPosition(sf::Vector2f(0.f, position.y));

    if (position.x + rect.width > bounds.x)
        object->GetGraphics()->GetSprite().setPosition(sf::Vector2f(bounds.x - rect.width, position.y));

    position = object->GetGraphics()->GetSprite().getPosition();

    if (position.y < 0)
        object->GetGraphics()->GetSprite().setPosition(sf::Vector2f(position.x, 0.f));

    if (position.y + rect.height > bounds.y)
        object->GetGraphics()->GetSprite().setPosition(sf::Vector2f(position.x, bounds.y - rect.height));
}

bool DebugScene::CheckCollision(const std::unique_ptr<GameObject>& playerComponent, const std::unique_ptr<GameObject>& object)
{
    //if (object->GetPhysics())
    //{
    //    if (playerComponent->GetSprite().getGlobalBounds().intersects(object->GetSprite().getGlobalBounds()))
    //    {
    //        object->SetTouchTag(true);
    //    }
    //}
    return false;
}

void DebugScene::SpawnShotParticle()
{
    //sf::Vector2f position = _player->GetComponent()->GetPosition();
    //GameObjectRef shotParticle = std::make_unique<ShotParticle>(_data->_holder, position);
    //_assets.push_back(std::move(shotParticle));
    //_player->Shoot(false);
}

void DebugScene::Pause()
{
}

void DebugScene::Resume()
{
}

