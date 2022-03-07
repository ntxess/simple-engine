#include "Particle.hpp"

Particle::Particle() : _inUse(false)
{}

void Particle::Init()
{

}

void Particle::SetNext(Particle* next)
{
	_state.next = next;
}

void Particle::Update(float deltaTime)
{
	//if(_inUse)
		
}

bool Particle::Animate(float deltaTime)
{
	return false;
}

bool Particle::Render(RenderWindowRef& rw, float interpolation)
{
	return false;
}

Particle* Particle::GetNext() const
{
	return _state.next;
}