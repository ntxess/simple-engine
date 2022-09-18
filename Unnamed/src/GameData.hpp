#pragma once
#include <memory>

#include "SFML/Graphics.hpp"
#include "Thor/Resources.hpp"
#include "Thor/Animations.hpp"
#include "StateMachine.hpp"
#include "WayPoint.hpp"

struct GameData
{
public:
    std::unique_ptr<sf::RenderWindow> _window;
    std::unique_ptr<StateMachine> _machine;
    std::unordered_map<std::string, std::unique_ptr<WayPoint>> _pathMap;
    thor::ResourceHolder<sf::Texture, std::string> _holder;
    thor::Animator<sf::Sprite, std::string> _animator;
    sf::View _defaultView;
    sf::View _focusedView;

    GameData()
    {
        _window = std::make_unique<sf::RenderWindow>();
        _machine = std::make_unique<StateMachine>();
    }
};