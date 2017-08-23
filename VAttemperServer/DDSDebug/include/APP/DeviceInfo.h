#pragma once
#define _WIN32_DCOM

#include <string>
using std::string;
#include <comdef.h>
#include <Wbemidl.h>

class DeviceInfo
{
public:
    DeviceInfo();
    ~DeviceInfo();
    string getOsName();
    string getMacAddr();
    string getNetworkAdapterId();
    string getDiskSerial();
    string getBaseBoardSerial();
    string getBiosSerial();
    string getProcessorId();

    string getMachineId();
private:
    int errorCode;
    HRESULT hres;
    IWbemLocator *pLoc;
    IWbemServices *pSvc;
    string WmiQuery(string select, WCHAR* property);
};

