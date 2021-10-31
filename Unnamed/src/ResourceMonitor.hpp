#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <SFML/Graphics.hpp>

typedef std::unique_ptr<sf::RenderWindow> RenderWindowRef;

class ResourceMonitor
{
private:
    sf::Clock _clock;
    sf::Text  _text;
    sf::Font  _font;
    double _fps;

public:
    ResourceMonitor();
    ~ResourceMonitor();
    std::string FloatToString(float d);
    void Reposition(sf::Vector2f pos);
    void Update();
    void Render(RenderWindowRef& rw);
};