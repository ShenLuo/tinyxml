/*
	windows的xml格式日志的处理
*/

#include "stdafx.h"
#include "WinEventHandle.h"
#include "../tinyxml/tinyxml.h"
#include <time.h>

bool WinEeventHandle::LoadFile()
{
	if (strcmp(m_sFilePath.c_str(), "") == 0)
	{
		return false;
	}

	// xml文件
	TiXmlDocument temp;
	if (!temp.LoadFile(m_sFilePath.c_str()))
	{
		return false;
	}

	// events结点
	const TiXmlElement* tempEvents = temp.RootElement();
	if (NULL == tempEvents)
	{
		return false;
	}

	// event结点
	const TiXmlElement* tempEvent = (const TiXmlElement*)tempEvents->FirstChild();
	while (tempEvent)
	{
		// event结点
		WinEvent weTemp;
		const TiXmlElement* tempSystem = 
					(const TiXmlElement*)tempEvent->FirstChild("System");
		if (tempSystem)
		{
			// eventID
			const TiXmlElement* tempEventID =
					(const TiXmlElement*) tempSystem->FirstChild("EventID");
			if (tempEventID)
			{
				std::string sTempVal = tempEventID->GetText();
				weTemp.nEventId = atoi(sTempVal.c_str());
			}

			// eventTime
			const TiXmlElement* tempEventTime = 
					(const TiXmlElement*)tempSystem->FirstChild("TimeCreated");
			if (tempEventTime)
			{
				std::string sTempVal = tempEventTime->Attribute("SystemTime");
				TimeStrToStruct(sTempVal.c_str(), weTemp.tsValue);
			}

			m_vEvent.push_back(weTemp);
		}

		// 下一次event结点
		tempEvent = (const TiXmlElement*)tempEvent->NextSibling();
	}

	return true;
}

float WinEeventHandle::GetHours()
{
	float fHours = 0.0f;
	for (int i = 0; i < m_vEvent.size(); i++)
	{
		WinEvent temp = m_vEvent[i];
		tm temptm;
		temptm.tm_year = temp.tsValue.nYear - 1900;
		temptm.tm_mon = temp.tsValue.nMonth - 1;
		temptm.tm_mday = temp.tsValue.nDay;

		temptm.tm_hour = temp.tsValue.nHour;
		temptm.tm_min = temp.tsValue.nMinute;
		temptm.tm_sec = temp.tsValue.nSecond;
		time_t temptime_t = mktime(&temptm);
		tm tempnewtm;
		localtime_s(&tempnewtm, &temptime_t);

		// 18:30 开始计算
		if (tempnewtm.tm_hour > 18)
		{
			fHours += (tempnewtm.tm_hour - 18);
			if (tempnewtm.tm_min < 29)
			{
				fHours -= 0.5f;
			}
		}

		if (tempnewtm.tm_wday == 0 || tempnewtm.tm_wday == 6)
		{
			// 周末
			fHours += 8.0f;
		}
	}

	return fHours;
}

void WinEeventHandle::TimeStrToStruct(const char* str, TimeStruct& ts)
{
	std::string temp(str);
	std::string t1 = temp.substr(0,4);
	ts.nYear = atoi(t1.c_str());
	t1 = temp.substr(5,2);
	ts.nMonth = atoi(t1.c_str());
	t1 = temp.substr(8,2);
	ts.nDay = atoi(t1.c_str());

	t1 = temp.substr(11,2);
	ts.nHour = atoi(t1.c_str());
	ts.nHour += 8;
	t1 = temp.substr(14,2);
	ts.nMinute = atoi(t1.c_str());
	t1 = temp.substr(17,2);
	ts.nSecond = atoi(t1.c_str());
}