#include "Event.h"

void Event::operator()()
{
	for (auto* listener : listeners)
	{
		listener->execute();
	}
}

void Event::addListener(EventListener* listener)
{
	listener->setRegisteredEvent(this);
	listeners.push_back(listener);
}