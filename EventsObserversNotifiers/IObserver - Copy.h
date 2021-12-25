#pragma once
#ifndef _IOBSERVER_H_
#define _IOBSERVER_H_
#include "EventData.h"
//
//namespace AdaptiveHumanTracker {
//	class IObserver
//	{
//
//	public:
//		IObserver() {}
//		virtual ~IObserver() {}
//		virtual void UpdateAction() = 0;
//		virtual void SetData(void*) = 0;
//		virtual void* GetData() = 0;
//	};
//
//
//
//	template <typename Implementer, typename DataType>
//	class Observer : public IObserver
//	{
//	public:
//		Observer() {}
//		virtual ~Observer() {}
//		virtual void SetData(void* data) override
//		{
//			static_cast<Implementer*>(this)->ActuallySetData(*(static_cast<DataType*>(data)));
//		}
//		virtual void UpdateAction() override
//		{
//			static_cast<Implementer*>(this)->ActuallyUpdateAction();
//		}
//		virtual void* GetData() override
//		{
//			return (static_cast<Implementer*>(this)->ActuallyGetData());
//		}
//	};
//
//	template < template <typename dtType, typename CLType> class Implementer, typename DataType, typename ClientType>
//	class GenericObserver : public IObserver
//	{
//	public:
//		GenericObserver() {}
//		virtual ~GenericObserver() {}
//		virtual void SetData(void* data) override
//		{
//			static_cast<Implementer<DataType, ClientType>*>(this)->ActuallySetData(*(static_cast<DataType*>(data)));
//		}
//		virtual void UpdateAction() override
//		{
//			static_cast<Implementer<DataType, ClientType>*>(this)->ActuallyUpdateAction();
//		}
//		virtual void* GetData() override
//		{
//			return (static_cast<Implementer<DataType, ClientType>*>(this)->ActuallyGetData());
//		}
//	};
//}


namespace AdaptiveHumanTracker {
	class IObserver
	{

	public:
		IObserver() {}
		virtual ~IObserver() {}
		virtual void UpdateAction() = 0;
		virtual void SetData(void*) = 0;
		//virtual void* GetData() = 0;
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

	// Declare a GenericObserver_traits traits class
	//template < template <typename DtType, typename CLType> class Implementer, typename DataType, typename ClientType>
	//class GenericObserver_traits;
	template <typename DataType, typename ClientType>
	class GenericObserver_Traits;


	// Define the base class that uses the GenericObserver_traits

	template < template <typename DtType, typename CLType> class Implementer >
	class GenericObserver : public IObserver
	{
	public:
		GenericObserver() {}
		virtual ~GenericObserver() {}
		void GenericObserverSetData(void* data)
		{
			GenericObserver_traits<Implementer>::Call_ActuallySetData(static_cast<Implementer*>(this), *(static_cast<GenericObserver_traits<Implementer>::DataType*>(data)));
		}
		void GenericObserverUpdateAction()
		{
			GenericObserver_traits<Implementer>::Call_ActuallyUpdateAction(static_cast<Implementer*>(this));
		}
		/*void* GenericObserverGetData()
		{
			return GenericObserver_traits<DataType, ClientType>::Call_ActuallyGetData(static_cast<Implementer*>(this));
		}*/

		virtual void SetData(void* data) override
		{
			GenericObserverSetData(data);
			//static_cast<Implementer*>(this)->ActuallySetData(*(static_cast<DataType*>(data)));
			//static_cast<Implementer*>(this)->CallTo_ActuallySetData(data);
		}
		virtual void UpdateAction() override
		{
			GenericObserverUpdateAction();
			//static_cast<Implementer*>(this)->ActuallyUpdateAction();
			//static_cast<Implementer*>(this)->CallTo_ActuallyUpdateAction();
		}
		//virtual void* GetData() override
		//{
		//	//return GenericObserverGetData();
		//	//return (static_cast<Implementer*>(this)->ActuallyGetData());
		//	return static_cast<Implementer*>(this)->CallTo_ActuallyGetData();
		//}

	};

	// Define the derived class GenericObserverImpl; it can use the traits too:
	template < typename DtType, typename CLType>
	class GenericObserverImpl : public GenericObserver<GenericObserverImpl>
	{
	private:
		std::unique_ptr<DataType> m_myData;
		CLType m_someObject;
		 

	public:

		typedef GenericObserverImpl<DtType, CLType> Implementer_Type;
		typedef CLType ClientType;
		typedef DtType DataType;

		GenericObserverImpl(ClientType& object) {
			m_myData = std::make_unique<DataType>();
			m_someObject = object;
		};
		GenericObserverImpl(const DataType& data) { m_myData = std::make_unique<DataType>(data); };
		virtual ~GenericObserverImpl()
		{
			std::cout << "Destructor of GenericObserverImpl::~GenericObserverImpl()" << std::endl;
		};
		/*void CallTo_ActuallySetData(void* data)
		{
			static_cast<GenericObserverImpl*>(this)->ActuallySetData(*(static_cast<DataType*>(data)));
		}
		void CallTo_ActuallyUpdateAction()
		{
			static_cast<GenericObserverImpl*>(this)->ActuallyUpdateAction();
		}
		void* CallTo_ActuallyGetData()
		{
			static_cast<GenericObserverImpl*>(this)->ActuallyGetData();
		}*/
		void ActuallySetData(DataType& data) 
		{ 
			*m_myData = data; 
		};
		void ActuallyUpdateAction()
		{
			m_someObject.OnEventNotified(*m_myData);
		}
		/*void* ActuallyGetData()
		{
			return m_myData.get();
		}*/
	};
	template<typename DataType, typename ClientType>
	class SubTraits
	{
	public:
		using typeNew = GenericObserverImpl<DataType, ClientType>;
	};

	template <class Impl>
	class GenericObserver_Traits<GenericObserverImpl<DataType, ClientType>>
	{
	public:
		using ImplType = GenericObserverImpl< DataType, ClientType>::Implementer_Type;
		using DataType = GenericObserverImpl< DataType, ClientType>::DataType;
		using ClientType = GenericObserverImpl< DataType, ClientType>::ClientType;

		static void Call_ActuallySetData(ImplType* impl, DataType& data)
		{
			impl->ActuallySetData(data);
		}
		static void Call_ActuallyUpdateAction(ImplType* impl)
		{
			impl->ActuallyUpdateAction();
		}
		static void* Call_ActuallyGetData(ImplType* impl)
		{
			return impl->ActuallyGetData();
		}

		/*typedef int IntType;
		typedef float FloatType;*/
	};
	//// Declare and define a base_traits specialization for derived:
	//template < template <typename DtType, typename CLType> class Implementer, typename DataType, typename ClientType>
	//class GenericObserver_traits<GenericObserverImpl, DataType, ClientType>
	//{
	//public:
	//	GenericObserver_traits() {}
	//	~GenericObserver_traits() {}
	//	static void Call_ActuallySetData(GenericObserverImpl<DataType, ClientType>* impl, DataType& data)
	//	{
	//		impl->ActuallySetData(data);
	//	}
	//	static void Call_ActuallyUpdateAction(GenericObserverImpl<DataType, ClientType>* impl)
	//	{
	//		impl->ActuallyUpdateAction();
	//	}
	//	static void* Call_ActuallyGetData(GenericObserverImpl<DataType, ClientType>* impl)
	//	{
	//		return impl->ActuallyGetData();
	//	}

	//};
}
#endif
