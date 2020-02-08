#pragma once
#include "Common.h"
#include <string>
#include <cstdlib>
#include <vector>
#include <regex>

#define MAX_KEY_NAME_LENGTH 512
#define MAX_VALUE_NAME_LENGTH 64
#define DATA_LEN 512

#define NAS 0
#define ONEDRIVE 1
#define SHARED_COMPUTER 2

#pragma pack(push, 1)
typedef struct {
	uint8_t storageType;

	std::wstring address = L"";
	std::wstring directory = L"";
	std::wstring ID = L"";
	std::wstring driveLetter = L"";
} Storage;
#pragma pack(pop)

class LocalConnectionInfo abstract{
public:

	virtual ~LocalConnectionInfo() {};
	virtual void setStorages(void) abstract;
	virtual void getStorages(void) const abstract;
};

