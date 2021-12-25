// FaceBodyDetectTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <ProtoLib.h>
#include <OpenVINOLib.h>
#include <EventsObserversNotifiers.h>
#include <EventData.h>
#include <AdaptiveHumanTracker::IObserver.h>
#include <EventHandler.h>
#include <Events.h>
#include <ObserverImpl.h>
#include <ObserverFactory.h>
#include <MyTest.h>

struct MyData
{
    int aa;
};

// Some class used by programmer
class SomeClass
{
public:
    SomeClass() {};
    ~SomeClass() {}
    void OnEventNotified(MyData& data)
    {
        std::cout << "Observation successful in SomeClass::OnEventNotified()" << std::endl;
        std::cout << "Data now is\t" << data.aa << std::endl;
        return;
    }
};

//template <typename EventDataType, typename ClientType>
//class MyObserverImpl : public Observer< MyObserverImpl<EventDataType, ClientType>, EventDataType>
//{
//private:
//    std::unique_ptr<EventDataType> m_myData;
//    ClientType m_someObject;
//
//public:
//    MyObserverImpl(ClientType& object) {
//        m_myData = std::make_unique<EventDataType>();
//        m_someObject = object;
//    };
//    MyObserverImpl(const EventDataType& data) { m_myData = std::make_unique<EventDataType>(data); };
//    virtual ~MyObserverImpl() {};
//    void ActuallySetData(EventDataType data) { *m_myData = data; };
//    void ActuallyUpdateAction() {
//        m_someObject.OnEventNotified(*m_myData);
//    }
//    void* ActuallyGetData()
//    {
//        return m_myData.get();
//    }
//};


int main()
{
    // Use CProtoLib class exported from PROTOLIB.DLL
    /*COpenVINOLib openvinolib;
    CEventsObserversNotifiers obs;*/

    // Event handler subscription
    Event myEvent = Event::WORK_STARTED; 
    MyData myData = { 10 };    
    auto *eventHandler = AdaptiveHumanTracker::EventHandler<Event, MyData>::GetInstance(myEvent);

    SomeClass someClass;
    //AdaptiveHumanTracker::IObserver* observer1 = new GenericObserverImpl<MyData, SomeClass>(someClass);
    std::unique_ptr<AdaptiveHumanTracker::IObserver> uObs = ObserverFactory<MyData, SomeClass>::CreateObserver(someClass);

    eventHandler->Subscribe(uObs.get());

    
    // Later
    myData.aa = 20;
    eventHandler->Notify(myData);



    // Test

    CMyTest myTest;
    std::cout << "\n\nHello World!\n";

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
