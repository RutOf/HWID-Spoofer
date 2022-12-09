@echo off
taskkill /f /im "EpicGamesLauncher.exe" /t /fi "status eq running">nul
taskkill /f /im "FortniteLauncher.exe" /t /fi "status eq running">nul
taskkill /f /im "FortniteClient-Win64-Shipping_BE.exe" /t /fi "status eq running">nul
taskkill /f /im "FortniteClient-Win64-Shipping.exe" /t /fi "status eq running">nul
echo your shitty reset
wmic baseboard get serialnumber
echo your shitty Bios
wmic bios get serialnumber
echo your shitty Cpu
wmic cpu get serialnumber
echo your shitty DiskDrive (#1) C: 
wmic diskdrive get serialnumber
echo Diskdrive (#2)
wmic path win32_physicalmedia get SerialNumber
wmic path win64_physicalmedia get SerialNumber
echo Diskdrive (#3)
wmic path win32_diskdrive get SerialNumber
echo your shitty BaseBoard 
wmic baseboard get manufacturer
echo RAM
wmic memorychip get serialnumber
echo CPU
wmic cpu get processorid
echo BaseBoard
wmic baseboard get manufacturer
echo GPUID
wmic PATH Win32_VideoController GET Description,PNPDeviceID
echo Mac Address
getmacnew
echo Other Stuff
AMIDEWIN.EXE /dms serials.txt
type serials.txt
random serial.ext
netsh winsock reset
del /f serials.txt
ipconfig /release
ipconfig /renew
exit
