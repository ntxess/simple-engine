#include "DebugScene.hpp"

DebugScene::DebugScene(std::shared_ptr<GameData> &data) 
    :_data(data) 
{}

DebugScene::~DebugScene()
{}

void DebugScene::Init()
{
    ComponentRef aircraft = std::make_unique<Component>(_data->_holder, "Ship");
    InputComponentRef controller = std::make_unique<PlayerInput>();
    PhysicsComponentRef rb = std::make_unique<RigidbodyBox>();
    GraphicsComponentRef animation = std::make_unique<ShipAnimation>();
    aircraft->SetInput(controller);
    aircraft->SetPhysics(rb);
    aircraft->SetGraphics(animation);
    aircraft->SetVelocity(500.f);
    aircraft->SetScale(sf::Vector2f(2, 2));
    aircraft->SetPosition(sf::Vector2f(360, 900));
    _player = std::make_unique<Player>(aircraft);
    
    ComponentRef background = std::make_unique<Component>(_data->_holder, "Background");
    _assets.push_back(std::move(background));
}

void DebugScene::ProcessInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        _data->_machine->AddState(std::make_unique<MainMenu>(_data));

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        _player->GetComponent()->GetInput()->Shoot(true);

    float horizontal = 0, vertical = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        vertical = -1.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        horizontal = -1.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        vertical = 1.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        horizontal = 1.f;

    _player->GetComponent()->GetInput()->Move(sf::Vector2f(horizontal, vertical));
}

void DebugScene::Update(float deltaTime)
{
    auto assetStart = _assets.begin();
    _player->Update(deltaTime);
    CheckBoundary(_player->GetComponent());
    for (int i = 0; i < _assets.size(); i++)
    {
        _assets[i]->Update(deltaTime);
        CheckCollision(_player->GetComponent(), _assets[i]);
        if (_assets[i]->IsTouched())
            _assets.erase(assetStart + i);
    }
}

void DebugScene::Render(RenderWindowRef& rw, float interpolation)
{
    for (int i = 0; i < _assets.size(); i++)
    {
        _assets[i]->Render(rw, interpolation);
    }

    _player->Render(rw, interpolation);
    _fps.Update();
    _fps.Render(rw);

    if (!_player->IsAlive())
    {
        _data->_machine->AddState(std::make_unique<MainMenu>(_data));
    }
}

void DebugScene::CheckBoundary(ComponentRef& object)
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

bool DebugScene::CheckCollision(ComponentRef& playerComponent, ComponentRef& object)
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

void DebugScene::Pause()
{
}

void DebugScene::Resume()
{
}
