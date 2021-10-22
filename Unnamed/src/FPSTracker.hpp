#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <SFML/Graphics.hpp>
#include "GameObject.hpp"

class FPSTracker
{
private:
    sf::Clock _clock;
    sf::Text  _text;
    sf::Font  _font;
    sf::Vector2f _position;
    double _fps;

public:
    FPSTracker();
    ~FPSTracker();
    std::string FloatToString(double d);
    void Reposition(sf::Vector2f pos);
    void Update();
    void Render(sf::RenderWindow &rw);
};