#pragma once
#include "../Component.hpp"
#include "../System.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

class RenderSystem : public System
{
public:
    void Update(entt::registry& reg, const float& dt = 0.f, entt::entity ent = entt::null)
    {}

    void Render(sf::RenderWindow& rw, entt::registry& reg)
    {
        auto view = reg.view<Sprite>();
        for (auto entity : view)
        {
            auto& sprite = view.get<Sprite>(entity).sprite;
            rw.draw(sprite);
        }
    }
};

