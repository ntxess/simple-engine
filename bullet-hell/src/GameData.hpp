#pragma once
#include "Managers/SceneManager.hpp"
#include "Managers/SpriteManager.hpp"
#include "Managers/WaypointManager.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

struct GameData
{
    sf::RenderWindow window;
    sf::View defaultViewPort;
    SceneManager sceneManager;
    SpriteManager spriteManager;
    WaypointManager waypointManager;
    // thor::ResourceHolder<sf::SoundBuffer, std::string> audioManager;
};