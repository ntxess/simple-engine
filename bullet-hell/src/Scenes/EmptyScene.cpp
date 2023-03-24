#include "EmptyScene.hpp"

EmptyScene::EmptyScene(std::shared_ptr<GameData>& data)
	: m_data(data)
{}

EmptyScene::~EmptyScene()
{}

void EmptyScene::Init()
{
    LoadResources();
    BuildEntities();
    SetupScene();
}

void EmptyScene::ProcessEvent(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::A)
            std::cout << "PRESSED" << std::endl;
           
    }
}

void EmptyScene::ProcessInput()
{

}

void EmptyScene::Update(const float& deltaTime)
{
    if (!m_entity["Player"]->GetComponent<AnimatedSprite>().animator.isPlayingAnimation()) {
        m_entity["Player"]->GetComponent<AnimatedSprite>().animator.playAnimation("playerIdle");
    }
    m_entity["Player"]->GetComponent<AnimatedSprite>().Update(sf::seconds(deltaTime));
    m_entity["Player"]->GetComponent<AnimatedSprite>().Animate();

    WaypointUpdate(deltaTime);
}

void EmptyScene::Render(sf::RenderWindow& rw, const float& deltaTime, const float& interpolation)
{
    rw.draw(m_entity["Background"]->GetComponent<Sprite>().sprite);
    rw.draw(m_entity["Player"]->GetComponent<AnimatedSprite>().sprite);
    rw.draw(m_entity["Enemy"]->GetComponent<AnimatedSprite>().sprite);
}

void EmptyScene::Pause()
{}

void EmptyScene::Resume()
{}

entt::registry& EmptyScene::GetRegistry()
{
	return m_reg;
}

void EmptyScene::LoadResources() 
{
    try
    {
        m_data->textureManager.acquire("BG_Space",
            thor::Resources::fromFile<sf::Texture>("resources/bg/Space_Stars2.png"),
            thor::Resources::Reuse);
        m_data->textureManager.acquire("SP_Player",
            thor::Resources::fromFile<sf::Texture>("resources/player/ship.png"),
            thor::Resources::Reuse);
        m_data->textureManager.acquire("SP_Enemy",
            thor::Resources::fromFile<sf::Texture>("resources/player/triangle.png"),
            thor::Resources::Reuse);
        m_data->textureManager.acquire("SP_Player2",
            thor::Resources::fromFile<sf::Texture>("resources/player/ship_alt.png"),
            thor::Resources::Reuse);
    }
    catch (thor::ResourceLoadingException& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

void EmptyScene::BuildEntities() 
{
    std::unique_ptr<AbstractFactory> interactable = std::make_unique<InteractableFactory>(m_data, this);
    std::unique_ptr<AbstractFactory> nonInteractable = std::make_unique<NonInteractableFactory>(m_data, this);

    m_entity["Player"] = interactable->CreateEntity(TYPE::PLAYER, m_data->textureManager["SP_Player"]);
    m_entity["Background"] = nonInteractable->CreateEntity(TYPE::BACKGROUND, m_data->textureManager["BG_Space"]);
    m_entity["Enemy"] = interactable->CreateEntity(TYPE::ENEMY, m_data->textureManager["SP_Player2"]);
}

void EmptyScene::SetupScene()
{
    m_entity["Player"]->GetComponent<AnimatedSprite>().sprite.setScale(10, 10);
    m_entity["Player"]->GetComponent<AnimatedSprite>().sprite.setPosition(960, 500);
    m_entity["Enemy"]->GetComponent<AnimatedSprite>().sprite.setPosition(200, 500);
}

void EmptyScene::WaypointUpdate(const float& dt)
{
    auto group = m_reg.group<MovementPattern, Speed>(entt::get<AnimatedSprite>);
    for (auto entity : group)
    {
        auto [wpc, spd, sp] = group.get<MovementPattern, Speed, AnimatedSprite>(entity);

        Waypoint* headPtr = wpc.currentPath;
        Waypoint* nextPtr = headPtr->nextWP.get();

        if (nextPtr == nullptr)
        {
            if (wpc.repeat)
            {
                wpc.currentPath = wpc.movePattern;
                wpc.distance = 0.f;
            }
            continue;
        }

        wpc.distance += spd.current * dt;
        if (wpc.distance > nextPtr->distanceTotal)
            wpc.currentPath = nextPtr;

        sf::Vector2f unitDist;
        unitDist.x = (nextPtr->location.x - headPtr->location.x) / headPtr->distanceToNext;
        unitDist.y = (nextPtr->location.y - headPtr->location.y) / headPtr->distanceToNext;

        sf::Vector2f velocity;
        velocity.x = unitDist.x * spd.current * dt;
        velocity.y = unitDist.y * spd.current * dt;

        float theta = (atan2(velocity.y, velocity.x)) * (180.f / float(std::numbers::pi));
        sp.sprite.setRotation(theta + 90);
        sp.sprite.move(velocity);
    }
}