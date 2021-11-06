#include "DebugScene.hpp"

DebugScene::DebugScene(std::shared_ptr<GameData> &data) 
    :_data(data) 
{}

DebugScene::~DebugScene()
{}

void DebugScene::Init()
{
    _currentFocus = std::make_unique<GameObject>(
        std::make_unique<PlayerInput>(), 
        nullptr, 
        std::make_unique<Sprite>(_data->_holder, "Player")
        );

    GameObjectRef background = std::make_unique<GameObject>(std::make_unique<Sprite>(_data->_holder, "Background"));

    _currentFocus->GetGraphics()->SetPosition(sf::Vector2f(400, 300));
    _assets.push_back(std::move(background));
}

void DebugScene::ProcessInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        _data->_machine->AddState(std::make_unique<MainMenu>(_data));
    }

    _inputHandler.HandleInput(*_currentFocus);
}

void DebugScene::Update(float deltaTime)
{
    _currentFocus->Update(deltaTime);
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
    _currentFocus->Render(rw, interpolation);
    _fps.Update();
    _fps.Render(rw);
}

void DebugScene::Pause()
{
}

void DebugScene::Resume()
{
}
