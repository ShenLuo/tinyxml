/*
	windows的xml格式日志的处理
*/

#ifndef _WINEVENTHANDLE_H_
#define _WINEVENTHANDLE_H_

#include <vector>

class  WinEeventHandle
{
	// 时间
	class TimeStruct
	{
	public:
		TimeStruct()
		{
			nYear=0,nMonth=0,nDay=0;
			nHour=0,nMinute=0,nSecond=0;
		}

		TimeStruct(const TimeStruct& val)
		{
			nYear=val.nYear,nMonth=val.nMonth,nDay=val.nDay;
			nHour=val.nHour,nMinute=val.nMinute,nSecond=val.nSecond;
		}

		int nYear,nMonth,nDay;
		int nHour,nMinute,nSecond;
	};

	// 事件
	class WinEvent
	{
	public:
		WinEvent():tsValue()
		{
			nEventId = 0;
		}

		WinEvent(const WinEvent& val):nEventId(val.nEventId),tsValue(val.tsValue)
		{
		}

		~WinEvent(){}

		TimeStruct tsValue;
		int nEventId;
	};

public:
	WinEeventHandle(const char* sFilePath):m_sFilePath(sFilePath){}
	~ WinEeventHandle(){}

	bool LoadFile();

	float GetHours();

private:
	void TimeStrToStruct(const char* str, TimeStruct& ts);

private:
	std::string m_sFilePath;
	std::vector<WinEvent> m_vEvent;
};

#endif