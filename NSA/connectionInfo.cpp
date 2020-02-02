#include "connectionInfo.h"


void connectionInfo::setConnectionType(void) {
#define MAX_KEY_NAME_LENGTH 512
#define MAX_VALUE_NAME_LENGTH 64

	//RegGetValueW(HKEY_CURRENT_USER, L"\Software\Microsoft\Windows\CurrentVersion\Explorer\Map Network Drive MRU");
	//RegGetValueW(HKEY_CURRENT_USER, L"\Software\Microsoft\Windows\CurrentVersion\Explorer\MountPoints2\##[IP]#[Directory]");
	//RegGetValueW(HKEY_CURRENT_USER, L"\Network");
	HKEY hkeyNetwork;
	DWORD numOfSubkeys;
	RegOpenKeyExW(HKEY_CURRENT_USER, L"Network", 0, KEY_READ | KEY_ENUMERATE_SUB_KEYS, &hkeyNetwork);
	RegQueryInfoKey(hkeyNetwork, NULL, 0, 0, &numOfSubkeys, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
	if (numOfSubkeys > 0) {
		DWORD retCode = 0;
		DWORD nameLength = MAX_KEY_NAME_LENGTH;
		wchar_t keyName[MAX_KEY_NAME_LENGTH];
		std::cout << "number of subkeys : " << numOfSubkeys << '\n';

		m_curConStorages = std::vector<currentConnectedStorages>(numOfSubkeys);

		for (DWORD i = 0; i < numOfSubkeys; i++) {
			retCode = RegEnumKeyExW(hkeyNetwork, i, keyName, &nameLength, NULL, NULL, NULL, NULL);
			if (retCode == ERROR_SUCCESS) {
				HKEY storageSubkey;
				DWORD valueLength = MAX_VALUE_NAME_LENGTH;
				wchar_t valueName[MAX_VALUE_NAME_LENGTH];

				std::wstring subkey = L"Network\\";
				subkey.append(keyName);
				RegOpenKeyExW(HKEY_CURRENT_USER, subkey.c_str(), NULL, KEY_READ | KEY_QUERY_VALUE, &storageSubkey);
				std::wcout << "subkey : " << subkey << '\n';
				nameLength = MAX_KEY_NAME_LENGTH;
				
				for (DWORD j = 0, retCode = ERROR_SUCCESS;; j++) {
					retCode = RegEnumValueW(storageSubkey, j, valueName, &valueLength, NULL, NULL, NULL, NULL);
					if (retCode == ERROR_SUCCESS) {
						std::wcout << "value name : " << valueName << '\n';
					}
					else break;

					valueLength = MAX_VALUE_NAME_LENGTH;
				}


				RegCloseKey(storageSubkey);
			}
		}
	}
	else std::cout << "현재 연결 된 네트워크 장치 없음\n";

	RegCloseKey(hkeyNetwork);
}

void connectionInfo::printConnectionInfo(void) {
	for (auto& curConStorage : m_curConStorages) {
		switch (curConStorage.storageType) {
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

}