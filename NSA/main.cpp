#include "Common.h"
#include "CurrentConnectionInfo.h"

int main(void) {
	CurrentConnectionInfo testObj;
	testObj.setStorages();
	testObj.getStorages();
	return 0;
}