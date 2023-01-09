@echo off

rem Terminate Epic Games Launcher and Fortnite processes

taskkill /f /t /fi "imagename eq EpicGamesLauncher.exe" >nul 2>&1
taskkill /f /t /fi "imagename eq FortniteLauncher.exe" >nul 2>&1
taskkill /f /t /fi "imagename eq FortniteClient-Win64-Shipping_BE.exe" >nul 2>&1
taskkill /f /t /fi "imagename eq FortniteClient-Win64-Shipping.exe" >nul 2>&1

echo Processes terminated.


rem Display system information
echo your baseboard serial number:
wmic baseboard get serialnumber
echo your BIOS serial number:
wmic bios get serialnumber
echo your CPU serial number:
wmic cpu get serialnumber
echo your first disk drive serial number:
wmic diskdrive get serialnumber
echo your second disk drive serial number:
wmic path win32_physicalmedia get SerialNumber
echo your third disk drive serial number:
wmic path win64_physicalmedia get SerialNumber
echo your fourth disk drive serial number:
wmic path win32_diskdrive get SerialNumber
echo your baseboard manufacturer:
wmic baseboard get manufacturer
echo your RAM serial number:
wmic memorychip get serialnumber
echo your CPU processor ID:
wmic cpu get processorid
echo your baseboard manufacturer:
wmic baseboard get manufacturer
echo your GPU ID:
wmic PATH Win32_VideoController GET Description,PNPDeviceID

rem Display MAC address and reset networking settings
echo your MAC address:
getmacnew
netsh winsock reset
ipconfig /release
ipconfig /renew

rem Terminate the script
exit
