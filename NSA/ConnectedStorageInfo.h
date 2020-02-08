#pragma once
#include "LocalConnectionInfo.h"


class ConnectedStorageInfo : public LocalConnectionInfo {
public:
	void setStorages(void);
	void getStorages(void) const;

	//std::vector<>
};