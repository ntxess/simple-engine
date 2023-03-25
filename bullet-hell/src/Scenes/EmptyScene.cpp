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
    SetupSystems();
}

void EmptyScene::ProcessEvent(const sf::Event& event)
{

}

void EmptyScene::ProcessInput()
{
    auto& controller = m_entity["Player"]->GetComponent<PlayerInput>();

    const float input = 1.f;
    controller.direction = sf::Vector2f(0, 0);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        controller.direction.y -= input;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        controller.direction.x -= input;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        controller.direction.y += input;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        controller.direction.x += input;
}

void EmptyScene::Update(const float& deltaTime)
{
    //if (!m_entity["Player"]->GetComponent<AnimatedSprite>().animator.isPlayingAnimation()) {
    //    m_entity["Player"]->GetComponent<AnimatedSprite>().animator.playAnimation("playerIdle");
    //}

    m_system.GetSystem<InputSystem>()->Update(deltaTime, m_reg, m_entity["Player"]->GetHandle());
    m_system.GetSystem<WaypointSystem>()->Update(deltaTime, m_reg);
    m_system.GetSystem<AnimationSystem>()->Update(deltaTime, m_reg);
}

void EmptyScene::Render(sf::RenderWindow& rw, const float& deltaTime, const float& interpolation)
{
    m_system.GetSystem<RenderSystem>()->Render(rw, m_reg);
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
    m_entity["Player"]->GetComponent<AnimatedSprite>().sprite.setPosition(960, 500);
    m_entity["Enemy"]->GetComponent<AnimatedSprite>().sprite.setPosition(200, 500);
}

void EmptyScene::SetupSystems()
{
    m_system.AddSystem<InputSystem>();
    m_system.AddSystem<WaypointSystem>();
    m_system.AddSystem<AnimationSystem>();
    m_system.AddSystem<RenderSystem>();
}