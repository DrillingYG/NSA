#pragma once
#include "Common.h"
#include <string>
#include <cstdlib>
#include <vector>
#include <regex>

#define NAS 0
#define ONEDRIVE 1
#define SHARED_COMPUTER 2

__interface ILocalConnectionInfo
{
	virtual void setStorages(void) abstract;
	virtual void getStorages(void) const abstract;
};

#pragma pack(push, 1)
typedef struct {
	uint8_t storageType;

	std::wstring address = L"";
	std::wstring directory = L"";
	std::wstring ID = L"";
	std::wstring driveLetter = L"";
} currentConnectedStorages;
#pragma pack(pop)

class CurrentConnectionInfo : public ILocalConnectionInfo
{
public:
	void setStorages(void);
	void getStorages(void) const;

	std::vector<currentConnectedStorages> curConStorages;
	DWORD numOfcurConStrages;
};

