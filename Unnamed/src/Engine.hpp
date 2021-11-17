#pragma once
#include <string>
#include <Thor/Animations/FrameAnimation.hpp>
#include "GameData.hpp"
#include "MainMenu.hpp"

class Engine
{
private:
    std::shared_ptr<GameData> _data;
    const float dt = 1.0f / 175.0f;

public:
    sf::Clock _clock;
    unsigned int _width;
    unsigned int _height;

    Engine(unsigned int width, unsigned int height, std::string title);
    ~Engine();
    void Run();
    bool IsOpen() const;
};