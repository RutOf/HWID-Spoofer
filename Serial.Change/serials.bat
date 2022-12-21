@echo off

rem Terminate processes related to the Epic Games Launcher and Fortnite
taskkill /f /im "EpicGamesLauncher.exe" /t /fi "status eq running" >nul
taskkill /f /im "FortniteLauncher.exe" /t /fi "status eq running" >nul
taskkill /f /im "FortniteClient-Win64-Shipping_BE.exe" /t /fi "status eq running" >nul
taskkill /f /im "FortniteClient-Win64-Shipping.exe" /t /fi "status eq running" >nul

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
