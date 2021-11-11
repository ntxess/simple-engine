#include "DebugScene.hpp"

DebugScene::DebugScene(std::shared_ptr<GameData> &data) 
    :_data(data) 
{}

DebugScene::~DebugScene()
{}

void DebugScene::Init()
{
    _player = std::make_unique<GameObject>(
        std::make_unique<PlayerInput>(), 
        nullptr, 
        std::make_unique<Sprite>(_data->_holder, "Ship", true)
        );
    _player->SetVelocity(720.f);
    _player->SetScale(sf::Vector2f(3,3));
    _player->SetPosition(sf::Vector2f(900, 600));

    thor::FrameAnimation idle, leftTurn, rightTurn;
    for (int i = 0; i < 4; i++)
        idle.addFrame(1.f, sf::IntRect(16 * i, 0, 16, 24));
    leftTurn.addFrame(1.f, sf::IntRect(0, 0, 16, 24));
    rightTurn.addFrame(1.f, sf::IntRect(64, 0, 16, 24));
    _player->AddAnimation("idle", idle, sf::seconds(1.f));
    _player->AddAnimation("leftTurn", leftTurn, sf::seconds(0.05f));
    _player->AddAnimation("rightTurn", rightTurn, sf::seconds(0.05f));

    GameObjectRef testDummy1 = std::make_unique<GameObject>(std::make_unique<Sprite>(_data->_holder, "Ship", true));
    testDummy1->SetScale(sf::Vector2f(3, 3));
    testDummy1->SetPosition(sf::Vector2f(300, 600));
    testDummy1->AddAnimation("idle", idle, sf::seconds(1.f));

    GameObjectRef testDummy2 = std::make_unique<GameObject>(std::make_unique<Sprite>(_data->_holder, "Ship", true));
    testDummy2->SetScale(sf::Vector2f(3, 3));
    testDummy2->SetPosition(sf::Vector2f(700, 400));
    testDummy2->AddAnimation("idle", idle, sf::seconds(1.f));

    GameObjectRef testDummy3 = std::make_unique<GameObject>(std::make_unique<Sprite>(_data->_holder, "Ship", true));
    testDummy3->SetScale(sf::Vector2f(3, 3));
    testDummy3->SetPosition(sf::Vector2f(400, 900));
    testDummy3->AddAnimation("idle", idle, sf::seconds(1.f));

    GameObjectRef background = std::make_unique<GameObject>(std::make_unique<Sprite>(_data->_holder, "Background"));
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
    if (_player->GetDirection().x > 0)
        _player->PlayAnimation("rightTurn");
    if (_player->GetDirection().x < 0)
        _player->PlayAnimation("leftTurn");
}

void DebugScene::Update(float deltaTime)
{
    _player->Update(deltaTime);
    for (int i = 0; i < _assets.size(); i++)
    {
        _assets[i]->Update(deltaTime);
    }

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

    if (object->GetPosition().x + object->GetGraphics()->GetSprite().getGlobalBounds().width > _data->_window->getSize().x)
        object->SetPosition(sf::Vector2f(_data->_window->getSize().x - object->GetGraphics()->GetSprite().getGlobalBounds().width, object->GetPosition().y));

    if (object->GetPosition().y + object->GetGraphics()->GetSprite().getGlobalBounds().height > _data->_window->getSize().y)
        object->SetPosition(sf::Vector2f(object->GetPosition().x, _data->_window->getSize().y - object->GetGraphics()->GetSprite().getGlobalBounds().height));
}

void DebugScene::Pause()
{
}

void DebugScene::Resume()
{
}
