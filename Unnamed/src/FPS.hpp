#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <SFML/Graphics.hpp>

class FPS
{
private:
    sf::Clock _clock;
    sf::Text  _text;
    sf::Font  _font;
    sf::Vector2f _position;
    double _fps;

    std::string FloatToString(double d);

public:
    FPS();
    ~FPS();
    void Reposition(sf::Vector2f pos);
    void Update();
    void Render(sf::RenderTarget* rt);
};