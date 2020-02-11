#pragma once
#include "LocalConnectionInfo.h"

class CurrentConnectionInfo : public LocalConnectionInfo
{
public:
	CurrentConnectionInfo();
	void setStorages(void);
	void getStorages(void) const;
	void mapCidToID(const std::wstring& cid);

	std::vector<Storage> curConStorages;
	DWORD numOfcurConStrages;
	std::map<std::wstring, std::wstring> cids;
};

