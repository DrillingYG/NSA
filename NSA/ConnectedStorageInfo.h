#pragma once
#include "LocalConnectionInfo.h"


class ConnectedStorageInfo : public LocalConnectionInfo {
public:
	ConnectedStorageInfo(void);
	void setStorages(void);
	void getStorages(void) const;
	
	std::vector<Storage> ConnectedStorages;
	DWORD numOfConnectedStrages;

};