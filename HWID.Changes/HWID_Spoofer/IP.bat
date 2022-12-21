@echo off

rem Set the title of the command prompt window
title IP Configuration Utility

rem Release the current IP address for the network adapter
echo Releasing IP address...
ipconfig /release
echo Done.

rem Flush the DNS cache
echo Flushing DNS cache...
ipconfig /flushdns
echo Done.

rem Renew the IP address for the network adapter
echo Renewing IP address...
ipconfig /renew
echo Done.

rem Flush the DNS cache again
echo Flushing DNS cache...
ipconfig /flushdns
echo Done.

rem Wait for 3 seconds to give the commands time to complete
ping localhost -n 3 >nul

echo All tasks completed successfully.
echo Press any key to exit.
pause >nul

rem Close the command prompt window
exit
