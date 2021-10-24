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
        std::make_unique<MusicNote>()
        );

    GameObjectRef noteBlock = std::make_unique<GameObject>(std::make_unique<MusicNote>());

    _currentFocus->Graphics()->SetPosition(sf::Vector2f(400, 300));
    noteBlock->Graphics()->SetPosition(sf::Vector2f(200, 100));
    _assets.push_back(std::move(noteBlock));
}

void DebugScene::ProcessInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
    {
        _data->_machine->RemoveState();
    }

    CommandRef command = _inputHandler.HandleInput();
    if (command) {
        command->Execute(*_currentFocus);
    }
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
    _currentFocus->Render(rw, interpolation);
    for (int i = 0; i < _assets.size(); i++)
    {
        _assets[i]->Render(rw, interpolation);
    }
    _fps.Update();
    _fps.Render(rw);
}

void DebugScene::Pause()
{
}

void DebugScene::Resume()
{
}
