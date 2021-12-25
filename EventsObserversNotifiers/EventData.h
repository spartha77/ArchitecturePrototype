#pragma once
#ifndef _IEVENTDATA_H_
#define _IEVENTDATA_H_
#include <memory>

template<typename EventType, typename DataType>
class EventData
{
private:
	std::unique_ptr<DataType> m_EventData;
	std::unique_ptr<EventType> m_Event;
public:
	EventData() 
	{ 
		
		m_Event = std::unique_ptr<EventType>(new EventType());
		
		m_EventData = std::unique_ptr<DataType>(new DataType());
	}
	EventData(EventType eventt, DataType data) 
	{ 
		
		m_Event = std::unique_ptr<EventType>(new EventType(eventt));
		
		m_EventData = std::unique_ptr<DataType>(new DataType(data));
	}
	~EventData() {}
	void Set(EventType& eventt, DataType& data)
	{
		*m_Event = eventt;
		*m_EventData = data;
	}
	void SetData(const DataType& data)
	{
		*m_EventData = data;
	}
	void SetEvent(const EventType& event)
	{
		*m_Event = event;
	}
	DataType GetData()
	{
		return *m_EventData.get();
	}

};

#endif
