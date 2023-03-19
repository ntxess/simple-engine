#include "Engine.hpp"

Engine::Engine(unsigned int width, unsigned int height, std::string title)
    : m_data(std::make_unique<GameData>())
{
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 0;
    settings.majorVersion = 4;
    settings.minorVersion = 3;

    m_data->window.create(sf::VideoMode(width, height), title, sf::Style::Default, settings);
    m_data->sceneManager.AddScene(std::make_unique<EmptyScene>(m_data));
}

void Engine::Run()
{
    float newTime, frameTime, interpolation;
    float currentTime = m_clock.getElapsedTime().asSeconds();
    float accumulator = 0.0f;

    while (m_data->window.isOpen())
    {
        newTime = m_clock.getElapsedTime().asSeconds();
        frameTime = newTime - currentTime;
        currentTime = newTime;
        accumulator += frameTime;

        m_data->sceneManager.ProcessSceneChange();

        sf::Event event;
        while (m_data->window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                m_data->window.close();
                break;
            case sf::Event::Resized:
                m_data->defaultViewPort.setSize(float(event.size.width), float(event.size.height));
                break;
            default:
                m_data->sceneManager.GetActiveScene()->ProcessEvent(event);
                break;
            }
        }
        m_data->sceneManager.GetActiveScene()->ProcessInput();

        while (accumulator >= m_deltaTime)
        {
            m_data->sceneManager.GetActiveScene()->Update(m_deltaTime);
            accumulator -= m_deltaTime;
        }

        interpolation = accumulator / m_deltaTime;

        m_data->window.clear();
        m_data->sceneManager.GetActiveScene()->Render(m_data->window, m_deltaTime, interpolation);
        m_data->window.display();
    }
}



