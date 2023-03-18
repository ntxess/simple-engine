#pragma once
#include "GameData.hpp"
#include "Scenes/EmptyScene.hpp"
#include "Thor/Animations/FrameAnimation.hpp"
#include <thread>
#include <atomic>
#include <string>

class Engine
{
private:
    const float m_deltaTime = 1.0f / 165.0f;
    std::shared_ptr<GameData> m_data;
    sf::Clock m_clock;

public:
    Engine() = default;
    Engine(unsigned int width, unsigned int height, std::string title);
    ~Engine() = default;

    void Run();
};
