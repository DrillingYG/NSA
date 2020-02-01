#pragma once
#include "Common.h"
#include <string>
#include <iostream>
#include <cstdlib>
#include <cstdio>

#define NAS 0
#define Cloud 1
#define SharedComputer 2

class connectionInfo
{
public:

	void setConnectionType(void) {
		//RegGetValueW(HKEY_CURRENT_USER, L"\Software\Microsoft\Windows\CurrentVersion\Explorer\Map Network Drive MRU");
		//RegGetValueW(HKEY_CURRENT_USER, L"\Software\Microsoft\Windows\CurrentVersion\Explorer\MountPoints2\##[IP]#[Directory]");
		//RegGetValueW(HKEY_CURRENT_USER, L"\Network");

		LONG Result = 0;
		DWORD index = 0;
		WCHAR namebuf[256];
		DWORD buflen = 255;
		PHKEY hsubkey = NULL;

		while (!Result) {
			wmemset(namebuf, 0, 256);
			Result = RegEnumKeyExW(HKEY_CURRENT_USER, index, namebuf, &buflen, NULL, NULL, NULL, NULL);
			std::cout << "Index : " <<  index << std::endl;;
			//std::cout << namebuf << std::endl;
			wprintf(L"namebuf : %s\n", namebuf);
			std::cout << "key length : " << buflen << std::endl;
			
		}
	}
	
	void printConnectionInfo(void) {
		switch (storageType) {
		case NAS:

			break;
		case Cloud:

			break;
		case SharedComputer:

			break;
		default:
			std::cerr << "Storage type is not defined\n";
		}
	}
	
private:
	uint8_t storageType;

	std::wstring m_IP;
	std::wstring m_directory;
	std::wstring m_cid;
	std::wstring m_driveLetter;
};

