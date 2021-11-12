#include "DebugScene.hpp"

DebugScene::DebugScene(std::shared_ptr<GameData> &data) 
    :_data(data) 
{}

DebugScene::~DebugScene()
{}

void DebugScene::Init()
{
    InputComponentRef controller = std::make_unique<PlayerInput>();
    PhysicsComponentRef rb = std::make_unique<RigidbodyBox>();
    GraphicsComponentRef animation = std::make_unique<ShipAnimation>();
    _player = std::make_unique<GameObject>(_data->_holder, "Ship");
    _player->SetInput(controller);
    _player->SetPhysics(rb);
    _player->SetGraphics(animation);
    _player->SetVelocity(720.f);
    _player->SetScale(sf::Vector2f(3, 3));
    _player->SetPosition(sf::Vector2f(900, 600));

    GameObjectRef testDummy1 = std::make_unique<GameObject>(_data->_holder, "Ship");
    GraphicsComponentRef animation1 = std::make_unique<ShipAnimation>();
    testDummy1->SetScale(sf::Vector2f(3, 3));
    testDummy1->SetPosition(sf::Vector2f(300, 600));
    testDummy1->SetGraphics(animation1);

    GameObjectRef testDummy2 = std::make_unique<GameObject>(_data->_holder, "Ship");
    GraphicsComponentRef animation2 = std::make_unique<ShipAnimation>();
    testDummy2->SetScale(sf::Vector2f(3, 3));
    testDummy2->SetPosition(sf::Vector2f(700, 400));
    testDummy2->SetGraphics(animation2);

    GameObjectRef testDummy3 = std::make_unique<GameObject>(_data->_holder, "Ship");
    GraphicsComponentRef animation3 = std::make_unique<ShipAnimation>();
    testDummy3->SetScale(sf::Vector2f(3, 3));
    testDummy3->SetPosition(sf::Vector2f(400, 900));
    testDummy3->SetGraphics(animation3);

    GameObjectRef background = std::make_unique<GameObject>(_data->_holder, "Background");
    _assets.push_back(std::move(background));
    _assets.push_back(std::move(testDummy1));
    _assets.push_back(std::move(testDummy2));
    _assets.push_back(std::move(testDummy3));
}

void DebugScene::ProcessInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        _data->_machine->AddState(std::make_unique<MainMenu>(_data));
    }
    _inputHandler.HandleInput(*_player);
}

void DebugScene::Update(float deltaTime)
{
    _player->Update(deltaTime);
    for (int i = 0; i < _assets.size(); i++)
    {
        _assets[i]->Update(deltaTime);
    }
    CheckBoundary(_player);
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

void DebugScene::Pause()
{
}

void DebugScene::Resume()
{
}
