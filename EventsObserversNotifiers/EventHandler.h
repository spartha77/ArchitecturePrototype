#pragma once
#ifndef _IEVENTHANDLER_H_
#define _IEVENTHANDLER_H_
#include <set>
#include <map>
#include "IObserver.h"
#include "Events.h"
#include "EventData.h"
#include "ObserverFactory.h"



namespace AdaptiveHumanTracker {
	template<typename EventType, typename DataType>
	class EventHandler //: public IEventNotifier
	{
	private:

		EventData<EventType, DataType> m_eventData;
		std::set<AdaptiveHumanTracker::IObserver<DataType>*> m_observers;
		
		EventHandler() {}
		EventHandler(EventType& eventt, DataType& data)
		{
			SetEventData(eventt, data);
		}
		EventHandler(EventType& eventt)
		{
			SetEvent(eventt);
		}


	public:

		static EventHandler<EventType, DataType>*
			GetInstance(EventType& eventt, DataType& data)
		{
			static EventHandler<EventType, DataType> __eventHandler(eventt, data);
			return &__eventHandler;
		}
		static EventHandler<EventType, DataType>*
			GetInstance(EventType& eventt)
		{
			static EventHandler<EventType, DataType> __eventHandler(eventt);
			return &__eventHandler;
		}

		template<typename ClientType>
		static void Register(EventType& eventt, ClientType& client)
		{
			auto* eventHandler = EventHandler<EventType, DataType>::GetInstance(eventt);
			auto* observer = ObserverFactory::GetObserverInstance<DataType, ClientType>(client);
			eventHandler->Subscribe(observer);
		}

		template<typename ClientType>
		static void UnRegister(EventType& eventt, ClientType& client)
		{
			auto* eventHandler = EventHandler<EventType, DataType>::GetInstance(eventt);
			auto* observer = ObserverFactory::GetObserverInstance<DataType, ClientType>(client);
			
			eventHandler->Unsubscribe(observer);
		}

		static void Notify(EventType& eventt, DataType& data)
		{
			auto* eventHandler = EventHandler<EventType, DataType>::GetInstance(eventt);
			eventHandler->Notify(data);
		}



		void SetEventData(EventType& eventt, DataType& data)
		{
			m_eventData.Set(eventt, data);
		}
		void SetEvent(EventType& eventt)
		{
			m_eventData.SetEvent(eventt);
		}
		~EventHandler() {};

		void Notify(DataType& data)
		{
			m_eventData.SetData(data);
			for (auto observer : m_observers)
			{	
				observer->UpdateAction(data);
			}
		}

		void Subscribe(AdaptiveHumanTracker::IObserver<DataType>* observer)
		{
			m_observers.insert(observer);
		}

		void Unsubscribe(AdaptiveHumanTracker::IObserver<DataType>* observer)
		{
			auto erasableIterator = std::find(m_observers.begin(), m_observers.end(), observer);
			m_observers.erase(erasableIterator);
		}
	};

}
#endif
