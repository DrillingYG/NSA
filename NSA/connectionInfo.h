#pragma once
#include "Common.h"
#include <string>
#include <iostream>

#define NAS 0
#define Cloud 1
#define SharedComputer 2

class connectionInfo
{
	void setConnectionType(void) {

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

