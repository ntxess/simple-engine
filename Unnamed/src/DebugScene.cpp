#include "DebugScene.hpp"

DebugScene::DebugScene(std::shared_ptr<GameData> &data) :_data(data) 
{}

DebugScene::~DebugScene()
{}

void DebugScene::Init()
{
    _player       = std::make_unique<Player>(_data->_holder, "Ship");
    _background   = std::make_unique<GameObject>(_data->_holder, "Background");
    _particlePool = std::make_unique<GameObjectPool<Particle>>(_data->_holder, "Shot");
}

void DebugScene::ProcessInput(sf::Event event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Escape)
            _data->_machine->AddState(std::make_unique<MainMenu>(_data));

        if (event.key.code == sf::Keyboard::Z)
        {
            std::cout << "Pressed Z" << std::endl;
            _player->Shoot(true);
        }

        if (event.key.code == sf::Keyboard::X)
        {
            std::cout << "Pressed X" << std::endl;
        }
    }

    float horizontal = 0, vertical = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        vertical = -1.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        horizontal = -1.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        vertical = 1.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        horizontal = 1.f;

    _player->GetComponent()->GetInput()->Update(sf::Vector2f(horizontal, vertical));
}

void DebugScene::Update(float deltaTime)
{
    _background->Update(deltaTime);
    _player->Update(deltaTime);

    if (_player->_isShooting)
        SpawnShotParticle();

    CheckBoundary(_player->GetComponent());

    auto assetStart = _assets.begin();
    for (int i = 0; i < _assets.size(); i++)
    {
        _assets[i]->Update(deltaTime);
        _assets[i]->GetInput()->Update(sf::Vector2f(0, -1));
        CheckBoundary(_assets[i]);
        //CheckCollision(_player->GetComponent(), _assets[i]);
        //if (_assets[i]->IsTouched())
        //    _assets.erase(assetStart + i);
    }

    if (!_player->IsAlive())
    {
        _data->_machine->AddState(std::make_unique<MainMenu>(_data));
    }
}

void DebugScene::Render(RenderWindowRef& rw, float interpolation)
{
    _background->Render(rw, interpolation);
    _player->Render(rw, interpolation);

    for (int i = 0; i < _assets.size(); i++)
        _assets[i]->Render(rw, interpolation);

    _fps.Update();
    _fps.Render(rw);
}

void DebugScene::CheckBoundary(GameObjectRef& object)
{
    if (object->GetPosition().x < 0)
        object->SetPosition(sf::Vector2f(0.f, object->GetPosition().y));

    if (object->GetPosition().y < 0)
        object->SetPosition(sf::Vector2f(object->GetPosition().x, 0.f));

    if (object->GetPosition().x + object->GetSprite().getGlobalBounds().width > _data->_window->getSize().x)
        object->SetPosition(sf::Vector2f(_data->_window->getSize().x - object->GetSprite().getGlobalBounds().width, object->GetPosition().y));

    if (object->GetPosition().y + object->GetSprite().getGlobalBounds().height > _data->_window->getSize().y)
        object->SetPosition(sf::Vector2f(object->GetPosition().x, _data->_window->getSize().y - object->GetSprite().getGlobalBounds().height));
}

bool DebugScene::CheckCollision(GameObjectRef& playerComponent, GameObjectRef& object)
{
    if (object->GetPhysics())
    {
        if (playerComponent->GetSprite().getGlobalBounds().intersects(object->GetSprite().getGlobalBounds()))
        {
            object->SetTouchTag(true);
            _player->TakeDamage(30.f);
        }
    }
    return false;
}

void DebugScene::SpawnShotParticle()
{
    sf::Vector2f position = _player->GetComponent()->GetPosition();
    GameObjectRef shotParticle = std::make_unique<ShotParticle>(_data->_holder, position);
    _assets.push_back(std::move(shotParticle));
    _player->Shoot(false);
}

void DebugScene::Pause()
{
}

void DebugScene::Resume()
{
}

