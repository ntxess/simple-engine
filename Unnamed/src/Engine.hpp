#pragma once
#include <string>
#include <Thor/Animations/FrameAnimation.hpp>

#include "GameData.hpp"
#include "MainMenu.hpp"
#include "Sandbox.hpp"
#include "MCircle.hpp"
#include "MRandom.hpp"
#include "MStraight.hpp"

static const float VIEW_HEIGHT = 1080.f;

class Engine
{
private:
    std::shared_ptr<GameData> _data;
    const float deltaTime = 1.0f / 165.0f;

public:
    sf::Clock _clock;
    unsigned int _width;
    unsigned int _height;

    Engine(unsigned int width, unsigned int height, std::string title);
    ~Engine();
    void Run();
    void ResizeView(const std::unique_ptr<sf::RenderWindow>& rw, sf::View& view);
};