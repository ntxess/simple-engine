#include "Engine.hpp"

Engine::Engine(unsigned int width, unsigned int height, std::string title)
    : _data(std::make_unique<GameData>())
    , _width(width)
    , _height(height)
{
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 0;
    settings.majorVersion = 4;
    settings.minorVersion = 3;

    _data->_window->create(sf::VideoMode(width, height), title, sf::Style::Titlebar | sf::Style::Close, settings);
    
    try
    {
        _data->_holder.acquire("Prototype",
            thor::Resources::fromFile<sf::Texture>("resources/Space/PNG/Space_Stars2.png"),
            thor::Resources::Reuse);
        _data->_holder.acquire("Ship", 
            thor::Resources::fromFile<sf::Texture>("resources/player/ship0.png"), 
            thor::Resources::Reuse);
        _data->_holder.acquire("Shot", 
            thor::Resources::fromFile<sf::Texture>("resources/player/shotParticle.png"), 
            thor::Resources::Reuse);
        _data->_holder.acquire("bar01",
            thor::Resources::fromFile<sf::Texture>("resources/ui/ProgressBar_01/BarV1_Bar.png"),
            thor::Resources::Reuse);
        _data->_holder.acquire("progressbar01",
            thor::Resources::fromFile<sf::Texture>("resources/ui/ProgressBar_01/BarV1_ProgressBar.png"),
            thor::Resources::Reuse);
        _data->_holder.acquire("progressbarborder01",
            thor::Resources::fromFile<sf::Texture>("resources/ui/ProgressBar_01/BarV1_ProgressBarBorder.png"),
            thor::Resources::Reuse);
        _data->_holder.acquire("TankTop",
            thor::Resources::fromFile<sf::Texture>("resources/player/tank_top.png"),
            thor::Resources::Reuse);
        _data->_holder.acquire("TankBot",
            thor::Resources::fromFile<sf::Texture>("resources/player/tank_bot.png"),
            thor::Resources::Reuse);
        _data->_holder.acquire("TankTurret",
            thor::Resources::fromFile<sf::Texture>("resources/player/tank_turret.png"),
            thor::Resources::Reuse);
    }
    catch (thor::ResourceLoadingException& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }

    std::unique_ptr<MCircle> mCircle = std::make_unique<MCircle>();
    std::unique_ptr<MRandom> mRandom = std::make_unique<MRandom>();
    std::unique_ptr<MStraight> mStraight = std::make_unique<MStraight>();

    _data->_pathMap["mCircle"] = std::move(mCircle->head);
    _data->_pathMap["mRandom"] = std::move(mRandom->head);
    _data->_pathMap["mStraight"] = std::move(mStraight->head);

    _data->_machine->AddState(std::make_unique<MainMenu>(_data));
}

Engine::~Engine()
{}

void Engine::Run()
{
    float newTime, frameTime, interpolation;
    float currentTime = _clock.getElapsedTime().asSeconds();
    float accumulator = 0.0f;

    while (_data->_window->isOpen())
    {
        newTime = _clock.getElapsedTime().asSeconds();
        frameTime = newTime - currentTime;
        currentTime = newTime;
        accumulator += frameTime;

        _data->_machine->ProcessStateChange();

        // Input/Event Block
        sf::Event event;
        while (_data->_window->pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                _data->_window->close();
                break;
            case sf::Event::Resized:
                _data->_focusedView.setSize(float(event.size.width), float(event.size.height));
                break;
            default:
                _data->_machine->GetActiveState()->ProcessEvent(event);
            }
        }
        _data->_machine->GetActiveState()->ProcessInput();

        // Update Block
        while (accumulator >= deltaTime)
        {
            _data->_machine->GetActiveState()->Update(deltaTime);
            accumulator -= deltaTime;
        }
        _data->_animator.update(sf::seconds(deltaTime));

        interpolation = accumulator / deltaTime;

        // Render Block
        _data->_window->clear();
        _data->_machine->GetActiveState()->Render(_data->_window, deltaTime, interpolation);
        _data->_window->display();
    }

    ImGui::SFML::Shutdown();
}



