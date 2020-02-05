#pragma once

__interface ILocalConnectionInfo
{
	virtual void setStorages(void) abstract;
	virtual void getStorages(void) const abstract;
};

