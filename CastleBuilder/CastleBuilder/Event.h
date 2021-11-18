#pragma once

#include <functional>
#include <vector>

class EventListener;
class Event
{
public:

	void addListener(EventListener* listener);

	void removeListener(const EventListener* listener)
	{
		auto it = std::find_if(listeners.begin(), listeners.end(), 
			[=](const EventListener* listenerInVector) {

				return listenerInVector == listener;
			});

		if (it != listeners.end())
		{
			listeners.erase(it);
		}
	}

	void removeListeners()
	{
		listeners.clear();
	}

	void operator()();

private:
	std::vector<EventListener*> listeners = {};
};

class EventListener
{
public:
	friend class Event;
	int num = 1;
	EventListener() = default;
	~EventListener()
	{
		if (registeredEvent)
		{
			registeredEvent->removeListener(this);
		}
	}

	EventListener(std::function<void()> function)
	{
		callback = function;
	}

	void execute()
	{
		if (callback)
		{
			callback();
		}
	}


private:
	std::function<void()> callback = nullptr;
	Event* registeredEvent = nullptr;

	void setRegisteredEvent(Event* newEvent)
	{
		registeredEvent = newEvent;
	}
};