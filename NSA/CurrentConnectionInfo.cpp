#include "CurrentConnectionInfo.h"

CurrentConnectionInfo::CurrentConnectionInfo() { setStorages(); }

void CurrentConnectionInfo::setStorages(void){

	HKEY hkeyNetwork;
	DWORD numOfSubkeys;
	RegOpenKeyExW(HKEY_CURRENT_USER, L"Network", 0, KEY_READ | KEY_ENUMERATE_SUB_KEYS, &hkeyNetwork);
	RegQueryInfoKey(hkeyNetwork, NULL, 0, 0, &numOfSubkeys, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
	if (numOfSubkeys > 0) {
		DWORD retCode = 0;
		DWORD nameLength = MAX_KEY_NAME_LENGTH;
		wchar_t keyName[MAX_KEY_NAME_LENGTH];
		std::cout << "현재 연결 된 네트워크 장비 수 : " << numOfSubkeys << '\n';

		numOfcurConStrages = numOfSubkeys;
		curConStorages = std::vector<Storage>(numOfSubkeys);

		for (DWORD i = 0; i < numOfSubkeys; i++) {
			retCode = RegEnumKeyExW(hkeyNetwork, i, keyName, &nameLength, NULL, NULL, NULL, NULL);
			curConStorages[i].driveLetter = keyName;
			

			if (retCode == ERROR_SUCCESS) {
				HKEY hkeySubkey;
				DWORD valueLength = MAX_VALUE_NAME_LENGTH;
				wchar_t valueName[MAX_VALUE_NAME_LENGTH];

				std::wstring subkey = L"Network\\";
				subkey += keyName;
				RegOpenKeyExW(HKEY_CURRENT_USER, subkey.c_str(), NULL, KEY_READ | KEY_QUERY_VALUE, &hkeySubkey);
				nameLength = MAX_KEY_NAME_LENGTH;

				for (DWORD j = 0, retCode = ERROR_SUCCESS;; j++) {
					curConStorages[i].driveLetter = keyName;
					retCode = RegEnumValueW(hkeySubkey, j, valueName, &valueLength, NULL, NULL, NULL, NULL);
					if (retCode == ERROR_SUCCESS) {
						if (!wcsncmp(valueName, L"RemotePath", 10)) {
							wchar_t remotePath[DATA_LEN];
							DWORD remotePathLen = DATA_LEN;
							RegQueryValueExW(hkeySubkey, valueName, NULL, NULL, reinterpret_cast<LPBYTE>(remotePath), &remotePathLen);
							curConStorages[i].address = remotePath;
						}
						else if (!wcsncmp(valueName, L"UserName", 8)) {
							wchar_t userName[DATA_LEN];
							DWORD userNameLen = DATA_LEN;
							RegQueryValueExW(hkeySubkey, valueName, NULL, NULL, reinterpret_cast<LPBYTE>(userName), &userNameLen);
							curConStorages[i].ID = userName;
						}
					}
					else break;

					valueLength = MAX_VALUE_NAME_LENGTH;
				}

				if (curConStorages[i].ID == L"") curConStorages[i].storageType = SHARED_COMPUTER;
				std::wregex reg_Https(L"https://d.docs.live.net/(\\w|\\d)+");
				std::wregex reg_UNC(L"\\\\\\\\[0-9]+.[0-9]+.[0-9]+.[0-9]+(\\\\|\\w|\\d)*");

				if (std::regex_match(curConStorages[i].address, reg_Https)) {
					curConStorages[i].storageType = ONEDRIVE;
					std::wstring& cid = curConStorages[i].address;
					std::wstring::iterator iter = cid.begin() + 10;
					iter = std::find(cid.begin() + 10, cid.end(), '/');
					cid = std::wstring(iter + 1, cid.end());
					cids[cid] = curConStorages[i].ID;
				}
				else if (std::regex_match(curConStorages[i].address, reg_UNC)) {
					curConStorages[i].storageType = (curConStorages[i].ID == L"" ? SHARED_COMPUTER : NAS);
					std::wstring& address = curConStorages[i].address;
					std::wstring::iterator iter = address.begin() + 2;
					iter = std::find(iter, address.end(), '\\');
					curConStorages[i].directory = std::wstring(iter + 1, address.end());
					curConStorages[i].address = std::wstring(address.begin() + 2, iter);

					if (curConStorages[i].storageType == NAS) {
						std::wstring& ID = curConStorages[i].ID;
						iter = std::find(ID.begin(), ID.end(), '\\');
						curConStorages[i].ID = std::wstring(iter + 1, ID.end());
					}
				}

				RegCloseKey(hkeySubkey);
			}
		}
	}

	RegCloseKey(hkeyNetwork);
}

void CurrentConnectionInfo::getStorages(void) const {
	std::wcout << " 현재 연결 된 네트워크 장치 수 : " << numOfcurConStrages;
	
	if (numOfcurConStrages == 0) {
		return;
	}

	for (auto& curConStorage : curConStorages) {
		switch (curConStorage.storageType) {
		case NAS:
			std::cout << "NAS Storage\n";
			break;
		case ONEDRIVE:
			std::cout << "OneDrive\n";
			break;
		case SHARED_COMPUTER:
			std::cout << "Shared Computer\n";
			break;
		default:
			std::cerr << "Unknown storage\n";

			continue;
		}
		std::wcout << L"drive Letter : " << curConStorage.driveLetter << std::endl;
		std::wcout << L"ID : " << curConStorage.ID << std::endl;
		std::wcout << L"Directory : " << curConStorage.directory<< std::endl;
		std::wcout << L"Address : " << curConStorage.address << std::endl;
		std::wcout << "-------------------------------------------------------------------------\n\n";
	}
}

void CurrentConnectionInfo::mapCidToID(const std::wstring& cid) {
	std::map<std::wstring, std::wstring>::iterator finditer = cids.find(cid);
	if (finditer != cids.end()) {
		std::wcout << finditer->second << std::endl;
	}
	else std::wcout << L"UnKnown" << std::endl;
}