// WinEventXml.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "tinyxml/tinyxml.h"
#include <string>

int _tmain(int argc, _TCHAR* argv[])
{
	// xml�ļ�
	TiXmlDocument temp;
	bool bLoad = temp.LoadFile("D:/��̴���\\WinEventXml\\Debug\\xmlfiles\\3333.xml");
	const TiXmlElement* tempEvents = temp.RootElement();

	// events���
	const TiXmlElement* tempEvent = (const TiXmlElement*)tempEvents->FirstChild();
	while (tempEvent )
	{
		// event���

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
		
		// ��һ��event���
		tempEvent = (const TiXmlElement*)tempEvent->NextSibling();
	}
	return 0;
}

