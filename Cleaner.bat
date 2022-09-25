@echo off
title Cleaner
ping localhost -n 3 >nul
echo Killing any related processes...
@taskkill /f /im "EpicGamesLauncher.exe" /t /fi "status eq running">nul
@taskkill /f /im "FortniteLauncher.exe" /t /fi "status eq running">nul
@taskkill /f /im "FortniteClient-Win64-Shipping_BE.exe" /t /fi "status eq running">nul
@taskkill /f /im "FortniteClient-Win64-Shipping.exe" /t /fi "status eq running">nul
@taskkill /f /im "EasyAntiCheat.exe" /t /fi "status eq running">nul
@timeout /t 2 >nul 2>&1 /nobreak
cls
Echo Cleaning!
ping localhost -n 3 >nul
@reg delete "HKEY_CURRENT_USER\Software\Epic Games" /f
@RD /S /Q "%localappdata%\FortniteGame"
@RD /S /Q "%localappdata%\EpicGamesLauncher"
@RD /S /Q "%localappdata%\UnrealEngine"
@RD /S /Q "%localappdata%\UnrealEngineLauncher"
@RD /S /Q "%localappdata%\Temp\ecache.bin"
@RD /S /Q "%localappdata%\FortniteGame\Saved\LMS\Manifest.sav"
@RD /S /Q "%localappdata%\Microsoft\Feeds"
del "C:\Recovery\ntuser.sys"
del "C:\MSOCache" /p
del "C:\Users\Public\Shared Files" 
ping localhost -n 3 >nul
exit 

:menu_1   Spoof HDD Serial

Set mycmdWidth=37
Set mycmdHeight=31

cls
echo %ESC%[44m%ESC%[92m------------------------
echo %ESC%[44m%ESC%[92m--- Spoof HDD Serial --- 
echo %ESC%[44m%ESC%[92m------------------------
echo(
echo(%ESC%[97m%ESC%[93mDisk Drive:%ESC%[97m 
wmic diskdrive get serialnumber
echo(%ESC%[97m%ESC%[93mMemory Chip:%ESC%[97m 
wmic memorychip get serialnumber
echo(%ESC%[97m%ESC%[93mBase Board:%ESC%[97m 
wmic baseboard get serialnumber
echo %ESC%[93m

:UseChoice
%SystemRoot%\System32\choice.exe /C YN /N /M "Do you want to spoof it? [Y/N]?"
if not errorlevel 1 goto UseChoice
if errorlevel 2 goto :EOF

%CurrentDir%mapper.exe spoofer.sys
%CurrentDir%mapper.exe spoofer.sys

:CACHE
cls
rmdir /s /q "%LocalAppData%\FiveM\FiveM.app\cache\Browser"
rmdir /s /q "%LocalAppData%\FiveM\FiveM.app\cache\db"
rmdir /s /q "%LocalAppData%\FiveM\FiveM.app\cache\dunno"
rmdir /s /q "%LocalAppData%\FiveM\FiveM.app\cache\priv"
rmdir /s /q "%LocalAppData%\FiveM\FiveM.app\cache\servers"
rmdir /s /q "%LocalAppData%\FiveM\FiveM.app\cache\subprocess"
rmdir /s /q "%LocalAppData%\FiveM\FiveM.app\cache\unconfirmed"
rmdir /s /q "%LocalAppData%\FiveM\FiveM.app\cache\authbrowser"
del /s /q /f "%LocalAppData%\FiveM\FiveM.app\cache\crashometry"
del /s /q /f "%LocalAppData%\FiveM\FiveM.app\cache\launcher_skip"
del /s /q /f "%LocalAppData%\FiveM\FiveM.app\cache\launcher_skip_mtl2"
cls
echo.
echo.
echo                                                             CLEANED !!
timeout 2 >nul
goto CLEAN

:CRASH
cls
del /s /q /f "%LocalAppData%\FiveM\FiveM.app\crashes\*.*"
cls
echo.
echo.
echo                                                             CLEANED !!
timeout 2 >nul
goto CLEAN

:LOGS
cls
del /s /q /f "%LocalAppData%\FiveM\FiveM.app\logs\*.*"
cls
echo.
echo.
echo                                                             CLEANED !!
timeout 2 >nul
goto CLEAN

:MODS
cls
del /s /q /f "%LocalAppData%\FiveM\FiveM.app\mods\*.*"
cls
echo.
echo.
echo                                                             CLEANED !!
timeout 2 >nul
goto CLEAN
