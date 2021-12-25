#pragma once
#include <memory>
#include "IObserver.h"
#include "ObserverImpl.h"

namespace AdaptiveHumanTracker {
	
	class ObserverFactory
	{
	private:
		ObserverFactory() {}
	public:
		
		template<typename ObserverDataType, typename ClientType>
		static AdaptiveHumanTracker::IObserver<ObserverDataType>* GetObserverInstance(ClientType& client)
		{
			
			AdaptiveHumanTracker::IObserver<ObserverDataType>* observer = AdaptiveHumanTracker::GenericObserverImplWrapper<ObserverDataType, ClientType>::GenericObserverImplementer::GetInstance(client);
			return observer;
		}
	};
}
