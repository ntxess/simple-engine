#include "Engine.hpp"

Engine::Engine(unsigned int width, unsigned int height, std::string title)
    : m_data(std::make_unique<GameData>()), m_aspectRatio(static_cast<float>(width) / height)
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
    sf::Thread gameThread(&Engine::GameThread, this);
    m_data->window.setActive(false);
    gameThread.launch();

    sf::Event event;
    while (m_data->window.waitEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            m_data->window.close();
            break;
        case sf::Event::Resized:
        {
            unsigned int newWidth = event.size.width;
            unsigned int newHeight = static_cast<unsigned int>(newWidth / m_aspectRatio);
            if (newHeight > event.size.height)
            {
                newHeight = event.size.height;
                newWidth = static_cast<unsigned int>(newHeight * m_aspectRatio);
            }
            m_data->window.setSize(sf::Vector2u(newWidth, newHeight));
            m_data->defaultViewPort.setSize(static_cast<float>(newWidth), static_cast<float>(newHeight));
            break;
        }
        default:
            m_data->sceneManager.GetActiveScene()->ProcessEvent(event);
            break;
        }
    }
    gameThread.wait();
}

void Engine::GameThread()
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

