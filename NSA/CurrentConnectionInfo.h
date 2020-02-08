#pragma once
#include "LocalConnectionInfo.h"


class CurrentConnectionInfo : public LocalConnectionInfo
{
public:
	void setStorages(void);
	void getStorages(void) const;

	std::vector<Storage> curConStorages;
	DWORD numOfcurConStrages;
};

