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
        std::make_unique<Sprite>(_data->_holder, "Ship")
        );
    _player->SetVelocity(720.f);
    _player->GetGraphics()->SetScale(sf::Vector2f(3,3));
    _player->GetGraphics()->SetPosition(sf::Vector2f(900, 600));

    thor::FrameAnimation idle, leftTurn, rightTurn;
    for (int i = 0; i < 4; i++)
        idle.addFrame(1.f, sf::IntRect(16 * i, 0, 16, 24));
    leftTurn.addFrame(1.f, sf::IntRect(0, 0, 16, 24));
    rightTurn.addFrame(1.f, sf::IntRect(64, 0, 16, 24));
    _player->GetGraphics()->GetAnimator().addAnimation("idle", idle, sf::seconds(1.f));
    _player->GetGraphics()->GetAnimator().addAnimation("leftTurn", leftTurn, sf::seconds(0.05f));
    _player->GetGraphics()->GetAnimator().addAnimation("rightTurn", rightTurn, sf::seconds(0.05f));

    GameObjectRef testDummy1 = std::make_unique<GameObject>(std::make_unique<Sprite>(_data->_holder, "Ship"));
    testDummy1->GetGraphics()->SetScale(sf::Vector2f(3, 3));
    testDummy1->GetGraphics()->SetPosition(sf::Vector2f(300, 600));
    testDummy1->GetGraphics()->GetAnimator().addAnimation("idle", idle, sf::seconds(1.f));

    GameObjectRef testDummy2 = std::make_unique<GameObject>(std::make_unique<Sprite>(_data->_holder, "Ship"));
    testDummy2->GetGraphics()->SetScale(sf::Vector2f(3, 3));
    testDummy2->GetGraphics()->SetPosition(sf::Vector2f(700, 400));
    testDummy2->GetGraphics()->GetAnimator().addAnimation("idle", idle, sf::seconds(1.f));

    GameObjectRef testDummy3 = std::make_unique<GameObject>(std::make_unique<Sprite>(_data->_holder, "Ship"));
    testDummy3->GetGraphics()->SetScale(sf::Vector2f(3, 3));
    testDummy3->GetGraphics()->SetPosition(sf::Vector2f(400, 900));
    testDummy3->GetGraphics()->GetAnimator().addAnimation("idle", idle, sf::seconds(1.f));

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
    if (_player->GetInput()->GetDirection().x > 0)
        _player->GetGraphics()->GetAnimator().playAnimation("rightTurn");
    if (_player->GetInput()->GetDirection().x < 0)
        _player->GetGraphics()->GetAnimator().playAnimation("leftTurn");
}

void DebugScene::Update(float deltaTime)
{
    _player->Update(deltaTime);
    for (int i = 0; i < _assets.size(); i++)
    {
        _assets[i]->Update(deltaTime);
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
}

void DebugScene::Pause()
{
}

void DebugScene::Resume()
{
}
