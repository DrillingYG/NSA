#include "connectionInfo.h"


void connectionInfo::setCurConStorages(void) {
#define MAX_KEY_NAME_LENGTH 512
#define MAX_VALUE_NAME_LENGTH 64
#define DATA_LEN 512
	HKEY hkeyNetwork;
	DWORD numOfSubkeys;
	RegOpenKeyExW(HKEY_CURRENT_USER, L"Network", 0, KEY_READ | KEY_ENUMERATE_SUB_KEYS, &hkeyNetwork);
	RegQueryInfoKey(hkeyNetwork, NULL, 0, 0, &numOfSubkeys, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
	if (numOfSubkeys > 0) {
		DWORD retCode = 0;
		DWORD nameLength = MAX_KEY_NAME_LENGTH;
		wchar_t keyName[MAX_KEY_NAME_LENGTH];
		std::cout << "현재 연결 된 네트워크 장비 수 : " << numOfSubkeys << '\n';

		m_numOfcurConStrages = numOfSubkeys;
		m_curConStorages = std::vector<currentConnectedStorages>(numOfSubkeys);

		for (DWORD i = 0; i < numOfSubkeys; i++) {
			retCode = RegEnumKeyExW(hkeyNetwork, i, keyName, &nameLength, NULL, NULL, NULL, NULL);
			m_curConStorages[i].m_driveLetter = keyName;
			

			if (retCode == ERROR_SUCCESS) {
				HKEY hkeySubkey;
				DWORD valueLength = MAX_VALUE_NAME_LENGTH;
				wchar_t valueName[MAX_VALUE_NAME_LENGTH];

				std::wstring subkey = L"Network\\";
				subkey += keyName;
				RegOpenKeyExW(HKEY_CURRENT_USER, subkey.c_str(), NULL, KEY_READ | KEY_QUERY_VALUE, &hkeySubkey);
				nameLength = MAX_KEY_NAME_LENGTH;

				for (DWORD j = 0, retCode = ERROR_SUCCESS;; j++) {
					retCode = RegEnumValueW(hkeySubkey, j, valueName, &valueLength, NULL, NULL, NULL, NULL);
					if (retCode == ERROR_SUCCESS) {

						if (!wcsncmp(valueName, L"RemotePath", 10)) {
							wchar_t remotePath[DATA_LEN];
							DWORD remotePathLen = DATA_LEN;
							std::wregex reg_Onedrive(L"https://d\.docs\.live\.net/(\\w|\\d)+");
							std::wregex reg_UNC(L"\\\\\\\\[0-9]+\.[0-9]+\.[0-9]+\.[0-9]+(\\\\|\\w|\\d)*");
							RegQueryValueExW(hkeySubkey, valueName, NULL, NULL, reinterpret_cast<LPBYTE>(remotePath), &remotePathLen);

							if (std::regex_match(remotePath, reg_Onedrive)) {
								m_curConStorages[j].storageType = ONEDRIVE;
							}
							else if (std::regex_match(remotePath, reg_UNC)) {
							}
							else std::wcout << "Not Match\n";

						}
						else if (!wcsncmp(valueName, L"UserName", 8)) {
							m_curConStorages[i].m_username = valueName;
						}
					}
					else break;

					valueLength = MAX_VALUE_NAME_LENGTH;
				}

				if (m_curConStorages[i].m_username == L"") m_curConStorages[i].storageType = SHARED_COMPUTER;

				RegCloseKey(hkeySubkey);
			}
		}
	}
	else std::cout << "현재 연결 된 네트워크 장치 없음\n";

	RegCloseKey(hkeyNetwork);
}

void connectionInfo::printCurConStorages(void) const {
	for (auto& curConStorage : m_curConStorages) {
		switch (curConStorage.storageType) {
		case NAS:

			break;
		case ONEDRIVE:

			break;
		case SHARED_COMPUTER:

			break;
		default:
			std::cerr << "Unknown storage\n";
		}
	}
}
