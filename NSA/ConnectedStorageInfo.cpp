#include "ConnectedStorageInfo.h"

ConnectedStorageInfo::ConnectedStorageInfo(void) {
	setStorages();
}

void ConnectedStorageInfo::setStorages(void) {
	HKEY hkeyNetDriveMRU;
	RegOpenKeyExW(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Map Network Drive MRU", 0,
		KEY_READ | KEY_QUERY_VALUE, &hkeyNetDriveMRU);

	DWORD numOfValues;
	RegQueryInfoKeyW(hkeyNetDriveMRU, NULL, NULL, 0, NULL, NULL, NULL, &numOfValues, NULL, NULL, NULL, NULL);

	if (numOfValues > 0) {
		std::wcout << "네트워크 장치 연결 이력\n";
		std::wcout << "총 " << numOfValues - 1<< "개\n\n";
		wchar_t valueName[MAX_VALUE_NAME_LENGTH];
		DWORD valueLength = MAX_VALUE_NAME_LENGTH;


		for (DWORD i = 0, retCode = ERROR_SUCCESS;; i++) {
			retCode = RegEnumValueW(hkeyNetDriveMRU, i, valueName, &valueLength, 0, NULL, NULL, NULL);
			if (retCode == ERROR_SUCCESS) {
				numOfConnectedStrages += 1;
				if (!wcsncmp(valueName, L"MRUList", 7)) continue;
				wchar_t remotePath[DATA_LEN];
				DWORD remotePathLen = DATA_LEN;
				RegQueryValueExW(hkeyNetDriveMRU, valueName, NULL, NULL, reinterpret_cast<LPBYTE>(remotePath), &remotePathLen);
				std::wregex reg_UNC(L"\\\\\\\\[0-9]+.[0-9]+.[0-9]+.[0-9]+(\\\\|\\w|\\d)*");
				std::wregex reg_Https(L"https://d.docs.live.net/(\\w|\\d)+");

				if (std::regex_match(remotePath, reg_UNC)) {
					std::wcout << "remote Path(UNC) : " << remotePath<< std::endl;
					ConnectedStorages.emplace_back()
				}
				else if (std::regex_match(remotePath, reg_Https)) {
					std::wcout << "remote Path(https) : " << remotePath << std::endl;
					std::wstring cid = std::wstring(remotePath);
					std::wstring::iterator iter = cid.begin() + 10;
					iter = std::find(cid.begin() + 10, cid.end(), '/');
					cid = std::wstring(iter + 1, cid.end());
					
				}
			}
			else break;
			valueLength = MAX_VALUE_NAME_LENGTH;
		}
	}
	else {
		std::wcout << "네트워크 장치 연결 기록 없음\n";
	}


	RegCloseKey(hkeyNetDriveMRU);
}

void ConnectedStorageInfo::getStorages(void) const {

}