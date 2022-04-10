#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include <Thor/Resources.hpp>

#include "StateMachine.hpp"

struct GameData
{
public:
    std::unique_ptr<StateMachine> _machine;
    std::unique_ptr<sf::RenderWindow> _window;
    thor::ResourceHolder<sf::Texture, std::string> _holder;
    thor::Animator<sf::Sprite, std::string> _animator;

    GameData()
    {
        _machine = std::make_unique<StateMachine>();
        _window = std::make_unique<sf::RenderWindow>();
    }
};