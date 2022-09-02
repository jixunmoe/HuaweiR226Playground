#include <iostream>
#include <tchar.h>
#include <Windows.h>
#include <winusb.h>
#include <SetupAPI.h>
#include <initguid.h>
#include <usbiodef.h>
#include <cfgmgr32.h>

DEFINE_GUID(guid_ew_busfilter, 0x36FC9E60, 0xC465, 0x11CF, 0x80, 0x56, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00);
DEFINE_GUID(guid_ew_cdcacm, 0x4D36E978, 0xE325, 0x11CE, 0xBF, 0xC1, 0x08, 0x00, 0x2B, 0xE1, 0x03, 0x18);
DEFINE_GUID(guid_ew_cdcecm, 0x4d36e972, 0xe325, 0x11ce, 0xbf, 0xc1, 0x08, 0x00, 0x2b, 0xe1, 0x03, 0x18);
DEFINE_GUID(guid_ew_cdcmdm, 0x4D36E96D, 0xE325, 0x11CE, 0xBF, 0xC1, 0x08, 0x00, 0x2B, 0xE1, 0x03, 0x18);
DEFINE_GUID(guid_ew_hwupgrade, 0x36fc9e60, 0xc465, 0x11cf, 0x80, 0x56, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00);
DEFINE_GUID(guid_ew_hwusbdev, 0x4D36E978, 0xE325, 0x11CE, 0xBF, 0xC1, 0x08, 0x00, 0x2B, 0xE1, 0x03, 0x18);
DEFINE_GUID(guid_ew_hwusbdevcfg, 0x4D36E978, 0xE325, 0x11CE, 0xBF, 0xC1, 0x08, 0x00, 0x2B, 0xE1, 0x03, 0x18);
DEFINE_GUID(guid_ew_jubusenum, 0x36FC9E60, 0xC465, 0x11CF, 0x80, 0x56, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00);
DEFINE_GUID(guid_ew_jucdcacm, 0x4D36E978, 0xE325, 0x11CE, 0xBF, 0xC1, 0x08, 0x00, 0x2B, 0xE1, 0x03, 0x18);
DEFINE_GUID(guid_ew_jucdcecm, 0x4d36e972, 0xe325, 0x11ce, 0xbf, 0xc1, 0x08, 0x00, 0x2b, 0xe1, 0x03, 0x18);
DEFINE_GUID(guid_ew_jucdcmdm, 0x4D36E96D, 0xE325, 0x11CE, 0xBF, 0xC1, 0x08, 0x00, 0x2B, 0xE1, 0x03, 0x18);
DEFINE_GUID(guid_ew_juextctrl, 0x4d36e97d, 0xe325, 0x11ce, 0xbf, 0xc1, 0x08, 0x00, 0x2b, 0xe1, 0x03, 0x18);
DEFINE_GUID(guid_ew_juwwanecm, 0x4d36e972, 0xe325, 0x11ce, 0xbf, 0xc1, 0x08, 0x00, 0x2b, 0xe1, 0x03, 0x18);
DEFINE_GUID(guid_ew_wwanecm, 0x4d36e972, 0xe325, 0x11ce, 0xbf, 0xc1, 0x08, 0x00, 0x2b, 0xe1, 0x03, 0x18);
DEFINE_GUID(guid_ewdcsc, 0x50DD5230, 0xBA8A, 0x11D1, 0xBF, 0x5D, 0x00, 0x00, 0xF8, 0x05, 0xF5, 0x30);
DEFINE_GUID(guid_ewmdm2k, 0x4D36E96D, 0xE325, 0x11CE, 0xBF, 0xC1, 0x08, 0x00, 0x2B, 0xE1, 0x03, 0x18);
DEFINE_GUID(guid_ewnet, 0x4d36e972, 0xe325, 0x11ce, 0xbf, 0xc1, 0x08, 0x00, 0x2b, 0xe1, 0x03, 0x18);
DEFINE_GUID(guid_ewser2k, 0x4D36E978, 0xE325, 0x11CE, 0xBF, 0xC1, 0x08, 0x00, 0x2B, 0xE1, 0x03, 0x18);
DEFINE_GUID(guid_ewsmartcard, 0x990A2BD7, 0xE738, 0x46c7, 0xB2, 0x6F, 0x1C, 0xF8, 0xFB, 0x9F, 0x13, 0x91);
DEFINE_GUID(guid_ewusbwwan, 0x4d36e972, 0xe325, 0x11ce, 0xbf, 0xc1, 0x08, 0x00, 0x2b, 0xe1, 0x03, 0x18);

