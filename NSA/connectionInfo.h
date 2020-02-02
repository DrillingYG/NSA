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

	void setConnectionType(void);
	
	void printConnectionInfo(void);
	
private:
	uint8_t storageType;

	std::wstring m_IP;
	std::wstring m_directory;
	std::wstring m_cid;
	std::wstring m_driveLetter;
};

