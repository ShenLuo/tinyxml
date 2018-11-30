// WinEventXml.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "tinyxml/tinyxml.h"
#include "winevent/WinEventHandle.h"
#include <string>
#include <libloaderapi.h>

std::string getExePath()
{
	char spath[128] = {0};
	GetModuleFileNameA(NULL, spath, 128);
	std::string temp(spath);
	int pos = temp.find_last_of("\\");
	std::string result = temp.substr(0, pos);
	result += "\\..\\";
	return result.c_str();
}

int _tmain(int argc, _TCHAR* argv[])
{
	std::string sPath = getExePath().c_str();
	sPath += "Res\\xmlfile.xml";
	WinEeventHandle xmlfile(sPath.c_str());
	xmlfile.LoadFile();
	xmlfile.GetHours();
	return 0;
}

