#include "EmptyScene.hpp"

EmptyScene::EmptyScene(std::shared_ptr<GameData>& data)
	: m_data(data)
{}

EmptyScene::~EmptyScene()
{}

void EmptyScene::Init()
{
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
    if (!m_entity["Player"]->GetComponent<AnimatedSprite>().animator.isPlayingAnimation()) {
        m_entity["Player"]->GetComponent<AnimatedSprite>().animator.playAnimation("idle2");
    }

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

void EmptyScene::BuildEntities() 
{
    InteractableFactory interactableFact(m_data, this);
    NonInteractableFactory nonInteractableFact(m_data, this);

    m_entity["Player"] = interactableFact.CreateEntity(TYPE::PLAYER, m_data->spriteManager.GetTexture("SP_Player"));
    m_entity["Background"] = nonInteractableFact.CreateEntity(TYPE::BACKGROUND, m_data->spriteManager.GetTexture("BG_Space"));
    m_entity["Enemy"] = interactableFact.CreateEntity(TYPE::ENEMY, m_data->spriteManager.GetTexture("SP_Player2"));
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