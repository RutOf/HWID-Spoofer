@echo off
title Cleaner
ping localhost -n 3 >nul
echo Killing any related processes...
@taskkill /f /im "EpicGamesLauncher.exe" /t /fi "status eq running">nul
@taskkill /f /im "FortniteLauncher.exe" /t /fi "status eq running">nul
@taskkill /f /im "FortniteClient-Win64-Shipping_BE.exe" /t /fi "status eq running">nul
@taskkill /f /im "FortniteClient-Win64-Shipping.exe" /t /fi "status eq running">nul
@taskkill /f /im "EasyAntiCheat.exe" /t /fi "status eq running">nul
@taskkill /f /im "explorer.exe" /t /fi "status eq running">nul
@timeout /t 2 >nul 2>&1 /nobreak
cls
cls
Echo Cleaning!


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
