#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include <Thor/Resources.hpp>
#include "StateMachine.hpp"

typedef std::unique_ptr<StateMachine> StateMachineRef;
typedef std::unique_ptr<sf::RenderWindow> RenderWindowRef;

struct GameData
{
public:
    StateMachineRef _machine;
    RenderWindowRef _window;
    thor::ResourceHolder<sf::Texture, std::string> _holder;
    thor::Animator<sf::Sprite, std::string> _animator;

    GameData()
    {
        _machine = std::make_unique<StateMachine>();
        _window = std::make_unique<sf::RenderWindow>();
    }
};