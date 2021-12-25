#pragma once
#ifndef _IOBSERVER_H_
#define _IOBSERVER_H_
#include "EventData.h"

namespace AdaptiveHumanTracker {
	class IObserver
	{

	public:
		IObserver() {}
		virtual ~IObserver() {}
		virtual void UpdateAction() = 0;
		virtual void SetData(void*) = 0;
		virtual void* GetData() = 0;
	};



	/*template <typename Implementer, typename DataType>
	class Observer : public IObserver
	{
	public:
		Observer() {}
		virtual ~Observer() {}
		virtual void SetData(void* data) override
		{
			static_cast<Implementer*>(this)->ActuallySetData(*(static_cast<DataType*>(data)));
		}
		virtual void UpdateAction() override
		{
			static_cast<Implementer*>(this)->ActuallyUpdateAction();
		}
		virtual void* GetData() override
		{
			return (static_cast<Implementer*>(this)->ActuallyGetData());
		}
	};*/

	template < template <typename dtType, typename CLType> class Implementer, typename DataType, typename ClientType>
	class GenericObserver : public IObserver
	{
	public:
		GenericObserver() {}
		virtual ~GenericObserver() {}
		virtual void SetData(void* data) override
		{
			static_cast<Implementer<DataType, ClientType>*>(this)->ActuallySetData(*(static_cast<DataType*>(data)));
		}
		virtual void UpdateAction() override
		{
			static_cast<Implementer<DataType, ClientType>*>(this)->ActuallyUpdateAction();
		}
		virtual void* GetData() override
		{
			return (static_cast<Implementer<DataType, ClientType>*>(this)->ActuallyGetData());
		}
	};


	template <typename DataType, typename ClientType>
	class GenericObserverImpl : public GenericObserver< GenericObserverImpl<DataType, ClientType>, DataType, ClientType>
	{
	private:
		std::unique_ptr<DataType> m_myData;
		ClientType m_someObject;

	public:
		GenericObserverImpl(ClientType& object) {
			m_myData = std::make_unique<DataType>();
			m_someObject = object;
		};
		GenericObserverImpl(const DataType& data) { m_myData = std::make_unique<DataType>(data); };
		virtual ~GenericObserverImpl()
		{
			std::cout << "Destructor of GenericObserverImpl::~GenericObserverImpl()" << std::endl;
		};
		void ActuallySetData(DataType& data) { *m_myData = data; };
		void ActuallyUpdateAction()
		{
			m_someObject.OnEventNotified(*m_myData);
		}
		void* ActuallyGetData()
		{
			return m_myData.get();
		}
	};
		
}


#endif