// CDROM: 4D36E965-E325-11CE-BFC1-08002BE10318
DEFINE_GUID(_CDROM,         0x4d36e965L, 0xE325, 0x11CE, 0xBF, 0xC1, 0x08, 0x00, 0x2B, 0xE1, 0x03, 0x18);
// Generic Mass Storage: 4d36e967-e325-11ce-bfc1-08002be10318
DEFINE_GUID(_Mass_STORAGE,  0x4d36e967L, 0xE325, 0x11CE, 0xBF, 0xC1, 0x08, 0x00, 0x2b, 0xe1, 0x03, 0x18);

// 4d36e972-e325-11ce-bfc1-08002be10318
DEFINE_GUID(_CDCECM, 0x4d36e972L, 0xE325, 0x11CE, 0xBF, 0xC1, 0x08, 0x00, 0x2b, 0xe1, 0x03, 0x18);
// 4D36E96D-E325-11CE-BFC1-08002BE10318
DEFINE_GUID(_cdcmdm, 0x4D36E96DL, 0xE325, 0x11CE, 0xBF, 0xC1, 0x08, 0x00, 0x2b, 0xe1, 0x03, 0x18);

DEFINE_GUID(GUID_DEVINTERFACE_USB_SETUP_CLASS_OLD1, 0x36fc9e60L, 0xc465, 0x11cf, 0x80, 0x56, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00);
// 8fd5c4f7-45a7-5d70-bba9-22013834e044
// DEFINE_GUID(GUID_DEVINTERFACE_USB_SETUP_CLASS, 0x8fd5c4f7, 0x45a7, 0x5d70, 0xbb, 0xa9,
//    0x22, 0x01, 0x38, 0x34, 0xe0, 0x44);
#define GUID_DEVINTERFACE_USB_SETUP_CLASS GUID_DEVINTERFACE_DISK;
// static GUID GUID_DEVINTERFACE_USB_SETUP_CLASS = GUID_DEVINTERFACE_USB_SETUP_CLASS2;

