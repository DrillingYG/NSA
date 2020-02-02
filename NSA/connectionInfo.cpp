#include "connectionInfo.h"


void connectionInfo::setConnectionType(void) {
#define MAX_KEY_NAME_LENGTH 255

	//RegGetValueW(HKEY_CURRENT_USER, L"\Software\Microsoft\Windows\CurrentVersion\Explorer\Map Network Drive MRU");
	//RegGetValueW(HKEY_CURRENT_USER, L"\Software\Microsoft\Windows\CurrentVersion\Explorer\MountPoints2\##[IP]#[Directory]");
	//RegGetValueW(HKEY_CURRENT_USER, L"\Network");
	HKEY hkeyNetwork;
	DWORD numOfSubkeys;
	RegOpenKeyExW(HKEY_CURRENT_USER, L"Network", 0, KEY_READ, &hkeyNetwork);
	RegQueryInfoKey(hkeyNetwork, NULL, 0, 0, &numOfSubkeys, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
	if (numOfSubkeys > 0) {
		DWORD retCode = 0;
		DWORD nameLength = MAX_KEY_NAME_LENGTH;
		wchar_t keyName[MAX_KEY_NAME_LENGTH];
		for (DWORD i = 0; i < numOfSubkeys; i++) {
			RegEnumKeyExW(hkeyNetwork, i, keyName, &nameLength, NULL, NULL, NULL, NULL);
			std::wcout << "subkey : " << keyName << "\n";
			
		}
	}
	else std::cout << "현재 연결 된 네트워크 장치 없음\n";

	RegCloseKey(hkeyNetwork);
}

void connectionInfo::printConnectionInfo(void) {
	switch (storageType) {
	case NAS:

		break;
	case Cloud:

		break;
	case SharedComputer:

		break;
	default:
		std::cerr << "Storage type is not defined\n";
	}

}