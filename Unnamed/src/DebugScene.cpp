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
        nullptr
        );

    GameObjectRef noteBlock = std::make_unique<GameObject>(
        nullptr, 
        nullptr, 
        std::make_unique<MusicNote>()
        );

    GameObjectRef noteBlock2 = std::make_unique<GameObject>(
        nullptr,
        nullptr,
        std::make_unique<MusicNote>()
        );

    noteBlock->Graphics()->SetPosition(sf::Vector2f(400, 300));
    noteBlock2->Graphics()->SetPosition(sf::Vector2f(200, 100));
    _entityAll.push_back(noteBlock);
    _entityAll.push_back(noteBlock2);
}

void DebugScene::ProcessInput()
{
    _inputHandler.HandleInput(*_currentFocus);
}

void DebugScene::Update(double deltaTime)
{
    for (int i = 0; i < _entityAll.size(); i++)
    {
        _entityAll[i]->Update(deltaTime);
    }
}

void DebugScene::Render(sf::RenderWindow* rt, double interpolation)
{
    for (int i = 0; i < _entityAll.size(); i++)
    {
        _entityAll[i]->Render(rt, interpolation);
    }
}

void DebugScene::Pause()
{
}

void DebugScene::Resume()
{
}
