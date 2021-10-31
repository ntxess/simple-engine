#pragma once
#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include <Thor/Resources.hpp>
#include "StateMachine.hpp"

typedef std::unique_ptr<StateMachine> StateMachineRef;
typedef std::unique_ptr<sf::RenderWindow> RenderWindowRef;
typedef std::unique_ptr<thor::ResourceHolder<sf::Texture, std::string>> ResourceHolderRef;

struct GameData
{
public:
    StateMachineRef _machine;
    RenderWindowRef _window;
    ResourceHolderRef _holder;

    GameData()
    {
        _machine = std::make_unique<StateMachine>();
        _window = std::make_unique<sf::RenderWindow>();
        _holder = std::make_unique<thor::ResourceHolder<sf::Texture, std::string>>();
    }
};