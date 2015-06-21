#include "stdafx.h"

int _tmain(int, _TCHAR*[])
{
	FreeConsole();
	RegisterHotKey(nullptr, 1, MOD_CONTROL | MOD_ALT, VK_CANCEL);
	MSG msg = {0};
	while (GetMessage(&msg, nullptr, 0, 0) != 0)
	{
		if (msg.message == WM_HOTKEY)
		{
			auto hDevInfo = SetupDiGetClassDevs(nullptr, REGSTR_KEY_PCIENUM, nullptr, DIGCF_PRESENT | DIGCF_ALLCLASSES);
			SP_DEVINFO_DATA deviceInfoData;
			deviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
			for (DWORD i = 0; SetupDiEnumDeviceInfo(hDevInfo, i, &deviceInfoData); i++)
			{
				DWORD dataT;
				LPTSTR buffer = nullptr;
				DWORD bufferSize = 0;

				while (!SetupDiGetDeviceRegistryProperty(hDevInfo, &deviceInfoData, SPDRP_DEVICEDESC, &dataT, reinterpret_cast<PBYTE>(buffer), bufferSize, &bufferSize))
				{
					if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
					{
						if (buffer) LocalFree(buffer);
						buffer = static_cast<LPTSTR>(LocalAlloc(LPTR, bufferSize * 2));
					}
					else break;
				}

				if (buffer == nullptr) break;

				if (_tcsncmp(buffer, _T("NVIDIA GeForce GTX 970"), 22) == 0)
				{
					SP_PROPCHANGE_PARAMS params;
					params.ClassInstallHeader.cbSize = sizeof(SP_CLASSINSTALL_HEADER);
					params.ClassInstallHeader.InstallFunction = DIF_PROPERTYCHANGE;
					params.Scope = DICS_FLAG_GLOBAL ;
					params.StateChange = DICS_DISABLE;
					SetupDiSetClassInstallParams(hDevInfo, &deviceInfoData, &params.ClassInstallHeader, sizeof(params));
					SetupDiCallClassInstaller(DIF_PROPERTYCHANGE, hDevInfo, &deviceInfoData);
					params.StateChange = DICS_ENABLE;
					SetupDiSetClassInstallParams(hDevInfo, &deviceInfoData, &params.ClassInstallHeader, sizeof(params));
					SetupDiCallClassInstaller(DIF_PROPERTYCHANGE, hDevInfo, &deviceInfoData);
				}

				if (buffer) LocalFree(buffer);
			}

			SetupDiDestroyDeviceInfoList(hDevInfo);
		}
	}

	return EXIT_SUCCESS;
}
