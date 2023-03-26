#pragma once
#include "../Component.hpp"
#include "../System.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

class RenderSystem : public System
{
public:
    void Update(const float& dt, entt::registry& reg, entt::entity ent = entt::null)
    {}

    void Render(sf::RenderWindow& rw, entt::registry& reg)
    {
        auto viewStatic = reg.view<Sprite>();
        for (auto entity : viewStatic)
        {
            auto& sprite = viewStatic.get<Sprite>(entity).sprite;
            rw.draw(sprite);
        }

        auto viewAnimated = reg.view<AnimatedSprite>();
        for (auto entity : viewAnimated)
        {
            auto& sprite = viewAnimated.get<AnimatedSprite>(entity).sprite;
            rw.draw(sprite);
        }
    }
};

