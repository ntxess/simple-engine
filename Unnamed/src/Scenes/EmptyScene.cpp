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

}

void EmptyScene::ProcessInput()
{

}

void EmptyScene::Update(const float& deltaTime)
{
    if (!m_entity["Player"]->GetComponent<AnimatedSprite>().animator.isPlayingAnimation()) {
        m_entity["Player"]->GetComponent<AnimatedSprite>().animator.playAnimation("playerIdle");
    }
}

void EmptyScene::Render(sf::RenderWindow& rw, const float& deltaTime, const float& interpolation)
{
    m_entity["Player"]->GetComponent<AnimatedSprite>().Update(sf::seconds(deltaTime));
    m_entity["Player"]->GetComponent<AnimatedSprite>().Animate();

    rw.draw(m_entity["Background"]->GetComponent<Sprite>().sprite);
    rw.draw(m_entity["Player"]->GetComponent<AnimatedSprite>().sprite);
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
            thor::Resources::fromFile<sf::Texture>("resources/Space/PNG/Space_Stars2.png"),
            thor::Resources::Reuse);
        m_data->textureManager.acquire("SP_Player",
            thor::Resources::fromFile<sf::Texture>("resources/player/ship.png"),
            thor::Resources::Reuse);
        m_data->textureManager.acquire("SP_Enemy",
            thor::Resources::fromFile<sf::Texture>("resources/player/triangle.png"),
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

    m_entity["Player"] = interactable->CreateEntity(TYPE::PLAYER);

    sf::IntRect frame1(0, 0, 16, 24);
    sf::IntRect frame2(16, 0, 16, 24);
    sf::IntRect frame3(32, 0, 16, 24);
    sf::IntRect frame4(48, 0, 16, 24);
    sf::IntRect frame5(64, 0, 16, 24);

    thor::FrameAnimation idle;
    idle.addFrame(1.f, frame1);
    idle.addFrame(1.f, frame2);
    idle.addFrame(1.f, frame3);
    idle.addFrame(1.f, frame4);
    idle.addFrame(1.f, frame5);

    m_entity["Player"]->GetComponent<AnimatedSprite>().animator.addAnimation("playerIdle", idle, sf::seconds(5.f));
    

    m_entity["Background"] = nonInteractable->CreateEntity(TYPE::BACKGROUND);
}

void EmptyScene::SetupScene()
{
    m_entity["Player"]->GetComponent<AnimatedSprite>().sprite.setScale(10, 10);
    m_entity["Player"]->GetComponent<AnimatedSprite>().sprite.setPosition(960, 500);
}