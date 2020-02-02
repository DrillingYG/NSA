#pragma once
#include "Common.h"
#include <string>
#include <iostream>
#include <cstdlib>
#include <vector>

#define NAS 0
#define Cloud 1
#define SharedComputer 2

#pragma pack(1)
typedef struct {
	uint8_t storageType;

	std::wstring m_IP;
	std::wstring m_directory;
	std::wstring m_cid;
	std::wstring m_driveLetter;
} currentConnectedStorages;
#pragma pop()

class connectionInfo
{
public:

	void setConnectionType(void);
	void printConnectionInfo(void);
	
private:
	std::vector<currentConnectedStorages> m_curConStorages;

	
};

