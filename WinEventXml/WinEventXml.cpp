// WinEventXml.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "tinyxml/tinyxml.h"
#include <string>

int _tmain(int argc, _TCHAR* argv[])
{
	// xml文件
	TiXmlDocument temp;
	bool bLoad = temp.LoadFile("D:/编程代码\\WinEventXml\\Debug\\xmlfiles\\3333.xml");
	const TiXmlElement* tempEvents = temp.RootElement();

	// events结点
	const TiXmlElement* tempEvent = (const TiXmlElement*)tempEvents->FirstChild();
	while (tempEvent )
	{
		// event结点

		const TiXmlNode* tempSystem = tempEvent->FirstChild("System");
		if (tempSystem)
		{
			const TiXmlNode* tempEventID = tempSystem->FirstChild("EventID");
			if (tempEventID)
			{
				std::string sTempVal = tempEventID->Value();
				int i = 0;
			}
		}
		
		// 下一次event结点
		tempEvent = (const TiXmlElement*)tempEvent->NextSibling();
	}
	return 0;
}

