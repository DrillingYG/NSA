#pragma once
#include "Common.h"
#include <string>
#include <cstdlib>
#include <vector>
#include <regex>

#define NAS 0
#define ONEDRIVE 1
#define SHARED_COMPUTER 2

#pragma pack(push, 1)
typedef struct {
	uint8_t storageType;

	std::wstring m_IP;
	std::wstring m_directory;
	std::wstring m_username;
	std::wstring m_driveLetter;
} currentConnectedStorages;
#pragma pack(pop)

class connectionInfo
{
public:
	void setCurConStorages(void);
	void printCurConStorages(void) const;

	std::vector<currentConnectedStorages> m_curConStorages;
	DWORD m_numOfcurConStrages;
};

