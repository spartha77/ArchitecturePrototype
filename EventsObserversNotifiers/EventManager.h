#pragma once
#ifndef _EVENTMANAGER_H_
#define _EVENTMANAGER_H_
#include <map>
#include <vector>
#include <string>
#include "EventsObserversNotifiers.h"
#include "Events.h"
#include "EventHandler.h"


class EVENTSOBSERVERSNOTIFIERS_API EventManager
{
public:
	static EventManager& GetInstance()
	{
		static EventManager __eventManager;
		return __eventManager;
	}

	

private:
	EventManager() = default;
	~EventManager() = default;
	EventManager(const EventManager&) = delete;
	EventManager& operator=(const EventManager&) = delete;

	
};

#endif
