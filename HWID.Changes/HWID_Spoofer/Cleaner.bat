@echo off

if exist "C:\MasculineUnban\SDIO\" goto skipbackup
title MasculineUnban - Cleaner - First run of cleaner only - backing up drivers
cls
echo since this is your first run of MasculineUnban backing up drivers just in case
echo in order to backup drivers I will open snappy driver installer orgin
echo 1st when it opens click "download indexes only"
echo 2nd then wait for it to load and find your netowk card
echo 4th click your network canrd then click install
echo 5th once its done installing x out of snappy driver installer
start /wait SDIO_x64_R748.exe>nul 2>nul
:skipbackup

rem STI change
REG ADD "HKEY_LOCAL_MACHINE\SYSTEM\ControlSet001\Control\StillImage\Events\Connected" /v GUID /t REG_SZ /d {A28BBADE-%Hex1%-%Hex0%-%Hex1%-00%Hex10%} /f
REG ADD "HKEY_LOCAL_MACHINE\SYSTEM\ControlSet001\Control\StillImage\Events\Disconnected" /v GUID /t REG_SZ /d {143E4E83-%Hex1%-%Hex0%-%Hex1%-00%Hex10%} /f
REG ADD "HKEY_LOCAL_MACHINE\SYSTEM\ControlSet001\Control\StillImage\Events\EmailImage" /v GUID /t REG_SZ /d {C66DCEE1-%Hex1%-%Hex0%-%Hex1%-2F%Hex10%} /f
REG ADD "HKEY_LOCAL_MACHINE\SYSTEM\ControlSet001\Control\StillImage\Events\FaxImage" /v GUID /t REG_SZ /d {C00EB793-%Hex1%-%Hex0%-%Hex1%-00%Hex10%} /f
REG ADD "HKEY_LOCAL_MACHINE\SYSTEM\ControlSet001\Control\StillImage\Events\PrintImage" /v GUID /t REG_SZ /d {B441F425-%Hex1%-%Hex0%-%Hex1%-00%Hex10%} /f
REG ADD "HKEY_LOCAL_MACHINE\SYSTEM\ControlSet001\Control\StillImage\Events\ScanButton" /v GUID /t REG_SZ /d {A6C5A715-%Hex1%-%Hex0%-%Hex1%-00%Hex10%} /f
REG ADD "HKEY_LOCAL_MACHINE\SYSTEM\ControlSet001\Control\StillImage\Events\STIproxyEvent" /v GUID /t REG_SZ /d {d711f81f-%Hex1%-%Hex0%-%Hex1%-92%Hex10%} /f


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
ping localhost -n 3 >nul'
restart 0
exit
