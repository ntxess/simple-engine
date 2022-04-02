#include "DebugScene.hpp"

DebugScene::DebugScene(std::shared_ptr<GameData> &data) :_data(data) 
{}

DebugScene::~DebugScene()
{}

void DebugScene::Init()
{
    _background   = std::make_unique<GameObject>(_data->_holder, "Background");
    _particlePool = std::make_unique<GameObjectPool<Particle>>(_data->_holder, "Shot");
    _player = std::make_unique<Player>(_data->_holder, "Ship");
}

void DebugScene::ProcessEvent(sf::Event event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Escape)
            _data->_machine->AddState(std::make_unique<MainMenu>(_data));
    }
}

void DebugScene::ProcessInput(sf::Event event)
{ 
    _player->InputUpdate(event);
}

void DebugScene::Update(float deltaTime)
{
    _background->Update(deltaTime);
    _player->PhysicsUpdate(deltaTime);
    CheckBoundary(_player);
    //_player->Update(deltaTime);
    //if (_player->_isShooting)
    //    SpawnShotParticle();

    //CheckBoundary(_player->GetComponent());

    //auto assetStart = _assets.begin();
    //for (int i = 0; i < _assets.size(); i++)
    //{
    //    _assets[i]->Update(deltaTime);
    //    _assets[i]->GetInput()->Update(sf::Vector2f(0, -1));
    //    CheckBoundary(_assets[i]);
    //}

    //if (!_player->IsAlive())
    //{
    //    _data->_machine->AddState(std::make_unique<MainMenu>(_data));
    //}
}

void DebugScene::Render(RenderWindowRef& rw, float deltaTime, float interpolation)
{
    _background->Render(rw, interpolation);

    _fps.Update();
    _fps.Render(rw);
    _player->GraphicsUpdate(rw, deltaTime, interpolation);

    //for (int i = 0; i < _assets.size(); i++)
    //    _assets[i]->Render(rw, interpolation);
}

void DebugScene::CheckBoundary(PlayerRef& player)
{
    sf::Vector2f position = player->GetGraphics()->GetSprite().getPosition();
    sf::FloatRect rect = player->GetGraphics()->GetSprite().getGlobalBounds();
    sf::Vector2u bounds = _data->_window->getSize();

    if ((position.x < 0) ||
        (position.y < 0) ||
        (position.x + rect.width  > bounds.x) ||
        (position.y + rect.height > bounds.y))
    {
        player->Rebound();
    }
}

bool DebugScene::CheckCollision(GameObjectRef& playerComponent, GameObjectRef& object)
{
    if (object->GetPhysics())
    {
        if (playerComponent->GetSprite().getGlobalBounds().intersects(object->GetSprite().getGlobalBounds()))
        {
            object->SetTouchTag(true);
        }
    }
    return false;
}

void DebugScene::SpawnShotParticle()
{
    //sf::Vector2f position = _player->GetComponent()->GetPosition();
    //GameObjectRef shotParticle = std::make_unique<ShotParticle>(_data->_holder, position);
    //_assets.push_back(std::move(shotParticle));
    //_player->Shoot(false);
}

void DebugScene::Pause()
{
}

void DebugScene::Resume()
{
}

