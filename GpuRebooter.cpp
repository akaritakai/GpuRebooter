#include "stdafx.h"

int _tmain(int, _TCHAR*[])
{
    FreeConsole();
    RegisterHotKey(nullptr, NULL, MOD_CONTROL | MOD_ALT, VK_CANCEL);
    MSG msg = { nullptr };
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (msg.message == WM_HOTKEY)
        {
            auto hDevInfo = SetupDiGetClassDevs(&GUID_DEVCLASS_DISPLAY, REGSTR_KEY_PCIENUM, nullptr, DIGCF_PRESENT | DIGCF_ALLCLASSES);
            SP_DEVINFO_DATA deviceInfoData;
            deviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
            for (DWORD i = 0; SetupDiEnumDeviceInfo(hDevInfo, i, &deviceInfoData); i++)
            {
                SP_PROPCHANGE_PARAMS params;
                params.ClassInstallHeader.cbSize = sizeof(SP_CLASSINSTALL_HEADER);
                params.ClassInstallHeader.InstallFunction = DIF_PROPERTYCHANGE;
                params.Scope = DICS_FLAG_GLOBAL;
                params.StateChange = DICS_DISABLE;
                SetupDiSetClassInstallParams(hDevInfo, &deviceInfoData, &params.ClassInstallHeader, sizeof(params));
                SetupDiCallClassInstaller(DIF_PROPERTYCHANGE, hDevInfo, &deviceInfoData);
                params.StateChange = DICS_ENABLE;
                SetupDiSetClassInstallParams(hDevInfo, &deviceInfoData, &params.ClassInstallHeader, sizeof(params));
                SetupDiCallClassInstaller(DIF_PROPERTYCHANGE, hDevInfo, &deviceInfoData);
            }
        }
    }

    return EXIT_SUCCESS;
}
