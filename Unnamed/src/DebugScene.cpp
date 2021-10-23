#include "DebugScene.hpp"

DebugScene::DebugScene()
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

    GameObjectRef noteBlock = std::make_unique<GameObject>(
        nullptr, 
        nullptr, 
        std::make_unique<MusicNote>()
        );

    _currentFocus->Graphics()->SetPosition(sf::Vector2f(400, 300));
    noteBlock->Graphics()->SetPosition(sf::Vector2f(200, 100));
    _entityAll.push_back(_currentFocus);
    _entityAll.push_back(noteBlock);
}

void DebugScene::ProcessInput()
{
    CommandRef command = _inputHandler.HandleInput();
    if (command)
        command->Execute(*_currentFocus);
}

void DebugScene::Update(float deltaTime)
{
    for (int i = 0; i < _entityAll.size(); i++)
    {
        _entityAll[i]->Update(deltaTime);
    }
}

void DebugScene::Render(sf::RenderWindow &rw, float interpolation)
{
    for (int i = 0; i < _entityAll.size(); i++)
    {
        _entityAll[i]->Render(rw, interpolation);
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
