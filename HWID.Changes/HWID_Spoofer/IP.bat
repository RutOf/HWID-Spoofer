@echo off

:start
cls
echo Choose:
echo [A] Set Static IP
echo [B] Set DHCP
echo.

set /p choice=[A,B]?

if /i "%choice%"=="A" (
    cls
    echo Please enter Static IP Address Information:
    echo.
    set /p IP_Addr=IP Address: 
    set /p D_Gate=Default Gateway: 
    set /p Sub_Mask=Subnet Mask: 
    echo.

    netsh interface ip set address LAN static %IP_Addr% %Sub_Mask% %D_Gate% 1
    echo.
    echo Static IP address has been set.
    pause
    goto end
)

if /i "%choice%"=="B" (
    cls
    echo Resetting IP Address and Subnet Mask for DHCP...
    echo.
    netsh interface ip set address name=LAN source=dhcp
    ipconfig /renew
    echo.
    echo DHCP has been set.
    pause
    goto end
)

echo Invalid choice. Please select either A or B.
pause
goto start

:end
cls
echo Current IP Configuration:
netsh int ip show config
pause
