#pragma once

class Event
{
public:
	enum class Type
	{
		Collision,
		PlaySound
	};

	bool handled;

private:
	Type _type;

public:
	Event(Type type);
	~Event();

	Type GetType();
};

