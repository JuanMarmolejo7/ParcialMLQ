@echo off
setlocal enabledelayedexpansion

set EXE=cmake-build-debug\Parcial_Japet.exe

if not exist output\profesor mkdir output\profesor

for %%f in (input\profesor\*.txt) do (
    set "nombre=%%~nf"
    echo Corriendo %%~nxf ...
    "%EXE%" "input\profesor\%%~nxf" "output\profesor\!nombre!_out.txt"
)

echo.
echo Listo! Revisa la carpeta output\profesor
pause