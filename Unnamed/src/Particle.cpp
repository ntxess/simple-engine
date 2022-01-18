#include "Particle.hpp"

Particle::Particle()
{}

void Particle::Init()
{

}

void Particle::SetNext(Particle* next)
{
	_state.next = next;
}

Particle* Particle::GetNext() const
{
	return _state.next;
}