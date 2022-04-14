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
    _enemy2 = std::make_unique<EnemyObject>(_data->_holder, "Ship");


    MCircle* path = new MCircle();
    _enemy->GetPhysics()->SetMovePattern(path->wps, true);
    _enemy2->GetPhysics()->SetMovePattern(path->wps);

    _enemy2->GetGraphics()->GetSprite().setPosition(1000.f, 800.f);

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
    _enemy2->GraphicsUpdate(rw, interpolation);

    //_playerDup->GraphicsUpdate(rw, interpolation);
    //_particlePool->Render(rw, deltaTime, interpolation);
    //for (int i = 0; i < _assets.size(); i++)
    //    _assets[i]->Render(rw, interpolation);
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

