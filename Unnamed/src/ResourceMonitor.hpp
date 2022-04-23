#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <SFML/Graphics.hpp>

class ResourceMonitor
{
private:
    sf::Clock _clock;
    sf::Text _text;
    sf::Font _font;
    float _fps;

public:
    ResourceMonitor();
    ~ResourceMonitor();
    std::string FloatToString(float d);
    void Reposition(sf::Vector2f pos);
    void Update();
    void Render(const std::unique_ptr<sf::RenderWindow>& rw);
};