byte payload[] = {
    0x55, 0x53, 0x42, 0x43, 0x12, 0x34, 0x56, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11,
    0x06, 0x20, 0x00, 0x00, 0x01, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

void HuaweiSwitchMode(const TCHAR* pDevicePath) {
    auto hDevice = CreateFile(pDevicePath, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, nullptr);
    if (hDevice == INVALID_HANDLE_VALUE) {
        std::cout << "    fail: could not open device" << std::endl;
        return;
    }

    WINUSB_INTERFACE_HANDLE interfaceHandle;
    if (WinUsb_Initialize(hDevice, &interfaceHandle)) {
        std::cout << "    ok: winusb init ok" << std::endl;
    }
    else {
        std::cout << "    fail: winusb init failed with error: " << GetLastError() << std::endl;

    }


    CloseHandle(hDevice);
}

void PrintDeviceInterfaces(HDEVINFO hDeviceInfoSet, SP_DEVINFO_DATA* deviceInfoData, const GUID* interfaceGuid) {
    DWORD deviceInterfaceIndex = 0;

    SP_DEVICE_INTERFACE_DATA deviceInterfaceData;
    deviceInterfaceData.cbSize = sizeof(deviceInterfaceData);

    while (SetupDiEnumDeviceInterfaces(hDeviceInfoSet, deviceInfoData, interfaceGuid, deviceInterfaceIndex, &deviceInterfaceData))
    {
        // deviceInterfaceData.cbSize = sizeof(deviceInterfaceData);
        // std::cout << deviceInterfaceIndex << std::endl;

        //get some more details etc
        DWORD requiredBufferSize;
        SetupDiGetDeviceInterfaceDetail(hDeviceInfoSet, &deviceInterfaceData, nullptr, 0, &requiredBufferSize, deviceInfoData);
        auto pBuffer = (PSP_DEVICE_INTERFACE_DETAIL_DATA)calloc(requiredBufferSize + 8, 1);
        pBuffer->cbSize = sizeof(SP_INTERFACE_DEVICE_DETAIL_DATA);
        if (SetupDiGetDeviceInterfaceDetail(hDeviceInfoSet, &deviceInterfaceData, pBuffer, requiredBufferSize, &requiredBufferSize, deviceInfoData)) {
            TCHAR* pDevicePath = &pBuffer->DevicePath[0];
            std::wcout << L"  device path: " << pDevicePath << std::endl;
            if (_tcsstr(pDevicePath, TEXT("vid_12d1&pid_1f07"))) {
                std::wcout << L"    found vid_12d1&pid_1f07 !!" << std::endl;
                HuaweiSwitchMode(pDevicePath);
            }
        }
        else {
            std::cout << "  device path: failed with error = " << GetLastError() << std::endl;
        }
        free(pBuffer);

        deviceInterfaceIndex++;
    }
}

void PrintDeviceInterfaces(HDEVINFO hDeviceInfoSet, SP_DEVINFO_DATA* deviceInfoData) {
    static GUID guidList[] = { guid_ew_busfilter,
        guid_ew_cdcacm,
        guid_ew_cdcecm,
        guid_ew_cdcmdm,
        guid_ew_hwupgrade,
        guid_ew_hwusbdev,
        guid_ew_hwusbdevcfg,
        guid_ew_jubusenum,
        guid_ew_jucdcacm,
        guid_ew_jucdcecm,
        guid_ew_jucdcmdm,
        guid_ew_juextctrl,
        guid_ew_juwwanecm,
        guid_ew_wwanecm,
        guid_ewdcsc,
        guid_ewmdm2k,
        guid_ewnet,
        guid_ewser2k,
        guid_ewsmartcard,
        guid_ewusbwwan };

    GUID* last = &guidList[_countof(guidList)];
    for (GUID* guid = &guidList[0]; guid < last; guid++) {
        PrintDeviceInterfaces(hDeviceInfoSet, deviceInfoData, guid);
    }
}

// Main
int main()
{
    DWORD guidSize = 1;

    SP_DEVINFO_DATA deviceInfoData = {0};
    deviceInfoData.cbSize = sizeof(deviceInfoData);
    SP_DEVICE_INTERFACE_DATA deviceInterfaceData = { 0 };
    deviceInterfaceData.cbSize = sizeof(deviceInterfaceData);
    
    PSP_INTERFACE_DEVICE_DETAIL_DATA deviceDetail = nullptr;

    for (int i = 0; i < guidSize; i++) {
        auto hDeviceInfoSet = SetupDiGetClassDevs(&GUID_DEVINTERFACE_USB_DEVICE, nullptr, NULL, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);

        int deviceIndex = 0;
        while (true) {
            if (!SetupDiEnumDeviceInfo(hDeviceInfoSet, deviceIndex, &deviceInfoData)) {
                break;
            }

            std::wcout << deviceIndex << ":" << std::endl;

            TCHAR deviceDataBuf[4096 + 1] = {0};
            SetupDiGetDeviceRegistryProperty(hDeviceInfoSet, &deviceInfoData, SPDRP_FRIENDLYNAME, nullptr, (PBYTE)(&deviceDataBuf), sizeof(deviceDataBuf) - sizeof(deviceDataBuf[0]), nullptr);
            if (deviceDataBuf[0]) {
                std::wcout << L"  name: " << deviceDataBuf << std::endl;
            }
            SetupDiGetDeviceRegistryProperty(hDeviceInfoSet, &deviceInfoData, SPDRP_DEVICEDESC, nullptr, (PBYTE)(&deviceDataBuf), sizeof(deviceDataBuf) - sizeof(deviceDataBuf[0]), nullptr);
            std::wcout << L"  desc: " << deviceDataBuf << std::endl;

            ULONG IDSize;
            CM_Get_Device_ID_Size(&IDSize, deviceInfoData.DevInst, 0);

            TCHAR* deviceID = (TCHAR*)calloc(IDSize, sizeof(TCHAR));
            CM_Get_Device_ID(deviceInfoData.DevInst, deviceID, MAX_PATH, 0);
            std::wcout << L"  id: " << deviceID << std::endl;
            // free(deviceID);

            PrintDeviceInterfaces(hDeviceInfoSet, &deviceInfoData);


            deviceIndex++;
        }

        std::cout << "(end)" << std::endl;
        SetupDiDestroyDeviceInfoList(hDeviceInfoSet);
    }
}