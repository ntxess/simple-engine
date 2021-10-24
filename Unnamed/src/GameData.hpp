#pragma once
#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include "StateMachine.hpp"

typedef std::unique_ptr<StateMachine> StateMachineRef;
typedef std::unique_ptr<sf::RenderWindow> RenderWindowRef;

struct GameData
{
    StateMachineRef _machine;
    RenderWindowRef _window;

    GameData()
    {
        _machine = std::make_unique<StateMachine>();
        _window = std::make_unique<sf::RenderWindow>();
    }
};