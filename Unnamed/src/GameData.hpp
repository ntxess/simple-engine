#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include <Thor/Resources.hpp>

#include "StateMachine.hpp"
//#include "MovementType.hpp"

struct GameData
{
public:
    std::unique_ptr<sf::RenderWindow> _window;
    std::unique_ptr<StateMachine> _machine;
    thor::ResourceHolder<sf::Texture, std::string> _holder;
    //thor::ResourceHolder<MovementType, std::string> _moveholder;
    thor::Animator<sf::Sprite, std::string> _animator;

    GameData()
    {
        _window = std::make_unique<sf::RenderWindow>();
        _machine = std::make_unique<StateMachine>();
    }
};