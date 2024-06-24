#ifdef _WIN64
  #define ORIGINAL_PATH "\\\\.\\GLOBALROOT\\SystemRoot\\System32\\dinput8.dll"
#else
  #define ORIGINAL_PATH "\\\\.\\GLOBALROOT\\SystemRoot\\SysWOW64\\dinput8.dll"
#endif

#pragma comment(linker, "/EXPORT:DirectInput8Create=" ORIGINAL_PATH ".DirectInput8Create")
#pragma comment(linker, "/EXPORT:DllCanUnloadNow=" ORIGINAL_PATH ".DllCanUnloadNow,PRIVATE")
#pragma comment(linker, "/EXPORT:DllGetClassObject=" ORIGINAL_PATH ".DllGetClassObject,PRIVATE")
#pragma comment(linker, "/EXPORT:DllRegisterServer=" ORIGINAL_PATH ".DllRegisterServer,PRIVATE")
#pragma comment(linker, "/EXPORT:DllUnregisterServer=" ORIGINAL_PATH ".DllUnregisterServer,PRIVATE")
#pragma comment(linker, "/EXPORT:GetdfDIJoystick=" ORIGINAL_PATH ".GetdfDIJoystick")