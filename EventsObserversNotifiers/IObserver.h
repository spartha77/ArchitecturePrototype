#pragma once
#ifndef _IOBSERVER_H_
#define _IOBSERVER_H_
#include "EventData.h"
#include <functional>

namespace AdaptiveHumanTracker {

    template<typename ObservableData>
    using EventNotifierType = typename std::function<void(ObservableData&)>;


    // Subbing class definition
    template<typename ObserverDataType>
    class DummyClient
    {
    public:
        DummyClient() {}
        ~DummyClient() {}
        void OnEventNotify(ObserverDataType& observeredData)
        {
            // Do nothing
        }
    };

    template<typename ObservableData>
    class IObserver
    {
    public:
        IObserver() {}
        virtual ~IObserver() {}
        virtual void UpdateAction(ObservableData& data) = 0;
        virtual void SetData(ObservableData& data) = 0;
        virtual ObservableData GetData() = 0;
    };


    template <typename GenericObserverImplWrapper, typename ObservableData>
    class GenericObserver : public IObserver< ObservableData>
    {
    public:
        GenericObserver() {}
        virtual ~GenericObserver() {}
        using GenericObserverImplementer = typename GenericObserverImplWrapper::GenericObserverImplementer;
        using observer_Data_type = typename GenericObserverImplWrapper::observer_data_type;
        //using client_type = typename GenericObserverImplWrapper::client_type;

        virtual void UpdateAction(ObservableData& data) override
        {
            static_cast<GenericObserverImplementer*>(this)->ActuallyUpdateAction(static_cast<observer_Data_type&>(data));
        }
        virtual void SetData(ObservableData& data) override
        {
            static_cast<GenericObserverImplementer*>(this)->ActuallySetData(static_cast<observer_Data_type&>(data));
        }
        virtual ObservableData GetData() override
        {
            return static_cast<GenericObserverImplementer*>(this)->ActuallyGetData();
        }
    };


    
    // GenericObserverImplWrapper holds our typedefs, derived does the rest
    template <typename ObservableDataType, typename ClientType>
    class GenericObserverImplWrapper
    {
    public:
        using observer_data_type = ObservableDataType;
        //using event_notifier_type = EventNotifierType<ObservableDataType>;
        using client_type = ClientType;

        class GenericObserverImplementer : public GenericObserver<GenericObserverImplWrapper, observer_data_type>
        { // GenericObserverImplWrapper is now complete
        private:
            std::unique_ptr<observer_data_type> m_observer_data;
            //std::shared_ptr<client_type> m_client;
            client_type* m_client;
            static client_type m_dummyClient;
            //event_notifier_type m_eventNotifyFunction;

            /*GenericObserverImplementer():m_client(m_dummyClient)
            {
            }*/
            GenericObserverImplementer(client_type& client):m_client(&client)
            {
                //m_client = std::make_shared< client_type>(client);
                //m_eventNotifyFunction = onNotify;
            }
            /*void SetEventNotifyFunction(event_notifier_type& eventNotify)
            {
                m_eventNotifyFunction = eventNotify;
            }*/
            void SetClient(client_type& client_)
            {
                m_client = &client_;
                //GenericObserverImplementer::GenericObserverImplementer(client_);
            }
        public:
           /* static GenericObserverImplementer*
                GetInstance(event_notifier_type& notifyFunc)
            {
                static GenericObserverImplementer __genericObserverImplementer;
                __genericObserverImplementer.SetEventNotifyFunction(notifyFunc);
                return &__genericObserverImplementer;
            }*/

            static GenericObserverImplementer*
                GetInstance(client_type& client)
            {
                static GenericObserverImplementer __genericObserverImplementer(client);
                __genericObserverImplementer.SetClient(client);
                return &__genericObserverImplementer;
            }
            virtual ~GenericObserverImplementer() = default;

            void ActuallyUpdateAction(observer_data_type& data)
            {
                ActuallySetData(data);
                
                if (m_client )
                    m_client->OnEventNotified(data);
            }
            void ActuallySetData(observer_data_type& data)
            {
                m_observer_data.reset(new observer_data_type(data));
            }
            observer_data_type ActuallyGetData()
            {
                return *m_observer_data.get();
            }
        };
    };

    // If you want you can give it a better name
   /* template <typename ObserverDataType, typename ClientType>
    using ConcreteObserver = typename GenericObserverImplWrapper<ObserverDataType, ClientType>::GenericObserverImplementer;*/
}
#endif
